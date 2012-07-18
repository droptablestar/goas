#! /bin/sh
set -e

make lib/par
cat $1 | lib/par
make lib/temp
lib/temp