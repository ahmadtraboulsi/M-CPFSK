/* -*- c++ -*- */

#define MFSK_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "MFSK_swig_doc.i"

%{
#include "MFSK/MFSK.h"
%}


%include "MFSK/MFSK.h"
GR_SWIG_BLOCK_MAGIC2(MFSK, MFSK);
