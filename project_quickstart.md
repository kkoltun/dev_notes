## Project quickstart notes

### 1. Maven compiler plugin working with Java 11 and newer

```xml
<plugin>
    <groupId>org.apache.maven.plugins</groupId>
    <artifactId>maven-compiler-plugin</artifactId>
    <version>3.8.1</version>
</plugin>
```

### Packing the dependencies in the jar file

Remember to replace the main class name.
```xml
<plugin>
    <groupId>org.apache.maven.plugins</groupId>
    <artifactId>maven-shade-plugin</artifactId>
    <version>3.2.4</version>
    <executions>
        <execution>
            <phase>package</phase>
            <goals>
                <goal>shade</goal>
            </goals>
            <configuration>
                <transformers>
                    <transformer implementation="org.apache.maven.plugins.shade.resource.ManifestResourceTransformer">
                        <mainClass>dev.karolkoltun.QuickStart</mainClass>
                    </transformer>
                </transformers>
            </configuration>
        </execution>
    </executions>
</plugin>

```

### Embedded Tomcat with servlet

Dependency:

```xml
<dependency>
  <groupId>org.apache.tomcat.embed</groupId>
  <artifactId>tomcat-embed-core</artifactId>
  <version>9.0.58</version>
</dependency>
```

Launching:
```java
public class QuickStart {
	public static void main(String[] args) {
			Tomcat tomcat = new Tomcat();
			tomcat.setPort(8080);
			// This is critical.
			tomcat.getConnector();

			Servlet servlet = new MyServlet();

			// No need for contexts; no static pages served.
			Context ctx = tomcat.addContext("", null);
			Wrapper servlet = Tomcat.addServlet(ctx, "servlet", servlet);
			// Don't wait for the first request.
			servlet.setLoadOnStartup(1);
			servlet.addMapping("/");

			tomcat.start();
    }
}
```

### Jackson

Dependency:

```xml
<dependency>
  <groupId>com.fasterxml.jackson.core</groupId>
  <artifactId>jackson-databind</artifactId>
  <version>2.13.3</version>
</dependency>
```

See Jackson training presentation for more recipes.

### Spring IOC container

Dependency:

```xml
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-context</artifactId>
    <version>5.3.10</version>
</dependency>
```

ApplicationContext stores the beans and needs one or more `@Configuration` classes.

Getting things from the ApplicationContext:
```java
AnnotationConfigApplicationContext ctx = new AnnotationConfigApplicationContext(ConfigurationClass.class);
this.userService = ctx.getBean(UserService.class);
```

### Using PostConstruct and PreDestroy

Dependency with annotations:

```xml
<dependency>
    <groupId>javax.annotation</groupId>
    <artifactId>javax.annotation-api</artifactId>
    <version>1.3.2</version>
</dependency>
```

Registering a shutdown hook in the JVM via the application context:
```java
context.registerShutdownHook();
```

### Using properties in pure Spring IOC container

Use the `@PropertySource()` annotation. Then, to access the values use `@Value("${cdn.url}")`.

Profile-specific property files:
```java
@PropertySource(value = "classpath:/application-${spring.profiles.active}.properties", ignoreResourceNotFound = true)
```

### Adding Spring MVC

Dependency:

```xml
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-webmvc</artifactId>
    <version>5.3.10</version>
</dependency>
```

Central point of handling requests is the **DispatcherServlet**.

Creating and registering the DispatcherServlet in the embedded Tomcat context:

```java
public class ApplicationLauncher {

	public static void main(String[] args) throws LifecycleException {
		Tomcat tomcat = new Tomcat();
		tomcat.setPort(8080);
		tomcat.getConnector();

		Context tomcatContext = tomcat.addContext("", null);

		// Create the application context.
		WebApplicationContext applicationContext = createWebApplicationContext(tomcatContext.getServletContext());
		// Create the DispatcherServlet, this is the one and only entry point for Spring WebMVC.
		// It needs the application context to for example know the controllers.
		DispatcherServlet dispatcherServlet = new DispatcherServlet(applicationContext);

		// Register the servlet in the Tomcat.
		Wrapper servlet = Tomcat.addServlet(tomcatContext, "dispatcherServlet", dispatcherServlet);
		servlet.setLoadOnStartup(1);
		servlet.addMapping("/");

		tomcat.start();
	}

	public static WebApplicationContext createWebApplicationContext(ServletContext servletContext) {
		// Create the web application context, it is annotation-driven.
		AnnotationConfigWebApplicationContext context = new AnnotationConfigWebApplicationContext();
		// The context knows about the configuration class.
		// The configuration class has @ComponentScan.
		// This way the context knows about the @Controller, @Component classes and other bean classes.
		context.register(ConfigurationClass.class);
		context.setServletContext(servletContext);
		context.refresh();
		context.registerShutdownHook();
		return context;
	}
}
```

