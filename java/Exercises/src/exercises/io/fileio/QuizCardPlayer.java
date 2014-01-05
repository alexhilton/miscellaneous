/**
 * 
 */
package exercises.io.fileio;
import javax.swing.*;
import javax.swing.filechooser.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
/**
 * @author gongzhihui
 *
 */
public class QuizCardPlayer {
	private JFrame mainFrame;
	private JPanel mainPanel;
	private ArrayList<QuizCard> cards;
	private JButton nextCard;
	private JButton showAnswer;
	private QuizCard currentCard;
	private JTextArea textView;
	private int currentCardIndex;
	private JButton exit;
	
	public void go() {
		mainFrame = new JFrame();
		mainFrame.setSize(new Dimension(480, 500));
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		mainFrame.setTitle("Quiz Card Player");
		
		mainPanel = new JPanel();
		
		JMenuBar menubar = new JMenuBar();
		JMenu file = new JMenu("File");
		JMenuItem loadItem = new JMenuItem("Load file");
		loadItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				JFileChooser chooser = new JFileChooser();
				chooser.setFileSelectionMode(JFileChooser.FILES_ONLY);
				FileNameExtensionFilter textOnly = new FileNameExtensionFilter("Text file", "txt");
				chooser.setFileFilter(textOnly);
				if (chooser.showOpenDialog(mainFrame) != JFileChooser.APPROVE_OPTION) {
					return;
				}
				File file = chooser.getSelectedFile();
				
				// now read data from this selected file
				cards = new ArrayList<QuizCard>();
				try {
					BufferedReader reader = new BufferedReader(new FileReader(file));
					String line = null;
					while ((line = reader.readLine()) != null) {
						String[] result = line.split("/");
						QuizCard card = new QuizCard(result[0], result[1]);
						cards.add(card);
					}
					
					reader.close();
					
					if (cards.size() < 1) {
						textView.setText("There are no questions in the file!");
						showAnswer.setEnabled(false);
						nextCard.setEnabled(false);
					} else {
						currentCardIndex = 0;
						currentCard = cards.get(currentCardIndex++);
						textView.setText(currentCard.getQuestion());
						showAnswer.setEnabled(true);
						nextCard.setEnabled(true);
					}
				} catch (IOException e) {
					e.printStackTrace();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
		file.add(loadItem);
		menubar.add(file);
		
		textView = new JTextArea(10, 24);
		Font font = new Font("sanserif", Font.BOLD, 18);
		textView.setFont(font);
		textView.setLineWrap(true);
		textView.setWrapStyleWord(true);
		textView.setEditable(true);
		textView.setText("Please select a data file!");
		JScrollPane questionScroll = new JScrollPane(textView);
		questionScroll.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
		questionScroll.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
		
		mainPanel.add(questionScroll);
		
		showAnswer = new JButton("Show Answer");
		showAnswer.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				textView.setText(currentCard.getAnswer());
				showAnswer.setEnabled(false);
			}
		});

		showAnswer.setEnabled(false);
		
		nextCard = new JButton("Next Card");
		nextCard.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				if (currentCardIndex < cards.size()) {
					currentCard = cards.get(currentCardIndex++);
					textView.setText(currentCard.getQuestion());
					showAnswer.setEnabled(true);
				} else {
					textView.setText("That is the last card");
					showAnswer.setEnabled(false);
					nextCard.setEnabled(false);
				}
			}
		});
		nextCard.setEnabled(false);
		
		exit = new JButton("Exit");
		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent eveent) {
				mainFrame.dispose();
				System.exit(0);
			}
		});
		
		mainPanel.add(showAnswer);
		mainPanel.add(nextCard);
		mainPanel.add(exit);
		mainFrame.add(mainPanel);
		mainFrame.setJMenuBar(menubar);
	}
	
	private void makeCard(String line) {
		String[] result = line.split("/");
		QuizCard card = new QuizCard(result[0], result[1]);
		cards.add(card);
	}
	
	public void setVisitble(boolean visible) {
		mainFrame.setVisible(visible);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		QuizCardPlayer player = new QuizCardPlayer();
		player.go();
		player.setVisitble(true);
	}

}
