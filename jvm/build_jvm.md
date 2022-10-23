## Build your own JVM instance

### TODO

1. Watch this: https://www.youtube.com/watch?v=5AFgNuGwLos.
2. Debug JVM from Visual Studio.
3. Investigate topics below.

---

### Steps to build the actual JVM instance

1. Watch this for most of the steps: https://www.youtube.com/watch?v=lhkjOrY65Ts&list=LL&index=1
2. Additional steps on WSL
   1. Install the java 12, 13 or 14 JDK on Ubuntu (do a local installation, just like you would do on ordinary Ubuntu). Point to it in the configure step.
   2. Disable treating C/C++ compilation warnings as errors.
   3. (Most importantly) Force building a linux version. If you see the point where Jose is actually accessing the final build, you can see that it is the linux build. He is doing it on an Ubuntu VM which is "slightly different situation" than running Ubuntu on WSL. Apparently, the autoconf software used in the build process returns host_os="wsl" when ran on WSL Ubuntu. The configuration script gets this and translates this into doing a windows build. Then it fails on lacking Microsoft toolchain and all of other strange errors (lacking Visual Studio, WTF). So I just forced it to do the linux build and then it used a linux gcc toolchain. 🙂 

Final configure command: `./configure --with-boot-jdk=/usr/lib/jvm/jdk-14 --openjdk-target=x86_64-linux-gnu --disable-warnings-as-errors`

---

### Debugging the JVM instance

#### Building the right target

Links:
* [SO topic: Debugging the JVM](https://stackoverflow.com/questions/44491385/how-to-use-gdb-to-trace-compiled-jdk9-hotspot)
* [SO topic: Debugging the JVM interpreter](https://stackoverflow.com/questions/68391777/openjdk-8-interpreter-debug)
* [SO topic: Debug JVM in Eclipse](https://stackoverflow.com/questions/42052262/how-to-debug-the-openjdk-9-mainly-the-hotspot-source-code-in-eclipse)
* [Quite old presentation about this](https://www.youtube.com/watch?v=k7IX_diKCEo)

Additional configure arguments:
1. Build the debug variant of the JVM: `--with-debug-level=slowdebug`.
2. Include native debug symbols (?): `--with-native-debug-symbols=internal`.

Final configure command: `./configure --with-boot-jdk=/usr/lib/jvm/jdk-14 --openjdk-target=x86_64-linux-gnu --disable-warnings-as-errors --with-debug-level=slowdebug --with-native-debug-symbols=internal`. For other options check `make\autoconf\jdk-options.m4`.

#### Debugging with gdb

`gdb --args /path/to/jvm/code/root/build/linux-x86_64-server-slowdebug/images/jdk/bin/java ExampleClass`

---

### Topics to investigate

#### JVM applying Flyweight pattern to the exceptions

1. Uncommon traps: https://shipilev.net/jvm/anatomy-quarks/29-uncommon-traps/
2. Bug report: https://bugs.java.com/bugdatabase/view_bug.do?bug_id=4292742
3. Property: OmitStackTraceInFastThrow - look for it in the repository
4. Debug: graphKit.cpp builtin_throw method
5. Answer: why Heinz's code repeating the ClassCastException does not use exception flyweight

#### Playing with the JVM instance

1. Java code:
   1. Add a new method to String class in the JVM -> use it.
   2. Change toString() implementation in the Object class.
2. Native methods:
   1. Add a new JNI method to the JVM -> use it in the actual Java code.
3. Implement an algorithm in Java and C++ and compare the performance.

#### Class definition process

1. Check how class is defined and put into the memory.
2. Check what is the class header internally and why it weights 12 bytes.

#### String pooling investigation

1. Provide a native Java API to pull the actual state of the string pool.
2. Get the string pool state from the Java code and observe how it changes.
3. Debug the string pool code.

#### JVM tests investigation

1. How is C++ code tested in JVM? Try to launch tests.
2. How is Java code tested in JVM? Try to launch tests.
