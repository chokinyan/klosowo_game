# KLOSOWO GAME

Auteur original : Cyril Meyer
Licence : [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/)

Projet réalisé dans le cadre de l'Immersion 2026 (ENSISA / UHA), semaine du 7 au 18
septembre 2026. Jeu de plateau opposant deux camps (bleu / rouge), jouable en local,
en réseau (UDP), en manuel ou face à une IA.


## Aperçu du jeu

Plateau de 7 lignes × 11 colonnes. Chaque camp démarre avec un roi et 9 soldats,
positionnés en miroir dans deux coins opposés du plateau ; les deux cases-cités
(une par camp) sont fixes et jamais contrôlables. Une case spéciale par ligne
(la "diagonale") peut recevoir une barricade — une par camp, interdite dans ou à
côté de son propre camp de départ.

Un coup déplace un pion en ligne ou en colonne ; un obstacle sur le trajet bloque
le déplacement. Le score de fin de partie combine le nombre de cases contrôlées
(hors cités) et le nombre de soldats encore vivants pour chaque camp.


## Prérequis

Le sujet impose gcc (pas clang) et GTK4 (pas GTK3), sur un Linux type Ubuntu.

```bash
sudo apt update
sudo apt install build-essential gcc pkg-config libgtk-4-dev doxygen
```
