package esi.bloc3.atlj.skyjo.client.gui;

import esi.bloc3.atlj.skyjo.model.Facade;
import esi.bloc3.atlj.skyjo.model.Status;
import java.util.Observable;
import java.util.Observer;
import javafx.event.EventHandler;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.HBox;

/**
 * Represents the main GUI class that interacts with the model and regroups
 * MiddleFx (Discard and Shuffle pane), Two PlayerFx panes with all of the
 * CardFx
 *
 * @author Christophe Rische
 */
public class GameFx extends HBox implements Observer {

    private final PlayerFx player1;
    private final PlayerFx player2;
    private final MiddleFx middle;
    private Facade game; //Removed final bcs of change of model
    private TypePlayer clientplayer;

    /**
     * Builds the GameFx instance that needs an instance from the model
     *
     * @param f Model / Observable
     * @param player is the player identifying the client
     */
    public GameFx(Facade f, TypePlayer player) {
        super(4);
        f.registerObserver(this);
        this.game = f;
        this.player1 = new PlayerFx(new PlayerScoreFx("Score Joueur 1 : "));
        this.player2 = new PlayerFx(new PlayerScoreFx("Score Joueur 2 : "));
        this.middle = new MiddleFx((Observable) f);
        getChildren().add(player1);
        getChildren().add(middle);
        getChildren().add(player2);
        this.clientplayer = player;
        addPlayerPaneFilters();
        addMiddleFilters();
        PlayerFx clientPlayerPane = clientplayer == TypePlayer.PLAYER_ONE
                ? player1 : player2;
        addPlayerCardsEvent(clientPlayerPane);
    }

    public void changeModel(Observable other) {
        Facade f = (Facade) other;
        f.registerObserver(this);
        middle.changeModel(other);
        this.game = f;
    }

    /**
     * Adds filters that are working based of the model currently selected
     * player, e.g if player 1 is currently playing we consume events comming
     * from the player2's cards. Also if the status is at pick_option both if
     * the events comming from the player's panes are consumed
     */
    private void addPlayerPaneFilters() {
        player1.addEventFilter(MouseEvent.MOUSE_CLICKED,
                new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent t) {
                if (!game.getPlayer()
                        || game.getStatus() == Status.PICK_OPTION) {
                    t.consume();
                }
            }
        });
        player2.addEventFilter(MouseEvent.MOUSE_CLICKED,
                new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent t) {
                if (game.getPlayer()
                        || game.getStatus() == Status.PICK_OPTION) {
                    t.consume();
                }
            }
        });
    }

    /**
     * Adds click events for each cards 12 of each two players it executes the
     * clickCard method of this class that is later relayed to the model
     *
     * @param player wich player to activate events to in function of client
     */
    private void addPlayerCardsEvent(PlayerFx player) {
        CardFx[][] cards = player.getCards();
        for (var row : cards) {
            for (var card : row) {
                card.setOnMouseClicked(new EventHandler<MouseEvent>() {
                    @Override
                    public void handle(MouseEvent t) {
                        clickCard(card.getRow(), card.getColumn());
                    }
                });
            }
        }

    }

    /**
     * Disables shuffle and discard related events if the game is in the
     * reveal_card stage
     */
    private void addMiddleFilters() {
        middle.addEventFilter(MouseEvent.MOUSE_CLICKED,
                new EventHandler<MouseEvent>() {
            @Override
            public void handle(MouseEvent t) {
                if (game.getStatus() == Status.REVEAL_CARD) {
                    t.consume();
                }
            }
        });
    }

    /**
     * If a specific card of a players card is triggered we need to get its row
     * and column, so that we can transmit it to the model wich will know based
     * of the status "picked_discard" or "picked_shuffled" wich card to replace
     * in the players card array with the deck "pop" / discard "pop"
     * Alternatively based on the status "reveal_card" the model will only
     * reveal the card
     *
     * @param row in the array where the card is situated
     * @param column in the array where the card is situated
     */
    public void clickCard(int row, int column) {
        game.handleCard(row, column);
    }

    /**
     * Is triggered from the model whenever the status is changed to pick_option
     * the two player panes are refreshed because this status and if not then
     * only the current playing player gets its pane refreshed pick_option wich
     * is the start of each round refreshes both players pane its implemented
     * that way so that it includes the eventual restart of the model wich
     * requires a restart of showned cards from the previous game
     *
     * @param o
     * @param o1
     */
    @Override
    public void update(Observable o, Object o1) {
        Status st = game.getStatus();
        var currentFx = game.getPlayer() ? player1 : player2;
        if (TypePlayer.getType(game.getPlayer()) != clientplayer) {
            middle.setDisable(true);
        } else {
            middle.setDisable(false);
        }
        boolean clear = st == Status.PICK_OPTION;
        currentFx.updateCards(game.getCards(), clear);
        currentFx.setScore(game.getScore());
        if (st == Status.PICK_OPTION || st == Status.GAME_OVER) {
            var otherFx = game.getPlayer() ? player2 : player1;
            boolean other = !game.getPlayer();
            otherFx.setScore(game.getScore(other));
            otherFx.setScore(game.getScore(!game.getPlayer()));
            if (st == Status.PICK_OPTION) {
                otherFx.updateCards(game.getCards(other), clear);
            }
        }
    }
}
