#! /bin/sh

make par
cat $1 | ./par
make temp
./temp