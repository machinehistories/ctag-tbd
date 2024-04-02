#include <atomic>
#include "ctagSoundProcessor.hpp"

namespace CTAG {
    namespace SP {
        class ctagSoundProcessorTemplate : public ctagSoundProcessor {
        public:
            virtual void Process(const ProcessData &) override;
            // no ctor, use Init() instead, is called from factory after successful creation
            virtual void Init(std::size_t blockSize, void *blockPtr) override;
            virtual ~ctagSoundProcessorTemplate();

        private:
            virtual void knowYourself() override;

            // private attributes could go here
            // autogenerated code here
            // sectionHpp
            // sectionHpp
        };
    }
}