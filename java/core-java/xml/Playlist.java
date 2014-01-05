import java.util.ArrayList;
import java.util.List;

public class Playlist {
    private List<Song> playlist;
    private String name;
    public Playlist() {
	playlist = new ArrayList<Song>();
	name = "";
    }

    public void addSong(Song song) {
	playlist.add(song);
    }
    public Song getSong(int index) {
	if (index >= 0 && index < playlist.size()) {
	    return playlist.get(index);
	}
	return null;
    }
    public int size() {
	return playlist.size();
    }
    public void setName(String name) {
	this.name = name;
    }
    public String getName() {
	return name;
    }
}