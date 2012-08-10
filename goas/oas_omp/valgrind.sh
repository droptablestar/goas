#!/bin/sh
valgrind --tool=memcheck --leak-check=yes --dsymutil=yes $2 $1
