#!/bin/perl
#multiplicate two numbers input from user
$first = <STDIN>;
if (!defined($first)) {
    $first = 0;
}
$second = <STDIN>;
if (!defined($second)) {
    $second = 0;
}
print "the product of $first and $second is ", $first * $second, "\n";
