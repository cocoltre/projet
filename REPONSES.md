[Question Q1.1] L'algorithme de «clamping» de la position devra être appliqué dans d'autres contextes que celui de la construction.

`				`Comment le coder pour que sa réutilisation dans une autre méthode de

`				`la classe Collider n'implique pas de duplication de code ?

[Reponse R1.1] Pour éviter la duplication de code on crée une nouvelle méthode clamp.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q1.2] Comment utiliser des boucles pour éviter d'avoir un

code trop répétitif dans la mise en oeuvre de cet algorithme ?

[Reponse R1.2] On peut utiliser une boucle sur un array de positions possibles afin de trouver la distance la plus courte entre deux points.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q1.3] Quels arguments de méthodes, parmi celles qu'il vous été demandé de coder ci-dessus, vous semble-t-il judicieux de passer par référence constante ?

[Reponse R1.3] Les méthodes ayant des arguments pouvant être passés en références constantes sont les méthodes directionTo, distanceTo, move et l'opérateur += car elles n'ont pas la vocation de changer les valeurs de leurs arguments et leurs arguments sont de type volumineux (Vec2d, Collider).

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q1.4] Quelles méthodes parmi celles que l'on vous a demandé de coder ci-dessus vous semble-t-il judicieux de déclarer comme const ?

[Réponse R1.4] Les méthodes directionTo et distanceTo car elles ne modifient aucun attribut de classe.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q1.5] Comment coder les trois opérateurs précédemment décrits en évitant toute duplication de code dans le fichier Collider.cpp ?

[Réponse R1.5] Il suffit de se servir des méthodes isColliderInside, isColliding, isPointInside définies juste avant afin de coder les trois opérateurs.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q1.6] Quelle surcharge choisissez-vous pour les opérateurs qu'il vous a été demandé de coder (interne ou externe) et comment justifiez-vous ce choix ?

[Réponse R1.6] Il est utile de choisir une surcharge interne car les quatre opérateurs ont besoin d'attributs de la classe pour fonctionner et donc cela permet de ne pas passer par des getters.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q1.7] Quels arguments de méthodes, parmi celles qu'il vous été demandé de coder ci-dessus, vous semble-t-il judicieux de passer par référence constante ?

[Réponse R1.7] Toutes les méthodes ci-dessus n'ont pas besoin (et de doivent pas) modifier les arguments qu'ils recoivent, d'autant que ceux-ci sont de type volumineux (Vec2d, Collider). On pourrait donc passer tous leurs arguments par référence constante.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q1.8] Quelles méthodes parmi celles que l'on vous a demandées de coder ci-dessus vous semble-t-il judicieux de déclarer comme const ?

[Réponse R1.8] Aucune des méthodes ne doit modifier l'instance courante car elles ne font que des tests et renvoient des bools, donc toutes doivent être déclarées comme const.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q2.1] Quelle taille donnez-vous à cells\_?

[Réponse R2.1] cells\_ prends la taille du carré de nbCells\_.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q2.2] À quelles séquences d'étiquettes du fichier .json correspondent les tournures getAppConfig().world\_cells et getAppConfig().world\_size ?

[Réponse R2.2] getAppConfig().world\_size correspond à la séquence d'étiquettes ["simulation"]["world"]["default size"]

getAppConfig().world\_cells à ["simulation"]["world"]["default cells"]

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q2.3] Quelles méthodes seront invoquées pour réaliser ces initialisations et dans quel ordre?

[Réponse R2.3] On utilise dans l'ordre reloadConfig, reloadCacheStructure et updateCache.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q2.4] Quel est l'avantage d'utiliser les méthodes ci-dessus plutôt que

d'associer au flot de lecture, la chaîne de caractère "res/world.map" directement dans le code ?

[Réponse R2.4] On peut ainsi exécuter le code avec plusieurs fichiers (maps) sans avoir à modifier le code même à chaque changement de map.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q2.5] Que doit faire la méthode loadFromFile pour mettre à jour les attributs nécessaires au rendu graphique du terrain après l'initialisation de cells\_ depuis un fichier ?

[Réponse R2.5] Elle appelle les méthodes reloadCacheStructure() et updateCache().

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q2.6] Comment choisissez vous de représenter l'ensemble seeds\_?

[Réponse R2.4] Par un vector de Seed, où Seed est une structure comprenant un Vector2i position et un Kind seed.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.1] Pour le moment, dessiner un Env c'est simplement dessiner son terrain, lequel n'évolue pas une fois créé. Régénérer un Env c'est régénérer son terrain (au moyen de sa méthode reset). Comment proposez-vous de coder le corps des méthodes Env::drawOn, Env::update et Env::reset ?

