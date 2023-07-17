#!/bin/bash
#parameters: 1 - period (sec), 2 - [directory]/[archive_name].tar, 3 - file or directory
watch -n$1 tar -cf $2 $3
