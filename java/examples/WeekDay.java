package javalancs;
import java.lang.Math;
import javalancs.*;

public class WeekDay extends OurDate {
    private int weekday, century;
    private String[] weekdayName = {
		"Sunday", "Monday", "Tuesday", "Wednsday",
		"Thursday", "Friday", "Saturday"
    };// end of weekdayName stirng array;
    public WeekDay( int y, int m, int d, int c ) {
	    super( y, m, d );
	    century = c;
    }//end of constructor method;
    public String getWeekDay() {
        weekday = ( super.dayOfMonth + Math.round( ( 2.6 * super.month ) -
	0.2 ) - ( 2 * century ) + super.year + Math.round( year / 4 ) +
		Math.round( century / 4 ) ) % 7;
	    return ( weekdayName[ weekday ] ); 
    }//end of get method;
}//end of WeekDay class;
