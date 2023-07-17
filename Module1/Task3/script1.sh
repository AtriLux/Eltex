#!/bin/bash
for ((i=0;i<10;i++))
do
	dir_name="dir_"$i
	mkdir $dir_name
	cd $dir_name

	for ((j=0;j<100;j++))
	do
		sub_dir_name="sub_dir_"$j
		mkdir $sub_dir_name
		cd $sub_dir_name

		for ((k=0;k<200;k++))
		do
			file_name="file_"$k
			touch $file_name
		done
		cd ..
	done
	cd ..
done
