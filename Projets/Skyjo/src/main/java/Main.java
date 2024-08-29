
import View.View;
import controller.Controller;
import model.Game;

/**
 *
 * @author Arhbal
 */
public class Main {
    public static void main(String[] args) {
        Controller controller = new  Controller(new Game(),new View());
    }
}
