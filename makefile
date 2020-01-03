all: control.o write.o
	gcc -o control control.o
	gcc -o write write.o

control.o: control.c
	gcc -c control.c

writer.o: write.o
	gcc -c write.c

clean:
	rm *~