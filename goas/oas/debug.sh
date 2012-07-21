#! /bin/sh

set -e

make src/par DEBUG='-g -ggdb'
cat $1 | bin/par
make bin/tempD DEBUG='-g -ggdb'
bin/tempD