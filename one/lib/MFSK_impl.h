/* -*- c++ -*- */
/* 
 * Copyright 2017 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_MFSK_MFSK_IMPL_H
#define INCLUDED_MFSK_MFSK_IMPL_H

#include <MFSK/MFSK.h>

namespace gr {
  namespace MFSK {

    class MFSK_impl : public MFSK
    {
     private:

        int   d_samples_per_sym;	// Samples per symbol, square pulse
        float d_freq;		// Modulation index*pi/samples_per_sym
        float d_ampl;		// Output amplitude
        float d_phase;		// Current phase
        float d_m;          // M-ary
        
     public:
      MFSK_impl(float k, float ampl, int m, int samples_per_symbol);
      ~MFSK_impl();

        
        void set_amplitude(float amplitude) { d_ampl = amplitude; }
        float amplitude() { return d_ampl; }
        float freq() { return d_freq; }
        float phase() { return d_phase; }
        int m() {return d_m;}
        std::vector<std::string> combinations;
        std::vector<char> bits;
        
        
        int fixed_rate_noutput_to_ninput(int noutput_items);
        int fixed_rate_ninput_to_noutput(int ninput_items);
        
      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);
      
      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace MFSK
} // namespace gr

#endif /* INCLUDED_MFSK_MFSK_IMPL_H */

