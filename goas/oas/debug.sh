#! /bin/sh

set -e

make lib/par DEBUG='-g -ggdb'
cat $1 | lib/par
make lib/temp DEBUG='-g -ggdb'
lib/temp