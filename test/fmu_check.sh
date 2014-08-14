rm -rf binaries
rm -f *.fmu
export MODELICAPATH="${HOME}/Code/openmodelica/libraries/Modelica 3.2.1"
omc +s +simCodeTarget=sfmi $1 Modelica
modelFile=$(exec basename $1 | sed 's/\.mo//')
g++ -Wall -g -c -fPIC -I../FMI_for_ModelExchange_and_CoSimulation_v2.0 -o sfmi_runtime.o ../runtime/sfmi_runtime.cpp
g++ -Wall -g -c -fPIC -I../FMI_for_ModelExchange_and_CoSimulation_v2.0 -I../runtime -o ${modelFile}_FMI.o ${modelFile}_FMI.cpp
g++ -shared -Wl,-soname,${modelFile}.so -o ${modelFile}.so sfmi_runtime.o ${modelFile}_FMI.o 
mkdir binaries
mkdir binaries/linux64
mv ${modelFile}.so binaries/linux64
zip -r ${modelFile}.fmu modelDescription.xml binaries
fmuCheck.linux64 -l 5 -f ${modelFile}.fmu > ${modelFile}.dat
