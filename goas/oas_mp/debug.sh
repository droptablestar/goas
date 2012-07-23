#! /bin/sh

sudo rm -rf bin/*
sudo rm /cores/*
make bin/par DEBUG='-g -ggdb'
cat $1 | bin/par
make bin/tempD DEBUG='-g -ggdb'
#bin/tempD > junk