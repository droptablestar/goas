#! /bin/bash
set -e

INC_DIR=../include
cat $1 | ../bin/par

g++ -o temp -g -ggdb -std=c++11 -I${INC_DIR} temp.cpp ../src/scan.cpp ../src/MMapLinux.cpp ../src/Meta.cpp ../src/Record.cpp ../src/Relation.cpp
# valgrind --dsymutil=yes --tool=callgrind --dump-line=yes ./temp > /dev/null
