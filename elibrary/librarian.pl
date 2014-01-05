#!/usr/bin/perl -w

my $library_path = "/media/datastore/Computer\ Science";
&genHeader();
opendir LIB, $library_path or die "Cannot open $library_path: $!";
foreach $file (readdir LIB) {
    if ($file =~ /^.{1,2}$/) {
        next;
    }
    #print "one file in $library_path is $file\n";
    &genFileElement($file);
}
closedir LIB;
&genTail();

sub genHeader {
    print "<html>\n";
    print "<head>\n\t<title>eLibrary</title>\n</head>\n";
    print "<body>\n";
}

sub genTail {
    print "</body>\n";
}

sub genFileElement {
    my $file = shift @_;
    print "\t<p>" . $file . "</p>\n";
}
