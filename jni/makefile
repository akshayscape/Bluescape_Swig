# Define a variable for classpath
CLASS_PATH = ../bin

# Define a virtual path for .class in the bin directory
vpath %.class $(CLASS_PATH)

all : libhello.so

# $@ matches the target, $< matches the first dependancy
libhello.so : example.o
	gcc -I/opt/java/jdk1.8.0_91/include -I/opt/java/jdk1.8.0_91/include/linux -Wall -fPIC -shared -O -g example.c example_wrap.c -lgclib -lgclibo -o libhello.so

# $@ matches the target, $< matches the first dependancy
example.o : example.c example.h
	swig -java example.i
	gcc -c example.c example_wrap.c -I/opt/java/jdk1.8.0_91/include -I/opt/java/jdk1.8.0_91/include/linux

# $* matches the target filename without the extension
example.h : example.class
	javah -classpath $(CLASS_PATH) $*

clean :
	rm example.h example.o libhello.so