### Using default Spring Web MVC configuration

Use the `@EnableWebMvc` in the configuration class. This automatically registers a JSON converter with Spring MVC as long as jackson is on the classpath.

### Writing straight to the response

Use `@Controller` with `@ResponseBody` on top of the class or method or just use `@RestController`.

### Using parameters

@RequestParam
```java
// http://localhost:8080/invoices?user_id=Karol&amount=100
@PostMapping("/invoices")
public Invoice addInvoice(@RequestParam("user_id") String userId, @RequestParam int amount) {
	return invoiceService.create(userId, amount);
}
```

@PathVariable
```java
// http://localhost:8080/invoices/Karol/100
@PostMapping("/invoices/{userId}/{amount}")
public Invoice addInvoice(@PathVariable String userId, @PathVariable int amount) {
	return invoiceService.create(userId, amount);
}
```

@RequestBody
```java
// http://localhost:8080/invoices and the invoice is in the request
@PostMapping("/invoices")
public Invoice addInvoice(@RequestBody InvoiceDto invoiceDto) {
    return invoiceService.create(invoiceDto.getUserId(), invoiceDto.getAmount());
}
```

### Adding validation to vanilla Spring MVC

Java Bean Validation (JSR 303) is the specification, the Hibernate-validator is reference implementation:

Dependencies:
```xml
<dependency>
    <groupId>org.hibernate.validator</groupId>
    <artifactId>hibernate-validator</artifactId>
    <version>6.2.0.Final</version>
</dependency>
<!-- This is needed to trigger Spring's autoconfiguration of its validation capabilities. -->
<dependency>
    <groupId>org.glassfish</groupId>
    <artifactId>javax.el</artifactId>
    <version>3.0.1-b12</version>
</dependency>
```

### Adding exception handling to vanilla Spring MVC

Use `@ControllerAdvice` or `@RestControllerAdvice` annotated class.

```java
@RestControllerAdvice
public class GlobalControllerExceptionHandler {
	@ResponseStatus(HttpStatus.BAD_REQUEST)
	@ExceptionHandler(MethodArgumentNotValidException.class)
	public String handleMethodArgumentNotValidException(MethodArgumentNotValidException exception) {
		return "Error: " + exception.getMessage();
	}

	@ResponseStatus(HttpStatus.BAD_REQUEST)
	@ExceptionHandler(Exception.class)
	public String handleUnknownException(Exception exception) {
		return "Unknown error " + exception.getMessage();
	}
}
```

### Adding embedded H2

H2 dependency:

```xml
<dependency>
	<groupId>com.h2database</groupId>
	<artifactId>h2</artifactId>
	<version>1.4.200</version>
</dependency>
```

Example initialization script `schema.sql`:

```sql
create table if not exists invoices
(
	id      uuid  default random_uuid() primary key,
	pdf_url varchar(255),
	user_id varchar(255),
	amount  int
);
```

Creating a H2 datasource that uses the `schema.sql` initialization file:

```java
@Configuration
class ConfigurationClass {
	@Bean
	public DataSource dataSource() {
		JdbcDataSource ds = new JdbcDataSource();
		ds.setURL("jdbc:h2:~/myFirstH2Database;INIT=RUNSCRIPT FROM 'classpath:schema.sql'");
		ds.setUser("sa");
		ds.setPassword("sa");
		return ds;
	}
}
```

### Adding Spring JDBC and JDBC Template

Dependency:

