#!/bin/bash
watch -n 1 -d "cat /proc/meminfo | grep -E \"MemFree|MemAvailable|Vmalloc|SwapTotal|SwapFree|Slab\""
