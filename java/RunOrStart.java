public class RunOrStart {
    private static class TaskRun implements Runnable {
        private String name;
        public TaskRun(String n) {
            name = n;
        }

        public void run() {
            System.out.println("TestRun.run(), start running are you aware of that" + name);
            try {
                Thread.sleep(2000);
            } catch (Exception e) {
            }
            System.out.println("TestRun.run(), end running" + name);
        }
    }

    private static class TaskStart extends Thread {
        private String name;
        public TaskStart(String n) {
            name = n;
        }

        public void run() {
            System.out.println("TastStart.run(), start running are you aware of that" + name);
            try {
                Thread.sleep(2000);
            } catch (Exception e) {
            }
            System.out.println("TastStart.run(), end running" + name);
        }
    }

    public static void main(String[] args) {
        new TaskRun("taskrun").run();
        System.out.println("taskrun is ending");
        new TaskStart("with run").run();
        System.out.println("taskstart.run is ending");
        new TaskStart("with start").start();
        System.out.println("main thread is ending");
    }
}
