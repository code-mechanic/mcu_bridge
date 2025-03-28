#!/bin/bash

##############################################################################
# file:    lint-dcf.sh
# author:  Mohan Arunachalam <hashincludefun.h@gmail.com>
# brief:   Utility to apply a common formatting to Delta Configuration Files
#          Example or baseline files that are in source control can be
#          difficult to compare from commit to commit without common format.
#          This script uses the `jq` utility to apply a standard format (4
#          space indent).
#
# usage:   ./lint-dcf.sh <path to DCF directory>
##############################################################################

CONFIG_DIR=${1%/}

for f in $CONFIG_DIR/*.dcf; do
    echo $f
    jq --indent 4 . $f > jq.tmp && mv jq.tmp $f
    if [ 0 != $? ]; then
        rm jq.tmp
    fi
done
