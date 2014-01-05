/**
 * 
 */
package exercises.interfaces;
import java.util.*;
/**
 * @author gongzhihui
 *
 */
public class Apply {
	public static void process(Processor p, Object s) {
		System.out.println("Using Prcoessor " + p.name());
		System.out.println(p.process(s));
	}
	public static String s = "Disagreement with beliefs is by definition incorrect";
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		process(new Upcase(), s);
		process(new Downcase(), s);
		process(new Spliter(), s);
	}

}


class Processor {
	public String name() {
		return getClass().getSimpleName();
	}
	Object process(Object obj) {
		return obj;
	}
}

class Upcase extends Processor {
	@Override
	String process(Object obj) {
		return ((String) obj).toUpperCase();
	}
}

class Downcase extends Processor {
	@Override
	String process(Object obj) {
		return ((String) obj).toLowerCase();
	}
}

class Spliter extends Processor {
	@Override
	String process(Object obj) {
		return Arrays.toString(((String) obj).split(" "));
	}
}

