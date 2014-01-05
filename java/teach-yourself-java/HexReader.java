class HexReader {
    String[] input = {
	"000A110D1D260219",
	"78900F1318141E0C",
	"6A%97D45B0FFFFFF" // used to test catch statement
    };
    public static void main(String[] args) {
	HexReader hex = new HexReader();
	for (int i = 0; i < hex.input.length; i++) {
	    hex.readLine(hex.input[i]);
	}
    }

    void readLine(String code) {
	try {
	    for (int j = 0; j + 1 < code.length(); j += 2) {
		String sub = code.substring(j, j+2);
		int num = Integer.parseInt(sub, 16);
		if (num == 255) {
		    return;
		}
		System.out.print(num + " ");
	    } 
	} catch (NumberFormatException e) {
	    e.printStackTrace();
	} finally {
	    System.out.println("**");
	}
	return;
    }
}
