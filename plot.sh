#!/bin/bash

cat /var/www/log/temperature_0x402551705016222573.log \
    | awk -F# '{ print $2, $3 }' \
    > /tmp/temp1

cat /var/www/log/temperature_0x402557128147225111.log \
    | awk -F# '{ print $2, $3 }' \
    > /tmp/temp2

gnuplot > /tmp/graph.png <<FOO
set terminal png
set timefmt '%s'
set xdata time
plot "/tmp/temp1" using 1:2 with lines title "temp1",\
     "/tmp/temp2" using 1:2 with lines title "temp2"
FOO

eog /tmp/graph.png

