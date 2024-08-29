package esi.bloc3.atlj.skyjo.client.gui;

import esi.bloc3.atlj.skyjo.model.Facade;
import java.util.Observable;
import java.util.Observer;
import javafx.geometry.Insets;
import javafx.scene.layout.VBox;

/**
 * Represents the vbox that contains the Hbox and the Status bar that is
 * suceptible to be notified by the observable that is the model
 *
 * @author Christophe Rische
 */
public class LayoutFx extends VBox implements Observer {

    private static final StatusBarFx bar = new StatusBarFx();

    /**
     * Builds the VBox that instanciates the GameFX class that is an HBox, the
     * VBox additionaly contains the statusBar that get modified by this class
     *
     * @param obs
     * @param player determines the type of the player associated to the client
     */
    public LayoutFx(Observable obs, TypePlayer player) {
        super(new GameFx((Facade) obs, player)); // Potential try catch to do
        if (obs == null) {
            throw new IllegalArgumentException("No Observable !");
        }
        Facade f = (Facade) obs;
        f.registerObserver(this);
        getChildren().add(bar);
        setStyle("-fx-background-color: #3EA03D;");
        setPadding(new Insets(10));
    }

    public void changeModel(Observable other) {
        Facade f = (Facade) other;
        f.registerObserver(this);
        var gameFX = (GameFx) getChildren().get(0);
        gameFX.changeModel(other);
    }

    /**
     * Gets elements related to the current playing player and updates the
     * StatusBar
     *
     * @param o
     * @param o1
     */
    @Override
    public void update(Observable o, Object o1) {
        Facade f = (Facade) o;
        bar.updatePlayer(f.getPlayer());
        bar.setStatus(f.getStatus());
    }

}
