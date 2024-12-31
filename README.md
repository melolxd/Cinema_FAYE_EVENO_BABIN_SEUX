# Cinema_FAYE_EVENO_BABIN_SEUX

Pour compiler, il faut installer **gcc**
=>>> **sudo apt install gcc**
puis 
=>>> **make**
puis
=>>> **./cinema 15 "Matrix reloaded" 300**


Une fois compilé, le projet s'exécute sans erreur notable, à voir si il reste des trucs à paufiner

SI erreur **semget: File exists**

il faut faire **ipcs -s**
puis
=>>> **ipcrm -s id**

