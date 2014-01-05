while (<>) {
    chomp;
    if (/\s+$/) {
	print "$_|\n";
    }
}
