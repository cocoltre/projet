=====================================================================
La simulation informatique de colonies d'abeilles vise à  modéliser la vie et les interactions des abeilles entres elles de même qu'avec les éléments qui les entourent dans un environnement.

Les abeilles sont séparées en deux catégories. Les Scout (éclaireuses) sont plus petites et orange, elles sont chargées de repérer les fleures avec le plus de nectar et de partagé la position 
de cette derniere avec l'autre classe d'abeilles. Les Workers (butineuses) sont plus larges et jaune, elles vont récolté le pollen dans les fleures et le rammene à la ruche.

Une abeille est caracterisée par:
-son appartenance a la ruche;
-sa vitesse;
-son energie;
-sa memoire;
-la valeure de sa memoire;
-son état (au repos, en recherche...)
-son but (target)
-son attribu spécifique à sa classe (quantité de nectar quelle transporte ou nombre d'abeilles avec qui elle partage de l'information) 



Les interactions entre les abeilles sont régies par des règles qui diffèrent dâ€™une cellule Ã  lâ€™autre, ces rÃ¨gles sont les rÃ¨gles dâ€™affrontement, de reproduction, de survie, de dÃ©placement et de mort ;
Les fleures représentent des sources de pollen. Il va être prélevé par les Workers. 
Le World est un lieu d'évolution pour les abeilles, les ruches et les fleures. C'est en fait une grille à deux dimensions (représenté par un vector unidimentionel) de Cell recouvert par un tableau de Seed (Eau, Herbe, Roche).


##COMPILATION ET EXECUTION:

Ce projet utilise  [Cmake](https://cmake.org/) pour compiler

* en ligne de commande :
    - dans le dossier build: cmake ../src
    - make nom_cible pour la gÃ©nÃ©ration de la cible

* Dans QTCreator:
       - mise en place du projet : ouvrir le fichier src/CmakeLists.txt
       - choisir les cibles citées dans ##CIBLES PRINCIPALES.

##CIBLES PRINCIPALES:

* FinalApplication -> correspond à l'application finale.
* CollaborationTest -> permet de tester l'interaction d'une Scout avec une Worker


## FICHIERS DE CONFIGURATION 

Les fichiers de configuration à utiliser pour application sont app6.json (permet de voir de près l'evolution d'une ruche)
                                                            et app3.json (permet de voir l'evolution de plusieurs ruches).


## COMMANDES

Les commandes pour l'utilisation d'une cible particulières sont données
dans un panneau d'aide à droite de la fenêtre de simulation.

### MODIFICATION DE CONCEPTION

Le codage du projet a été réalisé en adéquation avec l'énoncé.


### EXTENSIONS

*[Description des extensions ajoutÃ©es et de comment les observer lors de l'exÃ©cution du programme]*