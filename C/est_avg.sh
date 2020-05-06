#!/bin/sh

N=20

log_fp=$@'.log'
#echo $log_fp
#touch $log_fp

if [ $# -le 0 ] ; then
	echo "Usage: "
	echo "    ./est_avg.sh [FL32/FL32_NEON/FL64/FL64_NEON/INT]"
	exit 0
fi

echo "*********************************************"
echo "*    " $@ " in "$N "average time(s)"
echo "*********************************************"

sum=0
for i in $(seq 1 $N);
do 
	num=`./$@ | cut -d " " -f 2`
	sum=$((sum + num))
	sleep 0.5
done

echo $((sum/N))' us'
