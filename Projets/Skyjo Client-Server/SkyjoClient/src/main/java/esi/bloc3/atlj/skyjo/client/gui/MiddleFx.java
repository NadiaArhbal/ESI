package esi.bloc3.atlj.skyjo.client.gui;

import esi.bloc3.atlj.skyjo.model.Card;
import esi.bloc3.atlj.skyjo.model.Facade;
import esi.bloc3.atlj.skyjo.model.Status;
import java.util.Observable;
import java.util.Observer;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.control.Button;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;

/**
 * Represents the middle pane composed of 4 boutons, 2 of them are active the
 * discard button and the shuffle button
 *
 * @see note that here we dont use cardFx since we dont need to localize the
 * card in a matrix like CardFx does !
 * @author Christophe Rische
 */
public class MiddleFx extends GridPane implements Observer {

    private final CardFx shuffle = new CardFx(0, 0);
    private final CardFx discard = new CardFx(0, 0);

    public MiddleFx(Observable obs) {
        Facade f = (Facade) obs;
        f.registerObserver(this);
        setPadding(new Insets(80, 10, 10, 10));
        setHgap(5);
        setVgap(40);
        var pickShuffle = new Button();
        pickShuffle.setGraphic(new ImageView("/data/Random_Picker.JPG"));
        pickShuffle.setStyle("-fx-background-color: #3EA03D;");
        add(pickShuffle, 0, 0);
        shuffle.setGraphic(new ImageView("/data/Card_Cover.JPG"));
        shuffle.setStyle("-fx-background-color: #3EA03D;");
        discard.setPrefSize(64, 103);
        add(shuffle, 1, 0);
        add(discard, 0, 1);
        var pickDiscard = new Button();
        pickDiscard.setGraphic(new ImageView("/data/Pick_Known.JPG"));
        pickDiscard.setStyle("-fx-background-color: #3EA03D;");
        add(pickDiscard, 1, 1);
        addEvents(f);
    }
    public void changeModel(Observable other) {
        Facade f = (Facade) other;
        f.registerObserver(this);
        addEvents(f);
    }

    /**
     * Sets the two actions for the discard button and shuffle button they are
     * respectfully calling the update method of the model with their associated
     * statuses
     *
     * @param f facade interface methods
     */
    private void addEvents(Facade f) {
        shuffle.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent t) {
                f.updateStatus(Status.PICKED_SHUFFLED);
            }
        });
        discard.setOnMouseClicked(new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent t) {
                f.updateStatus(Status.PICKED_DISCARD);
            }
        });
    }

    /**
     * Always updates the shuffle button and discard button note that the
     * shuffle button depending on the model top deck card, hidden boolean can
     * either be reset gets its cover back or get a new value. And for the
     * discard its easy it always gets a value and is always shown
     *
     * @param o casted to facade
     * @param o1 no params
     */
    @Override
    public void update(Observable o, Object o1) {
        Facade f = (Facade) o;
        Card discardCopy = f.getDiscard();
        Card shuffleCopy = f.getShuffle();
        if (!shuffleCopy.isHidden()) {
            this.shuffle.giveValue(shuffleCopy.getValue());
        } else {
            this.shuffle.reset();
        }
        this.discard.giveValue(discardCopy.getValue());
    }

}
