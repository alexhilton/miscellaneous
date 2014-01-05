#!/bin/perl
#calculate the circumestances of circle
$pi = 3.1415926;
$radius = <STDIN>;
if (!defined($radius)) {
    $radius = 0;
}
if ($radius <= 0) {
    print "circumstances is zero\n";
} else {
    print 2 * $pi * $radius, "\n";
}
