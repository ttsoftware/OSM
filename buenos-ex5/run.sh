#!/bin/bash

make clean
make
make clean -C tests/
make -C tests/
rm fyams.harddisk
util/tfstool create fyams.harddisk 2048 arkimedes
util/tfstool write fyams.harddisk tests/tlbtest3 tlbtest3
fyams-sim buenos 'initprog=[arkimedes]tlbtest3'

