# Spring Framework - WebMVC

## Books

[Expert One-on-One J2EE Design and Development](https://www.amazon.com/exec/obidos/tg/detail/-/0764543857/)
[Expert Spring MVC and Web Flow](http://index-of.es/Java/Apress.Expert.Spring.MVC.and.Web.Flow.Feb.2006.pdf)

## Contents

* [Servlet configuration and contexts](./webmvc/configuration.md)

## Controller Return Values

With `@ResponseBody`:
* the return value is converted through `HttpMessageConverter` and written to response;
* for debugging - check `RequestResponseBodyMethodProcessor#handleReturnValue`.

With any object not listed in special objects [here](https://docs.spring.io/spring/docs/current/spring-framework-reference/web.html#mvc-ann-return-types):
* simple types remain unresolved, basing on `BeanUtils#isSimpleProperty`;
* objects are translated to view name with `RequestToViewNameTranslator` and then view name is rendered in `DispatcherServlet#render`.
