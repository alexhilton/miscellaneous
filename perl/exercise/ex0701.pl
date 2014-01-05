# exercise of 1 in chapter 07

foreach (<STDIN>) {
    # so you can choose your favorite delimiter
    #if (/fred/) {
    #if (m%fred%) {
    if (m{fred}) {
	print;
    }
}
