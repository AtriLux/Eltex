#!/bin/bash
cd $1
for ((i=0;i<$2;i++))
do
	dir_name=$5$i
	mkdir $dir_name
	cd $dir_name

	for ((j=0;j<$3;j++))
	do
		subdir_name=$6$j
		mkdir $subdir_name
		cd $subdir_name

		for ((k=0;k<$4;k++))
		do
			file_name=$7$k
			touch $file_name
		done
		cd ..
	done
	cd ..
done
