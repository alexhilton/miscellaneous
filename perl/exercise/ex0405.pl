#!/usr/bin/perl -w
use 5.010;
use strict;

sub greet {
    my($name) = @_;
    state @last_names;
    #if (defined($last_names[0])) {
    if (defined(@last_names)) {
        print "Hi $name, I've seen: @last_names\n";
    } else {
        print "Hi $name, You are the first one here!\n";
    }
    push(@last_names, $name);
}

&greet("Fred");
&greet("Barney");
&greet("Wilma");
&greet("Betty");
