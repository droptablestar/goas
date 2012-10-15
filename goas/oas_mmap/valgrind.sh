#!/bin/sh
valgrind --tool=memcheck --leak-check=yes --dsymutil=yes $1 $2
