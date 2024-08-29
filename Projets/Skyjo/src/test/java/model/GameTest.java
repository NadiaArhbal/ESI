package model;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

/**
 *
 * @author Arhbal
 */
public class GameTest {
    
    public GameTest() {
    }

    @Test
    public void testIsFinished() {
//        Game game = new Game();
//        game.initGame();
//       
//       
//        for (int i = 0; i < 10; i++) {
//            game.getPlayer1().getCardsPlayer().get(i).setVal(10);
//        }
//        game.
//        assertTrue(game.isFinished());
        
    }

  

 

    @Test
    public void testGetWinner() {
        System.out.println("getWinner");
             Game game = new Game();
        game.initGame();
       
       
        for (int i = 0; i < 10; i++) {
            game.getPlayer1().getCardsPlayer().get(i).setVal(10);
       }
       
        assertEquals(game.getWinner(),game.getPlayer2());
    }

    @Test
    public void testGetOppositePlayer() {
           Game game = new Game();
        game.initGame();
        System.out.println("Test player starting");
        game.getPlayer1().getCardsPlayer().get(0).setVisible(true);
        game.getPlayer1().getCardsPlayer().get(0).setVal(2);
        game.getPlayer2().getCardsPlayer().get(0).setVisible(true);
        game.getPlayer2().getCardsPlayer().get(0).setVal(5);
        game.getPlayer1().getCardsPlayer().get(1).setVisible(true);
        game.getPlayer1().getCardsPlayer().get(1).setVal(4);
        game.getPlayer2().getCardsPlayer().get(1).setVisible(true);
        game.getPlayer2().getCardsPlayer().get(1).setVal(10);
        game.setCurrPlayer(game.getStartingPlayer());
        assertEquals(game.getPlayer1(), game.getOppositePlayer());
    }



   
   

    @Test
    public void testReveal() {
        Game game = new Game();
        game.initGame();
        game.getPlayer1().reveal();
        boolean hasOneCardRevealed=false;
        for (Card card : game.getPlayer1().getCardsPlayer()) {
            if(card.isVisible())
                hasOneCardRevealed=true;
        }
        
        assertTrue(hasOneCardRevealed);
    }

   

    @Test
    public void testGetStartingPlayer() {
        Game game = new Game();
        game.initGame();
        System.out.println("Test player starting");
        game.getPlayer1().getCardsPlayer().get(0).setVisible(true);
        game.getPlayer1().getCardsPlayer().get(0).setVal(2);
        game.getPlayer2().getCardsPlayer().get(0).setVisible(true);
        game.getPlayer2().getCardsPlayer().get(0).setVal(5);
        game.getPlayer1().getCardsPlayer().get(1).setVisible(true);
        game.getPlayer1().getCardsPlayer().get(1).setVal(4);
        game.getPlayer2().getCardsPlayer().get(1).setVisible(true);
        game.getPlayer2().getCardsPlayer().get(1).setVal(10);

        assertEquals(game.getPlayer2(), game.getStartingPlayer());
    
    }

    @Test
    public void testSwapCard() {
        Game game = new Game();
        game.initGame();
        game.start();
        int card= game.getCurrPlayer().getCardsPlayer().get(0).getVal();
        int card2 = game.getDefausse().getCards().get(0).getVal();
        game.swapCard(0, game.getDefausse());
        assertTrue(game.getDefausse().getCards().get(0).getVal()==card
        &&game.getCurrPlayer().getCardsPlayer().get(0).getVal()==card2);
    }
     @Test
     public void testSetFinalScore(){
         Game game = new Game();
         game.initGame();
         for (int i = 0; i < game.getPlayer1().getCardsPlayer().size(); i++) {
             game.getPlayer1().getCardsPlayer().get(i).setVal(5);
             game.getPlayer1().getCardsPlayer().get(i).setVisible(true);
             game.getPlayer2().getCardsPlayer().get(i).setVal(0);
         }
         game.setIsFinished();
         game.setCurrPlayer(game.getPlayer1());
         game.setFinalScore();
         assertTrue(game.getPlayer1().cmptValCardsVisibles()==120);
     }
  


    
    
}
