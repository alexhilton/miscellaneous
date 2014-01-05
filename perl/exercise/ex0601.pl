#!/usr/bin/perl -w

my %names = ("fred" => "flintstone", "barney" => "rubble", "wilma" => "flintstone");

while (chomp(my $person = <STDIN>)) {
    if (exists $names{$person}) {
        print "$names{$person}\n";
    } else {
        print "sorry man, we cannot report your family name\n";
    }
}
