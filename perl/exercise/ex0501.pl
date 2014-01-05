#!/usr/bin/perl -w
# I love perl, it really nice, neaty and handy
#print reverse <>;

# or more hard way
my @lines;
foreach (<>) {
    push @lines, $_;
}
@lines = reverse @lines;
print "@lines";
