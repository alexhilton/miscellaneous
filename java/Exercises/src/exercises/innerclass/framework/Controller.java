/**
 * 
 */
package exercises.innerclass.framework;
import java.util.*;
/**
 * @author gongzhihui
 *
 */
public class Controller {
	private List<Event> eventList = new ArrayList<Event>();
	public void addEvent(Event c) {
		eventList.add(c);
	}
	
	public void run() {
		while (eventList.size() > 0) {
			// Make a copy so you're not modifying the list while you're selecting the elemetns
			// in it
			for (Event e : new ArrayList<Event>(eventList)) {
				if (e.ready()) {
					System.out.println(e);
					e.action();
					eventList.remove(e);
				}
			}
		}
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
