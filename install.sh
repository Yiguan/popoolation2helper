#!/usr/bin/env  bash
g++ -c calFreqByField.c
g++ -c popdiff.c
g++ -c popfreq.c
g++ calFreqByField.o popdiff.o -o caldiff
g++ calFreqByField.o popfreq.o -o calfreq
