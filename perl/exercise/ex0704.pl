# exercise of 4 in chapter 7

foreach (<STDIN>) {
    if (/[A-Z]([ \t]|[a-z]+)/) {
	print;
    }
}
