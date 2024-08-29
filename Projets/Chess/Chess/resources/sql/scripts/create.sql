----------------------
-- Creer les tables
----------------------

CREATE TABLE PLAYER (
        playerID        INTEGER PRIMARY KEY NOT NULL,
        pseudo          VARCHAR(30)     	NOT NULL,
		password		VARCHAR(30)				NULL,
		img				INT 					NULL,
		nationality     VARCHAR(2)             	NULL,
        elo             NUMERIC(4)             	NULL,
        UNIQUE (pseudo),
		CHECK (elo > 100 AND elo <= 3500)
);

CREATE TABLE GAME(
	   gameID  INTEGER PRIMARY KEY NOT NULL,
	   playerID INTEGER NOT NULL,
	   moves  VARCHAR NOT NULL,
	   dateString  VARCHAR NOT NULL,
	   winnerID INTEGER NOT NULL,
	   difficulty VARCHAR(4),
	   FOREIGN KEY (playerID) REFERENCES PLAYER(playerID),
	   FOREIGN KEY (winnerID) REFERENCES PLAYER(playerID)
);
CREATE TABLE PLAYERSTAT (
	statId INTEGER PRIMARY KEY NOT NULL,
	playerID INTEGER NOT NULL,
	gamesWon INTEGER DEFAULT 0,
	gamesLost INTEGER DEFAULT 0
);
CREATE TABLE SEQUENCES(
		id				VARCHAR(50)	PRIMARY KEY	NOT NULL,
		sValue			NUMERIC(10)			    NOT NULL
);
