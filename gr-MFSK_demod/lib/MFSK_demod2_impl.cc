/* -*- c++ -*- */
/* 
 * Copyright 2017 AHMAD TRABOULSI
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
#include "MFSK_demod2_impl.h"
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

    MFSK_demod2::sptr
    MFSK_demod2::make(float k, int m, int samples_per_symbol)
    {
      return gnuradio::get_initial_sptr
        (new MFSK_demod2_impl(k, m, samples_per_symbol));
    }

    /*
     * The private constructor
     */
    MFSK_demod2_impl::MFSK_demod2_impl(float k, int m, int samples_per_symbol)
      : gr::block("MFSK_demod2",
              gr::io_signature::make(1, 1, sizeof(gr_complex)),
              gr::io_signature::make(1, 1, sizeof(unsigned char)))
    {
    
        d_m=m;
        d_k=k;
        d_offset=0.0;
        samp_sym=samples_per_symbol;
        
        for(int i=0; i<d_m ;i++)
        {
            sum.push_back(gr_complex(0,0));
        }
        
        
        int nbits= log2(d_m); // number of bits   where  d_m is number of tones.
        int max_dec=std::pow(2,nbits)-1; // decimal  max is (2^x) -1
        
        for (int i=0; i<=max_dec; i++)
        {
            
            boost::dynamic_bitset<> bs(nbits, i);
            std::string buffer;
            to_string(bs, buffer);
         // combinations hold all possible n bits combinations sorted in decimal order.
            combinations.push_back(buffer);
        }
        
        set_relative_rate(1.0 *log2(d_m)/ samples_per_symbol);
        set_output_multiple(log2(d_m));
    }

    /*
     * Our virtual destructor.
     */
    MFSK_demod2_impl::~MFSK_demod2_impl()
    {
    }

    void
    MFSK_demod2_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        unsigned ninputs = ninput_items_required.size();
        for(unsigned i = 0; i < ninputs; i++)
        ninput_items_required[i] = noutput_items/log2(d_m) * samp_sym; //+ history() - 1;
    }
      
      
      
      

    int
    MFSK_demod2_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        const int noutput=noutput_items;
        const gr_complex *in = (const gr_complex *) input_items[0];
        unsigned char *out = (unsigned char *) output_items[0];
        
      // Do <+signal processing+>
        
        int count=0;
        
        for (int i=0; i <noutput * samp_sym/log2(d_m); i++)
        {
            //clear jexp_i
            jexp_i.clear();
            
            //preparing Tones using 2k-(m-1) k=0,...,m-1 tones
            for (int j=0; j< d_m; j++)
            {
                double phase= ((2*j-(d_m-1))*d_k*M_PI*d_offset/samp_sym);
                gr_complex temp = gr_expj(-phase);
                jexp_i.push_back(temp);
            }
            
            
            
            
                // Integrating over each baud using each tone above
                for (int p=0; p<d_m; p++)
                {
                    sum[p]+= in[i]* jexp_i[p];
                }
                
                //Check if a number of samples equal to that of one baud i.e sps
                if ((i + 1) % samp_sym == 0)
                {
                    // need to clear squared_sum here !!!!!!!!!
                    squared_sum.clear();
                    
                    //compute the square of each sum,
                    for (int k=0;k<d_m;k++)
                    {
                        squared_sum.push_back(std::pow(std::abs(sum[k]),2));
                    }
                    
                    
                    //get the position of the tone with maximum statistics
                    auto biggest = std::max_element(std::begin(squared_sum), std::end(squared_sum));
                    int index_biggest= std::distance(std::begin(squared_sum), biggest);
                    
                    // return the bits
                    for(int f=0; f<log2(d_m);f++)
                    {
                        unsigned char x=combinations[index_biggest][f];
                        bool bValue = ( x == '1' ? true : false );
                        out[count]=bValue;
                                            count++;
                    }

                    
                    for (int j=0; j<d_m;j++)
                    sum[j]= gr_complex(0,0);
                    
                }
                
            
            d_offset++;
        }
        
       
      // Tell runtime system how many input items we consumed on
      // each input stream.
      consume_each (noutput * samp_sym /log2(d_m));

      // Tell runtime system how many output items we produced.
      return count;
    }

  } /* namespace MFSK_demod */
} /* namespace gr */

