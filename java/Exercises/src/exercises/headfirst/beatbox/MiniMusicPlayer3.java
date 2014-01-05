/*
 * MiniMusicPlayer3
 * Alex Hilton
 * (c) Copyright 2009 Alex Hilton, All rights reserved 
 */
package exercises.headfirst.beatbox;
import javax.sound.midi.*;
import javax.swing.*;
import java.awt.*;
/**
 * MiniMusic version 3 with drawing a ramdom sized and colored rectangle
 * as the note off event handler
 * @author gongzhihui
 */
public class MiniMusicPlayer3 {
	/**
	 * Inner class which draws a random-sized, random-colored rectangle acts
	 * as an event listener of Note off.
	 * @author Alex Hilton
	 */
	private class MyDrawPanel extends JPanel implements ControllerEventListener {
		private boolean msg = false;
		
		public void controlChange(ShortMessage event) {
			msg = true;
			repaint();
		}
		
		public void paintComponent(Graphics g) {
			if (msg) {
				Graphics2D g2d = (Graphics2D) g;
				
				// Clear the window first
				g2d.setColor(Color.white);
				g2d.fillRect(0, 0, getWidth(), getHeight());
				
				// Create a random color
				int red = (int) (Math.random() * 250);
				int green = (int) (Math.random() * 250);
				int blue = (int) (Math.random() * 250);
				g2d.setColor(new Color(red, green, blue));
				
				// Create a random size
				int height = (int) ((Math.random() * 120) + 10);
				int width = (int) ((Math.random() * 120) + 10);
				int x = (int) ((Math.random() * 40) + 10);
				int y = (int) ((Math.random() * 40) + 10);
				
				// A rectangle with random size and random color
				g2d.fillRect(x, y, width, height);
				
				msg = false;
			}
		}
	}
	
	private JFrame mainWindow = new JFrame("My First Music Video");
	private MyDrawPanel mainPanel;
	
	private void setupGUI() {
		mainPanel = new MyDrawPanel();
		mainWindow.setContentPane(mainPanel);
		mainWindow.setBounds(30, 30, 300, 300);
		mainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainWindow.setVisible(true);
	}
	
	public void go() {
		setupGUI();
		
		try {
			Sequencer sequencer  = MidiSystem.getSequencer();
			sequencer.open();
			sequencer.addControllerEventListener(mainPanel, new int[] {127});
			Sequence seq = new Sequence(Sequence.PPQ, 4);
			Track track = seq.createTrack();
			
			int r = 0;
			for (int i = 0; i < 60; i += 4) {
				r = (int) ((Math.random() * 50) + 1);
				track.add(makeEvent(144, 1, r, 100, i));
				track.add(makeEvent(176, 1, 127, 0, i));
				track.add(makeEvent(128, 1, r, 100, i+2));
			}
			
			sequencer.setSequence(seq);
			sequencer.start();
			sequencer.setTempoInBPM(120);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/**
	 * Make a customized event
	 * @author gongzhihui
	 */
	private MidiEvent makeEvent(int cmd, int channel, int one, int two, int tick) {
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
		MiniMusicPlayer3 mini = new MiniMusicPlayer3();
		mini.go();
	}

}
