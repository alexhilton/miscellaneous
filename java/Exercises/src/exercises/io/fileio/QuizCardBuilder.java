/**
 * 
 */
package exercises.io.fileio;
import javax.swing.*;
import javax.swing.filechooser.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.*;
/**
 * @author gongzhihui
 *
 */
public class QuizCardBuilder {
	private JFrame mainFrame;
	private JPanel mainPanel;
	private JButton nextCard;
	private ArrayList<QuizCard> cardList;
	private JTextArea questionView;
	private JTextArea answerView;
	private JButton exit;
	
	public void go() {
		mainFrame = new JFrame();
		mainFrame.setTitle("Quiz Card Builder");
		mainFrame.setSize(new Dimension(480, 580));
		mainFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

		mainPanel = new JPanel();
		Font bigFont = new Font("sanserif", Font.BOLD, 24);
		/*
		 * Build top menu
		 */
		JMenuBar menubar = new JMenuBar();
		JMenu file = new JMenu("File");
		JMenuItem newItem = new JMenuItem("New Session");
		newItem.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				cardList.clear();
				clearCard();
			}
		});
		JMenuItem save = new JMenuItem("Save Session");
		save.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String question = questionView.getText();
				String answer = answerView.getText();
				if ((question != null && !question.equals("")) 
						&& (answer != null && !answer.equals(""))) {
					QuizCard card = new QuizCard(questionView.getText(), answerView.getText());
					cardList.add(card);
					clearCard();
				}
				
				JFileChooser chooser = new JFileChooser();
				chooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
				FileNameExtensionFilter textOnly = new FileNameExtensionFilter("Text file", "txt");
				chooser.setFileFilter(textOnly);
				if (chooser.showSaveDialog(mainFrame) != JFileChooser.APPROVE_OPTION) {
					return;
				}
				saveFile(chooser.getSelectedFile());
			}
		});
		file.add(newItem);
		file.add(save);
		menubar.add(file);
		
		// build text area
		questionView = new JTextArea(6, 20);
		questionView.setEditable(true);
		questionView.setWrapStyleWord(true);
		questionView.setLineWrap(true);
		questionView.setFont(bigFont);
		JScrollPane questionScroll = new JScrollPane(questionView);
		questionScroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		questionScroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		
		answerView = new JTextArea(6, 20);
		answerView.setEditable(true);
		answerView.setLineWrap(true);
		answerView.setWrapStyleWord(true);
		answerView.setFont(bigFont);
		JScrollPane answerScroll = new JScrollPane(answerView);
		answerScroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		answerScroll.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		
		nextCard = new JButton("Next card");
		nextCard.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				QuizCard card = new QuizCard(questionView.getText(), answerView.getText());
				cardList.add(card);
				clearCard();
			}
		});
		exit = new JButton("Exit");
		exit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				mainFrame.dispose();
				System.exit(0);
			}
		});
		
		JLabel questionLabel = new JLabel("Question: ");
		JLabel answerLabel = new JLabel("Answer: ");
		
		cardList = new ArrayList<QuizCard>();
		
		mainPanel.add(questionLabel);
		mainPanel.add(questionScroll);
		mainPanel.add(answerLabel);
		mainPanel.add(answerScroll);
		mainPanel.add(nextCard);
		mainPanel.add(exit);
		
		mainFrame.setJMenuBar(menubar);
		mainFrame.add(mainPanel);
	}
	
	/*
	 * If you put setVisible ahead of creating and adding widgets, you cannot see those
	 * widgets until you refresh the frame(wndow). So always put setVisible() at bottom
	 * of your code. It is also a good idea that the user of this class calls 
	 * setVisible(). It can make sure that everything on the frame will be shown and the
	 * caller can decide whether to show the panel.
	 */
	public void setVisible(boolean visible) {
		mainFrame.setVisible(visible);
	}
	
	private void saveFile(File file) {
		assert(file != null);
		try {
			BufferedWriter writer = new BufferedWriter(new FileWriter(file));
			for (QuizCard card : cardList) {
				writer.write(card.getQuestion() + "/");
				writer.write(card.getAnswer() + "\n");
			}
			
			writer.close();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	private void clearCard() {
		questionView.setText("");
		answerView.setText("");
		questionView.requestFocus();
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		QuizCardBuilder gui = new QuizCardBuilder();
		gui.go();
		gui.setVisible(true);
	}

}
