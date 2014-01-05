/*
 * MiniMusicPlayer2
 * Alex Hilton
 * (c) Copyright 2009 Alex Hilton, All rights reserved 
 */
package exercises.headfirst.beatbox;
import javax.sound.midi.*;

/**
 * Version 2 of Beatbox in chapter 12
 * @author gongzhihui
 */
public class MiniMusicPlayer2 implements ControllerEventListener {
	public void go() {
		try {
			Sequencer sequencer = MidiSystem.getSequencer();
			sequencer.open();
			
			int[] eventsIWant = { 127 };
			sequencer.addControllerEventListener(this, eventsIWant);
			
			Sequence seq = new Sequence(Sequence.PPQ, 4);
			Track track = seq.createTrack();
			
			for (int i = 5; i < 60; i += 4) {
				track.add(makeEvent(144, 1, i, 100, i));
				track.add(makeEvent(176, 1, 127, 0, i));
				track.add(makeEvent(128, 1, i, 127, i));
				track.add(makeEvent(128, 1, i, 100, i+2));
			}
			sequencer.setSequence(seq);
			sequencer.setTempoInBPM(220);
			sequencer.start();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * We gonna do soemthing when this event happens
	 */
	public void controlChange(ShortMessage event) {
		System.out.println("0x1a");
	}
	
	/**
	 * Make a customized Midi event with the arguments provided
	 * @param cmd
	 * @param channel
	 * @param one
	 * @param two
	 * @param tick
	 * @return
	 */
	public MidiEvent makeEvent(int cmd, int channel, int one, int two, int tick) {
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
	
	/*
	 * Test driver
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		MiniMusicPlayer2 music = new MiniMusicPlayer2();
		music.go();
	}

}
