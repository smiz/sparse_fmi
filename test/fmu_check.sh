rm -rf binaries
rm -f *.fmu
rm -f a.out
export OPENMODELICALIBRARY="${HOME}/Code/openmodelica/trunk/libraries/Modelica 3.2.1":${HOME}/Code/SOEP/modelica-buildings
fmucheck="${HOME}/Code/SOEP/FMUChecker-2.0b3/build/fmuCheck.linux64"
omc +s +simCodeTarget=sfmi $1 Modelica Buildings ModelicaReference ModelicaServices
modelFile=$(exec basename $1 | sed 's/\.mo//')
g++ -Wall -g -c -fPIC -I../../FMI_for_ModelExchange_and_CoSimulation_v2.0 -o sfmi_runtime.o ../runtime/sfmi_runtime.cpp
g++ -Wall -g -c -fPIC -I../../FMI_for_ModelExchange_and_CoSimulation_v2.0 -I../runtime -o ${modelFile}_FMI.o ${modelFile}_FMI.cpp
g++ -shared -Wl,-soname,${modelFile}.so -o ${modelFile}.so sfmi_runtime.o ${modelFile}_FMI.o -llapack
mkdir binaries
mkdir binaries/linux64
mv ${modelFile}.so binaries/linux64
zip -r ${modelFile}.fmu modelDescription.xml binaries
${fmucheck} -h 1E-3 -c ' ' -l 5 -f ${modelFile}.fmu > ${modelFile}.dat
g++ -Wall ${modelFile}_check.cpp 
./a.out
