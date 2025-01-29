# Projet de Vision Basé sur une Caméra USB

Ce projet, réalisé dans le cadre du cours **ELE4205 - Système d’exploitation et interfaces matérielles**, consiste à développer un système basé sur une caméra USB connectée à une Odroid-C2. Il combine des concepts de traitement d'images, de communication client/serveur via TCP/IP, et d'intégration matérielle.

## Fonctionnalités Principales

1. **Capture vidéo** : Enregistrer des vidéos de 5 secondes en différents formats et résolutions.
2. **Client/Serveur TCP** : Transférer les images de l'Odroid-C2 au poste de travail pour affichage.
3. **Changement de résolution** : Permettre de choisir dynamiquement parmi plusieurs résolutions.
4. **Intégration matérielle** : Utiliser une résistance photosensible et un bouton pour ajouter des fonctionnalités.
5. **Détection de codes QR** : Analyser et annoter les images contenant des codes QR.
6. **Transmission Morse** : Décoder le contenu des codes QR et les transmettre en code Morse.

---

## Livrables

1. **Livrable 1** : Capture vidéo et sauvegarde en fichier `.avi`.
2. **Livrable 2** : Transmission d'images via une connexion TCP/IP.
3. **Livrable 3** : Gestion dynamique des résolutions via un menu interactif.
4. **Livrable 4** : Lecture de capteurs (lumière et bouton) pour modifier le comportement du serveur.
5. **Livrable 5** : Décodage et annotation des codes QR sur les images.
6. **Livrable 6** : Transmission et interprétation des données QR sous forme de code Morse.

---

## Compilation et Exécution

### Prérequis

- **OpenCV 3.1.0** installé sur l'Odroid-C2.
- **ZBAR** installé sur l'Odroid-C2.
- **Docker** pour configurer l'environnement.
- **CMake** pour la gestion de la compilation.


### Instructions de Compilation

1. **Cloner le projet** :
   ```bash
   git clone <url_du_dépôt>
   cd gX-vlsi4YY-odroid

2. **Configurer avec CMake** :
    mkdir build && cd build
    cmake ..
    make

3. **Lancer le programme sur l'Odroid-C2** :
    ./build/Projet

4. **Lancer le programme sur le poste de travail** :
    ./build/Client
