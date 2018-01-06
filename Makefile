all:libvld_cpp.a libvld_c.a

libvld_cpp.a:vld_cpp.o
	ar -cr libvld_cpp.a vld_cpp.o
vld_cpp.o:vld_cpp.h vld_cpp.cpp
	g++ -o vld_cpp.o -c vld_cpp.cpp

libvld_c.a:vld_c.o
	ar -cr libvld_c.a vld_c.o
vld_c.o:vld_c.h vld_c.c
	gcc -o vld_c.o -c vld_c.c

.PHONY:clean install
clean:
	rm *.a *.o
install:
	./install-sh