[Réponse Q3.1] Ces méthodes devraient être codées en appelant les méthodes de la classe World pour modifier et mettre à jour le terrain (dessiner, updater et reseter).

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.2] Comment codez-vous cette méthode et où l'utiliserez vous dans le code écrit jusqu'ici pour la classe Env? Quel est le fichier qui sera utilisé concrètement pour initialiser le terrain? Enfin, quelle partie du code fourni fait en sorte que l'appui de la touche 'R' cause l'appel de la méthode reset de la classe Env?

[Réponse R3.2] loadWorldFromFile peut être codée en utilisant la méthode loadFromFile de la classe World, il est intéressant d'ajouter un catch pour l'erreur jetée par loadFromFile. Le fichier pour initialiser le terrain sera celui associé au fichier json utilisé. La partie du code fourni est située dans "Application.cpp" (l.519).

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.3] À quel(s) endroit(s) du code existant de World, l'algorithme précédent doit-il être appliqué ? Comment sera t-il mis en oeuvre dans votre code (nouvelle(s) méthode(s))?

[Réponse R3.3] Cet algorithme doit être appliqué dans la fonction step(), smooth(), reset(). On crée une nouvelle méthode set\_humidity().

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.4] La méthode updateCache parcourt déjà toutes les cellules (x,y) pour définir la transparence des sf::Quad des waterVertexes\_, rockVertexes\_ etc. Comment éviter un nouveau parcours de toutes les cellules (x,y) de humidityVertexes\_?

[Réponse R3.4] Pour éviter un nouveau parcours de toutes les cellules, il faut traiter les humidityVertexes\_ et les autres Vertexes dans la même boucle.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.5] Comment proposez-vous d'utiliser la classe Collider pour modéliser cet aspect ?

[Réponse R3.5] Flower est une sous-classe de Collider, on peut donc utiliser les mêmes méthodes et attributs de Collider.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.6] Si l'on tire au sort l'indice dans la méthode de dessin, la texture de la fleur va changer à chaque appel à la méthode de dessin. Comment faire pour assurer que le choix de la texture se fasse une fois pour toute lors de la création de la fleur?

[Réponse R3.6] Pour assurer que la texture d'une fleur ne change pas à chaque appel de drawOn, on crée un nouvel attribut de classe indice qu'on initialise avec le constructeur.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.7] Comment coder cette collection si l'on anticipe que plus tard, il peut y avoir différentes sortes de fleurs (p.ex. des fleurs contenant des toxines pour les abeilles)?

[Réponse R3.7] Il faut coder cette collection comme un tableau dynamique de pointeur sur des Flower pour avoir un comportement polymorphique des éléments du tableau.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.8] Les fleurs appartiennent à l'environnement (Env) et ne peuvent vivre en dehors de lui (cela n'a pas de sens d'avoir la même fleur partagée entre plusieurs environnements/terrains par exemple). Quelle incidence cela a t-il sur la destruction d'un Env?

[Réponse R3.8] Le destructeur de la classe Env doit être caractérisé par la suppression de toutes les fleurs de l'environnement. Pour cela, on crée dans Env la méthode delete\_flowers qui supprime toutes les instances de la classe Flower ainsi que les pointeurs pointant sur ces Flower.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.9] La régénération d'un environnement (reset ou le chargement du terrain depuis une fichier) implique de repartir d'un nouveau terrain et donc de supprimer aussi les fleurs. Comment suggérez-vous de procéder à ces suppressions (en évitant toute duplication de code) ?

[Réponse R3.9] Dans ces deux méthodes on réutilise la méthode delete\_flowers expliquée dans la réponse précédente.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.10] Quelle méthode existante doit être modifiée pour permettre le dessin des fleurs nouvellement ajoutées?

[Réponse R3.10] La méthode drawOn de Env doit être modifiée pour permettre le dessin de nouvelles fleurs.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.11] Où placeriez-vous une telle méthode?

[Réponse R3.11] Cette méthode devrait être placée dans Env.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.12] Quelle méthode de Env faut-il modifier et comment pour que l'évolution des fleurs deviennent visible lors de l'exécution du test graphique ?

[Réponse R3.12] Il faut modifier la méthode update pour qu'elle appelle la méthode update des Flower.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.13] Que devez-vous modifier et dans quelle classe pour faire en sorte que les fleurs de votre simulation meurent/disparaissent si leur quantité de pollen est/devient nulle?

