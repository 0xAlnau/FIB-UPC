#!/bin/bash

#SBATCH --job-name=submit-seq.sh
#SBATCH -D .
#SBATCH --output=submit-seq.sh.o%j
#SBATCH --error=submit-seq.sh.e%j


USAGE="\n USAGE: submit-seq.sh PROG size\n
        PROG   -> omp program name\n"

if (test $# -lt 1 || test $# -gt 1)
then
	echo -e $USAGE
    exit 0
fi

make $1

HOST=$(echo $HOSTNAME | cut -f 1 -d'.')

if [ ${HOST} = 'boada-11' ] || [ ${HOST} = 'boada-12' ] || [ ${HOST} == 'boada-13' ]
then
    echo "Use sbatch to execute this script"
    exit 0
fi

/usr/bin/time -o time-$1-${HOST} ./$1
