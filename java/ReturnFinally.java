public class ReturnFinally {
    public static void main(String[] args) {
        new ReturnFinally().returnValue();
    }

    public int returnValue() {
        int a = 8;
        try {
            System.out.println("in try, a = " + a);
            System.out.println("in finally a = " + a);
            return a = 10;
        } finally {
            System.out.println("in finally a = " + a);
            return a;
        }
    }
}
