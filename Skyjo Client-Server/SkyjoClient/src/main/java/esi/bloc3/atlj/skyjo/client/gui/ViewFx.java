package esi.bloc3.atlj.skyjo.client.gui;

import esi.bloc3.atlj.skyjo.model.Facade;
import esi.bloc3.atlj.skyjo.model.Status;
import java.io.Serializable;
import java.util.Observable;
import java.util.Observer;
import java.util.Optional;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.ButtonType;
import javafx.stage.Stage;

/**
 * Is the view of the project the layout is available in the project file
 *
 * @author chris
 */
public class ViewFx implements Observer , Serializable {

    private static final int WIDTH = 890;
    private static final int HEIGHT = 480;
    private final static Alert endDialog
            = new Alert(Alert.AlertType.CONFIRMATION);
    private final ButtonType yes = new ButtonType("Rejouer");
    private final ButtonType no = new ButtonType("Quitter");
    private final Stage main;
    private final LayoutFx lay;

    /**
     * Initialises the ViewFx so with the main stage and sets the dimensions of
     * it
     *
     * @param obs observable / model
     * @param main stage comming from the start method
     * @param player indicated wich player this client is refering too
     */
    public ViewFx(Observable obs, Stage main, TypePlayer player) {
        this.main = main;
        Facade f = (Facade) obs;
        f.registerObserver(this);
        lay = new LayoutFx(obs, player);
        endDialog.getButtonTypes().clear();
        endDialog.getButtonTypes().addAll(yes, no);
        main.setTitle("ESI-Skyjo | "+player);
        Scene scene = new Scene(lay, WIDTH, HEIGHT);
        main.setScene(scene);
        main.setResizable(false);
        main.show();
    }
    public void changeModel(Observable other) {
        Facade f = (Facade) other;
        f.registerObserver(this);
        lay.changeModel(other);
    }

    /**
     * This method sets the dialog window based on the winning player and the
     * score of both players
     *
     * @param winner true if player 1 and false if player 2
     * @param player1 score of player 1
     * @param player2 score of player 2
     * @return the options "oui" or "non"
     */
    private Optional<ButtonType> showEnding(boolean winner, int player1,
            int player2) {
        char playerChar = winner ? '1' : '2';
        endDialog.setTitle("Le joueur " + playerChar + " a gagné !");
        endDialog.setHeaderText("Score Joueur 1 : "
                + player1 + "  Score Joueur 2 : " + player2 + "\n"
                + "Voulez-vous relancez une manche ?");

        return endDialog.showAndWait();
    }

    /**
     * This methpd sets a normal dialogue window based on a error message and
     * itt prompts the user to either relaunch a game or quit the game
     *
     * @param error message form the status
     * @return the options "oui" or "non"
     */
    private Optional<ButtonType> showEnding(String error) {
        endDialog.setTitle("Une erreur s'est produite !");
        endDialog.setHeaderText(error);
        return endDialog.showAndWait();
    }

    /**
     * If the game is over the dialog window is shown and the option that the
     * user picked, determines if we call the close method of the main stage or
     * call the restart method of the model that reinstanciates its elements
     *
     * @param o
     * @param o1
     */
    @Override
    public void update(Observable o, Object o1) {
        Facade f = (Facade) o;
        Status st = f.getStatus();
        Optional<ButtonType> opt = null;
        if (st == Status.GAME_OVER) {
            opt = showEnding(f.getPlayer(), f.getScore(true),
                    f.getScore(false));
        } else if (st == Status.SHUFFLED_EMPTY) {
            opt = showEnding("" + f.getStatus());
        }
        if (opt != null && opt.get() == yes) {
            f.restart();
        } else if (opt != null) {
            main.close();
        }
    }
}
