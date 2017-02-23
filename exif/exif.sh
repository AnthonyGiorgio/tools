#!/bin/sh
#
# Write exif data to a photo that doesn't have any, using the filename
# to compute the date/timestamp.
#
# Copyright 2017 Anthony Giorgio
#
for file in *.jpg
	do
	hour=`echo $file | cut --bytes=10-11`
	minute=`echo $file | cut --bytes=12-13`
	time="$hour:$minute:00"
	year=`echo $file | cut --bytes=7-8`
	year=20$year
	month=`echo $file | cut --bytes=1-2`
	day=`echo $file | cut --bytes=4-5`
	date="$year:$month:$day $time" 
	echo $file
	exiftool "-DateTimeOriginal=$date" $file
	folder="$year"_"$month"_"$day"
	if [ ! -d $folder ]
	then
		mkdir $folder
	fi
	mv $file $folder
	done
