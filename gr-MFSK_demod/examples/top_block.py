#!/usr/bin/env python2
# -*- coding: utf-8 -*-
##################################################
# GNU Radio Python Flow Graph
# Title: Top Block
# Generated: Thu Apr 27 19:05:22 2017
##################################################

from gnuradio import blocks
from gnuradio import eng_notation
from gnuradio import filter
from gnuradio import gr
from gnuradio.eng_option import eng_option
from gnuradio.filter import firdes
from optparse import OptionParser
import MFSK_demod
import math


class top_block(gr.top_block):

    def __init__(self):
        gr.top_block.__init__(self, "Top Block")

        ##################################################
        # Variables
        ##################################################
        self.interpolation = interpolation = 200
        self.sps = sps = 48000/interpolation*5
        self.samp_rate = samp_rate = 48000
        self.baud_rate = baud_rate = float(samp_rate)/(sps)/interpolation
        self.w = w = 1/baud_rate
        self.deviation = deviation = 1
        self.carrier = carrier = 97
        self.bplc = bplc = float(baud_rate)-(baud_rate*(10**-12))
        self.bphc = bphc = float(baud_rate)+(baud_rate*(10**-12))
        self.a = a = math.sqrt(abs(((w/2)**2)-1))
        self.y = y = 1.0
        self.x1 = x1 = 1/baud_rate
        self.x = x = 1.0
        self.transition_width = transition_width = 2
        self.modulation_index = modulation_index = float(float(deviation)/(baud_rate/2))
        self.low_cut_off_freq = low_cut_off_freq = carrier-deviation
        self.kaiserB = kaiserB = 0.1102
        self.high_cut_off_freq = high_cut_off_freq = carrier+deviation
        self.diff = diff = float(bphc-bplc)
        self.b = b = math.pi*a
        self.Delay = Delay = 0

        ##################################################
        # Blocks
        ##################################################
        self.freq_xlating_fir_filter_xxx_0_0_0 = filter.freq_xlating_fir_filter_ccc(interpolation, (filter.firdes.low_pass(1, samp_rate, high_cut_off_freq,transition_width)), carrier, samp_rate)
        self.blocks_wavfile_source_1 = blocks.wavfile_source("/Volumes/Seagate Backup Plus Drive/NEWProjectWithMWS/Simulations/2-CPFSK/96_98/5sec/lowStripping/Realization20/SNR30R20.wav", False)
        self.blocks_multiply_const_vxx_0 = blocks.multiply_const_vcc((10**0, ))
        self.blocks_float_to_complex_0 = blocks.float_to_complex(1)
        self.blocks_file_sink_0 = blocks.file_sink(gr.sizeof_char*1, "/Users/ahmadtrabousli/Desktop/NEWProjectWithMWS/Simulations/2-CPFSK/96_98/testoutput", False)
        self.blocks_file_sink_0.set_unbuffered(False)
        self.blocks_delay_0 = blocks.delay(gr.sizeof_gr_complex*1, 0)
        self.band_pass_filter_0 = filter.interp_fir_filter_fff(1, firdes.band_pass(
        	1, samp_rate/interpolation, bplc, bphc, baud_rate*10**-2, firdes.WIN_BLACKMAN, b))
        self.MFSK_demod_symbol_timing_signal_0 = MFSK_demod.symbol_timing_signal(modulation_index, 2, sps)
        self.MFSK_demod_MFSK_demod3_0 = MFSK_demod.MFSK_demod3(modulation_index, 2, sps)

        ##################################################
        # Connections
        ##################################################
        self.connect((self.MFSK_demod_MFSK_demod3_0, 0), (self.blocks_file_sink_0, 0))    
        self.connect((self.MFSK_demod_symbol_timing_signal_0, 1), (self.band_pass_filter_0, 0))    
        self.connect((self.MFSK_demod_symbol_timing_signal_0, 0), (self.blocks_delay_0, 0))    
        self.connect((self.band_pass_filter_0, 0), (self.MFSK_demod_MFSK_demod3_0, 1))    
        self.connect((self.blocks_delay_0, 0), (self.MFSK_demod_MFSK_demod3_0, 0))    
        self.connect((self.blocks_float_to_complex_0, 0), (self.blocks_multiply_const_vxx_0, 0))    
        self.connect((self.blocks_multiply_const_vxx_0, 0), (self.freq_xlating_fir_filter_xxx_0_0_0, 0))    
        self.connect((self.blocks_wavfile_source_1, 0), (self.blocks_float_to_complex_0, 0))    
        self.connect((self.freq_xlating_fir_filter_xxx_0_0_0, 0), (self.MFSK_demod_symbol_timing_signal_0, 0))    

    def get_interpolation(self):
        return self.interpolation

    def set_interpolation(self, interpolation):
        self.interpolation = interpolation
        self.set_baud_rate(float(self.samp_rate)/(self.sps)/self.interpolation)
        self.set_sps(48000/self.interpolation*5)
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate/self.interpolation, self.bplc, self.bphc, self.baud_rate*10**-2, firdes.WIN_BLACKMAN, self.b))

    def get_sps(self):
        return self.sps

    def set_sps(self, sps):
        self.sps = sps
        self.set_baud_rate(float(self.samp_rate)/(self.sps)/self.interpolation)

    def get_samp_rate(self):
        return self.samp_rate

    def set_samp_rate(self, samp_rate):
        self.samp_rate = samp_rate
        self.set_baud_rate(float(self.samp_rate)/(self.sps)/self.interpolation)
        self.freq_xlating_fir_filter_xxx_0_0_0.set_taps((filter.firdes.low_pass(1, self.samp_rate, self.high_cut_off_freq,self.transition_width)))
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate/self.interpolation, self.bplc, self.bphc, self.baud_rate*10**-2, firdes.WIN_BLACKMAN, self.b))

    def get_baud_rate(self):
        return self.baud_rate

    def set_baud_rate(self, baud_rate):
        self.baud_rate = baud_rate
        self.set_bphc(float(self.baud_rate)+(self.baud_rate*(10**-12)))
        self.set_bplc(float(self.baud_rate)-(self.baud_rate*(10**-12)))
        self.set_modulation_index(float(float(self.deviation)/(self.baud_rate/2)))
        self.set_w(1/self.baud_rate)
        self.set_x1(1/self.baud_rate)
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate/self.interpolation, self.bplc, self.bphc, self.baud_rate*10**-2, firdes.WIN_BLACKMAN, self.b))

    def get_w(self):
        return self.w

    def set_w(self, w):
        self.w = w
        self.set_a(math.sqrt(abs(((self.w/2)**2)-1)))

    def get_deviation(self):
        return self.deviation

    def set_deviation(self, deviation):
        self.deviation = deviation
        self.set_high_cut_off_freq(self.carrier+self.deviation)
        self.set_low_cut_off_freq(self.carrier-self.deviation)
        self.set_modulation_index(float(float(self.deviation)/(self.baud_rate/2)))

    def get_carrier(self):
        return self.carrier

    def set_carrier(self, carrier):
        self.carrier = carrier
        self.set_high_cut_off_freq(self.carrier+self.deviation)
        self.set_low_cut_off_freq(self.carrier-self.deviation)
        self.freq_xlating_fir_filter_xxx_0_0_0.set_center_freq(self.carrier)

    def get_bplc(self):
        return self.bplc

    def set_bplc(self, bplc):
        self.bplc = bplc
        self.set_diff(float(self.bphc-self.bplc))
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate/self.interpolation, self.bplc, self.bphc, self.baud_rate*10**-2, firdes.WIN_BLACKMAN, self.b))

    def get_bphc(self):
        return self.bphc

    def set_bphc(self, bphc):
        self.bphc = bphc
        self.set_diff(float(self.bphc-self.bplc))
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate/self.interpolation, self.bplc, self.bphc, self.baud_rate*10**-2, firdes.WIN_BLACKMAN, self.b))

    def get_a(self):
        return self.a

    def set_a(self, a):
        self.a = a
        self.set_b(math.pi*self.a)

    def get_y(self):
        return self.y

    def set_y(self, y):
        self.y = y

    def get_x1(self):
        return self.x1

    def set_x1(self, x1):
        self.x1 = x1

    def get_x(self):
        return self.x

    def set_x(self, x):
        self.x = x

    def get_transition_width(self):
        return self.transition_width

    def set_transition_width(self, transition_width):
        self.transition_width = transition_width
        self.freq_xlating_fir_filter_xxx_0_0_0.set_taps((filter.firdes.low_pass(1, self.samp_rate, self.high_cut_off_freq,self.transition_width)))

    def get_modulation_index(self):
        return self.modulation_index

    def set_modulation_index(self, modulation_index):
        self.modulation_index = modulation_index

    def get_low_cut_off_freq(self):
        return self.low_cut_off_freq

    def set_low_cut_off_freq(self, low_cut_off_freq):
        self.low_cut_off_freq = low_cut_off_freq

    def get_kaiserB(self):
        return self.kaiserB

    def set_kaiserB(self, kaiserB):
        self.kaiserB = kaiserB

    def get_high_cut_off_freq(self):
        return self.high_cut_off_freq

    def set_high_cut_off_freq(self, high_cut_off_freq):
        self.high_cut_off_freq = high_cut_off_freq
        self.freq_xlating_fir_filter_xxx_0_0_0.set_taps((filter.firdes.low_pass(1, self.samp_rate, self.high_cut_off_freq,self.transition_width)))

    def get_diff(self):
        return self.diff

    def set_diff(self, diff):
        self.diff = diff

    def get_b(self):
        return self.b

    def set_b(self, b):
        self.b = b
        self.band_pass_filter_0.set_taps(firdes.band_pass(1, self.samp_rate/self.interpolation, self.bplc, self.bphc, self.baud_rate*10**-2, firdes.WIN_BLACKMAN, self.b))

    def get_Delay(self):
        return self.Delay

    def set_Delay(self, Delay):
        self.Delay = Delay


def main(top_block_cls=top_block, options=None):

    tb = top_block_cls()
    tb.start()
    tb.wait()


if __name__ == '__main__':
    main()
