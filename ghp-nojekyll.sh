#!/bin/bash
#set -x

branch=$1

[[ -z $branch ]] && branch=gh-pages


if ! git ls-tree  --name-only $branch 2> /dev/null | grep -q \.nojekyll ; then
    curbranch=$(git branch --show-current)
    upstream=$(dirname $(git rev-parse --abbrev-ref --symbolic-full-name @{u}))
   if [[ -z $curbranch ]]; then
     echo "ERROR: cannot determine current branch ... aborting"
     exit -1
   fi
   if [[ -z $upstream ]]; then
       echo "ERROR: cannot determine upstream ... aborting"
       exit -1
   fi
   if ! git checkout $branch
   then
     echo "ERROR: cannot switch to $branch ... please fix and retry"
     exit -1
   fi
   touch .nojekyll
   git add .nojekyll
   git commit -m "adding .nojekyll"
   git push $upstream $branch
   git switch $curbranch
fi
