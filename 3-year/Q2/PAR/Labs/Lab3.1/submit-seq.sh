#!/bin/bash

#SBATCH --job-name=submit-seq.sh
#SBATCH -D .
#SBATCH --output=submit-seq.sh.o%j
#SBATCH --error=submit-seq.sh.e%j

USAGE="\n USAGE: ./run_tareador.sh prog options \n
        prog        -> Tareador program name \n
        options     -> Tareador options: -d -h ... \n"

HOST=$(echo $HOSTNAME | cut -f 1 -d'.')

if [ ${HOST} = 'boada-6' ] || [ ${HOST} = 'boada-7' ] || [ ${HOST} == 'boada-8' ]
then
        echo "Use sbatch to execute this script"
        exit 0
fi

if (test $# -eq 0)
then
        echo -e $USAGE
        exit 0
fi

filename=$1
shift
make $filename

options=
# Loop until all Tareador parameters are used up
while [ "$1" != "" ]; do
    options+=$1
    options+=" "
    shift
done

./$filename $options
