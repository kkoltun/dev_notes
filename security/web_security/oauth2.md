# OAUTH 2

## Entities

* `Protected resource` = the thing that is protected.
* `Resource owner` = you, the user, who hold the rights to that `resource`.
* `Client` = a 3rd party application that wants to access the `protected resource`.
* `Scope` = the 3rd party access can be limited to a subset of data/actions.
* `Authorization server` = the entity that checks credentials and hands out the access tokens.
* `Resource server` = API that hosts the protected resource and validates the token.

## OAUTH2 dance

*Rewritten to pretty-print from https://www.marcobehler.com/images/guides/oauth2/oauth2_flow_v2-8c394ca4.png.*

```
 Resource Owner                  Client               Authorization Server           Resource Server
        |                           |                           |                           |
==== 1. Getting an authorization code ==============================================================
        |                           |                           |                           |
        | add new Google mailbox    |                           |                           |
        |-------------------------->|                           |                           |
        |                           |                           |                           |
        | redirect to auth endpoint |                           |                           | There the client can specify the flow and the scopes - they are set in the URL.
        |<- - - - - - - - - - - - - |                           |                           | https://accounts.google.com/o/oauth2/v2/auth
        |                           |                           |                           |     ?client_id=woodpecker-123
        |                           |                           |                           |     &redirect_uri=https://app.woodpecker.co/callback
        |                           |                           |                           |     &response_type=code
        |                           |                           |                           |     &scope=email https://www.googleapis.com/auth/gmail.readonly
        |                           |                           |                           |     &state=xyz
        |                           |                           |                           |     &code_challenge=...
        |                           |                           |                           |
        |          navigate to Google authorization endpoint    |                           |
        |------------------------------------------------------>|                           | Opens a pop-up or does a full page redirect.
        |                           |                           |                           |
        |                ask for authentication                 |                           |
        |<- - - - - - - - - - - - - - - - - - - - - - - - - - - |                           |
        |                           |                           |                           |
        |          authenticate with owner credentials          |                           | Here you can choose the account you are already logged in or log into a new one.
        |------------------------------------------------------>|                           |
        |                           |                           |                           |
        |                ask to authorize client                |                           |
        |<- - - - - - - - - - - - - - - - - - - - - - - - - - - |                           | Here Google asks whether you allow Woodpecker to read/write your emails.
        |                           |                           |                           | The things shown here are based on the scopes the client requested.
        |                grant access to client                 |                           |
        |------------------------------------------------------>|                           |
        |                           |                           |                           |
        |       redirect to client w/ authorization code        |                           |
        |<- - - - - - - - - - - - - - - - - - - - - - - - - - - |                           | This redirects back to a callback endpoint in Woodpecker.
        |                           |                           |                           |
==== 2. Getting an access token ====================================================================
        |                           |                           |                           |
        |  back to client w/ code   |                           |                           |
        |-------------------------->|                           |                           |
        |                           |                           |                           |
        |                           | auth code + client_id +   |                           |
        |                           |     + client_secret       |                           | Client credentials are the ones obtained when Woodpecker registered in Google as an app that will want to access user mailboxes. 
        |                           |-------------------------->|                           | While registering you also set a callback URL there.
        |                           |                           |                           |
        |                           |                           | only if code + creds +    | The code-for-token exchange is server-to-server, the token never passes through the browser.
        |                           |                           |     + redirect_uri valid  | 
        |                           |                           |                           | 
        |                           |    valid access token     |                           |
        |                           |<- - - - - - - - - - - - - |                           |
        |                           |                           |                           |
==== 3. Calling the protected resource =============================================================
        |                           |                           |                           |
        |                           |               GET /inbox + token                      | Get the inbox state 
        |                           |------------------------------------------------------>|
        |                           |                           |                           |
        |                           |                    {inbox payload}                    |
        |                           |<- - - - - - - - - - - - - - - - - - - - - - - - - - - |
        |                           |                           |                           |
        |       messages in inbox   |                           |                           |
        |<- - - - - - - - - - - - - |                           |                           |
        |                           |                           |                           |
```

## Auth request

The client specifies what it needs and how it wants this to work in the auth redirect.

Example URL:

```
https://accounts.google.com/o/oauth2/v2/auth
    ?client_id=woodpecker-123
    &redirect_uri=https://app.woodpecker.co/callback
    &response_type=code
    &scope=email https://www.googleapis.com/auth/gmail.readonly
    &state=xyz
    &code_challenge=...
```

* `client_id` - the ID of the client received why registering it in Google.
* `redirect_uri` - where to send the authorization code, must be same as the URI registered in Google.
* `response_type` - `code` for authorization code flow.
* `scope` - list of different requested scopes, cannot be broader than the scopes set when registering the client.
* `state` - a random value the client sends, gets back and compares - a CSRF protection.
* `code_challenge` - PKCE, see below.

