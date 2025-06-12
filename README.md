# IRC (Internet Relay Chat)

## installation

## Bot

pour l'utilisation du bot il est necessaire d'avoir un fichier api_key au meme niveau que l'application binaire. Ce fichier doit contenir la cle fourni par le site [AccuWeather api](https://developer.accuweather.com/).

Pour en obtenir une:
- creez un compte (gratuit).
- Allez dans votre compte, et cliquez sur l'onglet "My Apps".
- Creez une Apps.
- Une fois sur la page de votre Apps vous trouverez l'API key, que vous n'avez plus qu'a copier dans le fichier.

A ce jour (12/06/2025), une cle permet gratuitement de realiser 50 requetes par jour.


Ce site a ete choisi car il permet d'obtenir les donnes meteo sans requerir le protocole ssl.

Un autre site gratuit avait ete trouve : [prevision_meteo](www.prevision-meteo.ch/services). Mais il necessite l'utilisation du protocole ssl.

Exemple de requete : [www.prevision-meteo.ch/services/json/Marseille](www.prevision-meteo.ch/services/json/Marseille)

## Liens utiles

[Wikipedia fr](https://fr.wikipedia.org/wiki/Internet_Relay_Chat#cite_note-RFC-2810-a-t-d-2)  
[Modern IRC Client Protocol](https://modern.ircdocs.horse/)  
[rfc1459 - IRC : Protocol (1993)](https://www.rfc-editor.org/rfc/rfc1459)  
[rfc2810 - IRC : Architecture, update 1459 (2000)](https://www.rfc-editor.org/rfc/rfc2810)  
[rfc2811 - IRC : Channel Management (2000)](https://www.rfc-editor.org/rfc/rfc2811)  
[rfc2812 - IRC : Client Protocol (2000)](https://www.rfc-editor.org/rfc/rfc2812)  
[rfc2813 - IRC : Server Protocol (2000)](https://www.rfc-editor.org/rfc/rfc2813)    
[inspircd](https://github.com/inspircd/inspircd)  
[Code quoi](https://www.codequoi.com/programmation-reseau-via-socket-en-c/)