/*
 * Beatbox
 * Alex Hilton
 * (c) Copyright 2009 Alex Hilton, all rights reserved 
 */
package exercises.headfirst.beatbox;
import javax.swing.*;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.sound.midi.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.io.*;
import java.net.*;
/**
 * @author gongzhihui
 *
 */
/*
 * Beatbox.java
 * #(@) Dec 31 2009
 * 		Add network function, you can communicate with other clients now
 * #(@) Dec 31 2009
 * 		Add buttons "Save Pattern" and "Restore Pattern"
 * #(@) Dec 30 2009
 * 		Initial verion, GUI and basic functions
 */
public class Beatbox {
	/** Incoming list */
	private JList incomingList;
	
	private JTextField userMessage;
	
	private int nextNum;
	
	private Vector<String> listVector = new Vector<String>();
	
	private String userName;
	
	private ObjectOutputStream out;
	
	private ObjectInputStream in;
	
	private HashMap<String, boolean[]> otherSequenceMap = new HashMap<String, boolean[]>();
	
	/** The beat boxes are checkboxes */
	/* We store the checkboxes in an ArrayList */
	private ArrayList<JCheckBox> checkboxes;
	
	/** Then music player */
	private Sequencer sequencer;
	
	/** The music */
	private Sequence sequence;
	
	private Sequence mySequence = null;
	
	/** the track, where the music message are */
	private Track track;
	
	/** The names of the instruments */
	/* Use an array of Strings for building the GUI */
	private String[] instrumentNames =  {
			"Bass Drum", // 0
			"Closed Hi-Hat", // 1
			"Open Hi-Hat", // 2
			"Acoustic Snare", // 3
			"Crash Cymbal", // 4
			"Hand Clap", // 5
			"High Tom", // 6
			"Hi Bongo", // 7
			"Maracas", // 8
			"Whistle", // 9
			"Low Conga", // 10
			"Cowbell", // 11
			"Vibraslap", // 12
			"Low-mid Tom", // 13
			"High Agogo", // 14
			"Open Hi Conga" // 15
	};
	
	/** instrument id */
	private int[] instruments = {
			35, 42, 46, 38, 49, 39, 50, 60,
			70, 72, 64, 56, 58, 47, 67, 63
	};
	
	public Beatbox() {
		userName = System.getProperty("user.name");
	}
	
