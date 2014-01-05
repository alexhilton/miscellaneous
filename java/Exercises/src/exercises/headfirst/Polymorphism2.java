/**
 * Simple example demonstrating basic Polymorphism
 */
package exercises.headfirst;

/**
 * @author gongzhihui
 *
 */
public class Polymorphism2 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		int size = 2;
		Pet[] pets = new Pet[size];
		pets[0] = new Cat();
		pets[1] = new Dog();
		for (Pet pet : pets) {
			pet.roar();
		}
	}

}

abstract class Pet {
	public void roar() {}
}

class Cat extends Pet {
	public void roar() {
		System.out.println("Cat roaring");
	}
}

class Dog extends Pet {
	public void roar() {
		System.out.println("Dog barking");
	}
}