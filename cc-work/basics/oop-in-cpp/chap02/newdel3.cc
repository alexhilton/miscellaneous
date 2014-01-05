/*
 * newdel3.cc
 * more on new and delete operators.
 */
#include <iostream>
#include <string>
using namespace std;

typedef struct Elephant {
  string name;
  struct Elephant *next;
} Elephant;

void print( const Elephant *p );
Elephant *get();
void free( const Elephant *p );

int main() {
  Elephant *head;
  head = get();
  print( head );
  free( head );
  return 0;
}

/*
 * get elephants dynamically allocates storage for nodes.
 * It builds the linked list and stores user-supplied
 * names in the name member of the nodes. It returns a 
 * pointer to the first such node.
 */
Elephant *get() {
  Elephant *current, *first;
  int response;
  // allocate first node;
  current = new Elephant;
  //store name of first Elephant;
  first = current;
  cout << endl << "name: ";
  cin >> current->name;

  // prompt user about another Elephant
  cout << endl << "Add another? (1--yes, 0--no): ";
  cin >> response;
  // add elephants to list until user signals halt.
  while ( response == 1 ) {
    //allocate another elephant nodes.
    current = current->next = new Elephant;
    // store name.
    cout << "Name: ";
    cin >> current->name;
    cout << "add another Elephant (1--yes, 0--no): ";
    cin >> response;
  }
  return first;
}

/*
 * print steps through the linked list pointed to by p.
 */
void print( const Elephant *p ) {
  int cnt = 1;
  cout << endl << endl << endl;
  while ( p != NULL ) {
    cout << "Elephant number " << cnt++ << " is " << p->name << endl;
    p = p->next;
  }
}

/*
 * free spaces.
 */
void free( const Elephant *p ) {
  Elephant *tp;
  while ( p != NULL ) {
    tp = p->next;
    delete p;
    p = tp;
  }
}
