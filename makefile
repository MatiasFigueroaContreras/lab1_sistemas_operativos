FLAGS = -g -Wall

all: clean lab1 run

lab1: lab1.c padre.o hijo.o linkedList.o
	gcc $(FLAGS) -o lab1 padre.o linkedList.o lab1.c 

padre.o: padre.c padre.h 
	gcc $(FLAGS) -c padre.c

hijo.o: hijo.c hijo.hijo
	gcc $(FLAGS) -c hijo.c

linkedList.o: linkedList.c linkedList.h
	gcc $(FLAGS) -c linkedList.c

informacion.o: informacion.c informacion.hijo
	gcc $(FLAGS) -c informacion.c

clean:
	rm -f lab1 *.o

run:
	./lab1