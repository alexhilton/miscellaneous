#!/bin/perl
#duplicate the input string with n times, where n is input from user.
$line = <STDIN>;
if (!defined($line)) {
    $line = '';
}
$count = <STDIN>;
if (!defined($count)) {
    $count = 0;
}
print $line x $count, "\n";
