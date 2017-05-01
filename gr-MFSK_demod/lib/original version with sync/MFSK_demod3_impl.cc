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
#include "MFSK_demod3_impl.h"
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

    MFSK_demod3::sptr
    MFSK_demod3::make(float k, int m, int samples_per_symbol)
    {
      return gnuradio::get_initial_sptr
        (new MFSK_demod3_impl(k, m, samples_per_symbol));
    }
      
      int choose(int n, int k)
      {
          if (k == 0)
          return 1;
          else{
              return (n * choose(n - 1, k - 1)) / k;
          }
      }
      
      
      
      
      struct foo{
          
          std::vector<float> a;
          std::vector<int> b;
          
          
      };
      
      struct foo zero_crossings(std::vector<float> all)
      {
          std::vector<float> x(all);
          std::vector<int> indx_all;
          int all_size=all.size();
          int k;
          float work;
          int m;
          float tmp2;
          
          
          // Finds +ve Zero Crossings
          for (k = 0; k < all_size; k++) {
              if (all[k] < 0.0) {
                  x[k] = -1.0;
              } else if (all[k] > 0.0) {
                  x[k] = 1.0;
              } else if (all[k] == 0.0) {
                  x[k] = 0.0;
              } else {
                  x[k] = all[k];
              }
          }
          
          k = 1;
          work = x[0];
          for (m = 0; m < (all_size-1); m++) {
              tmp2 = work;
              work = x[k];
              tmp2 = x[k] - tmp2;
              k++;
              if(tmp2<0)
              {
                  tmp2=0;
              }
              x[m] = tmp2;
              if(tmp2>0)
              {
                  indx_all.push_back(m);
              }
          }
          foo res;
          res.a=x;
          res.b.swap(indx_all);
          return res;
          
      }


    /*
     * The private constructor
     */
    MFSK_demod3_impl::MFSK_demod3_impl(float k, int m, int samples_per_symbol)
      : gr::block("MFSK_demod3",
              gr::io_signature::make2(1, 2, sizeof(gr_complex), sizeof(float)),
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
        
        nck=choose(d_m,2);
        
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
        
        set_history((samp_sym));
        set_relative_rate(1.0 *log2(d_m)/ samples_per_symbol);
        set_output_multiple(log2(d_m));

    
    }

    /*
     * Our virtual destructor.
     */
    MFSK_demod3_impl::~MFSK_demod3_impl()
    {
    }

    void
    MFSK_demod3_impl::forecast (int noutput_items, gr_vector_int &ninput_items_required)
    {
        unsigned ninputs = ninput_items_required.size();
        for(unsigned i = 0; i < ninputs; i++)
        ninput_items_required[i] = noutput_items/log2(d_m) * samp_sym + history() - 1;
    }
      
      
      
      
      
      

    int
    MFSK_demod3_impl::general_work (int noutput_items,
                       gr_vector_int &ninput_items,
                       gr_vector_const_void_star &input_items,
                       gr_vector_void_star &output_items)
    {
        
        const int noutput=noutput_items;
        const gr_complex *in = (const gr_complex *) input_items[0];
        const float *in2= (const float *) input_items[1];
        unsigned char *out = (unsigned char *) output_items[0];
        
        // Do <+signal processing+>
        
        //First we need to find out where our symbol starts using the incoming bandpassed symbol sync signal
        // to do this we find the +ve zero_crossings in that signal and start the sampling at those zero crossings.
        // sometimes we might find several zero crossings within 10 samples or 20 samples which we should ignore.
        // we will call this tolerance parameter delta_p and will set it to 10% of a symbol time i.e ceil(0.1*samp_sym).
        // we need a duration of two symbols and another function called indx_up which returns the index of all +ve crossings in the signal upon which we will choose where to sample.
        //we require a history of sps items. i.e. uncomment set_history(samp_sym) above
        
        
        
        //read in the sync signal
        std::vector<float> sync;
        int cntr=0;
       // sync.clear();
        //This loop includes a history of one symbol time.
        for (int i=0; i <noutput * samp_sym/log2(d_m)+history(); i++)
        {
            cntr++;
            sync.push_back(in2[i]);
            
        }
                        
                    
        
        //find the crossings
        foo crossings= zero_crossings(sync);
        
        //size of current readings
        int size_of_current_input=(noutput * (samp_sym/log2(d_m))+history());
        
       
        
        //getting the right indices put them in samp_
        
        std::vector<int> samp_;
       /*
        std::ofstream myfile;
        myfile.open("/Users/ahmadtrabousli/Desktop/blocks/log.txt",std::ios::app);
        if (myfile.is_open())
        {
            myfile << crossings.b.size() <<',';
            
            myfile.close();
        }
        */
        for (int i=0; i<crossings.b.size();i++){
            
            // This is to avoid sampling a symbol where the not all of its samples haves been read yet
            //this might be the issue
            if(!(crossings.b[i]>(size_of_current_input-(samp_sym))))
            {
                samp_.push_back(crossings.b[i]);
                
            }
            
            
            
        }
        
        
        //all what remains to do is:
        // sample the signal starting from the index provided by the above samp_ vector.
        // need to find where to stop sampling the symbol,
        //need to know when to start sampling the second symbol
        // all of which will be derived from the samp_
        
        //first find how many zero crossings are there currently
        int zc_size= samp_.size();
        
        int count=0;
        
        

        for (int kkj=0; kkj < zc_size; kkj++)
        {
            //sampling of the symbols
           
            
            
            std::ofstream myfile;
            myfile.open("/Users/ahmadtrabousli/Desktop/NEWProjectWithMWS/Simulations/2-CPFSK/96_98/log.txt",std::ios::app);
            if (myfile.is_open())
            {
                myfile << samp_[kkj] <<',';
                
                myfile.close();
            }
            
            
            
            
            
            int count_samp=0;
            for (int i=(samp_[kkj]); i<(samp_[kkj]+(samp_sym));i++)
            
            {     count_samp++;
                
                //clear jexp_i
                jexp_i.clear();
                
                
    
                //preparing Tones using 2k-(m-1) k=0,...,m-1 tones
                for (int j=0; j< d_m; j++)
                
                {   // phase of each tone filter = (2*j-(d_m-1)*fd        deviation=mod_index*baud_rate/2
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
                if ( count_samp == samp_sym)
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
                
                
                d_offset++; //might need to reset this at the begining of the for loop
                
            }

        }

        // Tell runtime system how many input items we consumed on
        // each input stream.
        consume_each (noutput * samp_sym /log2(d_m));
        
        // Tell runtime system how many output items we produced.
        return count;

    }

  } /* namespace MFSK_demod */
} /* namespace gr */





// Now done outside of this block. Implemented in another block.
//NEWLY ADDED
//Generating a SYmbol Clock timing signal
//C(nt)= summation |ei(nt) - ej(nt)|   where 0<=i<j<=m-1
/*     float sumtemp=0;
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
 Csum.push_back(sumtemp);
 
 
 
 std::ofstream myfile;
 myfile.open("/Users/ahmadtrabousli/Desktop/blocks/log.txt",std::ios::app);
 if (myfile.is_open())
 {
 
 myfile << sumtemp <<',';
 
 myfile.close();
 }
 
 */







//old code


/*
int count=0;


for (int i=0; i <noutput * samp_sym/log2(d_m)+history(); i++)
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
    
    
    d_offset++; //might need to reset this at the begining of the for loop
    
    
}
 */






/*
 std::ofstream myfile;
 myfile.open("/Users/ahmadtrabousli/Desktop/blocks/log.txt",std::ios::app);
 if (myfile.is_open())
 {
 myfile << zc_size <<',';
 
 myfile.close();
 }
 */