package View;

/**
 * The interface Observable
 * 
 * @author Arhbal
 */
public interface Observable {

    public void registerObserver(Observer obs);  

    public void removeObserver(Observer obs);

    public void notifyObservers(); 

}