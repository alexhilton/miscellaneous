package src;

public class Student {
    private String name;
    private String nation;
    private int age;
    public Student() {}
    public Student(String name, int age, String nation) {
	this.name = name;
	this.age = age;
	this.nation = nation;
    }
    public String toString() {
	return "Hi, everyone, my name is " + this.name + " and i am " + this.age +
	    "years old\n" + "I am from " + this.nation;
    }
    public void print() {
	System.out.println(this.toString());
    }
}
