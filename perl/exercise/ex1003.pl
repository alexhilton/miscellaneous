#!/usr/bin/perl -w
$ENV{UNDEFINED} = undef;
$ENV{ZERO} = undef;
my @variables = keys %ENV;
foreach (sort @variables) {
    printf "'$_'->'%s'\n", ($ENV{$_} // "Undefined");
}
