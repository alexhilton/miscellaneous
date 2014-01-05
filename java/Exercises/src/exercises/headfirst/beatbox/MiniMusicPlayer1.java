/*
 * MiniMusicPlayer1
 * Alex Hilton
 * (c) copyright 2009 Alex Hilton all rights reserved 
 */
package exercises.headfirst.beatbox;
import javax.sound.midi.*;

/**
 * Version one of Beatbox in chapter 12
 * @author gongzhihui
 */
/*
 * Version one of Beatbox in chapter 12
 * Use a static method makeEvent() to avoid duplicate code
 */
public class MiniMusicPlayer1 {
	/**
	 * Create a customized midi event
	 * @param cmd
	 * @param channel
	 * @param one
	 * @param two
	 * @param tick
	 * @return the event created by those args
	 * @author gongzhihui
	 */
	// use this method to avoid duplicate codes
	public static MidiEvent makeEvent(int cmd, int channel, int one,
			int two, int tick) {
		MidiEvent event = null;
		try {
			ShortMessage a = new ShortMessage();
			a.setMessage(cmd, channel, one, two);
			event = new MidiEvent(a, tick);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return event;
	}
	/**
	 * Test driver
	 * @author gongzhihui
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			Sequencer sequencer = MidiSystem.getSequencer();
			sequencer.open();
			
			Sequence seq = new Sequence(Sequence.PPQ, 4);
			Track track = seq.createTrack();
			
			for (int i = 5; i < 61; i += 4) {
				// 144 is note ON, 128 is note OFF
				track.add(makeEvent(144, 1, i, 100, i));
				track.add(makeEvent(128, 1, i, 100, i+2));
			}
			
			sequencer.setSequence(seq);
			sequencer.setTempoInBPM(220);
			sequencer.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
