/**
 * 
 */
package exercises.io.fileio;

/**
 * @author gongzhihui
 *
 */
public class QuizCard {
	private String question;
	private String answer;
	
	public QuizCard() {}
	
	public QuizCard(String question, String answer) {
		this.question = question;
		this.answer = answer;
	}
	
	public String getQuestion() {
		return question;
	}
	
	public String getAnswer() {
		return answer;
	}
	
	public void setQuestion(String question) {
		this.question = question;
	}
	
	public void setAnswer(String answer) {
		this.answer = answer;
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

	}

}
