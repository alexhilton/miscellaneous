#!/usr/bin/perl -w
use 5.010;
use strict;

sub greet {
    my($name) = @_;
    state $last_name;
    if (defined($last_name)) {
        print "Hi $name, $last_name is also here!\n";
    } else {
        print "Hi $name, You are the first one here!\n";
    }
    $last_name = $name;
    $name;
}

&greet("Fred");
&greet("Barney");
