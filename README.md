# 4e Etape: Photos et videos

**Comment appelle-t'on ce type de méthode et comment faut-il les déclarer ?**

Le type de méthode que vous décrivez est appelé une "méthode purement virtuelle" en C++.

Pour déclarer une méthode comme purement virtuelle, vous utilisez le mot-clé virtual suivi de = 0 à la fin de la déclaration de la méthode. Par exemple :

"""
virtual void maMethode() const = 0;
"""

**Si vous avez fait ce qui précède comme demandé, il ne sera plus possible d'instancer des objets de la classe de base. Pourquoi ?**

Lorsqu'une classe contient au moins une méthode purement virtuelle, cette classe est considérée comme une classe abstraite. Les classes abstraites ne peuvent pas être instanciées directement, elles sont destinées à être héritées par d'autres classes.

# 5e Etape: Traitement uniforme (en utilisant le polymorphisme)

**Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ?**

La propriété caractéristique de l'orienté objet qui permet de traiter de manière uniforme une liste comprenant à la fois des photos et des vidéos sans avoir à se préoccuper de leur type est le polymorphisme. Le polymorphisme permet à une classe dérivée d'hériter des méthodes et des attributs d'une classe de base, et de les redéfinir si nécessaire.

**Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ?**

En C++, pour utiliser le polymorphisme, il est nécessaire de déclarer les méthodes que vous souhaitez redéfinir dans les classes dérivées comme virtual dans la classe de base. Si vous voulez que la méthode soit purement virtuelle (c'est-à-dire qu'elle doit être redéfinie dans toutes les classes dérivées), vous pouvez utiliser virtual suivi de = 0.

**Quel est le type des éléments du tableau : le tableau doit-il contenir des objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.**

le tableau doit contenir des pointeurs vers des objets de ses classes dérivées. Cela permet de traiter de manière uniforme les objets de différentes classes dérivées.

En Java, tous les objets sont manipulés par référence, ce qui signifie que lorsque vous créez un objet et l'assignez à une variable ou le placez dans un tableau, vous travaillez avec une référence à l'objet, pas l'objet lui-même.

# 6e étape. Films et tableaux


# 7e étape. Destruction et copie des objets

Ci-dessous est le résultat de la commande valgrind --leak-check=full ./myprog.

"""
==682== HEAP SUMMARY:
==682==     in use at exit: 0 bytes in 0 blocks
==682==   total heap usage: 26 allocs, 26 frees, 75,351 bytes allocated
==682==
==682== All heap blocks were freed -- no leaks are possible
"""

**Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait pas de fuite mémoire quand on détruit les objets ? Modifiez le code de manière à l'éviter.**

Parmi les classes précédemment écrites, la seule qui a le potentiel de causer des fuites de mémoire est la classe Film, car il y a pas mal de "new" qui est utilisé. En tout cas, comme on peut voir le résultat du Valgrind, il n'y a pas de fuites de mémoire, ce qui veut dire que la mémoire a été bien utilisée. Pour obtenir ce résultat, il fallait écrire le destructeur comme montré ci-dessous :

"""
    ~Film()
    {
        delete[] chapitres;
    }

"""

**La copie d'objet peut également poser problème quand ils ont des variables d'instance qui sont des pointeurs. Quel est le problème et quelles sont les solutions ? Implementez-en une.**

Le problème se produit lorsque vous effectuez une copie superficielle d'un objet qui a des pointeurs comme variables d'instance. Dans une copie superficielle, les pointeurs sont copiés, pas les objets auxquels ils pointent. Cela signifie que la copie et l'original pointent vers le même objet. Si l'original est détruit et que sa mémoire est libérée, la copie se retrouve avec un pointeur vers de la mémoire qui a été libérée, ce qui peut entraîner des erreurs.

La solution à ce problème est de faire une copie profonde. Dans une copie profonde, une nouvelle mémoire est allouée pour la copie, et l'objet vers lequel pointe l'original est copié dans la nouvelle mémoire. Cela signifie que la copie et l'original sont complètement indépendants.

Pour implémenter une copie profonde, il faut écrire un construteur de copie. 