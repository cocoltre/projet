\=====================================================================

La simulation informatique de colonies d'abeilles vise à modéliser la vie et les interactions des abeilles entre elles, et avec les éléments qui les entourent dans un environnement créé.

Les abeilles sont séparées en deux catégories. Les Scouts (éclaireuses) sont petites et oranges, elles sont chargées de repérer les fleurs avec le plus de nectar et de partager la position

de ces dernières avec l'autre classe d'abeilles. Les Workers (butineuses) sont larges et jaunes, elles vont récolter le pollen dans les fleurs, dont la position leur a été transmise par les

Scouts, et le ramener à la ruche.

Une abeille est caractérisée par :

- son appartenance à la ruche;
- sa vitesse;
- son énergie;
- sa mémoire;
- la valeur de sa mémoire (si elle a du sens ou non);
- son état (au repos, en recherche de fleurs...)
- sa cible
- son attribut spécifique à sa classe (quantité de nectar qu'elle transporte pour les Workers, ou nombre d'abeilles avec qui elle partage de l'information pour les Scouts)



Les interactions des abeilles sont régies par des règles qui diffèrent d'une abeille à l'autre, ces règles sont des règles de déplacement et de fonction propre à chaque type d'abeille ;

Les fleurs représentent des sources de pollen, qui va être prélevé par les Workers.

Le World est un lieu d'évolution pour les abeilles, les ruches et les fleurs. C'est en fait une grille à deux dimensions (représentée par un vector unidimensionnel) de cellules Cell,

recouvert par un tableau de graines Seed (Eau, Herbe, Roche).


##COMPILATION ET EXECUTION :

Ce projet utilise  [Cmake](https://cmake.org/) pour compiler

* en ligne de commande :
- dans le dossier build: cmake ../src
- make nom\_cible pour la génération de la cible

* Dans QTCreator:
- mise en place du projet : ouvrir le fichier src/CmakeLists.txt
- choisir les cibles citées dans ##CIBLES PRINCIPALES.


##CIBLES PRINCIPALES:

* FinalApplication -> correspond à l'application finale, trace la simulation finale
* CollaborationTest -> permet de tester l'interaction d'une Scout avec une Worker
* WorldTest -> permet de créer un environnement
* Il existe d'autres cibles comme HiveTest, ou FlowerTest, mais celles-ci nous semblent moins intéressantes à tester et à visualiser.

\## FICHIERS DE CONFIGURATION

Les fichiers de configuration à utiliser pour application sont app6.json (permet de voir la simulation dans un environnement assez simple)

ou app3.json (permet de voir la simulation dans un environnement plus complexe, plus proche de la réalité mais qui demande plus d'énergie à l'ordinateur).


\## COMMANDES

Les commandes pour l'utilisation d'une cible particulière sont données

dans un panneau d'aide à droite de la fenêtre de simulation.


\### MODIFICATION DE CONCEPTION

Le codage du projet a été réalisé en adéquation avec l'énoncé. Seulement, pour une raison inconnue, la partie 5 ne contient plus rien. Cela ne devrait pas pour autant gêner la simulation comme une partie 6 a été créée et fonctionne très bien.


\### EXTENSIONS

\*[Description des extensions ajoutées et de comment les observer lors de l'exécution du programme]\*
