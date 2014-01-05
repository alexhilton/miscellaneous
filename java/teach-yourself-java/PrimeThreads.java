public class PrimeThreads {
    public static void main(String[] args) {
	PrimeThreads pt = new PrimeThreads(args);
    }

    public PrimeThreads(String[] args) {
	PrimeFinder[] finder = new PrimeFinder[args.length];
	for (int i = 0; i < args.length; i++) {
	    try {
		long count = Long.parseLong(args[ i ]);
		finder[ i ] = new PrimeFinder(count);
		System.out.println("Looking for prime " + count );
	    } catch (NumberFormatException e) {
		System.out.println("Error: " + e.getMessage());
	    }
	}
	boolean complete = false;
	while (!complete) {
	    complete = true;
	    for (int j = 0; j < finder.length; j++ ) {
		if (finder[j] == null) continue;
		if ( !finder[j].finished ) {
		    complete = false;
		} else {
		    displayResult( finder[j] );
		    finder[j] = null;
		}
	    }
	    try {
		Thread.sleep( 1000 );
	    } catch ( InterruptedException e ) {
		// do nothing
	    }
	}
    }
    private void displayResult(PrimeFinder finder) {
	System.out.println("Prime " + finder.target + " is " + finder.prime );
    }
}

class PrimeFinder implements Runnable {
    public long target;
    public long prime;
    public boolean finished = false;
    private Thread runner;
    PrimeFinder(long inTarget) {
	target = inTarget;
	if ( runner == null ) {
	    runner = new Thread(this);
	    runner.start();
	}
    }

    public void run() {
	long numPrimes = 0;
	long candidate = 2;
	while ( numPrimes < target ) {
	    if ( isPrime( candidate ) ) {
		numPrimes++;
		prime = candidate;
	    }
	    candidate++;
	}
	finished = true;
    }

    boolean isPrime(long checkNumber) {
	double root = Math.sqrt(checkNumber);
	for (int i = 2; i <= root; i++ ) {
	    if ( checkNumber % i == 0 ) {
		return false;
	    }
	}
	return true;
    }
}

