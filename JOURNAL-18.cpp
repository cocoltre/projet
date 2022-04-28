Journal 2:

Tout d'abord la mise en place du fichier pour la partie 2
s'est passée sans difficulté.

Lors de la séance de TP semaine 6 nous avons créé:
Le type énuméré Kind et le tableau de cellules cells_ sans difficulté.
La méthode reloadConfig nous a posés quelques problèmes car il fallait des pointeurs.
Après les avoir mis, reloadConfig fonctionnait correctement.
Puis à la fin de cette séance, nous avons fini de coder reloadCacheStructure.
Le reste (methode reset et updateCache) a été fini dans notre temps libre.
Au final, le test 2 a fonctionné.

Avant la séance de TP semaine 7 nous avons commencé l'étape 2.2
Les retouches à updateCache sont faites à l'aide de boucles conditionelles
pour chaque texture, les rendant apparentes uniquement quand il faut. Cela a demandé
plusieurs essais mais le Test 3 s'est déroulé sans trop de difficulté.
Nous avons dit "woaw".

Durant la séance de TP semaine 7 nous effectuons les retouches sur
la méthode reset avec la fonction uniform pour le placement aléatoire et des boucles
conditionelles limitant le nombre de seed d'eau ou d'herbe.
Test 4 effectué sans problème

Nous créons ensuite la méthode step et steps de même que seed_position afin de
modulariser.
Teste 5 effectué sans problème
Ensuite la méthode smooth et smooths dans lesquelles on travaille sur une copie de
cells comme demandé.
Test 6 a bien fonctionné
Nous utilisons maintenant le paramètre booléen regenerate de reset (introduit dans
l'étape 2.1)
Test 7 s'est déroulé comme il le faut

La sauvegarde d'une configuration a été plus laborieuse.
Aucun message d'erreur ne s'affichait or la map ne se rechargeait pas quand on tapait
'L'
Nous avons ensuite trouvé l'erreur qui provenait en partie de saveToFile et de
loadFromFile.
Le chemin d'ouverture mais aussi de sauvegarde ne fonctionnaient pas.
Avec l'aide d'un assistant la sauvegarde et l'ouverture ont fonctionné après l'heure de
TP de la semaine 8.

Pendant la séance de TP semaine 8 nous avons réglé des petits problèmes de mise en
place du dossier partie 3 et un bug sur un de nos ordinateurs (Erreur: cannot output
file permission denied).

Nous avons ensuite continué à coder la classe Env qui avait été commencée au préalable.
Le Test 9 n'a pas posé de soucis.

Les retouches à World et updateCache ont bien fonctionné et dans le Test 10 les niveaux
de bleus étaient cohérents avec la map.

Par contre l'affichage en mode debugging n'a pas bien fonctionné avec debugging.
Les niveaux d'humidité étaient complètement faux (pafois 'NO', parfois des grands
nombres où il n'y avait pas d'eau)
Mais au final nous avons résolu le problème avec l'aide d'un assitant à la fin de la
séance du TP.

Enfin, pour la partie 3.2 et 3.3, on a eu quelques problèmes comme le dessin des fleurs. En effet, d'abord les fleurs
n'apparaissaient pas puis elles apparaissaient mais changeaient tout le temps de texture.
On a alors pensé à mettre l'indice de texture en attribut, et tout a marché.
Tout s'est alors bien déroulé et nous avons fini l'étape 3 dans les temps.