```xml
<dependency>
    <groupId>org.springframework</groupId>
    <artifactId>spring-jdbc</artifactId>
    <version>5.3.10</version>
</dependency>
```

Bean to add in the configuration class:

```java
@Configuration
class ConfigurationClass {
	@Bean
	public DataSource dataSource() {
		JdbcDataSource ds = new JdbcDataSource();
		ds.setURL("jdbc:h2:~/myFirstH2Database;INIT=RUNSCRIPT FROM 'classpath:schema.sql'");
		ds.setUser("sa");
		ds.setPassword("sa");
		return ds;
	}

	@Bean
	public JdbcTemplate jdbcTemplate() {
		return new JdbcTemplate(dataSource());
	}
}
```

### Adding Spring transaction management

[Read this](https://www.marcobehler.com/guides/spring-transaction-management-transactional-in-depth)

(assuming that the right dependency line `spring-jdbc` or `spring-tx` is already there)

Add the `@EnableTransactionManagement` to the configuration class and the `TransactionManager` bean:

```java
@Configuration
@EnableTransactionManagement
class ConfigurationClass {
	@Bean
	public DataSource dataSource() {
		JdbcDataSource ds = new JdbcDataSource();
		ds.setURL("jdbc:h2:~/myFirstH2Database;INIT=RUNSCRIPT FROM 'classpath:schema.sql'");
		ds.setUser("sa");
		ds.setPassword("sa");
		return ds;
	}

	@Bean
	public TransactionManager platformTransactionManager() {
		// This class is responsible for actually opening up and committing transactions on database connections. 
		return new DataSourceTransactionManager(dataSource());
	}
}
```

### Adding database to the Spring-Boot

Dependencies:

```xml
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-jdbc</artifactId>
	<!-- You can specify the version if not inheriting from the Spring Parent project. -->
</dependency>
<dependency>
	<groupId>com.h2database</groupId>
	<artifactId>h2</artifactId>
	<!-- You can specify the version if not inheriting from the Spring Parent project. -->
</dependency>
```

Properties:

```properties
spring.datasource.driver-class-name=org.h2.Driver
spring.datasource.url=jdbc:h2:mem:
spring.datasource.username=sa
spring.datasource.password=sa
```

Spring-Boot will automatically look for any `schema.sql` file, so create it.

Then you can autowire the `JdbcTemplate` object and use `@Transactional` annotation.

This does the following magic:
1. Spring detects `spring.datasource.*` properties and configures the `DataSource` `@Bean` automatically.
2. Spring `JdbcTemplate` is also created.
3. The `TransactionManagement` features are automatically enabled.
4. The `schema.sql` script is automatically executed.

[What can be configured via application.properties.](https://docs.spring.io/spring-boot/docs/current/reference/html/application-properties.html)

### Listing added dependencies

This is useful when adding new Spring Starter dependencies - see what is added inside.

```bash
mvn dependency:tree
```

### Seeing all SQL logs in Spring JDBC

```properties
logging.level.org.springframework.jdbc.core.JdbcTemplate = DEBUG
```

### Starter projects

Many starter projects like spring-boot-starter-web, spring-boot-starter-tomcat, spring-boot-starter-security consist of only a single `pom.xml` file.
This is just dependency management.

Almost all Spring-Boot magic is done in spring-boot-autoconfigure. There is `spring.factories` file and then more than a hundred `...AutoConfiguration` classes.

```java
// So this is another @Configuration class!
@Configuration(proxyBeanMethods = false)

// Continue only if these classes exist (DataSource comes with JDK, EmbeddedDatabaseType comes with Spring-Boot).
// There are many more ConditionalOn variants, eg. @ConditionalOnJava to specify the Java version.
@ConditionalOnClass({ DataSource.class, EmbeddedDatabaseType.class })

// DataSourceProperties has a list of the properties, all prefixed with "spring.datasource".
// Our properties will be mapped to the DataSourceProperties class.
@EnableConfigurationProperties(DataSourceProperties.class)

@Import({ DataSourcePoolMetadataProvidersConfiguration.class, DataSourceInitializationConfiguration.class })
public class DataSourceAutoConfiguration {

	// More configuration classes below, see source for details...

}
```