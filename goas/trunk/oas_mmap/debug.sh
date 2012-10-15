#! /bin/sh

sudo rm /cores/*
rm temp*
cat $1 | bin/par
make tempD DEBUG='-g -ggdb'