[Réponse R3.13] Il faut modifier la méthode update de la classe Env pour qu'elle supprime les fleurs sans pollen.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.14] Quelles classes de votre conception actuelle serait-il bon de faire hériter de ces sous-classes ? Quel plus cela amène t-il à la conception ?

[Réponse R3.14] Les classes Env, Flower, World devraient hériter de la super-classe Drawable et les classes Env et Flower de la super-classe Updatable; cela permet un comportement polymorphique de ces classes.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.15 ] Un objet de type World (et par conséquent un objet de type Env) est volumineux. Il est important de se prémunir d'une copie accidentelle de tels objets. Quelle(s) solution(s) proposeriez-vous pour satisfaire cette contrainte?

[Réponse R3.15] On crée une méthode saveWorldToFile().

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q3.16] Quelle modification doit être faite dans Env et dans quelle méthode pour permettre au générateur d'effectivement générer des fleurs dans l'environnement?

[Réponse R3.16] Il faut modifier la méthode update de Env pour qu'elle appelle celle de FlowerGenerator et puisse générer automatiquement des fleurs dans le temps.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.1] Pourquoi à votre avis est-il nécessaire de modéliser l'ensemble des abeilles comme un ensemble de Bee\*?

[Réponse R4.1] L'ensemble des abeilles doit être modélisé comme un ensemble de Bee\* pour permettre un usage polymorphique des méthodes associées aux abeilles.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.2] Au vu de ce qui précède, comment proposez-vous de modéliser la classe Hive (héritage, attributs, méthodes , ...) ?

[Réponse R4.2] La classe Hive devait être modélisée en héritant de Drawable, Updatable et Collider. Ses méthodes seront celles

énoncées plus haut et l'addition d'une méthode permet de supprimer les abeilles.

Ses nouveaux attributs seront sa collection de Bees (un vector de Bee\*), et sa quantité de pollen. Elle serait dôtée d'un constructeur et d'un destructeur qui appelle

la méthode supprimant sa collection d'abeilles;

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.3] On souhaite ne pas permettre la copie d'une Hive ni l'affectation.

Quelle(s) solution(s) proposeriez-vous pour satisfaire cette contrainte?

[Réponse R4.3] Pour cela il faut supprimer l'opérateur d'affectation et le constructeur de copie.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.4] La liste d'attributs de Hive suggère que chaque ruche dispose de son propre ensemble d'abeilles.

Il n'est par ailleurs pas très réaliste de permettre aux abeilles de vivre sans être rattachées à une ruche particulière.

Une Hive peut donc être considérée responsable de la durée de vie de ses propres abeilles.

Quelle incidence cela a-t-il sur la destruction d'une ruche ?

[Réponse R4.4] La destruction d'une ruche entraine donc la destruction de toute la colonie d'abeilles y habitant.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.5] Peut-on permettre aux ruches de survivre à la destruction de l'environnement ?

[Réponse R4.5] Laisser les ruches exister en dehors de leur environnement n'a pas vraiment de sens, il faut donc

une méthode appelée par le destructeur de Env qui permettrait de détruire toutes les ruches.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.6] Comment proposez-vous de procéder pour empêcher que les fleurs puissent se propager ou être plantées dans

un endroit occupé par une ruche ?

[Réponse R4.6] On peut mettre en oeuvre une méthode qui teste s'il y a collision entre une Flower et l'ensemble des ruches, et l'appeler dans la méthode Env::addFlowerAt.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.7] Dessiner l'environnement implique maintenant de dessiner ses fleurs... et ses ruches. Régénérer

l'environnement implique la disparition des ruches et des fleurs existantes. Quelles modifications devez-vous

apporter au code existant pour mettre en oeuvre ces contraintes?

[Réponse R4.7] On doit appeler les méthodes DrawOn de Hive et de Flower dans la méthode DrawOn de Env; de même,

on doit créer des méthodes delete\_flowers et delete\_hives qui suppriment les ruches et fleurs existantes, et les appeler dans

la méthode reset de Env.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.8] Au vu de ce qui précède, comment proposez-vous de modéliser la classe Bee

(héritage, attributs, méthodes , ...) ?

[Réponse R4.8] La classe Bee devrait hériter de Drawable, Updatable et de Collider. Ses attributs sont

sa ruche, sa vitesse, son energie. Ses méthodes seront drawOn, update, une permettant de savoir si elle est morte,

une permettant le déplacement. Elle serait dôtée d'un constructeur et d'un destructeur.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.9] La méthode getConfig est amenée à être redéfinie dans les sous-classes.

Que cela implique-t-il dans son prototypage?

