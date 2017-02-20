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


#ifndef INCLUDED_MFSK_DEMOD_MFSK_DEMOD2_H
#define INCLUDED_MFSK_DEMOD_MFSK_DEMOD2_H

#include <MFSK_demod/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace MFSK_demod {

    /*!
     * \brief <+description of block+>
     * \ingroup MFSK_demod
     *
     */
    class MFSK_DEMOD_API MFSK_demod2 : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<MFSK_demod2> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of MFSK_demod::MFSK_demod2.
       *
       * To avoid accidental use of raw pointers, MFSK_demod::MFSK_demod2's
       * constructor is in a private implementation
       * class. MFSK_demod::MFSK_demod2::make is the public interface for
       * creating new instances.
       */
      static sptr make(float k, int m, int samples_per_symbol);
    };

  } // namespace MFSK_demod
} // namespace gr

#endif /* INCLUDED_MFSK_DEMOD_MFSK_DEMOD2_H */

