#!/usr/bin/perl -W

use File::Find;
use MIME::Base64;
use URI::Escape;
use strict;

my @ directory_list = ('../src/web/');
my $files_processed = 0;

my $cprogramheader = <<END
#include "resources.h"

END
;

my $addroutes = "";
my $functions = "";

sub get_file_content {
   my ($filename) = @_;

   my $ret = "";
   open(IN, $filename) or die "Can't open $filename";
   while(<IN>) {
      chomp;
      my $line = $_;
      $line =~ s/\\/\\\\/g;
      $line =~ s/\"/\\\"/g;
      $line =~ s/\%/\%\%/g;
      $ret .= '"' . $line . '"' . "\n";
   }
   close(IN);
   return $ret;
}

sub get_image_content {
   my ($filename) = @_;

   my $ret = "";
   my $raw_image = "";
   my $image_string = "";
   open(IN, $filename) or die "Can't open $filename";
   $raw_image = do{ local $/ = undef; <IN>; };
   close(IN);

   $image_string = MIME::Base64::encode_base64($raw_image);
   $image_string =~ s/\\/\\\\/g;
   $image_string =~ s/\"/\\\"/g;
   $image_string =~ s/\%/\%\%/g;
   $image_string =~ s/\n/"\n"/g;

   $ret .= '"' . $image_string . '"' . "\n";
   return $ret;
}

#-----------------------------------------------------------------------
#Process a single file in a directory
#-----------------------------------------------------------------------
sub process_file {
    my $filename = $_;
    my $filename_full = $File::Find::name;
    my $filename_web = $File::Find::name;
    my $directory = $File::Find::dir;

    if($filename_full =~ /\.(.{2,4})$/) {
       my $type = $1;
       print "$filename - type: $type\n";
       if($type eq "css" || 
          $type eq "js" || 
          $type eq "html" ||
	  $type eq "jpg" ||
	  $type eq "jpeg" ||
	  $type eq "png") {
          $filename_web =~ s/..\/src\/web//;
          my $function_name = $filename_web;
          $function_name =~ s/[\/\.\-]/\_/g;
          $addroutes .= "   add_route(\"$filename_web\",$function_name);\n";  

          ###  put file content in one string
          my $content = "";
          my $generic_type = "";
	  if( $type eq "jpg" ||
	      $type eq "jpeg" ||
	      $type eq "png"){
	     $content = get_image_content($filename);
             $generic_type = "image";
	  } else {
             $content = get_file_content($filename);
             $generic_type = "text";
	  }

          my $one_function = <<END 
int $function_name(struct mg_connection *conn)
{
    mg_send_header(conn, "Content-Type", "$generic_type/$type");
    mg_send_header(conn, "Cache-Control", "public, max-age=604800");
    mg_printf_data(conn, $content);
    return MG_TRUE;
}

END
;
          $functions .= $one_function;
          $files_processed++;
       }
    }
    return;
}

find(\&process_file, @directory_list);
print "\nfiles processed : $files_processed\n";

open(OUT, ">../src/resources.c");
print OUT $cprogramheader;
print OUT $functions;
print OUT "\nvoid init_resources_table() {\n";
print OUT $addroutes;
print OUT "}\n\n";
close OUT;

