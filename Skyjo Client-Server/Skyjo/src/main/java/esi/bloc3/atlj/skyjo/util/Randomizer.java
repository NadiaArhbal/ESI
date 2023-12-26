package esi.bloc3.atlj.skyjo.util;

import java.io.Serializable;
import java.util.Random;

/**
 * Picks a random card for a Player at the start of the game
 *
 * @author chris
 */
public class Randomizer implements Serializable{

    /**
     * Generates two distinct indexes composed of row then column
     *
     * @return a size 4 array with respective indexes of the first card and
     * second card
     */
    public static int[] generateIndexes() {
        //generate row between 0 and 2
        //generate column between 0 and 3
        int[] indexes = new int[4];
        Random r = new Random();
        do {
            indexes[0] = r.nextInt(2); // rows !
            indexes[1] = r.nextInt(2);
            indexes[2] = r.nextInt(3); // columns !
            indexes[3] = r.nextInt(3);
        } while (indexes[0] == indexes[1] && indexes[2] == indexes[3]);
        return indexes;
    }

    /**
     * Picks a number between 0 and 1, if it draws 0 true gets returned else its
     * false that gets returned
     *
     * @return true for player1 and false for player 2
     */
    public static boolean randomPlayer() {
        Random r = new Random();
        return r.nextInt(1) == 0;
    }
}
