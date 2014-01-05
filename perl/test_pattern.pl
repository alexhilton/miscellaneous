my $pattern = "fred";
while (<>) {
    chomp;
    if (/$pattern/) {
	print "Matched: |$`<$&>$'|\n";
    } else {
	print "No match: |$_|\n";
    }
}
