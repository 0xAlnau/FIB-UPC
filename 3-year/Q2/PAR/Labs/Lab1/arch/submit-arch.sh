#!/bin/bash

#SBATCH --job-name=submit-arch.sh
#SBATCH -D .
#SBATCH --output=submit-arch.sh.o%j
#SBATCH --error=submit-arch.sh.e%j

HOST=$(echo $HOSTNAME | cut -f 1 -d'.')

if [ ${HOST} = 'boada-11' ] || [ ${HOST} = 'boada-12' ] || [ ${HOST} == 'boada-13' ]
then
    echo "Use sbatch to execute this script"
    exit 0
fi

PROG=lscpu
$PROG > ${PROG}-${HOST}.txt

PROG='lstopo'
$PROG > ${PROG}-${HOST}.txt
PROGFIG='lstopo --of fig map.fig'
$PROGFIG
mv map.fig map-${HOST}.fig

cat /sys/devices/system/cpu/cpu0/cache/index0/coherency_line_size > cache_line_size-$HOST.txt
