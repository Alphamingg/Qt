#!/bin/bash
watch -n 1 -d "cat /proc/meminfo | grep -E \"SReclaimable|Cached|Buffers\""
