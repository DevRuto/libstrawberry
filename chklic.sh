#!/bin/sh

printf "\x1B[31;1m"
grep -rL "The MIT License" . --exclude-dir=dep --exclude-dir=obj --exclude-dir=Properties | grep -e "\.c$" -e "\.h$" -e "\.cs$" -e "\.sh$"
if [ $? != 0 ] ; then
	echo "\x1B[33;1mAll files seem okay.";
fi
printf "\x1B[0m"
if [ $SHLVL == 3 ] ; then
	read -n 1 x;
fi
