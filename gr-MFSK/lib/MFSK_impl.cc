/* -*- c++ -*- */
/* 
 * Copyright 2017 AHMAD TRABOULSI.
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
#include "MFSK_impl.h"
#include <gnuradio/expj.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <complex>
#include <boost/dynamic_bitset.hpp>
#include <algorithm>
#include <string>
#include <sstream>


namespace gr {
  namespace MFSK {

#define M_TWOPI (2*M_PI)

      
    MFSK::sptr
    MFSK::make(float k, float ampl, int m, int samples_per_symbol)
    {
      return gnuradio::get_initial_sptr
        (new MFSK_impl(k, ampl, m, samples_per_symbol));
    }

    /*
     * The private constructor
     */
    MFSK_impl::MFSK_impl(float k, float ampl, int m, int samples_per_symbol)
      : gr::block("MFSK",
              gr::io_signature::make(1, 1, sizeof(char)),
              gr::io_signature::make(1, 1, sizeof(gr_complex)))
    {
    
        d_samples_per_sym = samples_per_symbol;
        d_freq = k*M_PI/samples_per_symbol; //needs edit
        d_ampl = ampl;
        d_phase = 0.0;
        d_m = m;
    
        set_relative_rate(1.0 * samples_per_symbol/log2(d_m));
        set_output_multiple(samples_per_symbol);
        
        
        
        
        
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

    
    }

    /*
     * Our virtual destructor.
     */
    MFSK_impl::~MFSK_impl()
    {
    }

    void
    MFSK_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        
        
        unsigned ninputs = ninput_items_required.size();
        for(unsigned i = 0; i < ninputs; i++)
        ninput_items_required[i] = fixed_rate_noutput_to_ninput(noutput_items);

        /*
         Estimate input requirements given output request.
         
         Parameters
         noutput_items	number of output items to produce
         ninput_items_required	number of input items required on each input stream
         Given a request to product noutput_items, estimate the number of data items required on each input stream. The estimate doesn't have to be exact, but should be close.
         
         
         */
    }
      
      
      
      int
      MFSK_impl::fixed_rate_noutput_to_ninput(int noutput_items)
      {
          return noutput_items *log2(d_m)/ d_samples_per_sym + history() - 1;
      }
      
      int
      MFSK_impl::fixed_rate_ninput_to_noutput(int ninput_items)
      {
          return std::max(0, ninput_items - (int)history() + 1) * d_samples_per_sym;
      }
      

    int
    MFSK_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
      const char *in = (const char *) input_items[0];
      gr_complex *out = (gr_complex *) output_items[0];

        
        /* wd= 2pi*fd
         
         set of frequencies
         wc+ wd[2k-(M-1)]        ,    M=2^k  where k is the number of bits per symbol for k=0,1,...,M-1
         
         
          d_freq = k*M_PI/samples_per_symbol;
         */
        
        
        
        //Testing  M-FSK
        
        // using d_m find the number of bits.  using nb=log2(d_m) (done in the constructor)

        // using nb find max decimal number presentation using nb ->  max_dec=(2^nb)-1 (done in the constructor)
        
        //loop through, creating bit strings and saving them into vector combinations (done in the constructor)
        
        //get the x bits required from input, form a string and find the index of that string index_k in the combinations vector. (done below)
        
        //using the index_k choose the tone accordingly. (done below)
        
        //The above contains extra work need to be modified.
        
        for(int i = 0; i < noutput_items/d_samples_per_sym; i++) {
          
            bits.clear();
            
            char bt;

            //forming the string of bits to modulate
            for (int p=0; p<log2(d_m);p++)
            {
                
                bt = (in[i+p]*1==1 ? '1':'0');
                bits.push_back(bt);
            }
            
            std::ostringstream xp;
            
            if (!bits.empty())
            {
                // Convert all but the last element to avoid a trailing ","
                std::copy(bits.begin(), bits.end()-1,
                          std::ostream_iterator<char>(xp, ""));
                
                // Now add the last element with no delimiter
                xp << bits.back();
            }
            
            
          
           
            
           
            
            
            //find the position of that string in vector combinations
            ptrdiff_t pos = find(combinations.begin(), combinations.end(), xp.str()) - combinations.begin();
            
            
           
            if(pos >= combinations.size()) {
                
                //error .. this should never occur
                
            }
            
            for(int j = 0; j < d_samples_per_sym; j++) {
                
                
                //pos has the actual tone number   k=pos in the equation Wd(2*k-(m-1))
                // calculating the phase
                d_phase += (2*pos-(d_m-1))*d_freq;
                
                while(d_phase > M_TWOPI)
                d_phase -= M_TWOPI;
                while(d_phase < -M_TWOPI)
                d_phase += M_TWOPI;
                
                *out++ = gr_expj(d_phase)*d_ampl;
           
                
            }
            i+=log2(d_m)-1;
         
           
            
        }
        
        
        
        
      // Tell runtime system how many input items we consumed on
      // each input stream.
        int ninputItems= noutput_items*log2(d_m)/d_samples_per_sym;
        
       
        
        if(noutput_items>0)
        consume_each(ninputItems);
        
        
      // Tell runtime system how many output items we produced.
      return noutput_items;
    }

  } /* namespace MFSK */
} /* namespace gr */

