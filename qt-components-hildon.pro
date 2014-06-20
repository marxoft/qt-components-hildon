TEMPLATE = subdirs
SUBDIRS = sub_src sub_examples

sub_src.subdir = src
sub_examples.subdir = examples
sub_examples.depends = sub_src
