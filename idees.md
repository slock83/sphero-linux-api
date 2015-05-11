Sphero :

Le Sphero doit pouvoir se déplacer dans la pièce en optimisant sa trajectoire.
Considérant un ensemble de sphero, ils doivent se déplacer de manière logique et coordonnée.


Idée :

Les sphero sont placés toujours plus ou moins au même endroit dans la pièce (contre un mur, dans un coin), ce qui leur permet d'avoir un référentiel de base constant.
Au début, ils se déplacent de manière totalement aléatoire. Grâce aux collisions, ils construisent une carte des lieux en établissant les points où ils ne peuvent pas aller.
En replaçant les spheros toujours au même endroit*, au fur et à mesure des jours, les sphero connaîtront mieux l'espace et des stratégies pourront être mises en place.

* Pour replacer le groupe de sphéro toujours au même endroit, c'est pas très compliqué.
Mais il faut repérer l'orientation de chaque sphero et aligner les spheros de sorte qu'il n'y ait qu'une translation du plan à faire.


Mais comment on fait alors ? :

Pourquoi ne pas utiliser un graphe pour stocker les points de collision ?
    -       -	parcourir l'espace en dessinant des triangles de manière à repérer les espaces (formés par l'enveloppe du graphe) ?

Pouvoir repérer que l'utilisateur a saisi un sphero ? Peut être avec l'axe z de l'acceléromètre ?
