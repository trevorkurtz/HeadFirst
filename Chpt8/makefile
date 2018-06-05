hfcal.o:
	gcc -I./Includes -fPIC -c hfcal.c -o hfcal.o

hfcal: hfcal.o
	gcc -shared hfcal.o -o .\libs\hfcal.dll

elliptical.o: elliptical.c hfcal
	gcc -I.\Includes -c elliptical.c -o elliptical.o

elliptical: elliptical.o
	gcc elliptical.o -L.\libs -lhfcal -o elliptical