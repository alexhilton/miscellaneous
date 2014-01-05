/**
 * 
 */
package exercises.interfaces;

/**
 * @author gongzhihui
 *
 */
public class EnumExercise {
	public enum Weather {
		Wind,
		Cloud,
		Rain,
		Sun,
		Lightening,
		Thunder
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		EnumExercise one = new EnumExercise();
		System.out.println("enum Weather:");
		System.out.println("wind: " + Weather.Wind + " " + Weather.Wind.ordinal());
		System.out.println("Cloud: " + Weather.Cloud + " " + Weather.Cloud.ordinal());
		System.out.println("Rain: " + Weather.Rain + " " + Weather.Rain.ordinal());
		System.out.println("Sun: " + Weather.Sun + " " + Weather.Sun.ordinal());
		System.out.println("Lightening: " + Weather.Lightening + " " + Weather.Lightening.ordinal());
		System.out.println("Thunders: " + Weather.Thunder + " " + Weather.Thunder.ordinal());
	}

}
