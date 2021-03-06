/* -*- c++ -*- */

#define MFSK_DEMOD_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "MFSK_demod_swig_doc.i"

%{
#include "MFSK_demod/MFSK_demod2.h"
#include "MFSK_demod/MFSK_demod3.h"
#include "MFSK_demod/symbol_timing_signal.h"
%}

%include "MFSK_demod/MFSK_demod2.h"
GR_SWIG_BLOCK_MAGIC2(MFSK_demod, MFSK_demod2);
%include "MFSK_demod/MFSK_demod3.h"
GR_SWIG_BLOCK_MAGIC2(MFSK_demod, MFSK_demod3);


%include "MFSK_demod/symbol_timing_signal.h"
GR_SWIG_BLOCK_MAGIC2(MFSK_demod, symbol_timing_signal);
