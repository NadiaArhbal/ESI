package controller;

import View.View;
import model.Game;

/**
 *
 * @author Arhbal
 */
public class Controller {
    private final Game game;
    private final View view;

    /**
     * Constructor of controller
     * @param game the game
     * @param view the view
     */
    public Controller(Game game, View view) {
        this.game = game;
        this.view = view;
    }

    /**
     * Getter of game 
     * @return the game
     */
    public Game getGame() {
        return game;
    }

    /**
     * Getter of view
     * @return the view
     */
    public View getView() {
        return view;
    }
    
    /**
     * Start the game
     */
    public void start(){
        game.start();
    }
}
