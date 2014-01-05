import java.util.*;

public class ArrayListTest {
    public static void main( String[] args ) {
	// fill the staff array list with three Employee objects
	ArrayList<Employee> staff = new ArrayList<Employee>( 3 );

	staff.add( new Employee( "Alex Hilton", 100000, 1990, 12, 3 ) );
	staff.add( new Employee( "Carl Cracker", 5000, 1998, 5, 3 ) );
	staff.add( new Employee( "Tony Tester", 40000, 1990, 3, 4 ) );

	// raise everyone's salary by 5%
	for ( Employee e : staff ) {
	    e.raiseSalary( 5 );
	}
	// print out information about all Employee objects
	for ( Employee e : staff ) {
	    System.out.println( "Name =" + e.getName() +
				"; Salary = " + e.getSalary() + 
				"; hire date = " + e.getHireDay() );
	}
    }
}

class Employee {
    public Employee( String name, double salary, int year, int month,
		     int day ) {
	this.name = name;
	this.salary = salary;
	GregorianCalendar calendar = new GregorianCalendar( year, 
							    month - 1, day );
	hireDay = calendar.getTime();
    }

    public String getName() {
	return name;
    }

    public double getSalary() {
	return salary;
    }

    public Date getHireDay() {
	return hireDay;
    }

    public void raiseSalary( double b ) {
	double raise = salary * b / 100;
	salary += raise;
    }

    private String name;
    private double salary;
    private Date hireDay;
}