[Réponse R4.9] Cette méthode doit être prototypée comme virtuelle pure pour que les sous-classes soient obligées de la redéfinir afin d'être instanciables.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.10]  Comment permettre de retrouver la texture de l'abeille de façon polymorphique (sachant que

les sous-classes d'abeilles pourront chacune avoir une texture spécifique)?

[Réponse R4.10] C'est en redéfinissant getConfig avec les textures spécifiques au type d'abeille que cela se fait.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.11] Quel est l'avantage ici d'accéder aux paramètres au travers de la méthode getConfig() plutôt

que par des raccourcis d'écriture permis par getAppConfig()?

[Réponse R4.11] L'intérêt est justement d'avoir un comportement polymorphique s'adaptant plus tard

aux différents types d'abeilles.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.12] Quelles méthodes de quelles classes doivent être modifiées, et quelles modifications faut-il

y apporter, pour permettre de voir effectivement les abeilles voler ?

[Réponse R4.12] Il faut modifier update de Bee (en appelant la méthode Bee::move) et de Hive (en appelant la méthode Bee::update pour chaque abeille). En effet, Env::update appelle Hive::update qui appelle

alors Bee::update.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.13] Que devez-vous modifier et dans quelle classe pour faire en sorte que les abeilles

meurent/disparaissent si leur énergie devient nulle ?

[Réponse R4.13] Il faut modifier isDead de Bee qui vérifie le taux d'énergie et update de Hive qui

supprimera les abeilles mortes en appelant justement IsDead.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q4.14] Quelle est l'utilité d'avoir créé la classe FakeHive dans le programme de test HiveTest ?

[Réponse R4.14] On crée la classe FakeHive afin d'utiliser la méthode addBee de Hive de manière publique.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.1] Vous avez codé la méthode getConfig dans la classe Bee à l'étape précédente.

Comment modifier cette méthode et la redéfinir:

pour qu'elle permette d'accéder aux paramètres spécifiques d'une éclaireuse ou d'une butineuse

(["simulation"]["bees"]["scout"] et ["simulation"]["bees"]["worker"] dans les fichiers de configuration);

pour modéliser le fait que l'on ne sait pas définir ces paramètres pour une abeille générique

(et que de ce fait, les Bee ne soient plus instantiables en tant que telles);

pour que le dessin de chaque sous-type d'abeille se fasse avec sa texture spécifique, sans qu'il soit

nécessaire de redéfinir drawOn dans les sous-classes de Bee?

[Réponse R5.1] Il faut la definir comme virtuelle pure dans Bee pour que Bee devienne une classe

abstraite et ne soit plus instanciable. Il faut ensuite la redéfinir dans les sous-classes de Bee avec

la texture qui leur est spécifique en utilisant la fonction getValueConfig. On assure alors un usage polymorphique.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.2] Pourquoi la méthode getConfig ne peut-elle pas être utilisée dans les constructeurs ?

[Réponse Q5.2] On n'utilise pas la méthode getConfig dans les constructeurs car il est préférable de ne pas appeler de méthode virtuelle pure dans un constructeur.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.3] Quelles modifications devez vous apporter aux constructeurs de ScoutBee et WorkerBee

pour initialiser les états qui leur sont spécifiques?

[Réponse R5.3] Il faut ajouter un attribut au constructeur de Bee qui est l'ensemble des états possibles dans lesquelles

peuvent se trouver les abeilles. Dans les constructeurs des sous classes, il faut donc dans la liste d'initialisation

initialiser les états possibles respectifs.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.4] Sachant qu'une abeille peut aussi être amenée à oublier une position de fleur, comment modélisez-vous

la mémoire des abeilles. Indiquez dans quelle(s) classe(s) et avec quel(s) attributs. Y a t-il des retouches à faire

aux constructeurs, si oui lesquelles?

[Réponse R5.4] On peut créer une mémoire (Vec2d) et une valeur de vérité pour voir si une fleur est en mémoire (bool). Il faut ajouter

à la classe Bee ces deux attributs. Le constructeur de Bee les initialisera par (0.00, 0.00) et la valeur false comme l'abeille qui vient d'être créée n'a aucune fleur en mémoire.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.5] Quelle méthode doit impérativement être définie dans les sous-classes pour que les classes

WorkerBee et ScoutBee soient instantiables?

[Réponse R5.5] La méthode getConfig() étant virtuelle pure dans Bee, elle doit être définie dans les sous-classes WorkerBee et ScoutBee pour qu'elles soient instantiables.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.6] Quel type suggérez-vous de donner à ces attributs?

[Réponse R5.6] Un type string pour le mode de déplacement courant et un Vec2d pour symboliser la cible courante.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.7] Pourquoi ce traitement peut-il être entièrement mis en oeuvre dans la classe Bee alors que

