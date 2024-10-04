# Solution logicielle de set-top box multimédia avec gestion des médias en C++ et intégration d'une interface graphique Java/Swing

**Nom du projet :** INF224 - Travaux Pratiques C++/Objet et Java/Swing

**Auteur :** Tarcisio DA SILVA BUENO

**Objectif du projet :** Créer l'ébauche du logiciel d'une set-top box multimédia permettant de jouer des vidéos, des films, d'afficher des photos, etc.

<div style="display: flex; justify-content: center;">
  <img src="https://github.com/user-attachments/assets/ccb187c2-72e6-4dc0-89d8-5631811ed508" alt="image" width="500" style="margin: 10px;"/>
  <img src="https://github.com/user-attachments/assets/06c4f2f0-cc3e-4148-97a7-35ff3d7179b4" alt="image" width="500" style="margin: 10px;"/>
</div>

**À propos de ce fichier README :** Ce fichier README a été créé dans le cadre du projet inf224. Il vise à fournir des informations essentielles sur le contenu du projet, y compris **les excercises traitées**, **les réponses correspondantes**, ainsi que tout commentaire jugé utile. Les sections suivantes détaillent les aspects traités dans ce document.

# Travaux Pratiques C++/Objet

## 1e Etape: Démarrage

## 2e Etape: Classe de base

Le symbole &: Dans std::ostream & indique que le paramètre est une référence à un objet std::ostream.

Le mot-clé const: En C++ est utilisé pour indiquer qu'une variable ne peut pas être modifiée après sa déclaration, ce qui signifie que sa valeur est constante et ne peut pas être changée.  Lorsqu'il est utilisé dans une déclaration de fonction (après la liste des paramètres et avant le corps de la fonction), const signifie que la fonction ne modifie pas l'état de l'objet sur lequel elle est appelée. 

## 3e Etape: Programme de test

## 4e Etape: Photos et videos

**Comment appelle-t'on ce type de méthode et comment faut-il les déclarer ?**

Le type de méthode est appelé une "méthode purement virtuelle" en C++.

Pour déclarer une méthode comme purement virtuelle, il faut utiliser le mot-clé virtual suivi de = 0 à la fin de la déclaration de la méthode. Par exemple :

```
virtual void maMethode() const = 0;
```

**Si vous avez fait ce qui précède comme demandé, il ne sera plus possible d'instancer des objets de la classe de base. Pourquoi ?**

Lorsqu'une classe contient au moins une méthode purement virtuelle, cette classe est considérée comme une classe abstraite. Les classes abstraites ne peuvent pas être instanciées directement, elles sont destinées à être héritées par d'autres classes.

## 5e Etape: Traitement uniforme (en utilisant le polymorphisme)

**Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ?**

La propriété caractéristique de l'orienté objet qui permet de traiter de manière uniforme une liste comprenant à la fois des photos et des vidéos sans avoir à se préoccuper de leur type est le polymorphisme. Le polymorphisme permet à une classe dérivée d'hériter des méthodes et des attributs d'une classe de base, et de les redéfinir si nécessaire.

**Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ?**

En C++, pour utiliser le polymorphisme, il est nécessaire de déclarer les méthodes que vous souhaitez redéfinir dans les classes dérivées comme virtual dans la classe de base. Si vous voulez que la méthode soit purement virtuelle (c'est-à-dire qu'elle doit être redéfinie dans toutes les classes dérivées), vous pouvez utiliser virtual suivi de = 0.

**Quel est le type des éléments du tableau : le tableau doit-il contenir des objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.**

le tableau doit contenir des pointeurs vers des objets. Cela permet de traiter de manière uniforme les objets de différentes classes dérivées.

En Java, tous les objets sont manipulés par référence, ce qui signifie que lorsque vous créez un objet et l'assignez à une variable ou le placez dans un tableau, vous travaillez avec une référence à l'objet, pas l'objet lui-même. Donc, le polymorphisme fonctionne automatiquement. 

## 6e étape. Films et tableaux


## 7e étape. Destruction et copie des objets

Ci-dessous est le résultat de la commande:

```
valgrind --leak-check=full ./myprog
```

Resultat:

```
==682== HEAP SUMMARY:
==682==     in use at exit: 0 bytes in 0 blocks
==682==   total heap usage: 26 allocs, 26 frees, 75,351 bytes allocated
==682==
==682== All heap blocks were freed -- no leaks are possible
```

**Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait pas de fuite mémoire quand on détruit les objets ? Modifiez le code de manière à l'éviter.**

Parmi les classes précédemment écrites, la seule qui a le potentiel de causer des fuites de mémoire est la classe Film, car il y a pas mal de "new" qui est utilisé. En tout cas, comme on peut voir le résultat du Valgrind, il n'y a pas de fuites de mémoire, ce qui veut dire que la mémoire a été bien utilisée. Pour obtenir ce résultat, il fallait écrire le destructeur comme montré ci-dessous :

```
    ~Film()
    {
        delete[] chapitres;
    }

```

**La copie d'objet peut également poser problème quand ils ont des variables d'instance qui sont des pointeurs. Quel est le problème et quelles sont les solutions ? Implementez-en une.**

Le problème se produit lorsque vous effectuez une copie superficielle d'un objet qui a des pointeurs comme variables d'instance. Dans une copie superficielle, les pointeurs sont copiés, pas les objets auxquels ils pointent. Cela signifie que la copie et l'original pointent vers le même objet. Si l'original est détruit et que sa mémoire est libérée, la copie se retrouve avec un pointeur vers de la mémoire qui a été libérée, ce qui peut entraîner des erreurs.

