#!/bin/bash

makefile_name=makefile;

__retval="";

#params: prompt value_y value_n 
#return code:0 on y and 1 on no.
#reference return: uses __retval
function y_n_choice() {

	local read_value;
	while true;
	do
		echo -n "$1 (y/n): ";
		read read_value;
		case $read_value in
			"y") __retval=$2; return 0; break;;
			"n") __retval=$3; return 1; break;;
		esac
	done;
}

y_n_choice "With optimizations" "OPTIMIZATION=-O2" "#OPTIMIZATION=-O2"
optimizations=$__retval;

y_n_choice "With debug" "DEBUG=-g" "#DEBUG=-g"
debug=$__retval;

y_n_choice "With C++14" "CPPREV=-std=c++14" "CPPREV=-std=c++11"
cpprev=$__retval

cp make/linux.template ./$makefile_name;

sed -i -e "s/__TEMPLATE_OPTIMIZATION__/$optimizations/g" ./$makefile_name;
sed -i -e "s/__TEMPLATE_DEBUG__/$debug/g" ./$makefile_name;
sed -i -e "s/__TEMPLATE_CPPREV__/$cpprev/g" ./$makefile_name;

y_n_choice "Begin compilation" "" ""
if [ $? -eq 0 ]; then 
	make clean; make all; echo "Done";
fi;

