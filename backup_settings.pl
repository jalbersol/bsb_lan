#!/usr/bin/perl

# This script retrieves all settings from the heater (optionally limted to a
# range limited by the first two command line arguments) and stores them in a
# CSV-style file.
# All you need to do is adjust the URL of BSB-LAN in the line below (including
# any potential credentials/passcode). Do NOT end the URL with a slash!

use utf8;
use open ':encoding(utf8)';

my $URL = "http://192.168.158.88";

my $from = $ARGV[0];
my $to = $ARGV[1];
if ($from le " " ) {
  $from = 0;
}
if ($to le " " ) {
  $to = 9999;
}

print "Creating backup for parameters $from to $to, this may take several minutes...\n";
my $date = `date "+%Y%m%d"`;
chomp ($date);
my $time = `date "+%H%M%S"`;
chomp ($time);

my $cmd = "wget -q -O - $URL/$from-$to";
print "CMD: $cmd\n";

if (-d "Data") {
  open (OUT, ">Data/backup_settings_${from}-${to}_${date}-${time}.csv");
} else {
  open (OUT, ">backup_settings-${from}-${to}_${date}-${time}.csv");
}
binmode(OUT, ":utf8");

my $dat = `date "+%x"`;
chomp ($d);
my $tim = `date "+%X"`;
chomp ($t);

print OUT "ProgNr;Kategorie;Name;Wert 1;Wert 2;Wert 3\n";
#if($from > 0) {
  print OUT "-1;CSV-Datei;Datum und Zeit;$dat;$tim;\n";
#}

open (WGET, "$cmd|");
while (my $line=<WGET>) {
  #    1 Uhrzeit und Datum -  Stunden/Minuten: 27.03.2021 15:35:02
  #    5 Uhrzeit und Datum -  Sommerzeitbeginn Tag/Monat: 25.
  #  500 Zeitprogramm Heizkreis 1 -  Mo: <ol style='margin-top:4px;'><li>05:00 - 22:00</li><li>--:-- - --:--</li><li>--:-- - --:--</li></ol>
  #  649 Ferien Heizkreis 2 -  Periode 1 Beginn Tag/Monat: ---
  #  682 Ferien Heizkreis P -  Betriebsniveau Ferien: 1 - Reduziert
  # 2702 Sitherm Pro -  Auslösen neuer Drifttest: 0 - Nein
  # 2727 Sitherm Pro -  Zünd und Überwach'bereich: 1 - Bereich 1
  # 2730 Sitherm Pro -  Ionisationsstrom: 0.00 &#181;A
  if ($line =~ /^\s*(\d+)\s+(.+)\s+-\s+(.+):\s+(.*)/) {
    #               Nr.     Kategorie  Name    Rest
    debug_print("M", $line);

    my $param_no   = $1;
    my $param_cat  = $2;
    my $param_name = $3;
    my $param_val1 = "";
    my $param_val2 = "";
    my $param_val3 = "";
    my $line_rest  = $4;

    if ($line_rest =~ /error/ || $line_rest =~ /unknown type/ || $line_rest =~ /not found/) {
      next;
    }

    $line_rest =~ s/[\r\n]//g;

    if($line_rest =~ /^<ol[^>]*><li>(.+)<\/li><\/ol>/) {
      # time program with html list
      debug_print("T", $line_rest);

      my @param_vals = split(/<\/li><li>/, $1);
      $param_val1 = $param_vals[0];
      $param_val2 = $param_vals[1];
      $param_val3 = $param_vals[2];

    } elsif($line_rest =~ /([^ ]+|\d{2}\.\d{2}\.\d{4} \d{2}:\d{2}:\d{2})(.*)/) {
      # default line  Wert                                         Einheit/Beschreibung        
      debug_print("D", $line_rest);

      $param_val1 = $1;
      $param_val2 = $2;

      $param_val2 =~ s/^\s+|\s+$//g; # trim
      $param_val2 =~ s/^-\s+//;

      $param_val2 =~ s/&#181;/µ/g;
      $param_val2 =~ s/&deg;/°/g;
      $param_val2 =~ s/&#037/%/g;

    } else {
      # unknown
      debug_print("U", $line_rest);

      next;
    }

    my $csv = "$param_no;$param_cat;$param_name;$param_val1;$param_val2;$param_val3";

    print "$csv\n";
    print OUT "$csv\n";
  } else {
    debug_print("I", $line);
  }
}

sub debug_print {
  return;
  my $message = $_[1];
  $message =~ s/\n/\\n/g;
  $message =~ s/\r/\\r/g;
  $message =~ s/\t/\\t/g;
  print "$_[0]: [".$message."]\n";
}