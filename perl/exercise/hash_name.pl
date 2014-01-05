#!/bin/perl
@names = qw ( fred betty barney dino wilma pebbles bamm-bamm );
print @names;
@indices = <STDIN>;
@indices = chomp(@indices);
print @indices;
foreach $i (@indices) {
    print $names[ $i-1 ];
}
