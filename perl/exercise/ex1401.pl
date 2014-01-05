#!/usr/bin/perl -w
print "Input a line of numbers separated by space:\n";
chomp ($line = <STDIN>);
@numbers = split / /, $line;
print "numbers are @numbers\n";
@numbers = sort { $a <=> $b } @numbers;
print "sorted numbers are @numbers\n";
@numbers = sort {$b <=> $a} @numbers;
print "another sorted are @numbers\n";
