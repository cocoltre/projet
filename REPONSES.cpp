    [Question Q1.1] L'algorithme de «clamping» de la position devra être appliqué dans d'autres contextes que celui de la construction.
    Comment le coder pour que sa réutilisation dans une autre méthode de
    la classe Collider n'implique pas de duplication de code ?

    [Reponse R1.1] Pour éviter la duplication de code on crée une nouvelle méthode clamp.

    *************************************************************************************************

    [Question Q1.2] Comment utiliser des boucles pour éviter d'avoir un
    code trop répétitif dans la mise en oeuvre de cet algorithme ?

    [Reponse R1.2] On peut utiliser une boucle sur un array de positions possibles afin de trouver la distance la plus courte entre deux points.

    *************************************************************************************************

    [Question Q1.3] Quels arguments de méthodes, parmi celles qu'il vous été demandé de coder ci-dessus, vous semble-t-il judicieux de passer par référence constante ?

    [Reponse R1.3] Les méthodes ayant des arguments pouvant être passés en références constantes sont les méthodes directionTo, distanceTo et move car elles n'ont pas la vocation de changer les valeurs de leurs arguments et leurs arguments sont de type volumineux (Vec2d, Collider).

    *************************************************************************************************

    [Question Q1.4] Quelles méthodes parmi celles que l'on vous a demandé de coder ci-dessus vous semble-t-il judicieux de déclarer comme const ?

    [Réponse R1.4] Les méthodes directionTo et distanceTo car elles ne modifient aucun attribut.

    *************************************************************************************************

    [Question Q1.5] Comment coder les trois opérateurs précédemment décrits en évitant toute duplication de code dans le fichier Collider.cpp ?

    [Réponse R1.5] Il suffit de se servir des méthodes isColliderInside, isColliding, isPointInside définies juste avant afin de coder les trois opérateurs.

    *************************************************************************************************

    [Question Q1.6] Quelle surcharge choisissez-vous pour les opérateurs qu'il vous a été demandé de coder (interne ou externe) et comment justifiez-vous ce choix ?

    [Réponse R1.6] Il est utile de choisir une surcharge interne car les quatre opérateurs ont besoin d'attributs de la classe pour fonctionner et donc cela permet de ne pas passer par des getters.

    *************************************************************************************************

    [Question Q1.7] Quels arguments de méthodes, parmi celles qu'il vous été demandé de coder ci-dessus, vous semble-t-il judicieux de passer par référence constante ?

    [Réponse R1.7] Toutes les méthodes ci-dessus n'ont pas besoin (et de doivent pas) modifier les arguments qu'ils recoivent, d'autant que ceux-ci sont de type volumineux (Vec2d, Collider). On pourrait donc passer tous leurs arguments en référence constante.

    *************************************************************************************************

    [Question Q1.8] Quelles méthodes parmi celles que l'on vous a demandées de coder ci-dessus vous semble-t-il judicieux de déclarer comme const ?

    [Réponse R1.8] Aucune des méthodes ne doivent modifier l'instance courante car elles ne font que des tests et renvoient des bools, donc toutes doivent être déclarées comme const.

    *************************************************************************************************

    [Question Q2.1] Quelle taille donnez-vous à cells_?

    [Réponse R2.1] cells_ prends la taille du carré de nbCells_.

    *************************************************************************************************

    [Question Q2.2] À quelles séquences d'étiquettes du fichier .json correspondent les tournures getAppConfig().world_cells et getAppConfig().world_size ?

    [Réponse R2.2] getAppConfig().world_size correspond à la séquence d'étiquettes
    ["simulation"]["world"]["default size"]
            getAppConfig().world_cells à ["simulation"]["world"]["default cells"]

    *************************************************************************************************

    [Question Q2.3] Quelles méthodes seront invoquées pour réaliser ces initialisations et dans quel ordre?

    [Réponse R2.3] On utilise dans l'ordre reloadConfig, reloadCacheStructure et updateCache.

    *************************************************************************************************

    [Question Q2.4] Quel est l'avantage d'utiliser les méthodes ci-dessus plutôt que
    d'associer au flot de lecture, la chaîne de caractère "res/world.map" directement dans le code ?

    [Réponse R2.4] On peut ainsi exécuter le code avec plusieurs fichiers (maps) sans avoor à modifier le code même.
    
    *************************************************************************************************

    [Question Q2.5] Que doit faire la méthode loadFromFile pour mettre à jour les attributs nécessaires au rendu graphique du terrain après l'initialisation de cells_ depuis un fichier ?

    [Réponse R2.5] Elle appelle les méthodes reloadCacheStructure() et updateCache().

    *************************************************************************************************

    [Question Q2.6] Comment choisissez vous de représenter l'ensemble seeds_?

    [Réponse R2.4] Par un vector de Seed, où Seed est une structure comprenant un Vector2i position et un Kind seed.

    *************************************************************************************************

    [Question Q3.1] Pour le moment, dessiner un Env c'est simplement dessiner son terrain, lequel n'évolue pas une fois créé. Régénérer un Env c'est régénérer son terrain (au moyen de sa méthode reset). Comment proposez-vous de coder le corps des méthodes Env::drawOn, Env::update et Env::reset ?

    [Réponse Q3.1] Ces méthodes devraient être codées en appelant les méthodes de la classe World pour modifier et mettre à jour le terrain (dessiner, updater et reseter).

    *************************************************************************************************

    [Question Q3.2] Comment codez-vous cette méthode et où l'utiliserez vous dans le code écrit jusqu'ici pour la classe Env? Quel est le fichier qui sera utilisé concrètement pour initialiser le terrain? Enfin, quelle partie du code fourni fait en sorte que l'appui de la touche 'R' cause l'appel de la méthode reset de la classe Env?

    [Réponse R3.2] loadWorldFromFile peut être codée en utilisant la méthode loadFromFile de la classe World, il est intéressant d'ajouter un catch pour l'erreur jeté par loadFromFile. Le fichier pour initialiser le terrain sera le dernier sauvegardé (??). La partie du code fourni est située dans "Application.cpp" (l.519).

    *************************************************************************************************

    [Question Q3.3] À quel(s) endroit(s) du code existant de World, l'algorithme précédent doit-il être appliqué ? Comment sera t-il mis en oeuvre dans votre code (nouvelle(s) méthode(s))?

    [Réponse R3.3] Cet algorithme doit être appliqué dans la fonction step(), smooth(), reset(). On crée une nouvelle méthode set_humidity().

    *************************************************************************************************

    [Question Q3.4] La méthode updateCache parcourt déjà toutes les cellules (x,y) pour définir la transparence des sf::Quad des waterVertexes_, rockVertexes_ etc. Comment éviter un nouveau parcours de toutes les cellules (x,y) de humidityVertexes_?

    [Réponse R3.4] On évite un nouveau parcours de toutes les cellules, il faut traiter les humidityVertexes_ et les autresVertexes dans la même boucle.

    *************************************************************************************************

    [Question Q3.5] Comment proposez-vous d'utiliser la classe Collider pour modéliser cet aspect ?

    [Réponse R3.5] Flower est une sous)-classe de Collider, on peut donc utiliser les mêmes méthodes et attributs de Collider.

    *************************************************************************************************

    [Question Q3.6] Si l'on tire au sort l'indice dans la méthode de dessin, la texture de la fleur va changer à chaque appel à la méthode de dessin. Comment faire pour assurer que le choix de la texture se fasse une fois pour toute lors de la création de la fleur?

    [Réponse R3.6] Pour assurer que la texture d'une fleur ne change pas à chaque appel de drawOn, on crée un nouvel attribut indice qu'on initialise avec le constructeur.

    *************************************************************************************************

    [Question Q3.7] Comment coder cette collection si l'on anticipe que plus tard, il peut y avoir différentes sortes de fleurs (p.ex. des fleurs contenant des toxines pour les abeilles)?

    [Réponse R3.7] Il faut coder cette collection comme un tableau dynamique de pointeur sur des Flower pour avoir un comportement polymorphique des éléments du tableau.

    *************************************************************************************************

    [Question Q3.8] Les fleurs appartiennent à l'environnement (Env) et ne peuvent vivre en dehors de lui (cela n'a pas de sens d'avoir la même fleur partagée entre plusieurs environnements/terrains par exemple). Quelle incidence cela a t-il sur la destruction d'un Env?

    [Réponse R3.8] Le destructeur de la classe Env doit être caractérisé par la suppression de toutes les fleurs de l'environnement. Pour cela, on crée dans Env la méthode delete_flowers qui supprime toutes les instances de la classe Flower ainsi que les pointeurs pointant sur ces Flower.

    *************************************************************************************************

    [Question Q3.9] La régénération d'un environnement (reset ou le chargement du terrain depuis une fichier) implique de repartir d'un nouveau terrain et donc de supprimer aussi les fleurs. Comment suggérez-vous de procéder à ces suppressions (en évitant toute duplication de code) ?

    [Réponse R3.9] Dans ces deux méthodes on réutilise la méthode delete_flowers expliquée dans la réponse précédente.

    *************************************************************************************************

    [Question Q3.10] Quelle méthode existante doit être modifiée pour permettre le dessin des fleurs nouvellement ajoutées?

    [Réponse R3.10] La méthode drawOn de Env doit être modifiée pour permettre le dessin de nouvelles fleurs.

    *************************************************************************************************

    [Question Q3.11] Où placeriez-vous une telle méthode?

    [Réponse R3.11] Cette méthode devrait être placée dans Env.

    *************************************************************************************************

    [Question Q3.12] Quelle méthode de Env faut-il modifier et comment pour que l'évolution des fleurs deviennent visible lors de l'exécution du test graphique ?

    [Réponse R3.12] Il faut modifier la méthode update pour qu'elle prenne maintenant en compte la variable dt de temps en conséquence.

    *************************************************************************************************

    [Question Q3.13] Que devez-vous modifier et dans quelle classe pour faire en sorte que les fleurs de votre simulation meurent/disparaissent si leur quantité de pollen est/devient nulle?

    [Réponse R3.13] Il faut modifier la méthode update de la classe Env pour qu'elle supprime les fleurs sans pollen.

    *************************************************************************************************

    [Question Q3.14] Quelles classes de votre conception actuelle serait-il bon de faire hériter de ces sous-classes ? Quel plus cela amène t-il à la conception ?

    [Réponse R3.14] Les classes Env, Flower, World devraient hériter de ces super-classes, cela permet un comportement polymorphique de ces classes.

    *************************************************************************************************

    [Question Q3.15 ] Un objet de type World (et par conséquent un objet de type Env) est volumineux. Il est important de se prémunir d'une copie accidentelle de tels objets. Quelle(s) solution(s) proposeriez-vous pour satisfaire cette contrainte?

    [Réponse R3.15] On crée une méthode saveWorldToFile().

    *************************************************************************************************

    [Question Q3.16] Quelle modification doit être faite dans Env et dans quelle méthode pour permettre au générateur d'effectivement générer des fleurs dans l'environnement?

    [Réponse R3.16] Il faut modifier la méthode update de Env pour qu'elle appelle celle de FlowerGenerator et puisse générer automatiquement des fleurs dans le temps.
