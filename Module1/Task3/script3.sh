#!/bin/bash
id=$(pidof -s $1)
if [ -z $id ]
then
	echo "Starting process..."
	$1 &
	echo "Done!"
else
	echo $1" running."
fi

