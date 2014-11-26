set datafile separator ","
plot 'ConductorMultiLayer.dat' using 1:($28-273.15) with lines
