# CSRF - Cross Site Request Forgery

## Mechanism

* A page on another site makes the victim's browser send a state-changing request to a site where the victim is
  logged in.
* The browser attaches that site's cookies by itself, so the request runs with the victim's rights.
* The attacker never sees the cookie or the response; they only trigger an action.
* The request has to come from the victim's browser. A request from the attacker's server would carry no cookies of
  the victim's.

Two conditions:

1. The victim opens a page with the attacker's code. It does not have to be the attacker's own site: an `<img>` in a
   forum post, an ad, or an HTML email that loads images.
2. The victim is logged in to the target site at that moment. This is the normal state: long sessions, "remember me",
   the bank open in another tab.

## Example

1. The bank withdraws money with `GET bank.example.com/withdraw?amount=10000&to=mallory`.
2. The attacker posts in a forum: `<img src="https://bank.example.com/withdraw?amount=10000&to=mallory">`.
3. A forum visitor who is logged in to the bank opens the post.
4. Their browser loads the "image": it sends the request with the bank's cookies.
5. The bank sees a normal request from its logged-in user and transfers the money.

With POST the same works through a hidden form that the attacker's script submits as soon as the page loads.

## Defences

### CSRF token (the main one)

The server puts a random secret tied to the session into each form:

```html
<form method="POST" action="/withdraw">
  <input type="hidden" name="_csrf" value="8f3a…c91">
</form>
```

The server accepts the request only if the token matches the value stored for the session. The attacker's page can
make the browser send the request, but it cannot read the bank's pages (the same-origin policy forbids it), so it does
not know the token. Spring Security turns this on by default for POST, PUT and DELETE.

### `SameSite` cookies

They tell the browser not to attach the cookie to requests that come from another site:

* `Strict`: never sent cross-site, not even when following a link (you arrive logged out).
* `Lax` (the browser default today): sent when following a link (top-level GET), not with a cross-site POST, `<img>`
  or `fetch`.

Without the cookie, the forged request arrives as anonymous.

### Other habits

* No state changes with GET: `Lax` still sends cookies on top-level GET, and `<img>` works only with GET.
* Check the `Origin` header on state-changing requests: the browser sets it and a page cannot fake it.
* Confirm sensitive actions with a password or 2FA.

Not a defence: filtering user input. The forged request comes from another site.

## CSRF and XSS

* XSS defeats CSRF protection: the injected script runs on the site itself, so it can read the token.
* Both rely on the cookie domain rule: `b.com` can never read `a.com`'s cookies. With XSS the attacker's code runs
  inside `a.com`. With CSRF the attacker uses the browser attaching `a.com`'s cookies on its own.

## CSRF and JWT

* A JWT kept in browser storage and sent in an `Authorization` header is not vulnerable to CSRF: the browser never
  attaches it on its own. That is why such APIs often turn CSRF protection off.
* A JWT kept in a cookie is vulnerable again.
