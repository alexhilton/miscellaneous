/**
 * 
 */
package exercises.headfirst;

import java.util.Date;
import java.util.Calendar;
/**
 * @author gongzhihui
 *
 */
public class NumberFormat {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		/*
		 * Play with String.format, an analogous of C formatted I/O. They are almost the same.
		 */
		String s = String.format("this is a double %g", 100.00);
		System.out.println(s);
		s = String.format("this is an integer %d", 1000);
		System.out.println(s);
		s = String.format("this is an float %.2f", 123.456);
		System.out.println(s);
		s = String.format("this is an integer with comma %, d", 123400000);
		System.out.println(s);
		s = String.format("This is a float with comma %, 4.2f", 12.34);
		System.out.println(s);
		s = String.format("That is a char %c", 55);
		System.out.println(s);
		s = String.format("That is a hex 0x%x", 0x1234abcd);
		System.out.println(s);
		s = String.format("the plan is about %, .6f to %, .6f", 123456.0982, 2837343.02383);
		System.out.println(s);
		
		/*
		 * Now play with Date and Calendar
		 */
		Date now = new Date();
		s = String.format("what time is it now? %tc", now);
		System.out.println(s);
		s = String.format("what time is it now? %tr", now);
		System.out.println(s);
		s = String.format("what time is it now? %tc", now);
		System.out.println(s);
		s = String.format("what time is it now? %tA, %tB, %td", now, now, now);
		System.out.println(s);
		s = String.format("what time is it now? %tA, %<tB, %<td", now, now, now);
		System.out.println(s);
		
		/*
		 * Now about Calendar
		 */
		Calendar today = Calendar.getInstance();
		System.out.println("now is: " + today.getTime());
		today.add(Calendar.DAY_OF_MONTH, 1);
		System.out.println("tomorrow is: " + today.getTime());
		today.add(Calendar.DATE, 1);
		System.out.println("add date by 1 yields: " + today.getTime());
	}

}
