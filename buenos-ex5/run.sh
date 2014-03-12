#!/bin/bash

make clean
make
make clean -C tests/
make -C tests/
rm fyams.harddisk
util/tfstool create fyams.harddisk 2048 arkimedes
#util/tfstool write fyams.harddisk tests/filesystemtest filesystemtest
#util/tfstool write fyams.harddisk tests/hej hej
util/tfstool write fyams.harddisk tests/osh osh
fyams-sim buenos 'initprog=[arkimedes]osh'

