#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

/******************************************************************************/
/*
 * Nouveau fichier pour gérer les caisses inspirée de entree.c
 * A modifier
 */
/******************************************************************************/

extern void attente_aleatoire(unsigned int delais);
extern int *attacher_segment_memoire();
extern int place_aleatoire();
extern int P();
extern int V();

bool achat_places(int *mem, int semid, int nb_places) {

    bool places_attribuees = false;

    P(semid);

   if (*mem < place_aleatoire() && *mem == 0){
    /*Plus de place*/
    printf("Caisse: Plus de places disponibles. Fermeture.\n");
    return 0;
   }
   else if(*mem < place_aleatoire()&& *mem > 0){
    places_attribuees = true;
   }
   else{
    *mem = *mem - place_aleatoire();
    places_attribuees = true;
   }

    V(semid);
    return places_attribuees;
   }
   
   


int main(int argc, char *argv[]) {

    unsigned int  delais=1;

    int shmid = atoi(argv[1]);
    int semid = atoi(argv[2]);

    int *mem = attacher_segment_memoire(NULL, &shmid);

    attente_aleatoire(delais);
    int places_dispo = *mem;
    int nb_places_random = place_aleatoire();


    
    while (1)
  {
    achat_places(mem, semid, nb_places_random);
    sleep(1);
  }
}
