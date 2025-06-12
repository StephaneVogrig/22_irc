# ft_irc

Un serveur IRC (Internet Relay Chat) simple et fonctionnel, développé en C++ dans le cadre du cursus de l'école 42. Ce projet met en œuvre les fonctionnalités de base du protocole IRC pour permettre la communication en temps réel entre plusieurs clients et la gestion de canaux de discussion. En bonus, un bot météo indépendant a été realisé. Nous avons utilisé HexChat comme client de référence pour le développement et les tests.

*Réalisé par [Gaël Cannaud](https://github.com/Helco18) et [Stéphane Vogrig](https://github.com/StephaneVogrig).*

---

### Table des matières
1.  [Fonctionnalités](#fonctionnalités)
2.  [Stack Technique](#stack-technique)
3.  [Installation et Lancement](#installation-et-lancement)
4.  [Comment utiliser](#comment-utiliser)
5.  [Configuration du Bot](#configuration-du-bot)
6.  [Licence](#licence)
7.  [Liens utiles](#liens-utiles)

---

## Fonctionnalités

Notre serveur IRC implémente les aspects suivants du protocole :

* ✅ **Authentification** des utilisateurs par mot de passe (`PASS`).
* ✅ **Gestion des utilisateurs** : choix et modification du pseudonyme (`NICK`), identification (`USER`, `WHO`).
* ✅ **Canaux de discussion** :
    * Rejoindre et quitter un canal (`JOIN`, `PART`).
    * Envoyer des messages à tous les membres d'un canal.
    * Lister les canaux existants (`LIST`).
	* Gérer les droits et accés (`MODE`, `INVITE`, `TOPIC`, `KICK`)
* ✅ **Messages privés** (`PRIVMSG`).
* ✅ **Messages spéciaux** (`NOTICE`).
* 🤖 **Bot Météo** : Obtenez la météo d'une ville en envoyant un message privé au Bot ou sur un canal dedie.

## Stack Technique

* **Langage :** C++98
* **API Réseau :** Sockets BSD
* **Multiplexage I/O :** `poll()`
* **Build System :** `make`

## Installation et Lancement

### Serveur
1.  **Clonez le dépôt :**
    ```sh
    git clone git@github.com:StephaneVogrig/22_irc.git
    cd 22_irc
    ```

2.  **Compilez le projet :**
    ```sh
    make
    ```

3.  **Lancez le serveur :**
	```sh
	./ircserv <port> <password>
	```
	- `<port>`: Le port sur lequel le serveur écoutera (ex: 6667).
	- `<password>`: Le mot de passe requis pour se connecter au serveur.

### Bot meteo
Le bot est indépendant du serveur et nécessite une clé d'API pour fonctionner. Il peut se connecter à d'autres serveurs que le nôtre.

1.  **Compilez le bot :**
	Dans un deuxieme terminal:
	```sh
	make bot
	```

2.  **Creez le fichier `api_key` :**
	- Créez un fichier nommé `api_key` à la racine du projet (au même niveau que l'exécutable `meteobot`).
	- Obtenez une clé d'API gratuite sur [AccuWeather api](https://developer.accuweather.com/).
		- Créez un compte et allez dans la section "My Apps".
		- Créez une nouvelle application pour générer une clé.
	- Copiez-collez cette clé dans le fichier api_key. Le bot est maintenant prêt !

3.  **Lancez le bot :**
    ```sh
    ./meteobot <adresse> <port> <password>
    ```
    - `<adresse>`: L'adresse du serveur' (ex: 127.0.0.1).
    - `<port>`: Le port sur lequel le serveur écoutera (ex: 6667).
    - `<password>`: Le mot de passe requis pour se connecter au serveur.

Nous avons choisi [AccuWeather api](https://developer.accuweather.com/) car il permet d'obtenir des données météo sans nécessiter le protocole ssl. À ce jour (12/06/2025), une clé permet gratuitement de réaliser 50 requêtes par jour. Un autre site gratuit avait été trouvé : [prevision_meteo](www.prevision-meteo.ch/services). Mais il nécessite l'utilisation du protocole ssl (limites du sujet).
## Comment utiliser

### Avec un client IRC (Hexchat, WeeChat...)

1.  Ajoutez un nouveau réseau dans votre client.
2.  Entrez l'adresse du serveur : `127.0.0.1` (ou l'IP de la machine hôte).
3.  Entrez le port que vous avez spécifié au lancement (ex: `6667`).
4.  Dans les options de connexion, spécifiez le mot de passe du serveur.
5.  Connectez-vous et commencez à discuter !

### Avec `nc` (Netcat)

Si le serveur est lancé sur le port 6667 avec le mot de passe "pass", vous pouvez vous connecter comme suit :

```sh
nc -C 127.0.0.1 6667
```
Puis, envoyez les commandes IRC fondamentales une par une, en validant avec Entrée après chaque ligne :

```
PASS pass  
NICK mon_pseudo  
USER mon_user 0 * :Mon Nom Reel  
JOIN #test  
PRIVMSG #test :Bonjour tout le monde !  
```
### Bot Météo
Pour obtenir la météo, envoyez un message privé au bot (qui se nomme meteobot par défaut) :

```sh
PRIVMSG meteobot :Paris
```

## Licence
Ce projet est distribué sous la licence MIT. Voir le fichier LICENSE pour plus de détails.

## Liens utiles

[Wikipedia fr - Internet Relay Chat](https://fr.wikipedia.org/wiki/Internet_Relay_Chat#cite_note-RFC-2810-a-t-d-2)  
[Modern IRC Client Protocol](https://modern.ircdocs.horse/)   
[rfc2810 - IRC : Architecture, update 1459 (2000)](https://www.rfc-editor.org/rfc/rfc2810)  
[rfc2811 - IRC : Channel Management (2000)](https://www.rfc-editor.org/rfc/rfc2811)  
[rfc2812 - IRC : Client Protocol (2000)](https://www.rfc-editor.org/rfc/rfc2812)  
[rfc2813 - IRC : Server Protocol (2000)](https://www.rfc-editor.org/rfc/rfc2813)  
[rfc1459 - IRC : Protocol (1993)](https://www.rfc-editor.org/rfc/rfc1459) 
