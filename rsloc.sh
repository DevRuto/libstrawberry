#!/bin/sh

find `realpath .` -type f -name '*.c' -print0 | wc -l --files0-from=- | awk '{printf("%5d %s\n", $1, $2)}'
