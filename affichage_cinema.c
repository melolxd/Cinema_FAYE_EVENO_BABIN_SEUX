#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/******************************************************************************/
/*
 * A MODIFIER
  * C'est l'équivalent de sortie.c
*/
/******************************************************************************/

/******************************************************************************/
/*
 * Fonctions externes
*/
/******************************************************************************/
extern void attente_aleatoire();
extern int * attacher_segment_memoire();
extern int P();
extern int V();

/******************************************************************************/
/*
 * Fonctions 
*/
/******************************************************************************/

int affichage_siege(int *mem, int semid, int nombre_siège, char *titre_film) {                                       

/* On protège l'accès à la shm */
P(semid);

  /* Si le nombre de places dans la shm = nombre de places du parking
 * alors plus de voitures à faire sortir 
 * */
  if (*mem != nombre_siège) {
  /* On écrit dans la shm */
  *mem=(*mem + 1);
  printf("\tDans le film %s,il y a %d places\n",titre_film, *mem);
  }

/* On protège l'accès à la shm */
V(semid);

return(0);

}



/******************************************************************************/
/*
 * Programme principal
*/
/******************************************************************************/
int main(int argc, char *argv[]) {

unsigned int  delais=1;

int shmid=atoi(argv[1]);
int semid=atoi(argv[2]);
int nb_places=atoi(argv[3]);
char *titre_film=argv[4];

int *mem;


/* Attachement du segment de mémoire partagée */
mem=attacher_segment_memoire(mem, &shmid);

while (1) {
  attente_aleatoire(delais);
 
  affichage_siege(mem, semid, nb_places, titre_film);
}

return(0);
}


