# Tomcat

## Basic things
* **Web application** - hierarchy of directories and files in a standard layout. Unpacked form = structure of directories; packed form = web archive (WAR).
* **Document root** - top level of the application.
* **Context path** - value assigned during the deployment.

## Standard directory layout
1. HTML and JSP pages that need to be visible for client browser:
```
document_root/*.html
document_root/*.jsp
```
2. Web application deployment descriptor
```
document_root/WEB-INF/web.xml
```

Purposes:
* contains servlets and other component that make up your application;
* initialization parameters, container-managed security constraints.

3. Application classes
```
document_root/WEB-INF/classes/
```

Purposes:
* any required Java classes for the application that are not combined into JAR files;
* associated resorces.

4. Libraries:
```
document_root/WEB-INF/lib/
```

Purposes:
* JAR files that contain Java class files required for the application - libs, JDBC drivers.

5. Tomcatt specific configuration options
```
document_root/META-INF/context.xml
```
