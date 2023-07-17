#!/bin/bash
crontab -l > crontab_copy
echo "$2 mplayer $1" >> crontab_copy
crontab crontab_copy
rm crontab_copy

