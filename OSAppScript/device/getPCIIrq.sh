#!/bin/bash

#还未实现换行功能
lspci -vvv |grep -E "Interrupt|MSI"
