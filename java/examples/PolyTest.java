/**
 * This example is designated to feel the polymorphism in Java
 */
public class PolyTest {
    public static void main(String[] args) {
	Animal[] zoo = new Animal[4];
	zoo[ 0 ] = new Dog();
	zoo[ 1 ] = new Cat();
	zoo[ 2 ] = new Tiger();
	zoo[ 3 ] = new Lion();
	PetAction[] pet = new PetAction[3];
	pet[ 0 ] = new Dog();
	pet[ 1 ] = new Cat();
	pet[ 2 ] = new Rat();
	for (int i = 0; i < zoo.length; i++) {
	    zoo[ i ].print();
	}
	for (int i = 0; i < pet.length; i++) {
	    pet[ i ].play();
	}
    }
}

class Animal {
    String name;
    public  void print() {
	System.out.print("Hi, everyone, I am a ");
    }
}

interface PetAction {
    public void play();
}

class Dog extends Animal implements PetAction {
    public void print() {
	super.print();
	System.out.println("dog!");
    }
    public void play() {
        System.out.println("I can roll over, sit and lay down!");
    }
}

class Cat extends Animal implements PetAction {
    public void print() {
	super.print();
	System.out.println("cat!");
    }
    public void play() {
	System.out.println("I can climb a tree!");
    }
}

class Tiger extends Animal {
    public void print() {
	super.print();
	System.out.println("tiger!");
    }
}

class Lion extends Animal {
    public void print() {
	super.print();
	System.out.println("lion");
    }
}

class Rat implements PetAction {
    public void play() {
	System.out.println("I can chew something, and run very fast");
    }
}
