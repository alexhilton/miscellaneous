/*
 * Alex Hilton (c) Copyrights, all rights reserved, 2000~2010
 */
public class StackTraceTag {
    public static void main(String args[]) {
        stackTrace();
        exceptionTrace();
    }

    public static void function() {
        Thread.dumpStack();
    }

    public static void stackTrace() {
        function();
    }
    
    public static void exceptionTrace() {
        String str = null;
        str.toString();
    }
}
