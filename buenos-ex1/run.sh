#!/bin/bash

make clean
make
make -C tests/
util/tfstool delete fyams.harddisk read
util/tfstool write fyams.harddisk tests/read read
fyams-sim buenos 'initprog=[disk1]read'

