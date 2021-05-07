#!/bin/bash

#Parameters description
# -p (Required): player type
# -i: IP Address of server (default localhost)
# -t: timeout (deafult 50s)
# -d: max-depth of search (only for debug, LEAVE DEFAULT)
# -c: value of constant C (only for debug, LEAVE DEFAULT)
# -w: number of threads to use (number of available core, LEAVE DEFAULT)

python3 Tablut-Player/src/client.py -p $1 -t $2 -i $3