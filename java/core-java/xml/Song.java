import java.io.File;

public class Song {
    private String name;
    private String path;
    private String filename;
    private int size;

    public void setSize(int size) {
	this.size = size;
    }
    public int getSize() {
	return size;
    }
    public Song() {
	name = "";
	path = "";
	filename = "";
    }

    public void setName(String name) {
	this.name = name;
    }

    public void setPath(String path) {
	this.path = path;
    }
    public void setFilename(String filename) {
	this.filename = filename;
    }

    public String toString() {
	return "Song: '" + name + "' at '" + path + File.separator + filename +
		"'\n\tthe file size is: " + size;
    }
}
