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

#include "ctagSoundProcessorTDelay.hpp"
#include <cmath>

using namespace CTAG::SP;

void ctagSoundProcessorTDelay::Process(const ProcessData &data) {
    float fDelay = delay / 4095.f;
    if(cv_delay != -1){
        fDelay = 0.05f * fabsf(data.cv[cv_delay]) + 0.95f * preDelay;
        preDelay = fDelay;
    }
    tdelay.SetDelay(fDelay);
    float fWet = wet / 4095.f;
    if(cv_wet != -1){
        fWet = fabsf(data.cv[cv_wet]);
    }
    tdelay.SetWet(fWet);
    float fDry = dry / 4095.f;
    if(cv_dry != -1){
        fDry = fabsf(data.cv[cv_dry]);
    }
    tdelay.SetDry(fDry);
    float fFeedback = feedback / 4095.f;
    if(cv_feedback != -1){
        fFeedback = fabsf(data.cv[cv_feedback]);
    }
    tdelay.SetFeedback(fFeedback);
    float fLNFT = lnft / 4095.f;
    if(cv_lnft != -1){
        fLNFT = 0.05f * fabsf(data.cv[cv_lnft]) + 0.95f * preLNFT;
        preLNFT = fLNFT;
    }
    tdelay.SetLNFT(fLNFT);
    float fDepth = depth / 4095.f;
    if(cv_depth != -1){
        fDepth = 0.05f * fabsf(data.cv[cv_depth]) + 0.95f * preDepth;
        preDepth = fDepth;
    }
    tdelay.SetDepth(fDepth);
    bool bByp = bypass;
    if(trig_bypass != -1){
        bByp = data.trig[trig_bypass] == 1 ? 0 : 1;
    }
    tdelay.SetBypass(bByp);
    tdelay.Process(data.buf, bufSz, processCh);
}

void ctagSoundProcessorTDelay::Init(std::size_t const &blockSize, void *const blockPtr) {
    // construct internal data model
    knowYourself();
    model = std::make_unique<ctagSPDataModel>(id, isStereo);
    LoadPreset(0);

}

ctagSoundProcessorTDelay::~ctagSoundProcessorTDelay() {
}

void ctagSoundProcessorTDelay::knowYourself(){
    // autogenerated code here
    // sectionCpp0
	pMapPar.emplace("bypass", [&](const int val){ bypass = val;});
	pMapTrig.emplace("bypass", [&](const int val){ trig_bypass = val;});
	pMapPar.emplace("depth", [&](const int val){ depth = val;});
	pMapCv.emplace("depth", [&](const int val){ cv_depth = val;});
	pMapPar.emplace("delay", [&](const int val){ delay = val;});
	pMapCv.emplace("delay", [&](const int val){ cv_delay = val;});
	pMapPar.emplace("feedback", [&](const int val){ feedback = val;});
	pMapCv.emplace("feedback", [&](const int val){ cv_feedback = val;});
	pMapPar.emplace("lnft", [&](const int val){ lnft = val;});
	pMapCv.emplace("lnft", [&](const int val){ cv_lnft = val;});
	pMapPar.emplace("dry", [&](const int val){ dry = val;});
	pMapCv.emplace("dry", [&](const int val){ cv_dry = val;});
	pMapPar.emplace("wet", [&](const int val){ wet = val;});
	pMapCv.emplace("wet", [&](const int val){ cv_wet = val;});
	isStereo = false;
	id = "TDelay";
	// sectionCpp0
}