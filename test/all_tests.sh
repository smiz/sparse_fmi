rm -f *.dat
rm -rf binaries
rm -f *.xml
rm -f *.fmu
rm -f *_FMI.*
filenames="
Test1.mo
Linsys.mo
Linsys2.mo
"
for f in $filenames;
do
	bash fmu_check.sh $f
done

