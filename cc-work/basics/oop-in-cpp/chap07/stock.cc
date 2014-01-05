/*
 * stock.cc
 * 
 * generate three reports on the daily performance of stocks for an
 * exhcange such as NASDAQ. 
 */
#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>
#include <string>
using namespace std;

// ** filename and miscellaneous globals
const string infile = "stock.dat";
const string unkown = "????";

// objects generated from input records
class Stock {
public:
  Stock() {
    symbol = unkown;
    open = close = gainLoss = volume = 0;
  }
  Stock( const string &s, double o, double c, unsigned long v ) {
    symbol = s;
    open = o;
    close = c;
    volume = v;
    gainLoss = ( close - open ) / open;
  }
  const string &getSymbol() const {
    return symbol;
  }
  double getOpen() const {
    return open;
  }
  double getClose() const {
    return close;
  }
  unsigned long getVolume() const {
    return volume;
  }
  double getGainLoss() const {
    return gainLoss;
  }
private:
  string symbol;
  double open;
  double close;
  double gainLoss;
  unsigned long volume;
};

// *** sort comparision: gains in descending order
struct WinCmp {
  bool operator()( const Stock &s1, const Stock &s2 ) const {
    return s1.getGainLoss() > s2.getGainLoss();
  }
};

// *** sort comparision: volume in descending order
struct VolCmp {
  bool operator()( const Stock &s1, const Stock &s2 ) const {
    return s1.getVolume() > s2.getVolume();
  }
};

// *** invoke by function objects to do output
void output( bool volFlag, const string &name, const char *openLabel,
	     double open, const char *closeLabel, double close,
	     const char *gainLabel, double gain,
	     const char *volLabel, unsigned long vol ) {
  cout << "*** " << name << endl;
  if ( volFlag ) { // true, volume comes first
    cout << "\t" << volLabel << vol << endl;
  }
  cout << '\t' << gainLabel << gain << endl;
  cout << '\t' << openLabel << open << endl;
  cout << '\t' << closeLabel << close << endl;
  if ( !volFlag ) { // false, volume comes last
    cout << '\t' << volLabel << vol << endl;
  }
}

// *** write Stocks sorted by gain-loss to standard output
struct Winptr {
  void operator()( const Stock &s ) const {
    output( false, s.getSymbol(), 
	    "Opening Price: ", s.getOpen(),
	    "Closing Price: ", s.getClose(),
	    "% Changed:     ", s.getGainLoss() * 100,
	    "Volume:        ", s.getVolume() );
  }
};

// *** write Stocks sorted by volume to standard output
struct Volptr {
  void operator()( const Stock &s ) const {
    output( true, s.getSymbol(), 
	    "Opening Price: ", s.getOpen(),
	    "Closing Price: ", s.getClose(),
	    "% Changed:     ", s.getGainLoss() * 100,
	    "Volume:        ", s.getVolume() );
  }
};

void herald( const char *s );
void input( deque< Stock > &s );

int main() {
  deque< Stock > stock;
  // input stocks and separate into vectors for winners, losers and
  // break=evens
  input( stock );
  // sort winners in descending order and output
  herald( "Gainers in descending order: " );
  sort( stock.begin(), stock.end(), WinCmp() );
  for_each( stock.begin(), stock.end(), Winptr() );

  // output losers in ascending order
  herald( "Losers in ascending order: " );
  for_each( stock.rbegin(), stock.rend(), Winptr() );

  // sort volume in descending order and output
  herald( "Volume in descending order: " );
  sort( stock.begin(), stock.end(), VolCmp() );
  for_each( stock.begin(), stock.end(), Volptr() );
  return 0;
}

void input( deque< Stock > &s ) {
  string n;
  double o, c;
  unsigned long v;
  ifstream input( infile.c_str() );
  // read input until end-of-file, creating a stock object per input
  //  record
  while ( input >> n >> o >> c >> v ) {
    s.insert( s.end(), Stock( n, o, c, v ) );
  }
  input.close();
}

void herald( const char *s ) {
  cout << endl << "******* " << s << endl;
}
