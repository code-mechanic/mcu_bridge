#!/usr/bin/perl

#########################################################################################################
# File    lint
# Author  Mark Mulrooney <mark.mulrooney@iontra.com>
# Brief   Ensure files meet the clang-format style
#########################################################################################################

# Make sure we're doing things on the up and up
use v5.10.1;
use strict;
use warnings;
use File::Spec;
no warnings 'experimental::smartmatch';

# Subroutines
sub recursive_lint($);

# Globals
my %ignore_dirs = 
(
    "_build"   => 1,
    "cmake"    => 1,
    "doc"      => 1,
    "external" => 1,
);

my @ignore_pattern =
(
    "stm32g4xx",
    "SEGGER_",
    "cpu_cfg",
    "lib_cfg",
    "os_cfg",
    "Global",
    "bsp",
    "os_app_hooks",
    "os_trace_events",
    "startup_stm32g474xx",
);

# get current working directory and root directory
my ($temp1, $cwd, $temp2) = File::Spec->splitpath(__FILE__);
my $root_dir = $ARGV[0];

# concatenate to get path to .clang-format
my $path_to_file = "${root_dir}/${cwd}.clang-format";

########
# MAIN #
########

# Clear the return code
my $rc = 0;

if(!$root_dir)
{
    print("lint: Error root_directory must be supplied");
    exit(1);
}

# Clean up the root dir
chomp($root_dir);

# Ensure a valid directory was passed in
if(!(-d "$root_dir"))
{
    print("lint: Invalid root directory $root_dir");
    exit(1);
}

# Start in the current working environment
$rc = recursive_lint($root_dir);

# All done.
exit($rc);


###############
# Subroutines #
###############

##################################################
# Subroutine:   recursive_lint($)                #
# Details:      Traverse all source directories  #
#               for files to lint                #
##################################################
#
sub recursive_lint($)
{
    my ($path) = @_;
    my $fail_cnt = 0;

    chdir($path);
    my @list = `ls -1 "$path"`;

    # Loop through the current directory listing
    foreach my $item (@list)
    {
        chomp($item);
        my $tmp_path = $path . "/" . $item;

        # Do not include any ignore directories
        if(exists($ignore_dirs{$item}))
        {
            next;
        }

        # If its a directory, search it
        elsif(-d $tmp_path)
        {
            $fail_cnt += recursive_lint($tmp_path);
        }

        # Add the directory to the list
        elsif(($tmp_path =~ /\.h$/) or ($tmp_path =~ /\.c$/))
        {
            my $skip = 0;

            # Check if the file should be ignored
            foreach my $pattern (@ignore_pattern)
            {
                if($tmp_path =~ /$pattern/)
                {
                    $skip = 1;
                    last;
                }
            }

            # If its not a file to skip, check clang-format
            if(!$skip)
            {
                my @cat = `cat $tmp_path`;
                my @clang = `clang-format --style=file:$path_to_file $tmp_path`; 

                # Use smartmatch to determine if the file if formatted correctly
                if(!(@cat ~~ @clang))
                {
                    print("lint: Clang Fail - $tmp_path\r\n");
                    $fail_cnt++;
                }
            }
        }
    }

    return $fail_cnt;
}