When `state` value is important:

1. The attacker starts the mailbox attachment on their account in Woodpecker, logs into their Google account and
   consents.
2. Google redirects to https://app.woodpecker.co/callback?code=ATTACKERS_CODE. The attacker copies the URL before it
   loads.
3. The attacker gets the user to open the URL - could be through a link, hidden image, page that redirects
   automatically. The user is logged into Woodpecker.
4. The victim's browser calls Woodpecker callback with the victim's session cookie and the attackers `ATTACKERS_CODE`.
5. Woodpecker exchanges the code, which is perfectly valid and attaches attacker's mailbox to the victim's account.

This is CSRF because the victim's browser makes a request the victim never intended.

Why `state` fixes that:

1. When attacker starts the flow, Woodpecker generates a random `state = xyz`, stores it in that user's session and puts
   into
   the redirect URL.
2. Google returns untouched `/callback?code=...&state=xyz`.
3. On the callback, Woodpecker compares the `state` in the URL with the one stored in the session of the browser making
   the request. Naturally, the victim did not initiate the flow with that state value or did not initiate the flow at
   all, so the request is rejected.

## PKCE (Proof Key for Code Exchange) - where it is mandatory

A solution that helps when you don't have a place to store the client credentials.

Examples:

* Mobile app that can be extracted and every string printed.
* SPA running in the browser - anyone can read the JS bundle in Devtools.

PKCE:

* Before redirect to the authorization server endpoint, the SPA/Native App creates a long random string named
  `code_verifier`. Then it generates a `code_challenge` from it. The `code_challenge` could be
  `plain_text(code_verifier)` or `sha_256(code_verifier)`.
* These values: `code_challenge` and `code_challenge_method` (hashing algorithm) get sent as a URL param to the
  redirect. The server stores them.
* When exchanging authorization code for an access token, the app sends the original `code_verifier` to the server. The
  server hashes it and compares with the stored `code_challenge`.

So when the original flow contains `client_credentials = client_id + client_secret`, in the PKCE flow the
`client_secret` is replaced with `code_verifier/code_challenge`.

Naturally:

* `client_credentials` PROVE that the Woodpecker itself is exchanging the code.
* `code_verifier/code_challenge` PROVE only that the client requesting the access_token is the same client that started
  the entire flow.

PKCE doesn't authenticate the client, but it still matters when:

* Mobile URL scheme hijacking:
    * You develop a Woodpecker mobile app. It declares that it handles links starting with `woodpecker://`. You register
      the `woodpecker://callback` URL in Google.
    * Someone delivers a malicious app that ALSO declares the `woodpecker://callback`.
    * User accesses your app, starts adding a mailbox and the system browser goes to Google's login page. The user logs
      in and consents.
    * Google redirects to `woodpecker://callback?code=abc123` and the browser asks the OS to open that link, OS finds
      two apps.
        * Android - user chooses the app.
        * IOS - undefined, it chooses one of the apps.
    * If malicious app is chosen, then the code goes to it, but it still does not have access to the Woodpecker app
      memory, so it does not have the `code_verifier`. Google rejects that exchange.
* URL leakage - logs, `Referer`, open redirects etc.

This still **does not** fix the case with the entire flow launched by a fake app - if the fake app launches entire flow,
it will get the access token provided that you are using URL schemes. Then, you need to:

* Redirect to your domain `https://woodpecker.co` instead of `woodpecker://callback`.
* Host a file on woodpecker.co that names the exact app that is allowed to handle the redirects (`assetlinks.json` for
  Android, `apple-app-site-association` for Apple).
* The OS will first fetch the file and check that it matches the app.

## PKCE (Proof Key for Code Exchange) where it is recommended

PKCE is recommended in the backend, where the `client_secret` is assumed to be private. Why?

The attack:

1. The attacker gets the victim's fresh authorization code (leaked URL, an open redirect, a compromised proxy).
2. The attacker cannot use the code themselves, because they do not know the client_secret.
3. The attacker launches their own mailbox attachment process in their Woodpecker account.
4. Instead of completing the Google step, they open the callback by hand with the victim's code.
5. Woodpecker backend sends the code with its valid `client_secret` to Google. Everything looks OK and Google returns a
   token for the victim's mailbox.
6. The attacker gets the victim's mailbox attached.

How PKCE fixes this:

1. The backend generates separate `code_verifier` values for the victim and attacker flows. It stores them attached to
   the user sessions and they are not exposed.
2. When the attacker opens the callback with the victims code, backend sends their, not victims `code_verifier`.
3. The `code_verifier` does not match the `code`, so Google rejects such request.

So, seeing the `state` paragraph above:

