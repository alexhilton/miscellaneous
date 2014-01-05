#!/usr/bin/perl -w
$^I = ".bak";
while (<>) {
    chomp;
    # to swap must use a tmp
    # just like: tmp = a; a = b; b = tmp;
    s/fred/\n/gi;
    s/wilma/fred/gi;
    s/\n/fred/gi;
    print;
}