La solution à ce problème est de faire une copie profonde. Dans une copie profonde, une nouvelle mémoire est allouée pour la copie, et l'objet vers lequel pointe l'original est copié dans la nouvelle mémoire. Cela signifie que la copie et l'original sont complètement indépendants.

Pour implémenter une copie profonde, il faut écrire un construteur de copie:

```
    Film(const Film &original) : Video(original), taille(original.taille) {
        chapitres = new int[taille];
        for(int i = 0; i < taille; i++){
            chapitres[i] = original.chapitres[i];
        }
    }
```
## 8e étape. Créer des groupes

**On rappelle aussi que la liste d'objets doit en fait être une liste de pointeurs d'objets. Pourquoi ? Comparer à Java.**

La première raison pour laquelle la liste d'objets doit être une liste de pointeurs est de permettre le polymorphisme.

La deuxième raison est la suivante :

En C++, lorsque vous créez une liste d'objets (comme std::list<Base>), les objets sont stockés directement dans la liste. Si vous retirez un objet de la liste ou si la liste est détruite, l'objet est également détruit. C'est différent de Java, où tous les objets non primitifs sont en fait des références (similaires aux pointeurs en C++). Donc, lorsque vous avez une liste d'objets en Java, vous avez en fait une liste de références. Lorsque la liste est détruite, les références sont détruites, mais pas les objets auxquels elles font référence.

Lorsque l'on utilise une liste de pointeurs, la liste contient des pointeurs vers les objets, et non les objets eux-mêmes. Lorsqu'un pointeur est retiré de la liste ou que la liste est détruite, seul le pointeur est détruit, pas l'objet auquel il pointe.

## 10e étape. Gestion cohérente des données

Pour garantir que seules certaines classes peuvent créer des instances d'une autre classe, il faut rendre les constructeurs protected, puis déclarer la classes DataBase comme friend.

**Question additionnelle**

La méthode "Supprimer" a été ajoutée.

## 11e étape. Client / serveur

Le serveur accepte les commandes suivantes :

- `search multimedia <nom>` : Recherche un objet multimédia par son nom.
- `search group <nom>` : Recherche un groupe par son nom.
- `play <nom>` : Joue un objet multimédia par son nom.
- `list` : Liste tous les objets multimédias.

Chaque commande doit être envoyée au serveur via TCP sur le port 3331.

**Questions additionnelles**

La command 'list' a été ajouté. 

## 12e étape. Sérialisation / désérialisation

La sérialisation et la désérialisation ont été implémentées. Pour les tester, le code suivant a été ajouté dans le fichier "main.cpp":

```c++
    // Sauvegarde des objets multimédias dans un fichier
    if (!db.saveAll("multimedia.txt")) {
        std::cerr << "Échec de l'enregistrement" << std::endl;
        return 1;
    }

    // Lecture des objets multimédias à partir du fichier
    if (!db.readAll("multimedia.txt")) {
        std::cerr << "Échec de la lecture" << std::endl;
        return 1;
    }
```

## 13e étape. Traitement des erreurs

Voici les erreurs qui ont été traité:

- si le tableau de durées d'un Film a une taille nulle ou inférieure à zéro
- si on crée plusieurs groupes ou objets ayant le même nom

La fonction vérifie si un objet multimédia avec le même nom existe déjà dans la base de données (Multimedia) ou si la taille du tableau de chapitres est nulle ou négative. Si l'une de ces conditions est vraie, la fonction retourne un BasePointer nul, indiquant que la création du film a échoué. 
La décision de retourner un BasePointer nul simplifie la gestion des erreurs lors de la création d'un film, tout en facilitant la création de messages à envoyer au client en cas d'échec de la création. 

- si on supprime un groupe ou un objet qui n'existe pas

La fonction vérifie d'abord si l'objet multimédia ou le groupe portant le nom spécifié existe dans la base de données (Multimedia ou Groupes). Si c'est le cas, elle le supprime. Sinon, elle affiche un message indiquant que l'objet n'a pas été trouvé. Cela assure que l'utilisateur est informé lorsque la suppression d'un objet ou d'un groupe inexistant est tentée.

# Java/Swing

Dans cette étape, une interface graphique Java/Swing a été développée pour interagir avec le logiciel créé lors du TP C++/Objet. Elle comprend une fenêtre principale avec des interacteurs, des menus, une barre d'outils, et des actions. De plus, l'interaction client/serveur a été mise en place pour rechercher et jouer des objets multimédias sur le serveur C++ depuis l'interface graphique Java. Une bouton pour retourner la liste des objets présents dans la base de données a également été ajouté.

## 1ere Etape: Fenêtre principale et quelques interacteurs

## 2eme Etape: Menus, barre d'outils et actions

## 3eme Etape: Interaction client/serveur

**Instructions :**

Fonctionnalités disponibles : "Rechercher média", "Rechercher groupe", "Jouer", "Finaliser" et "Lister".

Pour utiliser ces fonctionnalités, saisissez le média ou groupe que vous souhaitez jouer/rechercher ou rechercher. Ensuite, appuyez sur le bouton correspondant à l'action que vous souhaitez effectuer : "Rechercher média/groupe" ou "Jouer".

Pour consulter la liste des éléments présents dans la base de données, appuyez sur le bouton "Lister".

Pour finaliser, appuyez sur le bouton "Finaliser".

## 4eme Etape : Créer un Makefile

