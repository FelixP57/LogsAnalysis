# Analog - Analyseur de Logs Apache

**Analog** est un outil en ligne de commande développé en C++ conçu pour analyser les fichiers journaux (logs) des serveurs web Apache. Il permet d'extraire des statistiques de consultation et de visualiser le parcours des utilisateurs sous forme de graphe.

---

## Fonctionnalités

L'application répond aux besoins d'analyse suivants :
* **Statistiques par défaut** : Affiche la liste des 10 documents les plus consultés par ordre décroissant de popularité.
* **Génération de graphe (-g)** : Produit un fichier au format GraphViz (`.dot`) où chaque document est un nœud et chaque arc indique le nombre de parcours entre deux pages.
* **Filtrage des ressources (-e)** : Permet d'exclure tous les documents ayant une extension de type image, CSS ou Javascript.
* **Filtrage horaire (-t)** : Limite l'analyse aux requêtes effectuées dans un créneau horaire spécifique `[heure, heure+1[`.

## Configuration
Pour configurer notre analyseur de logs, il faut modifier le fichier config.txt. Ce fichier contient :
- l'url utilisée comme base, considérée comme locale (par défaut : http://intranet-if.insa-lyon.fr)
- les extensions des fichiers non pris en compte avec la commande -e (par défaut : les images, documents CSS et Javascript)

## Utilisation

Le programme peut-être utilisé en exécutant la commande make puis la commande suivante :

```bash
./analog [-g nomfichier.dot] [-e] [-t heure] nomfichier.log
```

---

## Compilation

Le projet utilise un **Makefile** pour automatiser la gestion des dépendances et la compilation avec les drapeaux d'optimisation nécessaires.

```bash
make
```

Pour nettoyer les fichiers objets et l'exécutable :
```bash
make clean
```