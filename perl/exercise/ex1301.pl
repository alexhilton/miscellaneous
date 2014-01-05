#!/usr/bin/perl -w
print "Enter a directory:";
chomp(my $dir = <STDIN>);
if ($dir =~ /^\s*$/) {
    $dir = "";
}
chdir $dir or die "cannot enter $dir: $!\n";
my @all_files = glob "*"; # or '<*>'
print "@all_files\n";
# or in a hard code
my @files;
# it is always dot(current directory) actually, because we have chdir to $dir
if ($dir =~ /^\s*$/) {
    $dir = ".";
}
opendir DIR, $dir or die "cannot open $dir:$!";
foreach (readdir DIR) {
    if ($_ =~ /^\.+/) {
        next;
    }
    push @files, $_ if -e -r -w -s $_;
}
@files = sort @files;
print "@files\n";