| Attack               | Whose code | Whose session | Result                             | `state` stops it? | PKCE stops it? |
|----------------------|------------|---------------|------------------------------------|-------------------|----------------|
| CSRF on the callback | Attacker's | Victim's      | Victim gets the attacker's mailbox | Yes (1)           | Yes (2)        |
| Code injection       | Victim's   | Attacker's    | Attacker gets the victim's mailbox | No (3)            | Yes (2)        |

1. Woodpecker will reject the callback immediately, because the `state` does not match the session.
2. Google will reject the request.
3. The attacker uses victim's code, but the entire flow is done on the attacker's side, so the `state` is always right.

## How are access tokens verified?

### Shared Database

In general, the `resource server` and `authorization server` can be different, separate entities. However, they could
also be the same system with two different endpoints.

The `authorization server` stores a hash of every token it issues in a database. The `resource server` hashes the
incoming token and looks it up in the same database.

### Token Introspection

The authorization server supplies an HTTP endpoint, which you can call with a token and get the token information back.

### JWT

OAUTH2 tokens are mostly opaque. **JWT can be used with OAUTH2**:

* The tokens will be longer.
* **This removes the necessity to use a storing service to verify stuff**;

The `access_token` is the JWT then and this removes the necessity to call the authorization server.

The `refresh_token` might or might not be a JWT:

* When it is opaque, you can make stateless, short-lived `access_tokens` and still have the opportunity to revoke a
  long-living refresh token.
* When it is JWT, then you definitely need a blacklist to be able to revoke access for a client.

Still, even with opaque `refresh_tokens`, you might need a blacklist to be able to immediately log out apps, without
waiting for the access token to expire.

Worth noting:

* Statelessness of `refresh_tokens` buys virtually nothing, because the refresh tokens goes only to the authorization
  server, only every few minutes.
* If you rotate the refresh token when new access token is got (endpoint returns new access token AND new refresh token)
  then you need state anyway. JWT has `exp` field, but this is point in time, you cannot set it AFTER the
  `refresh token` has been used. The server must know that a token was already used.

See [JWT notes](jwt.md).

## OpenID Connect

**OAUTH2 is all about authorization - it lets the user delegate access, so the client may act on a resource.**

**OIDC is authentication - it tells the client who the user is.**

The OAUTH2 dance includes the "authenticate with owner credentials" where the user logs into the Google account, but it
does not give the client any standard way to learn the result. The way of logging in is out of scope, could be a
password, passkey, 2FA, session cookie...

OIDC does not specify the way to log in either, but it specifies the ID token - the way the client learns who the user
is.

Changes in the OpenID Connect w.r.t. OAUTH2:

* The `protected resource` is now the users profile.
* The `resource server` and the authorization server are now really one conceptual entity called the
  `Identity Provider`.
* The `client` (Woodpecker) can call an endpoint `/userinfo` at the `Identity Provider`.
* The `Identity Provider` acts as a `Resource Server` and `Authorization Server`.

Taken from https://www.marcobehler.com/images/guides/oauth2/oauth2_openid-0bf9c048.png.

```
          User                        Relying Party (client)        Identity Provider
 (karolkoltundev@gmail.com)
            |                               |                               |
==== 1. Getting an authorization code ==========================================================
            |                               |                               |
            |   login via openid-connect    |                               |
            |------------------------------>|                               |
            |                               |                               |
            |  redirect to login endpoint   |                               |
            |<- - - - - - - - - - - - - - - |                               | The client includes `openid` in the requested scopes. The scope parameter is part of the redirect URL.
            |                               |                               | Without it, no `id_token` comes back.
            |                  navigate to login endpoint                   |
            |-------------------------------------------------------------->|
            |                               |                               |
            |                    ask for authentication                     |
            |<- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |
            |                               |                               |
            |              authenticate with owner credentials              |
            |-------------------------------------------------------------->|
            |                               |                               |
            |                    ask to authorize client                    |
            |<- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |
            |                               |                               |
            |                    grant access to client                     |
            |-------------------------------------------------------------->|
            |                               |                               |
            |           redirect to client w/ authorization code            |
            |<- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - |
            |                               |                               |
==== 2. Getting an access token and id token ===================================================
            |                               |                               |
            |  back to client w/ auth code  |                               |
            |------------------------------>|                               |
            |                               |                               |
            |                               |   auth code + client creds    |
            |                               |------------------------------>|
            |                               |                               |
            |                               |    access token + id token    |
            |                               |<- - - - - - - - - - - - - - - | The ID token is an additional token w.r.t. original OAUTH2 dance.
            |                               |                               | It contains authentication event in JWT format including some user profile information.
==== 3. Getting the user profile ===============================================================
            |                               |                               |
            |                               |   user info w/ access token   |
            |                               |------------------------------>|
            |                               |                               |
            |                               |      {user info payload}      |
            |                               |<- - - - - - - - - - - - - - - |
            |                               |                               |
            |           user info           |                               |
            |<- - - - - - - - - - - - - - - |                               |
            |                               |                               |
```