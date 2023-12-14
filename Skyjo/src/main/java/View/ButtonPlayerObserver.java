package View;

import javafx.scene.control.Button;
import model.Player;

/**
 *
 * @author Arhbal
 */
public class ButtonPlayerObserver extends Button  implements Observer {
    private final String string;
    private final  Player player;

    /**
     * Constructor of ButtonPlayerObserver
     * @param player the player
     * @param string the string
     */
    public ButtonPlayerObserver(Player player,String string) {
        this.player = player;
        this.string=string;
    }

    /**
     * Updating the player's score according to the values ​​of the cards turned over
     */
    @Override
    public void update() {
      this.setText(string +" "+ player.cmptValCardsVisibles());
    }
    
    
    

}
