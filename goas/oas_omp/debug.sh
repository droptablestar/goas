#! /bin/sh

sudo rm /cores/*
cat $1 | bin/par
make tempD DEBUG='-g -ggdb'
