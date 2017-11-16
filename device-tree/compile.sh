cpp -nostdinc -I /usr/src/linux-headers-`uname -r`/include -undef -x assembler-with-cpp am57xx-beagle-x15-revb1.dts > am57xx-beagle-x15-revb1.dts.tmp
dtc -O dtb -b 0 -o am57xx-beagle-x15-revb1.dtb am57xx-beagle-x15-revb1.dts.tmp
rm am57xx-beagle-x15-revb1.dts.tmp
