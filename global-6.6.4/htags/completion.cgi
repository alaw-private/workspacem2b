#! /usr/bin/perl
#
# Copyright (c) 2010, 2016 Tama Communications Corporation
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
#
use strict;
use warnings;
#
# Set PATH and remove some environment variables to satisfy taint mode.
# If you installed idutils outside of the PATH, you should add the place 
# to the PATH. 
#
$ENV{'PATH'} = '/bin:/usr/bin:/usr/local/bin';
delete @ENV{'IFS', 'CDPATH', 'ENV', 'BASH_ENV'};
my $script_name = 'completion.cgi';
my $global_command = '/home/gitpod/exec/bin/global';
sub error_and_exit {
	print STDERR "$script_name: " . $_[0] . "\n";
	exit 1;
}
my $query_string = defined($ENV{'QUERY_STRING'}) ? $ENV{'QUERY_STRING'} : '';
my @pairs = split (/&/, $query_string);
my %form;
foreach (@pairs) {
	my($name, $value) = split(/=/, $_);
	$value =~ tr/+/ /;
	$value =~ s/%([\dA-Fa-f][\dA-Fa-f])/pack("C", hex($1))/eg;
	$form{$name} = $value;
}
if (!defined($form{'q'})) {
	error_and_exit("request value is null.");
}
my $q = $form{'q'};
#
# Execute a ceremony to satisfy taint mode.
#
if ($q =~ /\A(.*)\z/) {
        $q = $1;
} else {
        $q = '';
}
my $type = $form{'type'};
my $flags = '';
my $limit = 0;
if ($type eq 'definition' || $type eq 'reference') {
	$flags = 'c';
} elsif ($type eq 'symbol') {
	$flags = 'cs';
} elsif ($type eq 'path') {
	$flags = 'cP';
} elsif ($type eq 'idutils') {
	$flags = 'cI';
} elsif ($type eq 'grep') {
	exit(0);	# Ignored because completion for grep is groundless.
} else {
	error_and_exit("invalid type name.");
}
if ($form{'icase'}) {
	$flags .= 'i';
}
if ($form{'other'}) {
	$flags .= 'o';
}
if ($form{'limit'}) {
	$limit = $form{'limit'};
}
if (-d "cgi-bin") {
	# This code avoids the bug of the python built-in web server.
	chdir("cgi-bin");
	if ($?) {
		error_and_exit("Couldn't change 'cgi-bin' directory.");
	}
}
my $gtagsroot = '';
if (-f "../GTAGSROOT" && open(GTAGSROOT, "../GTAGSROOT")) {
	$gtagsroot = <GTAGSROOT>;
	chop($gtagsroot);
	close(GTAGSROOT);
} else {
	$gtagsroot = "../..";
}
chdir($gtagsroot);
print "Content-Type: text/html\n\n";
if ($^O eq 'MSWin32') {
	#
	# This code was commented out, because it may have a security hole in the
	# future.  To use this code, please uncomment in your own responsibility.
	#
	#open(PIPE, $global_command . " -${flags}e \"$q\" |");
	error_and_exit("Feature not implemented.");
} else {
	open(PIPE, "-|") || exec $global_command, '-'.$flags.'e', $q;
}
if ($limit > 0) {
	while (<PIPE>) {
		print if ($limit-- > 0);
	}
} else {
	print <PIPE>;
}
close(PIPE);
exit(0);
