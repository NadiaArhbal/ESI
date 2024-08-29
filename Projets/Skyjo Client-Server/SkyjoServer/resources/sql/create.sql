----------------------
-- Creer les tables
----------------------

CREATE TABLE PLAYER (
        playerID        INTEGER PRIMARY KEY NOT NULL,
        pseudo          VARCHAR(30)     	NOT NULL,
		password		VARCHAR(30)			NOT NULL,
		nbPlayed        INT             	NULL,
        nbWin           INT             	NULL,
        UNIQUE (pseudo)
);

CREATE TABLE GAME (
        gameID          INTEGER PRIMARY KEY	NOT NULL,
        playerID1       INT             	NOT NULL,
        playerID2       INT             	NOT NULL,
        winner          INT             	NOT NULL,
		winnerScore		INT					NOT NULL,
		loserScore		INT					NOT NULL,
        FOREIGN KEY (playerID1) REFERENCES PLAYER(playerID),
        FOREIGN KEY (playerID2) REFERENCES PLAYER(playerID),
        FOREIGN KEY (gameID) 	REFERENCES PLAYER(playerID)
);

CREATE TABLE SEQUENCES(
		id				VARCHAR(50)	PRIMARY KEY	NOT NULL,
		sValue			NUMERIC(10)			    NOT NULL
);
