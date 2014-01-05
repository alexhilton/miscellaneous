while (<>) {
    chomp;
    #if (/\w+a(?:\s|$)/) {
    if (/a\b/) {
	print "Matched: |$`<$&>$'|\n";
    } else {
	print "No match: |$_|\n";
    }
}
