while (<>) {
    chomp;
    #if (/(\w*a)(?:\s|$)/) {
    if (/(\b\w*a\b)/) {
	print "Matched: |$`<$&>$'|\n";
	print "\$1 contains '$1'\n";
    } else {
	print "No match: |$_|\n";
    }
}
