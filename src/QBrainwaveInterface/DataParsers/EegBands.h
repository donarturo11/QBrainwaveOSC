#ifndef BRAINWAVE_EEGBANDS
#define BRAINWAVE_EEGBANDS
namespace Brainwave {
struct EegBands {
    float eegDelta;
    float eegTheta;
    float eegLowAlpha;
    float eegHighAlpha;
    float eegLowBeta;
    float eegHighBeta;
    float eegLowGamma;
    float eegHighGamma;
};
}
#endif
