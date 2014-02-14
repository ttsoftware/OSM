#!/bin/bash

make clean
make
make -C tests/
util/tfstool delete fyams.harddisk readwrite
util/tfstool write fyams.harddisk tests/readwrite readwrite
fyams-sim buenos 'initprog=[disk1]readwrite'

