while (<>) {
    chomp;
    if (/(?<got>\w+a)(?:\s|$)/) {
	print "Matched: |$`<$&>$'|\n";
	print "'got' contains '$+{got}'\n";
    } else {
	print "No match: |$_|\n";
    }
}
