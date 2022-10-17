cat /proc/cpuinfo | grep -w 'flags' | grep -v 'vmx flags' | uniq
