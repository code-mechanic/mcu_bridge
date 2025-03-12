#!/bin/bash

###############################################################################
# file:    check-sub-branch.sh
# brief:   Check that a submodule is pointing to a commit on a given branch or
#          branch pattern.  Returns exit code 0 if the submodule commit is
#          found on a matching branch or 1 if not.
#
# usage:   check-sub-branch.sh <submodule> <branch_pattern>
#
# example: check-sub-branch.sh external/delta origin/develop
# example: check-sub-branch.sh external/delta origin/hotfix/*
#
###############################################################################

SUBMODULE=$1
BRANCH_PATTERN=$2

COMMIT=$(git submodule status $SUBMODULE | awk '{print $1}')

for BRANCH in $(git -C $SUBMODULE branch --list --remotes $BRANCH_PATTERN); do
    git -C $SUBMODULE merge-base --is-ancestor $COMMIT $BRANCH
    if [ "$?" -eq "0" ]; then
        echo "$SUBMODULE commit FOUND on $BRANCH."
        exit 0
    fi
    echo "$SUBMODULE commit is NOT on $BRANCH."
done

echo "$SUBMODULE commit is not on any matching branches."
exit 1
