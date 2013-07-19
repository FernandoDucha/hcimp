#!/bin/bash
# 
# File:   newscript.sh
# Author: fordem
#
# Created on Jun 3, 2013, 3:31:06 AM
#
#/bin/bash

for ((  i = 90 ;  i <= 90;  i+=10 ))
do
for (( j = $2 ; j <= $3 ; j++ ))
do
    echo "Executando $1 tipo $i instancia $j"  
    dist/Release/GNU-Linux-x86/hcimp $1 $i $j
done
done

