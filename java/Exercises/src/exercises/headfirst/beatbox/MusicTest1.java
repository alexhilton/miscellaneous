/**
 * Chap11.exception
 * A fairy tale of exception
 */
package exercises.headfirst.beatbox;

import javax.sound.midi.*;
/**
 * @author gongzhihui
 *
 */
public class MusicTest1 {
	public void play() {
		try {
			Sequencer sequencer = MidiSystem.getSequencer();
			System.out.println("Successfully got a sequencer");
		} catch (MidiUnavailableException e) {
			System.out.println("Bummer: " + e.getMessage());
			e.printStackTrace();
		}
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MusicTest1 test = new MusicTest1();
		test.play();
	}

}
