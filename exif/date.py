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

import sys
import os
import datetime

if len(sys.argv) < 2:
    print("No filename specified.")
    exit(-1)

filename = sys.argv[1]
t = os.path.getmtime(filename)
imagedate = str(datetime.datetime.fromtimestamp(t))[:10]
imagedate = imagedate.replace("-", "_")

if not os.path.exists(imagedate):
    print("Creating directory %s" % imagedate)
    os.makedirs(imagedate)

os.rename(filename, imagedate + "/" + filename)

