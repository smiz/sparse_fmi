model EventTests
 parameter Real p = 0.25;
 parameter Real x1 = p;
 parameter Real x2 = 2*p;
 Real x(start=0);
 Boolean v1(start=false), v2(start=false); 
equation
 der(x) = 1;
 v1 = if x>x1 then true else false;
 v2 = if x>x2 then true else false;
end EventTests;

