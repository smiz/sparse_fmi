#! /bin/sh

case "`uname -s`" in
     CYGWIN*) arch=win
     	      sharedLibrarySuffix=dll;;
     Darwin)  arch=darwin64
     	      sharedLibrarySuffix=dylib;;
     Linux)   arch=linux64
     	      pic=-fPIC
     	      sharedLibrarySuffix=so;;
esac     

# Cleanup from prior test
rm -rf binaries
rm -f ${modelFile}.fmu 
rm -f modelDescription.xml 
rm -f a.out
rm -f ${modelFile}.dat
# Jim' s paths
export OPENMODELICALIBRARY="${HOME}/Code/openmodelica/trunk/libraries/Modelica 3.2.1":${HOME}/Code/SOEP/modelica-buildings
fmucheck="${HOME}/Code/SOEP/FMUChecker-2.0b3/build/fmuCheck"
# Ozgur's paths
#export OPENMODELICALIBRARY="${HOME}/Documents/openmodelica/libraries/Modelica 3.2.1":${HOME}/Desktop/modelica-buildings
#fmucheck="${HOME}/Desktop/FMUChecker-2.0b3/fmuCheck"

# Compile and execute test
# Generating the .cpp files.
#omc +s +simCodeTarget=sfmi +tearingMethod=noTearing $1 Modelica Buildings ModelicaReference ModelicaServices
omc +s +simCodeTarget=sfmi $1 Modelica
modelFile=$(exec basename $1 | sed 's/\.mo//')

# Compile.
case "$arch" in
    darwin64)
	c++ -dynamiclib -g -I/opt/openmodelica/include -I../FMI_for_ModelExchange_and_CoSimulation_v2.0 -o sfmi_runtime.o -I../runtime -o ${modelFile}.${sharedLibrarySuffix} ${modelFile}_FMI.cpp ../runtime/sfmi_runtime.cpp
	;;
    linux64)
	g++ -Wall -g -c -fPIC -I../../FMI_for_ModelExchange_and_CoSimulation_v2.0 -o sfmi_runtime.o ../runtime/sfmi_runtime.cpp 
	g++ -Wall -g -c -fPIC -I../../FMI_for_ModelExchange_and_CoSimulation_v2.0 -I../runtime -o ${modelFile}_FMI.o ${modelFile}_FMI.cpp
	g++ -shared -Wl,-soname,${modelFile}.so -o ${modelFile}.so sfmi_runtime.o ${modelFile}_FMI.o -llapack 
	;;
    *)
	echo "$0: Do not know about arch $arch"
	exit -2
esac


# Create the FMU.
mkdir binaries
mkdir binaries/${arch}
mv ${modelFile}.${sharedLibrarySuffix} binaries/${arch}
zip -r ${modelFile}.fmu modelDescription.xml binaries
# Run the FMU Checker.
${fmucheck}.${arch} -h 0.001 -l 5 -f ${modelFile}.fmu > ${modelFile}.dat
g++ -Wall ${modelFile}_check.cpp
./a.out
