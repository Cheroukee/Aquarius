echo ds3231 0x68 > /sys/class/i2c-adapter/i2c-1/new_device
hwclock -s -f /dev/rtc1
hwclock -w
date
echo 0x68 > /sys/class/i2c-adapter/i2c-1/delete_device