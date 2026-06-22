#!/bin/bash
rm -rf .tareador_precomputed_*
source /Soft/PAR/environment.bash
export LD_PRELOAD_TMP=$LD_PRELOAD
echo "Removing LD_PRELOAD"
export -n LD_PRELOAD
echo "Calling tareador"
tareador_gui.py --llvm --lite $1
export LD_PRELOAD=$LD_PRELOAD_TMP
echo "Exporting again LD_PRELOAD"
