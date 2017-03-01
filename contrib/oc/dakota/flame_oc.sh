#!/bin/bash

#
# script to run flame_oc driver
# Tong Zhang <zhangt@frib.msu.edu>
# 2016-10-16 21:05:58 PM EDT
#

dakota_infile=$1
dakota_outfile=$2

latfile='/home/tong1/work/FRIB/projects/flame_github/optdrivers/oc/test_392.lat'

#flamedriver ${dakota_infile} ${dakota_outfile} ${latfile}
flamedriver ${latfile} ${dakota_infile} ${dakota_outfile}

