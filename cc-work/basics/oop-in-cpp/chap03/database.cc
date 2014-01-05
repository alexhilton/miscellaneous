/*
 * database.cc
 *
 * implement a database class which manipulates a table of Employee
 * records. It can create database, add and remove records, display
 * table and find information about one record.
 * It is based on Employee class which maniputlates the information
 * of an employee including name, boss, department and ID. ID should
 * be unique for each employee. ID is the key field of database as
 * key to query and compare.
 */
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;


// class Employee
class Employee {
private:
  string name; //
  string ID; //
  string boss; // boss employee belongs to
  string depart; // department employee belongs to
public:
  Employee();
  Employee( const string &n, const string &id, const string &b, 
	    const string &d );
  void setName( const string &n );
  void setID( const string &id );
  void setBoss( const string &b );
  void setDepart( const string &d );
  string getName() const;
  string getID() const;
  string getBoss() const;
  string getDepart() const;
  int compare( const Employee &another );
  Employee copy();
  void display();
  void print();
};

Employee::Employee() {
  name = "unkown";
  ID = "000-00-0000";
  boss = "unkown";
  depart = "unkown";
}

Employee::Employee( const string &n, const string &id, const string &b,
		    const string &d ) {
  name = n;
  ID = id;
  boss = b;
  depart = d;
}

void Employee::setName( const string &n ) {
  name = n;
}

void Employee::setID( const string &id ) {
  ID = id;
}

void Employee::setBoss( const string &b ) {
  boss = b;
}

void Employee::setDepart( const string &d ) {
  depart = d;
}

string Employee::getName() const {
  return name;
}

string Employee::getID() const {
  return ID;
}

string Employee::getBoss() const {
  return boss;
}

string Employee::getDepart() const {
  return depart;
}

int Employee::compare( const Employee &another ) {
  string tmpid = another.getID();
  if ( ID == tmpid ) {
    return 0;
  } else if ( ID > tmpid ) {
    return 1;
  } else {
    return -1;
  }
}

// this is a bad implementation of copy, violating information hiding rule
/*Employee Employee::copy() {
  Employee res;
  res.name = name;
  res.ID = ID;
  res.boss = boss;
  res.depart = depart;
  return res;
}*/

// this is much better
Employee Employee::copy() {
  Employee res( name, ID, boss, depart );
  return res;
}

void Employee::print() {
  cout << "\tname is: " << name << endl;
  cout << "\tID is: " << ID << endl;
  cout << "\tboss is: " << boss << endl;
  cout << "\tdepart is: " << depart << endl << endl;
}

void Employee::display() {
  cout << left << setw( 15 ) << ID;
  cout << left << setw( 20 ) << name;
  cout << left << setw( 15 ) << depart;
  cout << left << setw( 20 ) << boss << endl;
}

// class Database
class Database {
private:
  Employee *table;
  int size;
  int cursor;
public:
  Database();
  Database( const int &s );
  Database create( const int &s );
  void setSize( const int &s );
  ~Database();
  void sortRecord();
  void addRecord( const Employee &emp );
  void removeRecord( const string &id );
  void display();
  Employee getByIndex( const int &index );
  int find( const string &id );
};

Database::Database() {
  table = NULL;
  size = 0;
  cursor = 0;
}

Database::Database( const int &s ) {
  size = s;
  table = new Employee[ size ];
  cursor = 0;
}

Employee Database::getByIndex( const int &index ) {
  Employee tmp;
  if ( index < cursor && index >= 0 ) {
    return table[ index ];
  }
  return tmp;
}

Database::~Database() {
  delete []table;
}

Database Database::create( const int &s ) {
  Database tmp( s );
  return tmp;
}

void Database::setSize( const int &s ) {
  size = s;
}

void Database::addRecord( const Employee &emp ) {
  if ( find( emp.getID() ) == -1 ) {
    table[ cursor++ ] = emp;
  }
}

void Database::removeRecord( const string &id ) {
  int i;
  i = find( id );
  if ( i != -1 ) {
    for ( ; i < cursor-1; i++ ) {
      table[ i ] = table[ i+1 ];
    }
  }
}

void Database::display() {
  int i;
  cout << left << setw( 15 ) << "ID";
  cout << left << setw( 20 ) << "Name";
  cout << left << setw( 15 ) << "Department";
  cout << left << setw( 20 ) << "Boss" << endl;
  for ( i = 0; i < 70; i++ ) {
    cout << "-";
  }
  cout << endl;
  for ( i = 0; i < cursor; i++ ) {
    table[ i ].display();
  }
  for ( i = 0; i < 70; i++ ) {
    cout << "-";
  }
  cout << endl;
}

int Database::find( const string &id ) {
  int i;
  for ( i = 0; i < cursor; i++ ) {
    if ( table[ i ].getID() == id ) {
      return i;
    }
  }
  return -1;
}

// insertion sort
void Database::sortRecord() {
  int i, j;
  Employee tmp;
  for ( i = 1; i < cursor; i++ ) {
    tmp = table[ i ].copy();
    for ( j = i; j > 0 && tmp.compare( table[ j-1 ] ) < 0; j-- ) {
      table[ j ] = table[ j-1 ].copy();
    }
    table[ j ] = tmp.copy();
  }
}

// main program
int main( int argc, char *argv[] ) {
  Database nefw( 10 );
  ifstream in;
  in.open( "database.in" );
  Employee tmp;
  string name, id, boss, depart;
  while ( in >> id >> name >> boss >> depart ) {
    tmp.setName( name );
    tmp.setID( id );
    tmp.setBoss( boss );
    tmp.setDepart( depart );
    nefw.addRecord( tmp );
  }
  in.close();
  nefw.display();
  cout << "sorting..." << endl;
  nefw.sortRecord();
  nefw.display();
  return 0;
}
