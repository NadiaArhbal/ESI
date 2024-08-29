package View;

import javafx.scene.control.Button;
import model.Card;

/**
 *
 * @author Arhbal
 */
public class ButtonObserver extends Button implements Observer {

    private Card card;
    private final int id;
    
    /**
     * Getter of the card
     * @return the card
     */
    public Card getCard() {
        return card;
    }

    /**
     * Setter of the card
     * @param card the card
     */
    public void setCard(Card card) {
        this.card = card;
    }
     
    /** 
     * Getter of the id card
     * @return the id of the card
     */
    public int getIdCard() {
        return id;
    }
    
    /**
     * Gives the card the correct color when our card is visible
     */
    @Override
    public void update() {
        if (card.isVisible()) {
            int val = card.getVal();

            this.setText(val + "");
            this.setId("none");
            if (val == 0) {
                this.setStyle("-fx-background-color: #87CEFA;-fx-font-size:20;");
            } else if (val >= 1 && val <= 4) {
                this.setStyle("-fx-background-color: #32CD32;-fx-font-size:20;");
            } else if (val >= 5 && val <= 8) {
                this.setStyle("-fx-background-color: #FFFF00;-fx-font-size:20;");
            } else if (val >= 9 && val <= 12) {
                this.setStyle("-fx-background-color: #FF0000;-fx-font-size:20;");
            } else {
                this.setStyle("-fx-background-color:   #778899;-fx-font-size:20;");
            }
        }else{
            this.setText("");
            this.setId("button");
        }
    }

    /**
     * ButtonObserver of the card (constructor)
     * @param card the card
     */
    public ButtonObserver(Card card) {
        this.card = card;
        this.id=-1;
    }
    
    /**
     * ButtonObserver of the card (constructor) 
     * @param card the card
     * @param id the id of the card
     */
    public ButtonObserver(Card card, int id) {
        this.card = card;
        this.id = id;
    }

}
