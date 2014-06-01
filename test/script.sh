#!/bin/bash

if (($# != 6))
then
    printf "usage: <script> <generator> <firstTask> <secondTask> <checker> <testsCount>"
    exit 1
fi

generator=`$2`
firstTask=`$3`
secondTask=`$4`
checker=`$5`
testsCount=$6

rm -f report.log

for ((i = 1; i <= $testsCount; ++i));
do
    echo $generator &> /dev/null
    echo $firstTask &> /dev/null
    echo $secondTask &> /dev/null
    printf "Test $i: " &>> result.log
    echo $checker &>> result.log
done
