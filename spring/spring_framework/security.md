## Spring Security notes

[Marco Behler article on Spring Securiry - check it.](https://www.marcobehler.com/guides/spring-security)

### Facts

Entire Spring Security is based on the Servlet filters correctly filtering the HTTP requests.

Authentication:
* Based on the `UserDetails`, `Authentication`, `PasswordEncoder` classes/interfaces.
* This can be done in multiple ways:
  * If you are holding the usernames and passwords:
    * Provide the `UserDetailsService` implementation, Spring will use the service to get the `UserDetails` object and authenticate.
    * Provide the `PasswordEncoder` implementation, Spring will use it to encode passwords. When multiple algorithms are used, use the `DelegatingPasswordEncoder`.
  * If you are using some external service for authentication:
    * Provide the `AuthenticationProvider` implementation, Spring will use it to get the `Authentication` object which means that the user is actually authenticated.
  * If you are using OAUTH: #TODO.

Authorization:
* Based on Authorities and Roles. Authority is (in it's simplest form) just a string. Role is an authority with `ROLE_` prefix. So a role called `ADMIN` is the same as the authority called `ROLE_ADMIN`. There is no good reason behind having this distinction.
* There are different classes representing the authorities, the simplest one is the `SimpleGrantedAuthority`.
* If you are using `UserDetailsService`, provide the roles in the `UserDetails` object.
### Basic terms

#### Authentication

The application needs to know if the user is who they claim to be, usually with the username and password.

#### Authorization

The application needs to know if the user is actually allowed to access the resource. It needs to check the permissions of the authenticated user.

#### Servlet filters

In the basic Spring Web application with `@Controller` classes, we have the single servlet - the DispatcherServlet.
It does not have any code handling security. Nor should the Controller, the security should be a step before.

You can set up a Servlet Filter that filters every incoming HTTP request before it hits the servlet.

In reality, you would have a multiple filters forming a chain.

#### Spring DefaultSecurityFilterChain

The chain consists of multiple filters in a strict order (copied from the Spring Security docs):

1. `ChannelProcessingFilter`, because it might need to redirect to a different protocol. 
2. `SecurityContextPersistenceFilter`, so a `SecurityContext` can be set up in the `SecurityContextHolder` at the beginning of a web request, and any changes to the `SecurityContext` can be copied to the `HttpSession` when the web request ends (ready for use with the next web request). 
3. `ConcurrentSessionFilter`, because it uses the `SecurityContextHolder` functionality but needs to update the `SessionRegistry` to reflect ongoing requests from the principal.
4. `Authentication` processing mechanisms - `UsernamePasswordAuthenticationFilter`, `CasAuthenticationFilter`, `BasicAuthenticationFilter` etc - so that the `SecurityContextHolder` can be modified to contain a valid `Authentication` request token. 
5. The `SecurityContextHolderAwareRequestFilter`, if you are using it to install a Spring Security aware `HttpServletRequestWrapper` into your servlet container. 
6. `RememberMeAuthenticationFilter`, so that if no earlier authentication processing mechanism updated the `SecurityContextHolder`, and the request presents a cookie that enables remember-me services to take place, a suitable remembered `Authentication` object will be put there. 
7. `AnonymousAuthenticationFilter`, so that if no earlier authentication processing mechanism updated the `SecurityContextHolder`, an anonymous `Authentication` object will be put there.
8. `ExceptionTranslationFilter`, to catch any Spring Security exceptions so that either an HTTP error response can be returned or an appropriate `AuthenticationEntryPoint` can be launched. 
9. `FilterSecurityInterceptor`, to protect web URIs and raise exceptions when access is denied.

#### Configuring

Create a class:
* annotated with `@EnableWebSecurity`;
* extending the `WebSecurityConfigurer`.

Check [those docs](https://spring.io/blog/2019/11/21/spring-security-lambda-dsl) on the configure DSL provided by the `WebSecurityConfigurer` class.

### Authentication methods

This can be done in three ways:
1. You have the access to the hashed password. For example you hold the username and password in the database.
2. You don't have the access to the hashed password, because you use some external identity management system. For example Atlassian Crowd REST service.
3. You use OAUTH2 or "Login with Google/Twitter/etc." functionalities, likely in combination with JWT.

#### Authenticating