CC = gcc
CFLAGS = -Wall -pedantic
LIBS = -lpthread

attuatore: funzioni_backend.c funzioni_frontend.c attuatore.c
	$(CC) $(CFLAGS) -c funzioni_backend.c funzioni_frontend.c attuatore.c
	$(CC) funzioni_backend.o funzioni_frontend.o attuatore.o $(LIBS) -o attuatore

clean:
	rm -f *.o *~