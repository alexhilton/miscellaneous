#!/usr/bin/perl -w
use 5.010;

my $debug = shift @ARGV // 1;
my $magic_number = int(1 + rand 100);
print "magic number is $magic_number\n" if $debug;
my $guess = "goon";
print "You guess(1~100):";
while (1) {
    chomp($guess = <STDIN>);
    print "input guess is '$guess'\n" if $debug;
    given ($guess) {
        when (/quit|exit|^\s*$/i) {
            print "Goodbye, have a nice day\n";
            last;
        }
        when ($_ == $magic_number) {
            print "Congratulation, you got it\n";
            last;
        }
        when ($_ > $magic_number) {
            print "Too high\n";
            continue
        }
        when ($_ < $magic_number) {
            print "Too low\n";
            continue
        }
        default {
            print "try again with another guess(1~100):";
        }
    }
}
