package esi.bloc3.atlj.skyjo.server.controller;

import esi.bloc3.atlj.skyjo.server.business.AdminFacade;
import esi.bloc3.atlj.skyjo.server.business.AdminModel;
import esi.bloc3.atlj.skyjo.server.console.SkyjoServerConsole;
import esi.bloc3.atlj.skyjo.server.model.SkyjoServer;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Is the controller that processes method calls from the server to interact
 * with model of the game
 *
 * @author Christophe Rische
 */
public class Controller {

    private final AdminFacade model = new AdminModel();
    
    public AdminFacade getModel() {
        return model;
    }
    
     /**
     * Entry points to the instant messaging server side.
     *
     * @param args no arguments needed.
     */
    public static void main(String[] args) {
        Controller controller = new Controller();
        controller.start();
    }
    
    public void start() {
         try {
            SkyjoServer model = new SkyjoServer(12_345, this);
            SkyjoServerConsole console = new SkyjoServerConsole(model);
            model.addObserver(console);
            System.out.println("Server started");
            System.out.println("");
        } catch (IOException ex) {
            Logger.getLogger(SkyjoServerConsole.class.getName()).log(Level.SEVERE, null, ex);
            System.exit(0);
        }
    }

}
