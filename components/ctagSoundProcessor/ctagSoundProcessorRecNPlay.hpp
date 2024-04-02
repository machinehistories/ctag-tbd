#include <atomic>
#include "ctagSoundProcessor.hpp"

#include "helpers/ctagWNoiseGen.hpp"
#include "filters/ctagWPkorg35.hpp"
#include "helpers/ctagADEnv.hpp"
#include "stmlib/stmlib.h"      // for CONSTRAIN Macro...
#include "fx/ctagDecimator.h"
#include "helpers/ctagSineSource.hpp"

// --- VULT "Library for TBD" ---
#include "./vult/vult_formantor.h"
#include "./vult/vult_formantor.tables.h"

using namespace CTAG::SP::HELPERS;
using namespace CTAG::SP;

namespace CTAG {
    namespace SP {
        class ctagSoundProcessorRecNPlay : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;
           virtual void Init(std::size_t blockSize, void *blockPtr) override;
            virtual ~ctagSoundProcessorRecNPlay();

        private:
            virtual void knowYourself() override;

            // --- Remember status of triggers / buttons ---
            inline int process_param_trig( const ProcessData &data, int trig_myparm, int my_parm, int prev_trig_state_id, int gate_type ); // rescale incoming data to bool
            enum trig_states
            {
                e_EGactiv, e_VoiceMute, e_StepperActive, e_ResetNow, e_StepAndEGtrigger, e_RecPlay, e_BitcrusherIsOn, e_RecNplay_options_max
            };
            int prev_trig_state[e_RecNplay_options_max] = {0};   // Initialize _all_ entries with "low value"
            bool low_reached[e_RecNplay_options_max] = {false};  // We need this for look for toggle-events

            // --- Clock-Metronome ---
            ctagSineSource metro;
            bool clockSinusWasLow = false;
            float f_BPMint_mem = 0.f;

            // --- Decimator ---
            ctagDecimator decimator;

            // --- White Noise ---
            ctagWNoiseGen wNoise;

            // --- Sample and Hold for Bitcrusher ---
            float wNoiseSnH = 0.f;
            bool SnHlatched_ = false;
            float f_DownsampleFactorMem_ = 0.f;

            // --- Filter ---
            ctagWPkorg35 wpKorg35;

            // --- Envelope ---
            HELPERS::ctagADEnv vol_env;

            // --- VULT Stuff ---
            Saw_eptr__ctx_type_0 saw_data;              // Saw oscillator data-structure

            // --- Stepper ---
            int step_id = 0;
            bool last_step_mode_play = false;
            int current_step_mem_ = 1;
            enum stepper_values
            {
                s_VoiceVol, s_PitchSaw, s_ExtSawMix, s_SawNoiseMix, s_Cutoff, s_Resonance, s_Drive, s_StepperMem_params_max
            };
            float stepMem[32][s_StepperMem_params_max];
            float f_VoiceVol_mem = 0.f;
            float f_PitchSaw_mem = 0.f;
            float f_ExtSawMix_mem = 0.f;
            float f_SawNoiseMix_mem = 0.f;
            float f_Cutoff_mem = 0.f;
            float f_Resonance_mem = 0.f;
            float f_Drive_mem = 0.f;

            // private attributes could go here
            // autogenerated code here
            // sectionHpp
	atomic<int32_t> Volume, cv_Volume;
	atomic<int32_t> EGactiv, trig_EGactiv;
	atomic<int32_t> Attack, cv_Attack;
	atomic<int32_t> Decay, cv_Decay;
	atomic<int32_t> StepAndEGtrigger, trig_StepAndEGtrigger;
	atomic<int32_t> VoiceVol, cv_VoiceVol;
	atomic<int32_t> PitchSaw, cv_PitchSaw;
	atomic<int32_t> ExtSawMix, cv_ExtSawMix;
	atomic<int32_t> SawNoiseMix, cv_SawNoiseMix;
	atomic<int32_t> Cutoff, cv_Cutoff;
	atomic<int32_t> Resonance, cv_Resonance;
	atomic<int32_t> Drive, cv_Drive;
	atomic<int32_t> BitsToCrush, cv_BitsToCrush;
	atomic<int32_t> DownsampleFactor, cv_DownsampleFactor;
	atomic<int32_t> SnHamount, cv_SnHamount;
	atomic<int32_t> StepperActive, trig_StepperActive;
	atomic<int32_t> RecPlay, trig_RecPlay;
	atomic<int32_t> CurrentStep, cv_CurrentStep;
	atomic<int32_t> NumberOfSteps, cv_NumberOfSteps;
	atomic<int32_t> BPMint, cv_BPMint;
	// sectionHpp
        };
    }
}