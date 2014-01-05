while (<>) {
    chomp;
    #if (/(?<got>\w+a)(?:\s|$)/) {
    if (/(?<got>\b\w*a\b)(?<more>.{0,5})/s) {
	print "Matched: |$`<$&>$'|\n";
	print "'got' contains '$+{got}$+{more}'\n";
    } else {
	print "No match: |$_|\n";
    }
}
