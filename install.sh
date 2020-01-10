#!/usr/bin/env  bash
gcc -c calFreqByField.c
gcc -c popdiff.c
gcc -c popfreq.c
gcc calFreqByField.o popdiff.o -o caldiff
gcc calFreqByField.o popfreq.o -o calfreq
