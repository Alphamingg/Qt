#lspci -kk |grep driver | awk '{print $5}'
lspci -nnk
echo
echo
echo
lspci -vt

echo
echo
echo
lspci -nn

echo
echo
echo
hwinfo  --pci

echo
echo
echo
lspci -xx

echo
echo
echo
lspci -vvv |grep "Interrupt"

echo
echo
echo
lspci -vvv |grep "MSI"

echo
echo
echo
lspci -vvv

echo
echo
echo


