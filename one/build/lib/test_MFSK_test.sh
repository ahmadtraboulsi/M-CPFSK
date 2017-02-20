#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/lib
export GR_CONF_CONTROLPORT_ON=False
export PATH=/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/build/lib:$PATH
export DYLD_LIBRARY_PATH=/Users/ahmadtrabousli/Desktop/blocks/MFSK/gr-MFSK/build/lib:$DYLD_LIBRARY_PATH
export PYTHONPATH=$PYTHONPATH
test-MFSK 
