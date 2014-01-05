import java.util.*;

public class ManagerTest {
    public static void main( String[] args ) {
	// construct a Manager object 
	Manager boss = new Manager( "Carl Cracker", 80000, 1987, 12, 15 );
	boss.setBonus( 5000 );

	Employee[] staff = new Employee[ 3 ];

	// fill the staff array with Manager and Employee objects
	staff[ 0 ] = boss;
	staff[ 1 ] = new Employee( "Harry Hacker", 50000, 1989, 10, 1 );
	staff[ 2 ] = new Employee( "Tommy Tester", 40000, 1990, 12, 4 );

	// print out information about all Employee objects
	for ( Employee e : staff ) {
	    System.out.println( "name = " + e.getName() +
				" salary = " + e.getSalary() );
	}
    }
}

class Employee {
    public Employee( String name, double salary, int year,
		     int month, int day ) {
	this.name = name;
	this.salary = salary;
	GregorianCalendar calendar = new GregorianCalendar(
							   year, month-1, day );
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

    public void raiseSalary( double byPercent ) {
	double raise = salary * byPercent / 100;
	salary += raise;
    }

    private String name;
    private double salary;
    private Date hireDay;
}

class Manager extends Employee {
    /**
     * @param name
     * @param salary
     * @param year
     * @param month
     * @param day
     */
    public Manager( String name, double salary, int year, int month, int day ) {
	super( name, salary, year, month, day );
	bonus = 0;
    }

    public double getSalary() {
	return super.getSalary() + bonus;
    }

    public void setBonus( double by ) {
	bonus = by;
    }
    private double bonus;
}
