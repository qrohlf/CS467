#!/bin/sh

make lab2

for i in {0..30};
    do 
    echo "rendering frame $i"
    bin/lab2 prefix $i $i &
done
wait
echo "Rendering complete"