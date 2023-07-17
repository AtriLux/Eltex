#!/bin/bash
file='/home/osboxes/Desktop/Task4/text5.txt'
num=`tail -1 $file | awk '{print $3 + 1}'`
if [[ -z "$num" ]]; then
num=1
fi
echo "| run $num" `date +'%T'` >> $file
