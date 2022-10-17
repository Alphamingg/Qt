#!/bin/bash
str=`cpupower frequency-info | grep "current policy"`
echo ${str:44:4}

