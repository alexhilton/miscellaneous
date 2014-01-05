# exercise of 5 in chapter 7

foreach (<STDIN>) {
    if (/(\S)\g{-1}/) {
	print;
    }
}
