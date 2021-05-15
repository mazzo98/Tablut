#!/bin/bash

cd bitboard
make
cd ..
cd Tablut-MCTS
python3 setup.py install
cd ..
cd Tablutpy
python3 setup.py install

