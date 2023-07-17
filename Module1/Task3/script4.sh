#!/bin/bash
timeL=$(date +%s -d $2)
timeR=$(date +%s -d $3)
logs=$(sudo grep -Ir $1 /var/log)
echo "$logs" | while read line
do
	dt=$(echo $line | awk '{print $1,$2}' | awk -F: '{print $2,$3}')
	sec=$(date +%s -d "$dt" 2>/dev/null)
	if (( sec >= timeL && sec <= timeR ))
	then
		echo $line
	fi
done
