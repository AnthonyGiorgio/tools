#!/usr/bin/python
#
# Extracts EXIF data from photos taken with a 
# FUJIFULM FinePix XP90 camera, and sorts photos into
# directories organized by shooting date.
#
# This is useful as it matches the format used by Canon cameras.
#
# Copyright 2017 Anthony Giorgio
#
# License: GPLv3

import exifread
import sys
import os

if len(sys.argv) < 2:
    print("No filename specified.")
    exit -1

filename = sys.argv[1]

f = open(filename, 'rb')
tags = exifread.process_file(f)
imagedate = str(tags['EXIF DateTimeOriginal'])[:10]
imagedate = imagedate.replace(":", "_")


if not os.path.exists(imagedate):
    print("Creating directory %s" % imagedate)
    os.makedirs(imagedate)

os.rename(filename, imagedate + "/" + filename)

