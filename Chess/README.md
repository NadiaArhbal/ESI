# [ATLC-Chess](https://www.echecs.club/regles/)

## :large_blue_circle: Description de l'application 
Un jeu d'échecs avec intéractions avec une base de données MySQL qui
sauvegarde les parties des joueurs sous forme de chaîne de caractères à une date
précise et un versus IA basé sur un moteur open source Stockfish.  
Lors du lancement de l’application, l’utilisateur devra se connecter à distance via une
base de données tournant sur un serveur dédié qui contient la liste des utilisateurs
par leur pseudo et mot de passe, etc…  
Nous utiliserons les outils QT creator pour la réalisation de la GUI.  

<p align="center">
<img src="https://github.com/NadiaArhbal/ESI/assets/99414756/da311dba-bd87-43ad-a812-7a0070a6c640">

## :large_blue_circle: Mode d'emploi précis
Lors du lancement du jeu, une fenêtre de paramétrage est affichée.  
L’utilisateur doit choisir entre jouer contre un autre joueur (en local) ou jouer contre
un ordinateur.  

<p align="center">
  <img src="https://github.com/NadiaArhbal/ESI/assets/99414756/2915ee37-b377-47ee-8fef-86bb56823430">

Une fois lancée, le programme nous propose de se connecter avec un nom
d’utilisateur et un mot de passe. S’il s’agit d’un nouveau joueur, un bouton est
disponible pour s’inscrire (“Create new Account”) :   

  <p align="center">
  <img src="https://github.com/NadiaArhbal/ESI/assets/99414756/34c95875-5db1-4ed5-bc07-476bb67aaf230">

Pour s’inscrire, l’utilisateur doit choisir un nom d’utilisateur, un mot de passe,
choisir sa nationalité et sélectionner une photo de profil. Une fois fait, cliquez sur ok
pour démarrer une partie.  

<p align="center">
  <img src="https://github.com/NadiaArhbal/ESI/assets/99414756/fdb57676-d61c-427d-9fde-f92af2b04061">  
  
Malheureusement, nous n’avons pas réussi à communiquer correctement
avec le serveur pour sauvegarder les comptes des joueurs. Par conséquent, la
partie “inscription” et “connexion” ne fonctionne pas.  
  
La partie peut néanmoins être jouée contre un autre joueur en local ou contre
un ordinateur.  

## :large_blue_circle: Description des classes   
  
