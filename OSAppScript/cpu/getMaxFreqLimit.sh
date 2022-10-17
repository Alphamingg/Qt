#!/bin/bash
str=`cpupower frequency-info | grep "current policy"`
echo ${str:57:4}
