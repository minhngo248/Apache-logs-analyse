# Apache-logs-analyse - mode d'emploi

-------------------------------------------------------------------------------
Ligne de commandes : (on peut taper plusieurs options dans une ligne de commandes)
- Fusion les fichiers .o, fichier exécutable : make analog
- Affiche 10 URLs plus cliqués : ./analog --fichier .log--: Dans tous les cas, le fichier log est obligatoirement 
fourni à la fin de la ligne de commande.
- Exporter le fichier .dot : ./analog -g --fichier .dot-- --fichier .log--: Dans tous les cas, l'option -e est
obligatoirement suivie directement par un fichier dot, dans lequel les lignes de code pour produire un fichier au format 
GraphViz sont écrites
- Exclure les images : ./analog -e --fichier .log--
- Affiche les URLs en heure souhaitée: ./analog -t --heure-- --fichier .log--: Dans tous les cas, l'option -t est
obligatoirement suivie directement par l'heure souhaitée, dont valeur doit être entre 0 est 23.