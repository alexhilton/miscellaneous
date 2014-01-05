import java.util.*;
import java.io.*;
import org.w3c.dom.*;
import org.xml.sax.*;
import javax.xml.parsers.*;

public class ParsePlaylist {
    private List<Playlist> plists;
    private String xmlFile;

    public ParsePlaylist(String xmlFile) {
	this.xmlFile = xmlFile;
	plists = new ArrayList<Playlist>();
    }

    public void doParse() {
	try {
	    DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
	    DocumentBuilder builder = factory.newDocumentBuilder();
	    File file = new File(xmlFile);
	    Document document = builder.parse(file);
	    Element root = document.getDocumentElement();
	    NodeList children = root.getChildNodes();
	    Playlist playlist = new Playlist();
	    System.out.println("for lists: '" + root.getNodeName() + "', it has " + children.getLength() + " playlists");
	    for (int i = 0; i < children.getLength(); i++) {
		Node child = children.item(i);
		if (child instanceof Element) {
		    if (child.getNodeName().equals("playlist")) {
			playlist = parsePlaylist(child);
			plists.add(playlist);
		    }
		}
	    }
	} catch (IOException e) {
	    e.printStackTrace();
	} catch (ParserConfigurationException e) {
	    e.printStackTrace();
	} catch (SAXException e) {
	    e.printStackTrace();
	}
    }

    private Playlist parsePlaylist(Node node) {
	NodeList children = node.getChildNodes();
	Playlist playlist = new Playlist();
	Song song = new Song();
	System.out.println("for playlist: '" + node.getNodeName() + "', it has " + children.getLength() + " songs");
	for (int i = 0; i < children.getLength(); i++) {
	    Node child = children.item(i);
	    if (child instanceof Element) {
		String nodeName = child.getNodeName();
		if ( nodeName.equals("name")) {
		    String playlistName = child.getFirstChild().getNodeValue().trim();
		    playlist.setName(playlistName);
		} else if (nodeName.equals("song")) {
		    song = parseSong(child);
		    playlist.addSong(song);
		}
	    }
	}
	return playlist;
    }

    private Song parseSong(Node node) {
	NodeList children = node.getChildNodes();
	Song song = new Song();
	System.out.println("for song: '" + node.getNodeName() + "', it has " + children.getLength() + " descriptions");
	for (int i = 0; i < children.getLength(); i++) {
	    Node child = children.item(i);
	    if (child instanceof Element) {
		String nodeName = child.getNodeName();
		if (nodeName.equals("name")) {
		    String songName = child.getFirstChild().getNodeValue().trim();
		    song.setName(songName);
		} else if (nodeName.equals("path")) {
		    String songPath = child.getFirstChild().getNodeValue().trim();
		    song.setPath(songPath);
		} else if (nodeName.equals("filename")) {
		    String filename = child.getFirstChild().getNodeValue().trim();
		    song.setFilename(filename);
		} else if (nodeName.equals("size")) {
		    String size = child.getFirstChild().getNodeValue().trim();
		    song.setSize(Integer.parseInt(size));
		}
	    }
	}
	return song;
    }

    public List<Playlist> getLists() {
	return plists;
    }

    // test driver
    public static void main(String[] args) {
	ParsePlaylist parser = new ParsePlaylist("playlist.xml");
	parser.doParse();
	List<Playlist> plists = parser.getLists();
	for (Playlist playlist : plists) {
	    System.out.println("====================Playlist: " + playlist.getName() + "=================");
	    for (int i = 0; i < playlist.size(); i++) {
		System.out.println(playlist.getSong(i));
	    }
	    System.out.println("=======================================================================\n\n");
	}
    }
}
