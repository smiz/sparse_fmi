filenames="
/home/nutarojj/Code/openmodelica/trunk/testsuite/openmodelica/fmi/ModelExchange/HelloFMIWorld.mo
Test1.mo
Linsys.mo
"
for f in $filenames;
do
	bash fmu_check.sh $f
done

