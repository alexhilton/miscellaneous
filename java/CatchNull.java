public class CatchNull {
    public static void  main(String args[]) {
        try {
            new CatchNull().throwNull();
        } catch (Exception e) {
            System.out.println("Catched Exception: " + e);
        }
    }

    public void throwNull() {
        String nullStr = null;
        nullStr.endsWith("null");
    }
}