les taux ont des valeurs spécifiques pour chaque sous-type d'abeille?

[Réponse R5.7] Il peut être mis en oeuvre dans Bee en utilisant getConfig qui, par un usage polymorphique, donnera les taux de perte correspondant à chaque type spécifique d'abeille.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.8] Les états utilisés pour modéliser le comportement des éclaireuses sont maintenant complètement

spécifiés (il y en aura d'autres pour les butineuses). Quelle incidence cela a t-il sur la "construction" ?

[Réponse R5.8] Maintenant, le constructeur de ScoutBee peut initialiser l'ensemble des états possibles pour l'abeille.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.9] : lors de quelle transition l'éclaireuse doit elle:

"vider" sa mémoire (oublier une fleur qu'elle aurait mémorisée);

se fixer sa ruche comme cible à atteindre.

[Réponse R5.9] Elle doit vider sa mémoire lors de la transition de quand elle est dans la ruche, à quand elle part à la recherche de fleurs.

Elle se fixe sa ruche comme cible à atteindre lors de la transition de la recherche de fleurs, à quand elle retourne à la ruche.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.10]: quelles autres méthodes et dans quelles classes proposez-vous d'introduire pour qu'une éclaireuse

mémorise la position d'une fleur de son champs de vision ? Quel avantage y a t'il à utiliser un pointeur sur objet

constant comme type de retour de getCollidingFlowerPosition(Collider const& body) ?

[Réponse R5.10] Il faut créer une méthode change\_memory dans Bee pour changer la mémoire de l'abeille, et change\_value\_memory dans Bee pour mettre la valeur de la mémoire de l'abeille à true.

On utilise un pointeur sur objet constant afin d'assurer que la fleur ne change pas entre les échanges de données.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.11] A quels moments et dans quelle(s) méthode(s), la butineuse doit elle

oublier qu'elle cible une fleur

se fixer pour cible la fleur qu'elle a en mémoire

se fixer pour cible sa propre ruche

passer en mode de déplacement aléatoire

passer en mode de déplacement ciblé ?

[Réponse R5.11] La butineuse doit :

oublier qu'elle cible une fleur : au moment où elle collecte le nectar de la fleur

se fixer pour cible la fleur qu'elle a en mémoire : au moment où elle part à la recherche de la fleur

se fixer pour cible sa propre ruche : au moment où elle retourne à la ruche

passer en mode de déplacement aléatoire : jamais

passer en mode de déplacement ciblé : au moment où elle part à la recherche de la fleur et quand elle rentre à la ruche

Tout cela dans la méthode onEnterState de WorkerBee.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question (ICC ;-))] Pourquoi le fait de commencer par répertorier les abeilles à l'intérieur de la ruche

permet-il potentiellement de réduire la complexité des traitements ? Réduira t-on ainsi la complexité au

pire cas ou plutôt en moyenne ?

[Réponse] Répertorier les abeilles à l'intérieur de la ruche permet de diminuer le nombre d'abeilles qui vont intéragir. On réduit ainsi la complexité au pire cas (quand toutes les abeilles sont comptées).


\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.12] à ce propos, savez-vous pourquoi les tests de type ont si mauvaise réputation?

[Réponse Q5.12] Les tests de type sont à éviter car ils affectent le principe même du polymorphime qui est de pouvoir partager des attributs et méthodes par héritage et non de tester

des types aussi explicitement.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q5.13] Où placez-vous ce traitement ?

[Réponse R5.13] Ce traitement est à placer dans Hive::update.

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q6.1] quelle(s) structure(s) de données choisissez-vous pour l'ensemble des graphes et l'ensemble des libellés de la classe Stats?

[Réponse Q6.1] On représente l'ensemble des graphes de la classe Stats par une std::map<int, std::unique\_ptr<Graph>> et

l'ensemble des libellés par une std::map<int, std::string> .

\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*

[Question Q6.2] Quelle méthodes prévoyez-vous d'ajouter/modifier et dans quelles classes pour réaliser les décomptes souhaités et construire les ensembles new\_data?

[Réponse Q6.2] : On ajoute deux attributs de classe Env nb\_scout et nb\_worker, puis les méthodes change\_nb\_scout et change\_nb\_worker dans Env pour changer le nombre total de ScoutBees

et de WorkerBees. On modifie alors les destructeurs des ScoutBees et WorkerBees en appelant ces méthodes respectives de Env et décrémenter le nombre total de ScoutBee et de WorkerBees de 1.

De même, on modifie la méthode addBee de Hive pour incrémenter ce nombre selon le type de l'abeille.
