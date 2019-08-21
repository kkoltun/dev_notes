# Keycloak

## Introduction

* Doing security yourself is probably the worst idea.
* Adding security and user handling to application pollutes the code.
* Keycloak is all about delegating security, users etc. to external service (server).

**Keycloak protects realms (territories)**

Logging in:
1. Go to page.
2. Get redirected to the login page.
3. If everything is all right, you get JSON Web Token which includes payload.

## Deployment

* From sources;
* Standalone;
* Wildfly/EAP subsystem;
* Docker images.
