#!/usr/bin/perl

use strict;
my %symbols;
my %addr;
my $count = 0;
my $offset = 0xd800;
my $ram_addr = 0;

$addr{"COMTAB"} = {
	label => "COMTAB", 
	bsize => 0,
	ADDR => 0xeee,
};

while(<>) {
	chomp;
	my $line = $_;

	$line =~ s/\s*;.*$//;

	if ($line =~ /^\s+\*=\$(\S+)/) {
		$count = hex($1);
		$ram_addr = hex($1);
	} elsif ($line =~ /^\s+\*=(\S+)/) {

		if (exists($symbols{$1})) {
			my $s = $symbols{$1};
			#$s =~ s/^.//;
			$count = $s - $offset; 
			#print "RESETTING COUNT!! $1\n";
		} else {
			print "NO SYMBOL: $1\n";
		}		

	} elsif ($line =~ /^(\S+)\s+\=\s*\*\s*$/) {

		if (!exists($addr{$1})) {
			$addr{$1} = {
				label => $1, 
				bsize => $0,
				ADDR => $ram_addr, 
			};
		}

	} elsif ($line =~ /^(\S+)\s+=\s*\$(\S+)$/) {
		$symbols{$1} = hex($2);
		#print "New Symbol: $symbols{$1}\n";
	} elsif ($line =~ /^(\S+)\s+=\s*\S+$/) {

			$addr{$1} = {
				label => $1, 
				bsize => $0,
				ADDR => $ram_addr, 
			};

	} elsif ($line =~ /\s+\*=\s*\$(\S+)/) {
		$ram_addr = hex($1);
	} elsif ($line =~ /^\s*(\S+)\s*=\s*(\S+)\s*/) {
		$symbols{$1} = $2;
		#print "$1 equals $2\n";
	} elsif ($line =~ /^(\S+:)?\s*\.(PAGE|TITLE)/) {
	} elsif ($line =~ /^(\S+):\s+\.ORG/) {
		if (!exists($addr{$1})) {
			$addr{$1} = {
				label => $1, 
				bsize => $0,
				ADDR => $ram_addr, 
			};
		}
	} elsif ($line =~ /^\s*(LIST|DEGFLG)/) {
	} elsif ($line =~ /^\s*\.RES\s*(\S+)/) {
				$ram_addr += $1;
	} elsif ($line =~ /^((\S+):)?\s*(\S+)\s*(\S+)?$/) {
		#print "Label: $2\nCommand: $3\nArgs: $4\n";
		if ($3 eq ".RES") {
			if (!exists($addr{$2})) {
				$addr{$2} = {
					label => $2, 
					bsize => $4,
					ADDR => $ram_addr, 
				};
				$ram_addr += $4;
			}

			next;
		} 

		my $l = sprintf("%04x %04x $line\n", $count, $count + $offset);
		$count += get_op_length($3, $4);
		print $l;
	}

	#print "$line\n";
}

#for my $s (sort keys %symbols) {
#	print $s . " " . $symbols{$s} ."\n";
#}  

for my $r (sort keys %addr) {
	my $size = $addr{r}->{bsize};
	#print "$r $addr{$r}->{bsize} $addr{$r}->{addr}\n";
	#print "$r $addr{$r}->{addr} $addr{$r}->{bsize}\n";
}

sub
get_op_length
{
	my $op = shift;
	my $arg = shift;

	my $ret = 0;

	if (is_always_1($op)) {
		$ret = 1;	
	} elsif (is_always_2($op)) {
		$ret = 2;
	} elsif (is_always_3($op)) {
		$ret = 3;
	}

	if ($op =~ /^\.?BYTE$/) {
		$ret = scalar split(/,/, $arg);
	} elsif ($op eq ".WORD") {
		$ret = (scalar split(/,/, $arg)) * 2;
	}

	if ($arg =~ /^#/) { #immediate value
		$ret = 2;
	}

	if ($arg =~ /^\$((\S\S)(\S\S)?)$/) { #immediate value
		if (hex($1) > 0xFF) {
			$ret = 2;
		} else {
			$ret = 3;
		}
	}

	if ($arg =~ /^A$/) { #accumulator
		$ret = 1;
	}

	if ($arg =~ /\((\S+((\+|-)[^,]+)?)\),(y|Y)$/) {
		$ret = 2;

	} elsif ($arg =~ /^(([A-Z0-9]+)((\+|-)\d+)?),(x|X|y|Y)$/) {
		if (exists($addr{$2})) {
			my $h = $addr{$2};
			#for my $z (keys(%{$h})) {
			#	print "'$z' '$h->{$z}'\n";
			#}
			#print "Found Address for: $op $arg $h->{\"ADDR\"}\n";
			if ($h->{"ADDR"} < 0x100) {
				$ret = 2;
			} else {
				$ret = 3;
			}
		}
	}

	if ($arg =~ /^([A-Z0-9]+)((\+|-)\d+)?$/) { 
		if (exists($addr{$1})) {
			my $h = $addr{$arg};
			#for my $z (keys(%{$h})) {
			#	print "'$z' '$h->{$z}'\n";
			#}
			#print "Found Address for: $op $arg $h->{\"ADDR\"}\n";
			if ($h->{"ADDR"} < 0x100) {
				$ret = 2;
			} else {
				$ret = 3;
			}	
		}
	}

	if (!$ret) {
		print "Unresolved: $op $arg\n";
		$ret = 3;
	}
	
	#print "$op length $ret\n";
	return $ret;
}

sub
is_always_1
{
	my @a = qw(
	brk clc cld cli clv
	dex dey inx iny nop
	pha php pla plp rti
	rts sec sed sei tax
	tay tsx txa txs tya
);
	my $op = shift;

	for my $a (@a) {
		#print "\U$a" ." ".  "\U$op\n";
		if ("\U$a" eq "\U$op") {
			return 1;
		}
	}
	
	return 0;
}

sub
is_always_2
{
	my @a = qw(
	bcc bcs beq
	bmi bne bpl
	bvc bvs ldx
	ldy 	 
);
	my $op = shift;

	for my $a (@a) {
		#print "\U$a" ." ".  "\U$op\n";
		if ("\U$a" eq "\U$op") {
			return 1;
		}
	}
	
	return 0;
}

sub
is_always_3
{
	my @a = qw(
	jmp jsr 
);
	my $op = shift;

	for my $a (@a) {
		#print "\U$a" ." ".  "\U$op\n";
		if ("\U$a" eq "\U$op") {
			return 1;
		}
	}
	
	return 0;
}
