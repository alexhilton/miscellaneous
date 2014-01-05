#!/usr/bin/perl  -w
my $debug = shift @ARGV // 1;
my $magic_number = int(1 + rand 100);
print "magic number is $magic_number\n" if $debug;
my $guess = "goon";
print "Your guess(1~100):";
while (1) {
    chomp($guess = <STDIN>);
    print "input guess is '$guess'\n" if $debug;
    #if ($guess eq "quit" || $guess eq "exit" || $guess eq "") {
    # better choice with regular expression
    if ($guess =~ /quit|exit|^\s*$/i) {
        last;
    }
    if ($guess == $magic_number) {
        print "Congratulation, you got it\n";
        last;
    }
    print "Too high\n" if ($guess > $magic_number);
    print "Too low\n" if ($guess < $magic_number);
    print "try again with another guess(1~100):";
}
