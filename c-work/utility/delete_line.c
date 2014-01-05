
/*
 * delete_line.c
 */
#include <stdio.h>

int main( int argc, char **argv ) {
	FILE *in, *out;
	char str[1024];
	if ( argc < 2 ) {
		perror( "No input file(s)." );
		return 1;
	}
	char *p;
	char tmpfile[] = "tmp.tmp";
	int i;
	for ( i = 1; i < argc; i++ ) {
		if ( ( in = fopen( argv[ i ], "r" ) ) == NULL ) {
			perror( argv[ i ] );
			continue;
		}
		if ( (out = fopen( tmpfile, "w" )) == NULL ) {
			perror( tmpfile );
			continue;
		}
		while ( fgets( str, sizeof( str ), in ) != NULL ) {
			p = str;
			while ( isspace( *p ) ) {
				p++;
			}
			while ( isdigit( *p ) ) {
				p++;
			}
			if ( *p == '.' ) {
				p++;
			}
			fputs( p, out );
		}
		fclose( in );
		fclose( out );
		if ( remove( argv[ i ] ) != 0 ) {
			perror( "remove" );
		}
		if ( rename( tmpfile, argv[ i ] ) != 0 ) {
			perror( "rename" );
		}
	}
	return 0;
}
