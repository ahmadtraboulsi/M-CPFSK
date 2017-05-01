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

#ifndef INCLUDED_MFSK_DEMOD_MFSK_DEMOD3_IMPL_H
#define INCLUDED_MFSK_DEMOD_MFSK_DEMOD3_IMPL_H

#include <MFSK_demod/MFSK_demod3.h>
#include <cmath>
#include <complex>
#include <boost/dynamic_bitset.hpp>
#include <algorithm>
#include <string>
#include <vector>

namespace gr {
  namespace MFSK_demod {

    class MFSK_demod3_impl : public MFSK_demod3
    {
     private:

     public:
        int samp_sym;
        int nck;
        int d_offset;
        int d_m;
        float d_k;
        int firstSymbol;
        std::vector<gr_complex> sum;
        std::vector<gr_complex> Csum;
        std::vector<gr_complex> jexp_i;
        std::vector<float> squared_sum;
        std::vector<std::string> combinations;
      MFSK_demod3_impl(float k, int m, int samples_per_symbol);
      ~MFSK_demod3_impl();

      // Where all the action really happens
      void forecast (int noutput_items, gr_vector_int &ninput_items_required);

      int general_work(int noutput_items,
           gr_vector_int &ninput_items,
           gr_vector_const_void_star &input_items,
           gr_vector_void_star &output_items);
    };

  } // namespace MFSK_demod
} // namespace gr

#endif /* INCLUDED_MFSK_DEMOD_MFSK_DEMOD3_IMPL_H */

