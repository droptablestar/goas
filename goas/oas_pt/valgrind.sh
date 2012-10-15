#!/bin/sh
valgrind --tool=memcheck --leak-check=yes --dsymutil=yes $3 $1 $2
