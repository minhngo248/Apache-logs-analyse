# Apache-logs-analyse - mode d'emploi

-------------------------------------------------------------------------------
Ligne de commandes : (on peut taper plusieurs options dans une ligne de commandes)
- Fusion les fichiers .o, fichier exécutable : make analog
- Affiche 10 URLs plus cliqués : ./analog --fichier .log--: Dans tous les cas, le fichier log est obligatoirement 
fourni à la fin de la ligne de commande.
- Exporter le fichier .dot : ./analog -g --fichier .dot-- --fichier .log--: Dans tous les cas, l'option -e est
obligatoirement suivie par un fichier dot, dans lequel le code pour 
- Exclure les images : ./analog -e --ficher .log--
- Affiche les URLs en heure souhaitée: ./analog -t --heure-- --fichier .log--: Dans tous les cas, l'option -t est
obligatoirement suivie par l'heure souhaitée, dont valeur doit être entre 0 est 23.