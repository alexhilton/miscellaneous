public class LiftOff implements Runnable {
  private int count;
  public LiftOff( int count ) {
    this.count = count;
  }

  public void run() {
    try {
      Thread.sleep( 1000 );
    } catch ( InterruptedException e ) {
      e.printStackTrace();
    }
    while ( count > 0 ) {
      System.out.print( count-- + " " );
    }
    System.out.println( "Lift off" );
  }

  public static void  main( String[] args ) {
    for ( int i = 0; i < 10; i++ ) {
      new LiftOff( 10 ).run();
    }

    System.out.println( "Waiting for lift off" );
    try {
      Thread.sleep( 5000 );
    } catch ( InterruptedException e ) {
      e.printStackTrace();
    }
  }
}
