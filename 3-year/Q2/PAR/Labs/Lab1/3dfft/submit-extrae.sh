#!/bin/bash

#SBATCH --job-name=submit-extrae.sh
#SBATCH -D .
#SBATCH --output=submit-extrae.sh.o%j
#SBATCH --error=submit-extrae.sh.e%j

USAGE="\n USAGE: ./submit-extrae.sh prog numthreads \n
        prog        -> Program name\n
        numthreads  -> Number of threads in parallel execution\n"

if (test $# -lt 2 || test $# -gt 2)
then
        echo -e $USAGE
        exit 0
fi

make $1

export OMP_NUM_THREADS=$2

HOST=$(echo $HOSTNAME | cut -f 1 -d'.')

if [ ${HOST} = 'boada-11' ] || [ ${HOST} = 'boada-12' ] || [ ${HOST} == 'boada-13' ]
then
    echo "Use sbatch to execute this script"
    exit 0
fi

export LD_PRELOAD=${INTEL_PATCH}/libhack.so:${EXTRAE_HOME}/lib/libomptrace.so
./$1
export LD_PRELOAD=${INTEL_PATCH}/libhack.so

mpi2prv -f TRACE.mpits -o $1-$2-${HOST}.prv -e $1 -paraver
rm -rf  TRACE.mpits set-0 >& /dev/null
