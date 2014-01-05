#!/usr/bin/perl -w

sub max {
    my @list = @_;
    my $max = shift @list;
    $max = length $max;
    foreach (@list) {
        $len = length $_;
        if ($max < $len) {
            $max = $len;
        }
    }
    return $max;
}

my @variable = keys %ENV;
@variable = sort @variable;
my $width = &max(@variable);
foreach (@variable) {
    printf "'%${width}s' '%s'\n", $_, $ENV{$_};
}
