# HTTP

## HTTP basics

### Basic facts about HTTP in Web traffic

Facts:
* The Web content lives on web servers;
* The Web servers speak the HTTP protocol;
* Clients send HTTP requests;
* Servers return the requested data with HTTP responses.

Most common usage of HTTP client - browser:
* Browse a page such as `http://example.com/index.html`;
* Browser sends a HTTP request to server `www.example.com`;
* Server tries to find the resource `/index.html`;
* If successful, server sends the resource in HTTP response with additional data about it.

### Resources

There are static resources on the Web:
* images;
* documents;
* text files etc.

However, resources can be dynamically generated on demand by Web applications:
* live image from camera;
* searching real estate databases;
* buying gifts.

In general, a resource is any kind of a content source:
* spreadsheet with your company's sales forecast;
* web gateway to scan your local library shelves;
* Internet search engine.

### Media types

To know how to handle each object, it is tagged with a data format label called `MIME type` (Multipurpose Internet Mail Extensions).
The tag consists of two pieces - the main type and the specific subtype delimited with a slash.

Examples:
* An HTML-formatted text document - `text/html`;
* A plain ASCII text document - `text/plain`;
* A JPEG version of an image - `image/jpeg`;
* A MS PowerPoint presentation - `application/vnd.ms-powerpoint`.

### URIs, URLs and URNs

URIs (unified resource identifiers) uniquely identify and locate information resources around the world.
For example `http://www.example.com/index.html` specifies the HTTP protocol to access the `index.html` document on `example.com` server.

**URIs come in two flawours called URLs and URNs.**

URLs (unified resource locators):
* specifies the location of a specific resource on a particular server;
* most common form of resource identifiers;
* example: `https://www.wolnelektury.pl/media/book/pdf/lalka.pdf` - means *1. Use HTTP protocol; 2. Go to server `wolnelektury.pl`; 3. Grab resource `/media/book/pdf/lalka.pdf`;
* example: `jdbc:mysql://127.0.0.1/hr` - means *1. Use JDBC MySQL protocol; 2. Go to server 127.0.0.1; 3. Grab database hr*;

URNs (unified resource name):
* specifies unique name of a resource independent of where the resource resides;
* this elasticity allows for the resource to be moved from place to place;
* still experimental; requires special support infrastructure to resolve resource locations;
* example: `urn:isbn:978-83-7779-206-3` - means *1. Use ISBN as an namespace identifier; 2. Go to book 978-83-7779-206-3 (Lalka, B. Prus)*;

### Transactions

The transaction in the context of HTTP consists of two things:
* request sent from client to server;
* response result (sent from the server back to the client).

#### Web pages can consist of multiple objects

Most commonly, the web browser requested to display a page must issue multiple HTTP transactions in order to accomplish the task.
In case of graphics-rich web page, a cascade of HTTP transactions is done in order to fetch all the resources.
It may be useful to investigate the transactions done when loading a webpage in browser's developer tools utility.

#### Methods

There are many HTTP methods.
Some of them are listed below:
* `GET` - send named resource from server to client;
* `PUT` - store data from client into a provided named server resource;
* `DELETE` - delete the named resource from the server;
* `POST` - send client data into a server gateway application;
* `HEAD` - send the HTTP headers from the response for the named resource.

#### Status codes

The main groups of HTTP status codes are:
* `1xx` - information responses;
* `2xx` - successful responses;
* `3xx` - redirection messages;
* `4xx` - client error responses;
* `5xx` - server error responses.

Example status codes:
* `200 OK` - the request has succeeded;
* `201 Created` - the request has succeeded and new resource has been created as a result of it (usually `POST` and `PUT` requests);
* `301 Moved Permanently` - the URI of the requested resource has been changed permanently; probably the new URI would be given in the response;
* `400 Bad Request` - the server could not understand the request due to invalid syntax;
* `401 Unauthorized` - the server could not provide the resource because the user is unauthenticated; the user should authenticate first;
* `403 Forbidden` - the client's identity is known to the server and it does not have the rights to the content;
* `404 Not Found` - the server cannot find the requested resource; in the browser this means the URL is not recognized;
in the API this could mean that the endpoint is valid but the resource itself does not exist;
* `418 I'm a teapot` - the server refused to brew coffee with a teapot;
* `500 Internal Server Error` - the server encountered a situation it does not know how to handle;
* `503 Service Unavailable` - the server is not ready to handle the request;
the code should be used for temporary conditions where the server is down or overcrowded;

Some additional facts:
* `200 OK` means different things depending on the HTTP method; for `GET` it means that the requested resource is in the response body;
for `POST` and `PUT` it means that the result of the requested action is sent in the message body;
* `401 Unauthorized` is in fact an semantical error - it is all about the difference between `authentication` and `authorization`;
* `418 I'm a teapot` is a reference to Hyper Text Coffee Pot Control Protocol, part of the 1998 April Fools` joke;
* The textual phrase after the code (eg. `Forbidden`) is supposed to provide a description and is arbitrary - the numeric code is used for all processing.

#### Messages

The main features of HTTP messages are the following:
* They are line-oriented sequences of characters;
* The request and response messages are very similar;

Mesages consist of three parts:
1. *Start line* - the first line of the message.
2. *Header fields* - zero or more headers following the start line.
Each header field consists of the header name, colon (:) and value. This part ends with a blank line.
3. *Body* - this part comes after the blank line. The message is of course optional and may contain any type of data.

Example HTTP request:
```
GET /test/hi-there.txt HTTP/1.0
Accept: text/*
Accept-Language: en,fr

```

Example HTTP response:
```
HTTP/1.0 200 OK
Content-type: text/plain
Content-length: 19

Hi! I’m a message!
```

### Connections

#### TCP/IP

HTTP is an application layer protocol.
The details of networking are left to TCP/IP.
The protocol provides:
* 


