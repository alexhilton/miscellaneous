#!/usr/bin/perl -w
my %words;
my $word = undef;
while (chomp($word = <STDIN>)) {
    if (exists $words{$word}) {
        $words{$word} += 1;
    } else {
        $words{$word} = 1;
    }
}
my @keys = keys %words;
@keys = sort @keys;
foreach (@keys) {
    printf "'%s' appears %d times\n", $_, $words{$_};
}
