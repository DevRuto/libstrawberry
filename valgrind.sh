#!/bin/sh

if [ $# -eq 1 ] ; then
	valgrind -v --track-fds=yes --leak-check=full --show-leak-kinds=all --track-origins=yes "$1"
else
	echo "Usage: ./valgrind.sh <path>"
fi
