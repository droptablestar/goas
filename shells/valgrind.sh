#!/bin/sh
cd ../bin
valgrind --tool=memcheck --leak-check=yes --dsymutil=yes $1 $2
