# Skyjo Client-Server

## Description
Notre projet sera un jeu de cartes avec une implémentation client/serveur.  
Le jeu de cartes se prénomme Skyjo (projet de l'année passée).  
[Les règles du jeu](https://www.regledujeu.fr/regle-du-skyjo/)  
Le but étant d'obtenir le moins de points possibles en inversant et échangeant des
cartes et se joue avec au minimum 2 joueurs et plusieurs spectateurs.  
Nous utiliserons donc un système de gestion de base de données (JDBC) pour pouvoir
stocker les informations des joueurs durant la partie ,les manipuler et les gérer dans la
base de données ainsi que des interfaces graphiques avec FXML pour permettre au
client de se connecter,de le mettre en attendre et afficher une erreur.  

### Notes d'utilisation  
Pour qu'un client se déconnecte il ne faut pas tout simplement fermer la fenêtre du
client en question mais il faut également arrêter le processus sur netbeans (carré rouge
sur netbeans)

## Description des classes
Notre projet est subdivisée en plusieurs projet :    
  - Skyjo : constituant la partie model de notre jeu.  
  - SkyjoClient : constituant tout ce qui se rapporte à un client.  
  - SkyjoMessages : constituant tout les messages pouvant être reçu ou envoyés.    
  - SkyjoServer : constituant tout ce qui se rapporte au serveur.  
  - SkyjoParent : qui reprend les 4 projets ci-dessus.  


