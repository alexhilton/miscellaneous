/*
 * Project: Bookmark
 *
 * implementation of interface bookmark.h
 */
#include "bookmark.hh"

bool compare( const Book &b1, const Book &b2 ) {
	return b1 > b2;
}
Bookmark::Bookmark() {
	// to do: add default construction function here
}

/*void output( ofstream &out, Book &b ) {
	long a = b.getDate();
	out << b.getName() << endl;
	out << b.getChap() << endl;
	out << b.getTopic() << endl;
	out << b.getPage() << endl;
	out << ctime( &a ) << endl;
}*/

Bookmark::Bookmark( const string &fn ) {
	ifstream in;
	filename = fn;
	in.open( filename.c_str() );
	if ( !in.is_open() ) {
		cerr << "Cannot open file: " << filename << endl;
		exit( EXIT_FAILURE );
	}
	number = 0;
	string str;
	getline( in, str );
	cout << str << endl;
	number = atoi( str.c_str() );
	//getline( in, str );
	//in >> number; // the first line of file is number of records
	//cout << "the number is: " << number << endl;
	int i;
	for ( i = 0; i < number; i++ ) {
		Book b;
		string str;
		getline( in, str );
		cout << str << endl;
		b.setName( str );
		getline( in, str );
		cout << str << endl;
		unsigned int a = atoi( str.c_str() );
		b.setChap( a );
		getline( in, str );
		b.setTopic( str );
		getline( in, str );
		a = atoi( str.c_str() );
		b.setPage( a );
		getline( in, str );
		unsigned long d = atol( str.c_str() );
		b.setDate( d );
		//b.input( in );
		book.insert( book.end(), b );
	}
	in.close();
	sort( book.begin(), book.end(), compare );
	//cout << "finish reading." << endl;
}

Bookmark::~Bookmark() {
	ofstream out;
	out.open( filename.c_str() );
	if ( !out.is_open() ) {
		cerr << "Cannot open file: " << filename << endl;
		exit( EXIT_FAILURE );
	}
	out << number << endl; // first line of output file is number of records
	int i;
	for ( i = 0; i < number; i++ ) {
		/*out << book[i].getName() << endl;
		out << book[i].getChap() << endl;
		out << book[i].getTopic() << endl;
		out << book[i].getPage() << endl;
		out << book[i].getDate() << endl;*/
		book[ i ].output( out );
	}
	out.close();
}

void Bookmark::listBook( char flag ) {
	int size = 5;
	switch ( flag ) {
	case 'a':
		size = number;
		break;
	case 'g':
		size = 5;
		break;
	default:
		cerr << "Unkown listing option: " << flag << endl;
		exit( EXIT_FAILURE );
	}
	int i;
	for ( i = 0; i < size; i++ ) {
		book[ i ].output();
	}
}



void Bookmark::addBook( const Book &b ) {
	book.insert( book.end(), b );
	number++;
}

void Bookmark::deleteBook( const Book &b ) {
	/*if ( index = searchBook( b ) < 0 ) {
		cerr << "Cannot find book: " << b.getName() << endl;
		return;
	}*/
	deque< Book >::iterator index;
	index = find( book.begin(), book.end(), b );
	book.erase( index );
	number--;
}

deque< Book >::iterator Bookmark::searchBook( const Book &b ) {
	deque< Book >::iterator index;
	index = find( book.begin(), book.end(), b );
	return index;
}

void Bookmark::openBook( const Book &b ) {
	deque< Book >::iterator index;
	index = find( book.begin(), book.end(), b );
	index->output();
}

void Bookmark::closeBook( const Book &b ) {
	deque< Book >::iterator index;
	index = find( book.begin(), book.end(), b );
	index->setChap( b.getChap() );
	index->setTopic( b.getTopic() );
	unsigned int a = b.getPage();
	index->setPage( a );
}

void Bookmark::sortBook() {
	sort( book.begin(), book.end(), compare );
}
