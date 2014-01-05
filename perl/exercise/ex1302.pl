#!/usr/bin/perl -w
print "Enter a directory:";
chomp(my $dir = <STDIN>);
if ($dir =~ /^\s*$/) {
    $dir = "";
}
chdir $dir or die "cannot enter $dir: $!\n";
# including all files dot and dot begins
my @all_files = glob ".* *"; # or new fashion way <.* *>
print "@all_files\n";
# or in a hard code
my @files;
# did you notice that it always dot because we have changed to here
if ($dir =~ /^\s*$/) {
    $dir = ".";
}
opendir DIR, $dir or die "cannot open $dir:$!";
foreach (readdir DIR) {
    # correct match should be /^\./ '+' is redundant
    if ($_ =~ /^\.+/) {
        #next;
    }
    push @files, $_ if -e -r -w -s $_;
}
@files = sort @files;
print "@files\n";
