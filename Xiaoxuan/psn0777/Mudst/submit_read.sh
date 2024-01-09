#!/bin/bash
starver DEV

date
path=$PWD
[ -d jobs ] || mkdir -p jobs
[ -d jobs/csh ] || mkdir -p jobs/csh
[ -d jobs/report ] || mkdir -p jobs/report
[ -d jobs/log ] || mkdir -p jobs/log
[ -d jobs/list ] || mkdir -p jobs/list

list=$PWD/Mudst_input.files

aklog 

#mkdir -p out/
star-submit-template -template submit_read.xml -entities base=${path}/jobs,filelist=${list}
