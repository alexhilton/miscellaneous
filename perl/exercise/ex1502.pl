#!/usr/bin/perl -w
use 5.010;

print "Input a number:";
chomp(my $number = <STDIN>);
given ($number) {
    when ($_ % 3 == 0 and $_ % 5 == 0 and $_ % 7 == 0) {
        print "Fizz Bin Sausage\n";
    }
    when ($_ % 3 == 0 and $_ % 5 == 0) {
        print "Fizz Bin\n";
    }
    when ($_ % 5 == 0 and $_ % 7 == 0) {
        print "Bin Sausage\n";
    }
    when ($_ % 3 == 0 and $_ % 7 == 0) {
        print "Fizz Sausage\n"
    }
    when ($_ % 3 == 0) {
        print "Fizz\n";
    }
    when ($_ % 5 == 0) {
        print "Bin\n";
    }
    when ($_ % 7 == 0) {
        print "Sausage\n";
    }
    default {
        print "nope, $_ is not what we want\n";
    }
}

# better option
if ($number % 3 == 0) {
    print "Fizz ";
}
if ($number % 5 == 0) {
    print "Bin ";
}
if ($number % 7 == 0) {
    print "Sausage ";
}
print "\n";

# better option with given-when
given ($number) {
    when ($_ % 3 == 0) {
        print "Fizz ";
        continue
    }
    when ($_ % 5 == 0) {
        print "Bin ";
        continue
    }
    when ($_ % 7 == 0) {
        print "Sausage ";
        continue
    }
    default {
        print "\n";
    }
}
