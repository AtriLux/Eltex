edit : static dynamic1 dynamic2
#static library
static : prog.o libstatic.a
	gcc prog.o -L. -lstatic -o s_prog
libstatic.a : sqrt2.o power2.o
	ar rc libstatic.a sqrt2.o power2.o
#dynamic with static compilation
dynamic1 : prog.o libdynamic.so
	gcc prog.o -L. -ldynamic -o d1_prog
#dynamic
dynamic2 : d2_prog.o libdynamic.so
	gcc d2_prog.o -o d2_prog -ldl
libdynamic.so : sqrt2.o power2.o
	gcc -shared -o libdynamic.so sqrt2.o power2.o
#create *.o files
d2_prog.o : d2_prog.c
	gcc -c d2_prog.c
prog.o : prog.c
	gcc -c prog.c
sqrt2.o : sqrt2.c
	gcc -fPIC -c sqrt2.c
power2.o : power2.c
	gcc -fPIC -c power2.c
#additional options
clean_all :
	rm *.o *.a *.so *prog
clean : 
	rm *.o *.a
