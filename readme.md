# Configuration
Pour configurer notre analyseur de logs, il faut modifier le fichier config.txt. Ce fichier contient :
- l'url utilisée comme base, considérée comme locale
- les extensions des fichiers non pris en compte avec la commande -e

# Utilisation
Le programme peut-être utilisé en exécutant la commande make puis la commande ./analysis
Les différentes options sont:
- -g filename.dot pour générer un graph des hits dans le fichier filename.dot
- -e pour enlever les fichiers image, script et style
- -t hour pour ne garder que les hits réalisés entre hour:00 et hour+1:00
