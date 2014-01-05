# exercise of 6 in chapter 7

foreach (<STDIN>) {
    # both are okay, | is an operator, while meta are patterns
    # so, there is only one operator here, no precedence issue.
    #if (/((wilma).*(fred))|(fred.*wilma)/) {
    if (/wilma.*fred|fred.*wilma/) {
	print;
    }
}
