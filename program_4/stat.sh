#!/bin/bash

echo -e "dlist\tmtf\ttranspose\tskip" > compare.txt
for i in {10..3500..10}
do
echo $i
./a.out $i >> compare.txt
done