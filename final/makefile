# Make file

net367: real_clean host.o switch.o utilities.o link.o man.o main.o net.o netconfig.o
	gcc -o net367 host.o switch.o utilities.o link.o man.o main.o net.o netconfig.o

main.o: main.c
	gcc -c main.c

host.o: host.c 
	gcc -c host.c  

switch.o: switch.c
	gcc -c switch.c

man.o:  man.c
	gcc -c man.c

net.o:  net.c
	gcc -c net.c

netconfig.o: netconfig.c
	gcc -c netconfig.c

utilities.o: utilities.c
	gcc -c utilities.c

link.o:  link.c
	gcc -c link.c

clean:
	rm -f *.o

real_clean: clean
	rm -f net367

