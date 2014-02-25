#!/bin/bash

make clean
make
make clean -C tests/
make -C tests/
rm fyams.harddisk
util/tfstool create fyams.harddisk 2048 arkimedes
# util/tfstool write fyams.harddisk tests/exec exec
# util/tfstool write fyams.harddisk tests/hw hw
# fyams-sim buenos 'initprog=[arkimedes]exec'

