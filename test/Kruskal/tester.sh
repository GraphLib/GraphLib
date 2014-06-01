#!/bin/bash

if (($# != 1))
then
    printf "usage: <script> <testsCount>"
    exit 1
fi

generator=`./GraphGen`
firstTask=`./BoostKruskal`
secondTask=`./GraphLibKruskal`
check=`./checker`
testsCount=$1

rm -f result.log

for ((i = 1; i <= $testsCount; ++i));
do
    echo $generator &> /dev/null
    echo $firstTask &> /dev/null
    echo $secondTask &> /dev/null
    printf "Test $i: " &>> result.log
    echo $check &>> result.log
done
