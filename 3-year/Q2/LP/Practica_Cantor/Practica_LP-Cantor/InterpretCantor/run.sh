#!/bin/bash

python3 cantor.py not.cantor <../Inputs/0.inp> ../Outputs/Tasca2/not_0.out
python3 cantor.py not.cantor <../Inputs/1.inp> ../Outputs/Tasca2/not_1.out

python3 cantor.py and.cantor <../Inputs/00.inp> ../Outputs/Tasca2/and_00.out
python3 cantor.py and.cantor <../Inputs/01.inp> ../Outputs/Tasca2/and_01.out
python3 cantor.py and.cantor <../Inputs/10.inp> ../Outputs/Tasca2/and_10.out
python3 cantor.py and.cantor <../Inputs/11.inp> ../Outputs/Tasca2/and_11.out

python3 cantor.py or.cantor <../Inputs/00.inp> ../Outputs/Tasca2/or_00.out
python3 cantor.py or.cantor <../Inputs/01.inp> ../Outputs/Tasca2/or_01.out
python3 cantor.py or.cantor <../Inputs/10.inp> ../Outputs/Tasca2/or_10.out
python3 cantor.py or.cantor <../Inputs/11.inp> ../Outputs/Tasca2/or_11.out

python3 cantor.py lt.cantor <../Inputs/1_17.inp> ../Outputs/Tasca3/lt_1_17.out
python3 cantor.py lt.cantor <../Inputs/3_2.inp> ../Outputs/Tasca3/lt_3_2.out
python3 cantor.py lt.cantor <../Inputs/3_3.inp> ../Outputs/Tasca3/lt_3_3.out
python3 cantor.py lt.cantor <../Inputs/47_32.inp> ../Outputs/Tasca3/lt_47_32.out

python3 cantor.py gt.cantor <../Inputs/1_17.inp> ../Outputs/Tasca3/gt_1_17.out
python3 cantor.py gt.cantor <../Inputs/3_2.inp> ../Outputs/Tasca3/gt_3_2.out
python3 cantor.py gt.cantor <../Inputs/3_3.inp> ../Outputs/Tasca3/gt_3_3.out
python3 cantor.py gt.cantor <../Inputs/47_32.inp> ../Outputs/Tasca3/gt_47_32.out

python3 cantor.py eq.cantor <../Inputs/1_17.inp> ../Outputs/Tasca3/eq_1_17.out
python3 cantor.py eq.cantor <../Inputs/3_2.inp> ../Outputs/Tasca3/eq_3_2.out
python3 cantor.py eq.cantor <../Inputs/3_3.inp> ../Outputs/Tasca3/eq_3_3.out
python3 cantor.py eq.cantor <../Inputs/47_32.inp> ../Outputs/Tasca3/eq_47_32.out

python3 cantor.py neq.cantor <../Inputs/1_17.inp> ../Outputs/Tasca3/neq_1_17.out
python3 cantor.py neq.cantor <../Inputs/3_2.inp> ../Outputs/Tasca3/neq_3_2.out
python3 cantor.py neq.cantor <../Inputs/3_3.inp> ../Outputs/Tasca3/neq_3_3.out
python3 cantor.py neq.cantor <../Inputs/47_32.inp> ../Outputs/Tasca3/neq_47_32.out

python3 cantor.py mod.cantor <../Inputs/10_4.inp> ../Outputs/Tasca4/mod_10_4.out
python3 cantor.py mod.cantor <../Inputs/2_1.inp> ../Outputs/Tasca4/mod_2_1.out
python3 cantor.py mod.cantor <../Inputs/3_2.inp> ../Outputs/Tasca4/mod_3_2.out
python3 cantor.py mod.cantor <../Inputs/47_32.inp> ../Outputs/Tasca4/mod_47_32.out

python3 cantor.py even.cantor <../Inputs/2.inp> ../Outputs/Tasca4/even_2.out
python3 cantor.py even.cantor <../Inputs/7.inp> ../Outputs/Tasca4/even_7.out
python3 cantor.py even.cantor <../Inputs/12.inp> ../Outputs/Tasca4/even_12.out
python3 cantor.py even.cantor <../Inputs/34.inp> ../Outputs/Tasca4/even_34.out

python3 cantor.py fibonacci.cantor <../Inputs/0.inp> ../Outputs/Tasca5/fibo_0.out
python3 cantor.py fibonacci.cantor <../Inputs/1.inp> ../Outputs/Tasca5/fibo_1.out
python3 cantor.py fibonacci.cantor <../Inputs/2.inp> ../Outputs/Tasca5/fibo_2.out
python3 cantor.py fibonacci.cantor <../Inputs/3.inp> ../Outputs/Tasca5/fibo_3.out
python3 cantor.py fibonacci.cantor <../Inputs/4.inp> ../Outputs/Tasca5/fibo_4.out
python3 cantor.py fibonacci.cantor <../Inputs/5.inp> ../Outputs/Tasca5/fibo_5.out
python3 cantor.py fibonacci.cantor <../Inputs/6.inp> ../Outputs/Tasca5/fibo_6.out
python3 cantor.py fibonacci.cantor <../Inputs/7.inp> ../Outputs/Tasca5/fibo_7.out

python3 cantor.py min.cantor <../Inputs/4_2.inp> ../Outputs/Tasca6/min_4_2.out
python3 cantor.py min.cantor <../Inputs/47_32.inp> ../Outputs/Tasca6/min_47_32.out
python3 cantor.py min.cantor <../Inputs/3_3.inp> ../Outputs/Tasca6/min_3_3.out
python3 cantor.py min.cantor <../Inputs/01.inp> ../Outputs/Tasca6/min_01.out

python3 cantor.py max.cantor <../Inputs/4_2.inp> ../Outputs/Tasca6/max_4_2.out
python3 cantor.py max.cantor <../Inputs/47_32.inp> ../Outputs/Tasca6/max_47_32.out
python3 cantor.py max.cantor <../Inputs/3_3.inp> ../Outputs/Tasca6/max_3_3.out
python3 cantor.py max.cantor <../Inputs/01.inp> ../Outputs/Tasca6/max_01.out

python3 cantor.py cond.cantor <../Inputs/26_8.inp> ../Outputs/Tasca6/cond_26_8.out
python3 cantor.py cond.cantor <../Inputs/20_8.inp> ../Outputs/Tasca6/cond_20_8.out

python3 cantor.py max2.cantor <../Inputs/4_2.inp> ../Outputs/Tasca6/max2_4_2.out
python3 cantor.py max2.cantor <../Inputs/47_32.inp> ../Outputs/Tasca6/max2_47_32.out
python3 cantor.py max2.cantor <../Inputs/3_3.inp> ../Outputs/Tasca6/max2_3_3.out
python3 cantor.py max2.cantor <../Inputs/01.inp> ../Outputs/Tasca6/max2_01.out


echo "Jocs de proves realitzats!"
exit
