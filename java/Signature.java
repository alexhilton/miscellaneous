import java.util.*;

public class Signature {
    public static void main(String[] args) {
        System.out.println("Signature of array: " + args);
        int[] a = new int[4];
        System.out.println("Signature of array: " + a);
        byte[] b = new byte[4];
        System.out.println("Signature of array: " + b);
        char[] c = new char[4];
        System.out.println("Signature of array: " + c);
        Something[] s = new Something[5];
        System.out.println("Signature of array: " + s);
    }

    class Something {
    }
}
