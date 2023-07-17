#!/bin/bash
source script5.conf
timeL=$(date +%s -d $LeftEdgeDate)
timeR=$(date +%s -d $RightEdgeDate)
logs=$(sudo grep -Ir $ProcessName /var/log)
echo "$logs" | while read line
do
	dt=$(echo $line | awk '{print $1,$2}' | awk -F: '{print $2,$3}')
	sec=$(date +%s -d "$dt" 2>/dev/null)
	if (( sec >= timeL && sec <= timeR ))
	then
		echo $line
	fi
done
