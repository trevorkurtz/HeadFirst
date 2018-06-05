encrypt.o: encrypt.c encrypt.h
	gcc -c encrypt.c

builder.o: builder.c encrypt.h
	gcc -c builder.c

builder: encrypt.o builder.o
	gcc encrypt.o builder.o -o builder