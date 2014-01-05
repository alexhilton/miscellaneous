import java.util.*;

public class IndexOfNull {
    public static void main(String[] args) {
        ArrayList<String> a = new ArrayList<String>();
        a.add("abcd");
        System.out.println(a);
        System.out.println(a.indexOf(null));
    }
}
