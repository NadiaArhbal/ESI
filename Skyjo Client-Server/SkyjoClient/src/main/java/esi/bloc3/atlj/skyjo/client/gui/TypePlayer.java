/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package esi.bloc3.atlj.skyjo.client.gui;

/**
 * Indicates the player of this current client so that the view can be adapted
 * in function of the player
 *
 * @author Christophe Rische
 */
public enum TypePlayer {
    PLAYER_ONE,
    PLAYER_TWO,
    SPECTATOR;

    public static TypePlayer getType(int value) {
        return switch (value) {
            case 1 ->
                TypePlayer.PLAYER_ONE;
            case 2 ->
                TypePlayer.PLAYER_TWO;
            default ->
                TypePlayer.SPECTATOR;
        };
    }
    public static TypePlayer getType(boolean currentPlayer) {
        return currentPlayer ? TypePlayer.PLAYER_ONE : TypePlayer.PLAYER_TWO;
    }
}
