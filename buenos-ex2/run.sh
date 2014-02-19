#!/bin/bash

make clean
make
make -C tests/
rm fyams.harddisk
#util/tfstool create fyams.harddisk 2048 arkimedes
util/tfstool delete fyams.harddisk exec
util/tfstool write fyams.harddisk tests/exec exec
fyams-sim buenos 'initprog=[arkimedes]exec'

