FLAGS = -g -Wall

all: clean lab1

lab1: lab1.c padre.o hijo.o linkedList.o informacion.o
	gcc $(FLAGS) -o lab1 padre.o hijo.o linkedList.o informacion.o lab1.c

padre.o: padre.c padre.h 
	gcc $(FLAGS) -c padre.c

hijo.o: hijo.c hijo.h
	gcc $(FLAGS) -c hijo.c

linkedList.o: linkedList.c linkedList.h
	gcc $(FLAGS) -c linkedList.c

informacion.o: informacion.c informacion.h
	gcc $(FLAGS) -c informacion.c

clean:
	rm -f lab1 *.o
