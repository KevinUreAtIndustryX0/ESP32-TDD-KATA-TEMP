#!/bin/bash
if [ -z "$1" ]
    then
        echo "Please add component name"
        exit
fi
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
pushd $DIR

cd components
mkdir $1
cd $1
mkdir include
mkdir test
touch "$1.c"
echo '#include "'$1'.h"' > $1.c
touch component.mk
touch CMakeLists.txt
echo 'idf_component_register(SRCS "'$1'.c"
                    INCLUDE_DIRS "include")' >CMakeLists.txt
cd test
touch component.mk
touch CMakeLists.txt
echo 'idf_component_register(SRC_DIRS "."
                    INCLUDE_DIRS "."
                    REQUIRES unity '$1')'>CMakeLists.txt
touch test_$1.c
echo '#include <limits.h>
#include "unity.h"
#include "'$1'.h"
TEST_CASE("New Test", "[tagme]")
{

}'>test_$1.c
cd ..
cd include
touch $1.h
echo "#pragma once">$1.h
cd $DIR
perl -i -pe 's/(?<=TEST\_COMPONENTS\s\")(.*?)(?=\")/$1 '$1'/g' test/CMakeLists.txt
perl -i -pe 's/(?<=TEST\_COMPONENTS\s\?\=\s)(.*?)(?=(\r\n|\n|\r))/$1 '$1'/g' test/Makefile
popd