	/**
	 * Start up the Application
	 */
	public void startup() {
		// Open connection to the server
		try {
			Socket socket = new Socket("127.0.0.1", 8888);
			out = new ObjectOutputStream(socket.getOutputStream());
			in = new ObjectInputStream(socket.getInputStream());
			Thread operator = new Thread(new RemoteReader());
			operator.start();
		} catch (Exception e) {
			System.out.println("Cannot connect -- you wlll have to play alone");
		}
		
		buildGUI();
	}
	/**
	 * Create and build the GUI
	 */
	public void buildGUI() {
		JFrame mainWindow = new JFrame("Cyber Beatbox");
		mainWindow.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		BorderLayout backgroundLayout = new BorderLayout();
		JPanel background = new JPanel(backgroundLayout);
		/*
		 * an empty border gives us a margin between the edges of the
		 * panel and where the components are placed.
		 * Purely aesthetic.
		 */
		background.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
		
		checkboxes = new ArrayList<JCheckBox>();
		
		// setup buttons
		Box buttonBox = new Box(BoxLayout.Y_AXIS);
		
		JButton start = new JButton("Start");
		start.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				buildTrackAndStart();
			}
		});
		buttonBox.add(start);
		
		JButton stop = new JButton("Stop");
		stop.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				sequencer.stop();
			}
		});
		buttonBox.add(stop);
		
		JButton upTempo = new JButton("Tempo Up");
		upTempo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				float tempoFactor = sequencer.getTempoFactor();
				sequencer.setTempoFactor((float) (tempoFactor * 1.03));
			}
		});
		buttonBox.add(upTempo);
		
		JButton downTempo = new JButton("Tempo Down");
		downTempo.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				float tempoFactor = sequencer.getTempoFactor();
				sequencer.setTempoFactor((float) (tempoFactor * .97f));
			}
		});
		buttonBox.add(downTempo);
		
		JButton savePattern = new JButton("Save Pattern");
		savePattern.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				boolean[] checkboxState = new boolean[256];
				
				// Fill checkboxState
				for (int i = 0; i < 256; i++) {
					checkboxState[i] = checkboxes.get(i).isSelected();
				}
				
				// Serialize checkboxState
				try {
					FileOutputStream fos = new FileOutputStream(new File("beatbox.pattern"));
					ObjectOutputStream op = new ObjectOutputStream(fos);
					op.writeObject(checkboxState);
					op.close();
				} catch (IOException e) {
					e.printStackTrace();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
		buttonBox.add(savePattern);
		
		JButton restorePattern = new JButton("Restore Pattern");
		restorePattern.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				boolean[] checkboxState = null;
				
				// Deserialize the checkboxState
				try {
					FileInputStream fis = new FileInputStream(new File("beatbox.pattern"));
					ObjectInputStream io = new ObjectInputStream(fis);
					checkboxState = (boolean[]) io.readObject();
					io.close();
				} catch (IOException e) {
					e.printStackTrace();
				} catch (Exception e) {
					e.printStackTrace();
				}
				
				// Set checkboxes
				for (int i = 0; i < 256; i++) {
					checkboxes.get(i).setSelected(checkboxState[i]);
				}
				
				/*
				 * Stop whatever is currently playing. And rebuild the sequence using
				 * the new state of checkbox in ArrayList
				 */
				sequencer.stop();
				buildTrackAndStart();
			}
		});
		buttonBox.add(restorePattern);
		
		JButton sendPattern = new JButton("Send Pattern");
		sendPattern.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				// Make an arraylist of just the state of the checkboxes
				boolean[] checkboxState = new boolean[256];
				for (int i = 0; i < 256; i++) {
					checkboxState[i] = checkboxes.get(i).isSelected();
				}
				
				String messageToSend = null;
				try {
					out.writeObject(userName + (nextNum++)
							+ ": " + userMessage.getText());
					out.writeObject(checkboxState);
				} catch (Exception e) {
					System.out.println("Sorray dude. Could not send it to the server!");
				}
				userMessage.setText("");
			}
		});
		buttonBox.add(sendPattern);
		
		JButton clearPattern = new JButton("Clear Pattern");
		clearPattern.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				sequencer.stop();
				
				// Walk through checkboxes, set each of them unselected
				for (JCheckBox cb : checkboxes) {
					cb.setSelected(false);
				}
			}
		});
		buttonBox.add(clearPattern);
		
		JButton exitProgram = new JButton("Exit Program");
		exitProgram.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				System.exit(0);
			}
		});
		buttonBox.add(exitProgram);
		
		// build up user message box
		userMessage = new JTextField();
		buttonBox.add(userMessage);
		
		incomingList = new JList();
		incomingList.addListSelectionListener(new ListSelectionListener() {
			public void valueChanged(ListSelectionEvent event) {
				// TODO Auto-generated method stub
				if (!event.getValueIsAdjusting()) {
					String selected = (String) incomingList.getSelectedValue();
					if (selected != null) {
						// Now go to the map and change the sequence
						boolean[] selectedState = (boolean[]) otherSequenceMap.get(selected);
						changeSequence(selectedState);
						sequencer.stop();
						buildTrackAndStart();
					}
				}
			}
		});
		JScrollPane listScroll = new JScrollPane(incomingList);
		buttonBox.add(listScroll);
		incomingList.setListData(listVector);
		
		Box nameBox = new Box(BoxLayout.Y_AXIS);
		for (int i = 0; i < instrumentNames.length; i++) {
			nameBox.add(new Label(instrumentNames[i]));
		}
		
		background.add(BorderLayout.EAST, buttonBox);
		background.add(BorderLayout.WEST, nameBox);
		
		mainWindow.getContentPane().add(background);
		
		GridLayout grid = new GridLayout(16, 16);
		grid.setVgap(1);
		grid.setHgap(2);
		JPanel mainPanel = new JPanel(grid);
		background.add(BorderLayout.CENTER, mainPanel);
		
		for (int i = 0; i < 256; i++) {
			JCheckBox checkbox = new JCheckBox();
			checkbox.setSelected(false);
			checkboxes.add(checkbox);
			mainPanel.add(checkbox);
		}
		
		setupMidi();
		
		mainWindow.setBounds(50, 50, 300, 300);
		mainWindow.pack();
		mainWindow.setVisible(true);
	}
	
	private void changeSequence(boolean[] checkboxState) {
		for (int i = 0; i < 256; i++) {
			checkboxes.get(i).setSelected(checkboxState[i]);
		}
	}
	
	public void setUserName(String userName) {
		this.userName = userName;
	}
	
	/*
	 * Create and initialize the Midi sound system
	 */
	private void setupMidi() {
		try {
			sequencer = MidiSystem.getSequencer();
			sequencer.open();
			sequence = new Sequence(Sequence.PPQ, 4);
			track = sequence.createTrack();
			sequencer.setTempoInBPM(120);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	/*
	 * Walk through 256 check boxes to gather the information, then create message
	 * and events according to them, and then make events.
	 */
	private void buildTrackAndStart() {
		int[] trackList = null;
		
		// Get rid of old track, add a new one
		sequence.deleteTrack(track);
		track = sequence.createTrack();
		
		// Do this for each of 16 Rows
		for (int i = 0; i < 16; i++) {
			trackList = new int[16];
			int key = instruments[i];
			
			// Do this for each of the beats for this row
			for (int j = 0; j < 16; j++) {
				JCheckBox cb = (JCheckBox) checkboxes.get(j + (i*16));
				if (cb.isSelected()) {
					trackList[j] = key;
				} else {
					trackList[j] = 0;
				}
			}
			
			makeTracks(trackList);
			track.add(makeEvent(176, 1, 127, 0, 16));
		}
		
		// note off message
		track.add(makeEvent(192, 9, 1, 0, 15));
		
		// After setuping, we can start playing
		try {
			sequencer.setSequence(sequence);
			sequencer.setLoopCount(sequencer.LOOP_CONTINUOUSLY);
			sequencer.start();
			sequencer.setTempoInBPM(120);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void makeTracks(int[] list) {
		for (int i = 0; i < 16; i++) {
			int key = list[i];
			if (key != 0) {
				track.add(makeEvent(144, 9, key, 100, i));
				track.add(makeEvent(128, 9, key, 100, i+1));
			}
		}
	}
	
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
		Beatbox alex = new Beatbox();
		alex.setUserName("Eagle");
		alex.buildGUI();
		
	}

	private class RemoteReader implements Runnable {
		private boolean[] checkboxState = null;
		private String nameToShow = null;
		Object obj = null;
		
		public void run() {
			try {
				while ((obj = in.readObject()) != null) {
					System.out.print("got an object from server: ");
					System.out.println(obj.getClass());
					
					String nameToShow = (String) obj;
					checkboxState = (boolean[]) in.readObject();
					otherSequenceMap.put(nameToShow, checkboxState);
					listVector.add(nameToShow);
					incomingList.setListData(listVector);
				}
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}
}
