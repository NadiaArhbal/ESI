package esi.bloc3.atlj.skyjo.client.gui;

import javafx.scene.control.Button;
import javafx.scene.image.ImageView;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;

/**
 * Represents a card but as a button in javafx each has an handler that allows
 * it to shown by changing its value via the update method of the observer
 *
 * @author Christophe Rische
 */
public class CardFx extends Button {

    private final int row;
    private final int column;
    private ImageView COVER = new ImageView("/data/Card_Cover.JPG");
    private final static Font NUMBER_FONT = new Font("Arial", 22);

    /**
     * Creates a button that has the graphic a skyjo card with a green
     * background to blend in with the window's backgeound color
     *
     * @param row the row index to be sent when pressed to the model
     * @param column the column index to be sent when pressen to the model
     */
    public CardFx(int row, int column) {
        this.row = row;
        this.column = column;
        setPrefSize(64, 103);
        setMinSize(64, 103);
        setMaxSize(64, 103);
        setGraphic(COVER);
        setStyle("-fx-background-color: #3EA03D;");
    }

    /**
     * Gives a value to a specific button of the interface note that the button
     * gets its image removed !
     *
     * @param value value of the cardd
     */
    public void giveValue(int value) {
        setGraphic(null);
        setText("" + value);
        setFont(NUMBER_FONT);
        setBckColor(value);
    }

    /**
     * Allows a card to retrieve its cover image so get a hidden state
     */
    public void reset() {
        setText("");
        setPrefSize(64, 103);
        setMinSize(64, 103);
        setMaxSize(64, 103);
        setGraphic(COVER);
        setStyle("-fx-background-color: #3EA03D;");
    }

    /**
     * Sets the background color of each card according to their values
     *
     * @param value to determine the color to pick
     */
    private void setBckColor(int value) {
        setTextFill(Color.BLACK);
        if (value < 2) {
            setStyle("-fx-background-color: #000099;");
            setTextFill(Color.WHITE);
        } else if (value < 7) {
            setStyle("-fx-background-color: #00FF00;");
        } else if (value < 10) {
            setStyle("-fx-background-color: #FFFF00;");
        } else if (value < 12) {
            setStyle("-fx-background-color: #FF0000;");
            setTextFill(Color.WHITE);
        } else if (value == 12) {
            setStyle("-fx-background-color: #9900FF;");
            setTextFill(Color.WHITE);
        }
    }

    /**
     * Simply gets the row of where this card is supposed to be at
     *
     * @return an integer
     */
    public int getRow() {
        return row;
    }

    /**
     * Simply gets the column of where this card is supposed to be at
     *
     * @return an integer
     */
    public int getColumn() {
        return column;
    }

}
