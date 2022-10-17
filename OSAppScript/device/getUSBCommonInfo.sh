lsusb

echo 
echo 
echo 

lsusb -t 

echo 
echo 
echo 

xinput

echo 
echo 
echo 

lsusb -v | grep -i bcdusb

echo 
echo 
echo 


lsusb -v | grep -Ei '(idVendor|Mass Storage)'

echo 
echo 
echo 

find /dev/bus/ 

echo 
echo 
echo 

dmesg |grep cdc_acm

echo 
echo 
echo

for i in /sys/bus/usb/devices/*/power/wakeup
do 
	echo $i
	cat $i
done

echo 
echo 
echo
for i in /sys/bus/usb/devices/*/power/control
do 
	echo $i
	cat $i
done
