# Maven
## Build Lifecycle Basics

### Build Lifecycles
Built-in build lifecycles:
* default - handles project deployment;
* clean - handles project cleaning;
* site - handles the creation of project's site documentation.

### Build Phases
**Build phase is responsible for a specific step in the build lifecycle.**

Default lifecycle comprises of the following phases:
* validate - validate the project is correct and all neccessary information is available;
* compile - compile the source code of the project;
* test - test compiled source code using a suitable unit testing framework. This phase should not require the code to be packaged or deployed;
* package - take the complied code adn package it in its distributable format (eg. JAR);
* verify - run any checks on results of integration tests to ensure quality criteria are met;
* install - install the package into the local repository, for use as a dependency in other projects **locally**;
* deploy - done in the build environment, copies the final package to the remote repository for sharing with other developers and projects.

### Plugin Goals
**Build phase is made up of plugin goals.**

Plugin goals characteristics:
* the are finer than a build phase;
* they are a way of customising the build phases;
* they are **bound** to zero or more build phases;
* in case a goal is not bound to any build phase, it could be executed outside of the build lifecycle by direct invocation;
* if a goal is bound to one or more build phases, it will be called in all those phases.

Build phase characteristics with regard to plugin goals:
* if a build phase has no goals bound to it, this phase will not be executed;
* the order of execution depends on the order in which the goal(s) and build phase(s) are invoked.

#### Build Phases and Plugin Goals Example:

Elements:
* `clean` and `package` are build phases;
* `dependency:copy-dependencies` is a goal of a plugin;

Process to be executed (in this order):
* `clean` phase with all preceding phases of clean lifecycle;
* `dependency:copy-dependencies` goal;
* `package` phase with all preceding phases of the default lifecycle

Command to use:

`mvn clean dependency:copy-dependencies package`

#### Build Phases That Are Not Called via CLI

The phases starings with `pre-*`, `post-*`, `process-*` are usually not directly called via CLI. These phases sequence the build, producing intermediate results that are not useful outside the build. **In the case of invoking `integration-test`, the environment may be left in a hanging state.**

## Assigning tasks to each of build phases
### Packaging
Setting the `packaging` property assigns goals to a build phase. This is done using `<packaging>` element in project's POM.

**Each packaging contains a list of goals to bind to a particular phase.**

Valid values of `<packaging>` element:
* `jar` (default value) - handles phases with almost a standard set of bindings;
* `war`;
* `ear`;
* `pom` - project that is purely metadata, only binds goals to the `install` and `deploy` phases.

Some packaging types require particular plugins in `<build>` section of POM and `<extensions>true</extensions>` specified.

#### Examples of plugin-phase bindings
##### `pom` packaging
```xml
<phases>
  <install>
    org.apache.maven.plugins:maven-install-plugin:2.4:install
  </install>
  <deploy>
    org.apache.maven.plugins:maven-deploy-plugin:2.7:deploy
  </deploy>
</phases>
```
##### `jar` packaging
```xml
<phases>
  <process-resources>
    org.apache.maven.plugins:maven-resources-plugin:2.6:resources
  </process-resources>
  <compile>
    org.apache.maven.plugins:maven-compiler-plugin:3.1:compile
  </compile>
  <process-test-resources>
    org.apache.maven.plugins:maven-resources-plugin:2.6:testResources
  </process-test-resources>
  <test-compile>
    org.apache.maven.plugins:maven-compiler-plugin:3.1:testCompile
  </test-compile>
  <test>
    org.apache.maven.plugins:maven-surefire-plugin:2.12.4:test
  </test>
  <package>
    org.apache.maven.plugins:maven-jar-plugin:2.4:jar
  </package>
  <install>
    org.apache.maven.plugins:maven-install-plugin:2.4:install
  </install>
  <deploy>
    org.apache.maven.plugins:maven-deploy-plugin:2.7:deploy
  </deploy>
</phases>
```

### Plugins
Configuring plugins is the second way of adding goals to phases.

Plugins characteristics:
* they are artifacts that provide goals to Maven;
* they may have one or more goals; **each goal represents a capability of the plugin**;
* example: Complier plugin with two goals: `compile` (compile main code) and `testCompile` (compile test code).

Steps of working with plugins:
1. Add the plugin;
1. Specify the goals you want to run as part of the build.

#### Examples of Plugin Usages

##### Plugin bound to one phase
Plugin goal `modello:java`:
  * generates Java source codes;
  * is bound to `generate-sources` phase.

To has it generate sources from a model and incorporate that into the build:
```xml
 <plugin>
   <groupId>org.codehaus.modello</groupId>
   <artifactId>modello-maven-plugin</artifactId>
   <version>1.8.1</version>
   <executions>
     <execution>
       <configuration>
         <models>
           <model>src/main/mdo/maven.mdo</model>
         </models>
         <version>4.0.0</version>
       </configuration>
       <goals>
         <goal>java</goal>
       </goals>
     </execution>
   </executions>
 </plugin>
```
The `<executions>` element is there to enable running the same goal multiple times with different configuration if needed.

##### Plugin bound to more phases
Plugin goal `display:time`:
  * echos the current time to the commandline;
  * can be bound to virtually any phase.

To bind the goal to `process-test-resources` phase:
```xml
 <plugin>
   <groupId>com.mycompany.example</groupId>
   <artifactId>display-maven-plugin</artifactId>
   <version>1.0</version>
   <executions>
     <execution>
       <phase>process-test-resources</phase>
       <goals>
         <goal>time</goal>
       </goals>
     </execution>
   </executions>
 </plugin>
```

## Todo
* (dalej maven)[https://maven.apache.org/guides/introduction/introduction-to-the-pom.html]
* (spring plugin)[https://maven.apache.org/guides/introduction/introduction-to-the-pom.html]
* multiple instances of the same plugin? Czy moze jest to powiazane z bugiem Gabriela - bylo wiele instancji pluginu Springa i zle budowaly (nie wspolpracowaly ze soba?)
* inwestygacja bledu u Gabriela - co takiego sie dzieje jak jest wszedzie referencja do pluginu a co innego sie dzieje jak sie da pluginManagement 
* what is the `<build>` tag
