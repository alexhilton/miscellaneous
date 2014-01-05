/*
 * Project: Bookmark
 *
 * main program
 */
#include "book.hh"
#include "bookmark.hh"

int main( int argc, char *argv[] ) {
	string filename = "bookmark.dat";
	Bookmark bm( filename );
	char ch;
	char flag = 'a';
	string n;
	Book b;
	deque< Book >::iterator index;
	cout << "Welcome to Bookmark program" << endl;
	while ( true ) {
		cout << "[l]ist books" << endl;
		cout << "[a]dd book" << endl;
		cout << "[d]elete book" << endl;
		cout << "[s]earch book" << endl;
		cout << "[o]pen book" << endl;
		cout << "[c]lose book" << endl;
		cout << "[q]uit Bookmark" << endl;
		cout << ">";
		cin >> ch;
		switch ( ch ) {
		case 'l':
			bm.listBook( flag );
			break;
		case 'a':
			b.input();
			bm.addBook( b );
			break;
		case 'd':
			cout << "Name: ";
			getline( cin, n );
			b.setName( n );
			bm.deleteBook( b );
			break;
		case 'o':
			cout << "Name: ";
			getline( cin, n );
			b.setName( n );
			index = bm.searchBook( b );
			index->output();
			break;
		case 'c':
			b.input();
			bm.closeBook( b );
			break;
		case 'q':
			return 0;
		default:
			cerr << "Unkown commands!" << endl;
			return 0;
		}
	}
	return 0;
}
