#!/usr/bin/env python

"""A Python version of grep utility.
    Search one or more named input files against one ore more given patterns.
    Print the line containing the match, if there are any.
"""

from optparse import OptionParser;
import re;
import fileinput;
import os.path;

FILENAME = '\033[92m';
LINENO = '\033[94m';
MATCH = '\033[91m';
ENDC = '\033[0m';

class MultiMatcher(object):
    """A set of searchable Regular Expression Patterns
        Accept one or more regular expression such that if any one of them
        matches a line the first successful match is returned.
    """
    def __init__(self, multipattern, ignore_case):
        flags = 0;
        if ignore_case:
            flags = re.IGNORECASE;

        self.multipattern = [re.compile(pattern, flags) for pattern in multipattern];

    def search(self, line):
        for pattern in self.multipattern:
            m = pattern.search(line);
            if m is not None:
                return m;

def build_options():
    parser = OptionParser(usage = "usage: %prog [options] -e PATTERN files", version = "%prog 1.0");
    parser.add_option("-i", "--ignore-case", action = "store_true", dest = "ignore_case",
            default = False, help = "ignore case of letters when matching");
    parser.add_option("-r", "--recursive", action = "store_true", dest = "recursive",
            default = False, help = "search for files in directory recursively");
    parser.add_option("-n", "--negative", action = "store_true", dest = "negative",
            default = False, help = "show the lines that does not match the pattern");
    parser.add_option("-e", "--regexpr", action = "append", dest = "regexpr",
            help = "specify pattern expression on which to match");
    return parser;

def do_matching(filename, matcher):
    for line in fileinput.input(filename):
        line = line.rstrip();

        match = matcher.search(line);
        if options.negative:
            if match is None:
                print "%s%s:%s%d %s%s" % (FILENAME, fileinput.filename(), LINENO, fileinput.filelineno(), ENDC, line);
        else:
            if match is not None:
                first_part = line[:match.start()];
                the_match = line[match.start():match.end()];
                second_part = line[match.end():];
                print "%s%s:%s%d %s%s%s%s%s%s" % (FILENAME, fileinput.filename(), LINENO, fileinput.filelineno(), \
                        ENDC, first_part, MATCH, the_match, ENDC, second_part);

def main():
    global options;
    parser = build_options();
    options, args = parser.parse_args();
    if not options.regexpr:
        parser.error("You must specify at least one PATTERN");
    if not args:
        parser.error("You must specify at least one input file or directory");

    matcher = MultiMatcher(options.regexpr, options.ignore_case);

    for filename in args:
        if not os.path.exists(filename):
            print "No such file or directory: ", filename;
            continue;

        if options.recursive and os.path.isdir(filename):
            for root, dirs, files in os.walk(filename):
                [do_matching(os.path.join(root, entry), matcher) for entry in files];
        elif os.path.isfile(filename):
            do_matching(filename, matcher);

if __name__ == "__main__":
    main();
