/***************
CTAG TBD >>to be determined<< is an open source eurorack synthesizer module.

A project conceived within the Creative Technologies Arbeitsgruppe of
Kiel University of Applied Sciences: https://www.creative-technologies.de

(c) 2020 by Robert Manzke. All rights reserved.

The CTAG TBD software is licensed under the GNU General Public License
(GPL 3.0), available here: https://www.gnu.org/licenses/gpl-3.0.txt

The CTAG TBD hardware design is released under the Creative Commons
Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0).
Details here: https://creativecommons.org/licenses/by-nc-sa/4.0/

CTAG TBD is provided "as is" without any express or implied warranties.

License and copyright details for specific submodules are included in their
respective component folders / files if different from this license.
***************/

#include <atomic>
#include "ctagSoundProcessor.hpp"
#include "stmlib/dsp/hysteresis_quantizer.h"
#include "stmlib/dsp/units.h"
#include "tides2/poly_slope_generator.h"
#include "tides2/ramp/ramp_extractor.h"
#include "tides2/io_buffer.h"
#include "helpers/ctagADEnv.hpp"

namespace CTAG {
    namespace SP {
        class ctagSoundProcessorTBDeep : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;

           virtual void Init(std::size_t const &blockSize, void *const blockPtr) override;


        private:

            virtual void knowYourself() override;

            // private attributes could go here
            tides2::PolySlopeGenerator poly_slope_generator;
            tides2::RampExtractor ramp_extractor;
            stmlib::HysteresisQuantizer ratio_index_quantizer;

            // State
            tides2::OutputMode output_mode;
            tides2::RampMode ramp_mode;

            // Buffers
            tides2::PolySlopeGenerator::OutputSample out[tides2::kBlockSize] = {};
            stmlib::GateFlags trig_flags[tides2::kBlockSize] = {};
            stmlib::GateFlags clock_flags[tides2::kBlockSize] = {};
            stmlib::GateFlags previous_trig_flag = stmlib::GATE_FLAG_LOW;
            stmlib::GateFlags previous_clock_flag = stmlib::GATE_FLAG_LOW;

            bool must_reset_ramp_extractor = true;
            tides2::OutputMode previous_output_mode = tides2::OUTPUT_MODE_GATES;
            uint8_t frame = 0;

            CTAG::SP::HELPERS::ctagADEnv loudAD, paramAD;
            bool eg_pre_trigger = false;

            // autogenerated code here
// sectionHpp
            atomic<int32_t> trigger, trig_trigger;
            atomic<int32_t> clock, trig_clock;
            atomic<int32_t> out0, cv_out0;
            atomic<int32_t> out0_level, cv_out0_level;
            atomic<int32_t> out1, cv_out1;
            atomic<int32_t> out1_level, cv_out1_level;
            atomic<int32_t> frequency, cv_frequency;
            atomic<int32_t> shape, cv_shape;
            atomic<int32_t> slope, cv_slope;
            atomic<int32_t> smoothness, cv_smoothness;
            atomic<int32_t> shift, cv_shift;
            atomic<int32_t> eg_trigger, trig_eg_trigger;
            atomic<int32_t> eg_loop, trig_eg_loop;
            atomic<int32_t> eg_attack, cv_eg_attack;
            atomic<int32_t> eg_decay, cv_eg_decay;
            atomic<int32_t> mod_level, cv_mod_level;
            atomic<int32_t> mod_frequency, cv_mod_frequency;
            atomic<int32_t> mod_shape, cv_mod_shape;
            atomic<int32_t> mod_slope, cv_mod_slope;
            atomic<int32_t> mod_smoothness, cv_mod_smoothness;
            atomic<int32_t> mod_shift, cv_mod_shift;
            // sectionHpp

        };
    }
}