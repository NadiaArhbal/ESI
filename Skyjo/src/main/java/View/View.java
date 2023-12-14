package View;

import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import model.Game;
import model.State;

/**
 *
 * @author Arhbal
 */
public class View extends Application {

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage stage) {
        stage.setTitle("HE2B ESI-Skyjo");
        stage.setMinWidth(1050);
        stage.setMinHeight(630);

        Game game = new Game();
        game.initGame();

        VBox root = new VBox(20);
        root.setAlignment(Pos.CENTER);

        HBox hbox = new HBox(20);
        hbox.setAlignment(Pos.CENTER);

        GridPane gri1 = new GridPane();
        GridPane gri2 = new GridPane();
        GridPane gri3 = new GridPane();
        ButtonPlayerObserver joueur2 = new ButtonPlayerObserver(game.getPlayer2(), "Joueur 2     Points :");
        ButtonPlayerObserver joueur1 = new ButtonPlayerObserver(game.getPlayer1(), "Joueur 1     Points :");
        Label indication = new Label();
        indication.setMinWidth(550);

        ButtonObserver def = new ButtonObserver(game.getDefausse().getFirstCard());
        ButtonObserver pioche = new ButtonObserver(game.getPioche().getFirstCard());
        int x = 0;
        int y = 0;
        for (int i = 0; i < 12; i++) {

            ButtonObserver b2 = new ButtonObserver(game.getPlayer2().getCardsPlayer().get(i), i);
            game.getPlayer2().getCardsPlayer().get(i).registerObserver(b2);
            b2.setOnAction(new EventHandler<ActionEvent>() {

                @Override
                public void handle(ActionEvent t) {
                    if (!game.isFinished()) {
                        if (game.getCurrPlayer() == game.getPlayer2()) {
                            if (game.getOppositePlayer().allCardsVisible()) {
                                game.setIsFinished();
                            }
                            if (null != game.getStatus()) {
                                switch (game.getStatus()) {
                                    case DEFAUSSE:
                                        game.playDefausse(b2.getIdCard());
                                        break;
                                    case DISCARD:
                                        game.playDiscard(b2.getIdCard());
                                        break;
                                    case PIOCHE:
                                        if (!game.isPiocheEmpty()) {
                                            game.getDefausse().addCard(game.getCurrPlayer().getCardsPlayer().get(b2.getIdCard()));
                                            game.getCurrPlayer().getCardsPlayer().remove(b2.getIdCard());
                                            game.getCurrPlayer().getCardsPlayer().add(b2.getIdCard(), game.getPioche().getFirstCard());
                                            game.getPioche().removeFirstCard();
                                            updateObservers(t, pioche, def, game, b2.getIdCard() );
                                        }
                                        break;
                                    default:
                                        break;
                                }
                            }
                        } else {
                            Alert alert = new Alert(AlertType.ERROR);
                            alert.setTitle("Erreur");
                            alert.setHeaderText("Mauvais joueur !");
                            String currplayer = game.getCurrPlayer() == game.getPlayer1() ? "Joueur 1" : "Joueur 2";
                            alert.setContentText(currplayer + " joue maintenant, ce n'est pas votre tour !");
                            alert.showAndWait();
                        }
                        if (game.isPiocheEmpty() || game.getPlayer1().cmptValCardsVisibles() >= 100 || game.getPlayer2().cmptValCardsVisibles() >= 100) {
                            game.setIsFinished();
                        }
                        indication.setText((game.getCurrPlayer() == game.getPlayer1() ? "Joueur 1 " : "Joueur 2 ")
                                + "prenez une carte de la défausse ou piochez une nouvelle carte");
                        if (game.isFinished()) {
                            game.setFinalScore();
                            indication.setText((game.getWinner() == game.getPlayer1() ? "Joueur 1 " : "Joueur 2 ") + "est le gagnant !");
                            if (game.getPlayer1().cmptValCardsVisibles() >= 100 || game.getPlayer2().cmptValCardsVisibles() >= 100) {
                                indication.setText(indication.getText() + " 100 points ont été atteints ");

                            }
                        }
                        joueur1.update();
                        joueur2.update();
                    }
                }
            });
            ButtonObserver b = new ButtonObserver(game.getPlayer1().getCardsPlayer().get(i), i);
            game.getPlayer1().getCardsPlayer().get(i).registerObserver(b);
            b.setOnAction(new EventHandler<ActionEvent>() {

                @Override
                public void handle(ActionEvent t) {
                    if (!game.isFinished()) {

                        if (game.getCurrPlayer() == game.getPlayer1()) {
                            if (game.getOppositePlayer().allCardsVisible()) {
                                game.setIsFinished();
                            }
                            if (null != game.getStatus()) {
                                switch (game.getStatus()) {
                                    case DEFAUSSE:
                                        game.playDefausse(b.getIdCard());
                                        break;
                                    case DISCARD:
                                        game.playDiscard(b.getIdCard());
                                        break;
                                    case PIOCHE:
                                        if (!game.isPiocheEmpty()) {
                                            game.getDefausse().addCard(game.getCurrPlayer().getCardsPlayer().get(b.getIdCard()));
                                            game.getCurrPlayer().getCardsPlayer().remove(b.getIdCard());
                                            game.getCurrPlayer().getCardsPlayer().add(b.getIdCard(), game.getPioche().getFirstCard());
                                            game.getPioche().removeFirstCard();
                                            updateObservers(t, pioche, def, game, b.getIdCard());
                                        }
                                        break;
                                    default:
                                        break;
                                }
                            }
                        } else {
                            Alert alert = new Alert(AlertType.ERROR);
                            alert.setTitle("Erreur");
                            alert.setHeaderText("Mauvais joueur !");
                            String currplayer = game.getCurrPlayer() == game.getPlayer1() ? "Joueur 1" : "Joueur 2";
                            alert.setContentText(currplayer + " joue maintenant, ce n'est pas votre tour !");
                            alert.showAndWait();
                        }
                        if (game.isPiocheEmpty() || game.getPlayer1().cmptValCardsVisibles() >= 100 || game.getPlayer2().cmptValCardsVisibles() >= 100) {
                            game.setIsFinished();
                        }
                        indication.setText((game.getCurrPlayer() == game.getPlayer1() ? "Joueur 1 " : "Joueur 2 ")
                                + "prenez une carte de la défausse ou piochez une nouvelle carte");
                        if (game.isFinished()) {
                            game.setFinalScore();
                            indication.setText((game.getWinner() == game.getPlayer1() ? "Joueur 1 " : "Joueur 2 ") + "est le gagnant !");
                            if (game.getPlayer1().cmptValCardsVisibles() >= 100 || game.getPlayer2().cmptValCardsVisibles() >= 100) {
                                indication.setText(indication.getText() + " 100 points ont été atteints ");

                            }
                        }
                        joueur1.update();
                        joueur2.update();
                    }
                }
            });

            gri1.add(b, y, x);
            gri3.add(b2, y, x);

            x++;
            if (x == 3) {
                x = 0;
                y++;
            }
        }

        for (int i = 0; i < game.getDefausse().getCards().size(); i++) {
            game.getDefausse().getCards().get(i).registerObserver(def);
        }

        pioche.setOnAction(new EventHandler<ActionEvent>() {

            @Override
            public void handle(ActionEvent t) {
                if (!game.isFinished()) {
                    if (game.getStatus() == State.TAKECARD) {
                        game.getPioche().getFirstCard().setVisible(true);
                        game.setStatus(State.PIOCHE);
                        game.getPioche().getFirstCard().notifyObservers();
                    }
                }
            }
        });

        def.setOnAction(new EventHandler<ActionEvent>() {

            @Override
            public void handle(ActionEvent t) {
                if (!game.isFinished()) {
                    if (game.getStatus() == State.TAKECARD) {
                        game.setStatus(State.DEFAUSSE);
                    } else if (game.getStatus() == State.PIOCHE) {
                        game.addFirstCardPiocheOnDef(pioche, def);
                    }
                }
            }
        });

        for (int i = 0; i < game.getPioche().getCards().size(); i++) {
            game.getPioche().getCards().get(i).registerObserver(pioche);
        }
        indication.setId("points");
        indication.setAlignment(Pos.CENTER);
        indication.setTranslateX(0);
        indication.setTranslateY(510);
        root.getChildren().add(indication);
        gri2.add(def, 0, 1);
        gri2.add(pioche, 1, 0);
        pioche.setTranslateY(-37);
        def.setTranslateY(39);

        def.setMinHeight(100);
        def.setMinWidth(60);

        pioche.setMinHeight(100);
        pioche.setMinWidth(60);

        game.getPlayer1().registerObserver(joueur1);
        joueur1.setMinWidth(300);
        joueur1.setOpacity(200);
        joueur1.setTranslateX(-315);
        joueur1.setDisable(true);
        joueur1.setId("points");
        joueur1.setMinHeight(30);
        game.getPlayer2().registerObserver(joueur2);

        joueur2.setDisable(true);
        joueur2.setId("points");
        joueur2.setMinHeight(30);
        joueur2.setOpacity(200);
        joueur2.setMinWidth(300);
        joueur2.setTranslateX(315);
        joueur2.setTranslateY(-50);
        gri1.setPadding(new Insets(7));
        gri1.setHgap(20);
        gri1.setVgap(20);

        gri3.setPadding(new Insets(7));
        gri3.setHgap(20);
        gri3.setVgap(20);

        gri2.setPadding(new Insets(42));
        gri2.setHgap(60);
        gri2.setVgap(60);

        root.getChildren().add(joueur1);
        root.getChildren().add(joueur2);
        root.getChildren().add(hbox);
        hbox.getChildren().add(gri1);
        hbox.getChildren().add(gri2);
        hbox.getChildren().add(gri3);
        hbox.setTranslateY(-50);

        for (Node node : gri3.getChildren()) {
            Button button = (Button) node;
            button.setMinHeight(100);
            button.setMinWidth(60);
            node.setId("button");
        }
        for (Node node : gri1.getChildren()) {
            Button button = (Button) node;
            button.setMinHeight(100);
            button.setMinWidth(60);
            node.setId("button");
        }
        for (Node node : gri2.getChildren()) {
            Button button = (Button) node;
            button.setMinHeight(100);
            button.setMinWidth(60);
            node.setId("button");
        }
        root.setId("root");
        game.start();
        indication.setText((game.getCurrPlayer() == game.getPlayer1() ? "Joueur 1 " : "Joueur 2 ")
                + "prenez une carte de la défausse ou piochez une nouvelle carte");

        Scene scene = new Scene(root, 1000, 600);
        scene.getStylesheets().addAll(this.getClass().getResource("/style.css").toExternalForm());
        stage.setScene(scene);
        stage.show();
    }

    public void updateObservers(ActionEvent t,ButtonObserver pioche,ButtonObserver def,Game game,int id) {
        ((ButtonObserver) t.getSource()).setCard(game.getCurrPlayer().getCardsPlayer().get(id));
        pioche.setCard(game.getPioche().getFirstCard());
        game.getCurrPlayer().getCardsPlayer().get(id).registerObserver(((ButtonObserver) t.getSource()));
        game.getDefausse().getFirstCard().registerObserver(def);
        def.setCard(game.getDefausse().getFirstCard());
        game.getCurrPlayer().getCardsPlayer().get(id).notifyObservers();
        game.getPioche().getFirstCard().notifyObservers();
        game.getDefausse().getFirstCard().setVisible(true);
        game.getDefausse().getFirstCard().notifyObservers();
        game.setCurrentPlayer();
        game.setStatus(State.TAKECARD);
    }

}
