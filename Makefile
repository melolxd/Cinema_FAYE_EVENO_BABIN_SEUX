# Project: tp_cinema

OBJ  = sem_op.o shm_op.o aleatoire.o
LINKOBJ  = $(OBJ)
BIN  = cinema caisse affichage_cinema
CFLAGS = -g #-Wall

all: cinema caisse affichage_cinema

cinema: $(LINKOBJ) shm_const.h cinema.c
	$(CC) cinema.c $(LINKOBJ) -o cinema $(CFLAGS)

affichage_cinema: $(LINKOBJ) shm_const.h affichage_cinema.c
	$(CC) affichage_cinema.c $(LINKOBJ) -o affichage_cinema $(CFLAGS)

caisse: $(LINKOBJ) shm_const.h caisse.c
	$(CC) caisse.c $(LINKOBJ) -o caisse $(CFLAGS)

shm_op.o: shm_op.c shm_const.h
	$(CC) -c shm_op.c $(CFLAGS)

sem_op.o: sem_op.c shm_const.h
	$(CC) -c sem_op.c $(CFLAGS)


aleatoire.o: aleatoire.c
	$(CC) -c aleatoire.c $(CFLAGS)

clean: 
	rm -f $(OBJ) $(BIN)


