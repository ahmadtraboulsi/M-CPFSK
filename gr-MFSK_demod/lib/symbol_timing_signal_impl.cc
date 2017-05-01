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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "symbol_timing_signal_impl.h"
#include <cmath>
#include <complex>
#include <boost/dynamic_bitset.hpp>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream>
#include <gnuradio/expj.h>

namespace gr {
  namespace MFSK_demod {

    symbol_timing_signal::sptr
    symbol_timing_signal::make(float k, int m, int sampples_per_symbol)
    {
      return gnuradio::get_initial_sptr
        (new symbol_timing_signal_impl(k, m, sampples_per_symbol));
    }
     
      
      int choosed(int n, int k)
      {
          if (k == 0)
          return 1;
          else{
              return (n * choosed(n - 1, k - 1)) / k;
          }
      }

    /*
     * The private constructor
     */
    symbol_timing_signal_impl::symbol_timing_signal_impl(float k, int m, int sampples_per_symbol)
      : gr::sync_block("symbol_timing_signal",
              gr::io_signature::make(1,1, sizeof(gr_complex)),
              gr::io_signature::make2(1,2, sizeof(gr_complex), sizeof(float)))
    {
    
        d_m=m;
        d_k=k;
        d_offset=0.0;
        samp_sym=sampples_per_symbol;
        nck=choosed(d_m,2);

    
    }

    /*
     * Our virtual destructor.
     */
    symbol_timing_signal_impl::~symbol_timing_signal_impl()
    {
    }

    int
    symbol_timing_signal_impl::work(int noutput_items,
        gr_vector_const_void_star &input_items,
        gr_vector_void_star &output_items)
    {
        const int noutput=noutput_items; 
      const gr_complex *in = (const gr_complex *) input_items[0];
      gr_complex *out1 = (gr_complex *) output_items[0];
          float  *out2=  (float *) output_items[1];

      // Do <+signal processing+>

        //CODE BEING DEVELOPED
      
        int count=0;
        
        
        for (int i=0; i <noutput; i++)
        {
            //clear jexp_i
            jexp_i.clear();
            
            //preparing Tones using 2k-(m-1) k=0,...,m-1 tones
            for (int j=0; j< d_m; j++)
            
            {   // phase of each tone filter = (2*j-(d_m-1)*fd        deviation=mod_index*baud_rate/2
                double phase= ((2*j-(d_m-1))*d_k*M_PI*d_offset/samp_sym);
                gr_complex temp = gr_expj(-phase);
                jexp_i.push_back(temp);
            }
            
            //Generating a SYmbol Clock timing signal
            //C(nt)= summation |ei(nt) - ej(nt)|   where 0<=i<j<=m-1
            long double sumtemp=0;
            int x_1, x_2;
            for (int hhh=0; hhh<nck;hhh++)
            {
                x_1=(d_m-1)-hhh;
                x_2=x_1-1;
                while(x_2>=0)
                {
                    

                sumtemp= sumtemp+ std::abs(std::pow((std::abs(in[i]* jexp_i[x_1])),2)- std::pow((std::abs(in[i]* jexp_i[x_2])),2));
                    x_2--;
                }
            }
            out2[i]=sumtemp;
            out1[i]=in[i]; //original signal is passed also
            //Csum.push_back(sumtemp);
            
            d_offset++; //might need to reset this at the begining of the for loop
            
            /*std::ofstream myfile;
            myfile.open("/Users/ahmadtrabousli/Desktop/blocks/log.txt",std::ios::app);
            if (myfile.is_open())
            {
                
                myfile << sumtemp <<',';
                
                myfile.close();
            }*/
            
            

            
        }
            
       
        //end of code being developed
        
        
        
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace MFSK_demod */
} /* namespace gr */