Notre projet se divise en plusieurs sous-projets comme suit :  
#### a) Chesscore  
![image](https://github.com/NadiaArhbal/ESI/assets/99414756/43955cf1-012b-43fe-881b-3b72e1e8d17d)  

Le sous-projet est composé d’une classe facade :
- Game : utilisée par ChessView.  
Elle permet d’exécuter un mouvement ou une promotion sur une pièce et d’une série de classes permettant de représenter un jeu d’échecs.
- Board : Il s’agit de la plus grosse classe.  
Elle se charge de vérifier tous les mouvements possibles du jeu d'échecs. Elle gère également le Roque, la prise “En passant” et la Promotion.  
Cette classe ne permet uniquement de vérifier les mouvements produits.
- Pieces : Cette classe représente une pièce du jeu des échecs
- PieceType : Enumération représentant le type d’une pièce (PAWN, ROOK,
KING,...)
- Position : Cette classe représente une Position au sein du plateau de jeu, un
indice sur l’axe des abscisses et sur l'axe des ordonnées.
- Side : Couleur d’une pièce ou d’un joueur (WHITE, BLACK)

#### b) GUI

![image](https://github.com/NadiaArhbal/ESI/assets/99414756/2d35bac0-999e-47cb-8e6e-e34ccf308e1a)  
La GUI se compose de la classe principale ChessView qui implémente le
pattern nvs::Observer, ça lui permettra de se rafraîchir à chaque fois que la Game
change d'état.
La classe ChessView implémentra aussi le pattern nvs::Subject, ce qui va
permettre à tous les éléments de la GUI de se synchroniser avec ChessView
Les classes qui observent ChessView sont :  
- BoardView
- EatenPieces
- History
- PlayerInfo
  
La classe BoardView (QGraphicsScene) est la classe principale de
ChessView, elle s’occupe d’afficher le plateau de jeu ainsi que toutes les pièces qui
le compose. Cette classe implémente nvs::Observer pour s’update à chaque
update de la classe ChessView, ce qui aura pour effet d’afficher correctement le
plateau de jeu.    
  
Les pièces du jeu sont représentées par des PieceItems
(QGraphicsPixmapItem) et les case possibles d’arrivée d’une pièce sont
représentées par des LandingChipItem (QGraphicsPixmapItem).  
  
Cette classe est interactive : à chaque fois que le joueur courant clique sur
une pièce, une série de LandingChipItem s'affiche sur les cases correspondantes
aux déplacements possibles de cette dernière, le joueur n’aura qu'à cliquer sur la
pastille de son choix et le move sera exécuté.    
  
La classe EatenPieces s’occupe d’afficher les pièces qui ont été mangées
par les joueurs. Elle comporte 2 parties :    
- Les pièces mangées par les Noirs,  
- Les pièces mangées par les Blancs.  
Il s’agit de 2 QGraphicsView qui sont rafraîchis à chaque mouvements du
jeu.  

<p align="center">
  <img src="https://github.com/NadiaArhbal/ESI/assets/99414756/d703b087-78c2-4de0-bf58-a71d8d46357d">  

La classe History se charge d’afficher chaque mouvement du jeu. Il s’agit
d’un QTableWidget, divisé en 2 colonnes, la colonne de gauche affiche les
mouvements des Blancs et la colonne de droite affiche les mouvements des Noirs.

<p align="center">
  <img src="https://github.com/NadiaArhbal/ESI/assets/99414756/8bbd9434-322e-4a9a-9c78-8ceac5c57057">    

Les mouvements sont représentés par une chaîne de caractères : [Position
de départ][Position d'arrivée].
La classe PlayerInfo affiche les informations des joueurs. Elle affiche le nom
d’utilisateur du joueur, son elo (niveau au échec), et sa photo de profil. C’est la seule
partie de l’affichage qui ne sera pas dynamique tout au long de la partie.

<p align="center">
  <img src="https://github.com/NadiaArhbal/ESI/assets/99414756/f6059d45-e2de-4f39-9bdf-5f3ebe969aee">    

#### c) Test
Ce sous projet contient les tests pour le modèle. Il permet de tester la
robustesse des classes que compose le sous-projet chesscore. 

#### d) TUI
Ce sous projet contient une bête interface console qui nous à permis de tester
la notation du jeux d’échecs et d’intégrer le moteur stockfish dans notre application

#### e) Chess_server
Ce sous projet contient le serveur d’authentification qui va interagir avec la
base de données dont les tables ont été définies dans le rapport descriptif de
l’application.

#### f) Stockfish
Stockfish est un exécutable qui est lancé à partir de Qprocess dans le sous
projet GUI qui communique grâce au protocole UCI (voir learning-resources) ou
alternativement ici http://wbec-ridderkerk.nl/html/UCIProtocol.html.  

Stockfish va permettre de générer le mouvement de la pièce adverse en
fonction des mouvements notés sous la forme Longue Algébrique.  
Exemple notre programme écrit comme commande au stdin de Stockfish :  

```
> position startpos moves e2e4
> go movetime 1500 “millisecondes”
-> Le programme répond au bout d’une seconde et demi
> bestmove e7e5
```

  
Notre programme sera donc en mesure d'interpréter les simples commandes
fournies par Stockfish tant que l’enchaînement des mouvements par leurs notations
et cohérentes.  
Celui-ci nous permet également de détecter les deux conditions de fin d’une
partie de jeux d’échecs, le pat et l’échec et mat.  
  Ceci est implémenté dans la méthode readyRead().  
  Malheureusement, Stockfish ne permet pas de gérer les contraintes liés au
board, c’est pour ça qu’il fallait que l’équipier responsable du Model soit apte à gérer
toutes tentatives de mouvements erronées __avant même__ d’envoyer les informations
au moteur Stockfish, si une mauvaise position est donnée à Stockfish, alors il
donnera simplement le mouvement du joueur qui à mal effectué son mouvement.  

