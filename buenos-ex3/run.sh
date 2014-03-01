#!/bin/bash

make clean
make
make clean -C tests/
make -C tests/
rm fyams.harddisk
util/tfstool create fyams.harddisk 2048 arkimedes
util/tfstool write fyams.harddisk tests/barrier barrier
util/tfstool write fyams.harddisk tests/prog0 prog0
util/tfstool write fyams.harddisk tests/prog1 prog1
fyams-sim buenos 'initprog=[arkimedes]barrier'

