#include <atomic>
#include "ctagSoundProcessor.hpp"
#include "airwindows/CStrip.hpp"


namespace CTAG {
    namespace SP {
        class ctagSoundProcessorCStrip : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;
            ctagSoundProcessorCStrip();
            virtual ~ctagSoundProcessorCStrip();

        private:
            virtual void knowYourself() override;

            airwindows::CStrip cStrip;

            // private attributes could go here
            // autogenerated code here
            // sectionHpp
	atomic<int32_t> treble, cv_treble;
	atomic<int32_t> mid, cv_mid;
	atomic<int32_t> bass, cv_bass;
	atomic<int32_t> lowpass, cv_lowpass;
	atomic<int32_t> trebfreq, cv_trebfreq;
	atomic<int32_t> bassfreq, cv_bassfreq;
	atomic<int32_t> hipass, cv_hipass;
	atomic<int32_t> gate, cv_gate;
	atomic<int32_t> comp, cv_comp;
	atomic<int32_t> compspd, cv_compspd;
	atomic<int32_t> timelag, cv_timelag;
	atomic<int32_t> outgain, cv_outgain;
	// sectionHpp
        };
    }
}