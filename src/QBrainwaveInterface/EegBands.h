#ifndef BRAINWAVE_EEGBANDS
#define BRAINWAVE_EEGBANDS
namespace Brainwave {
struct EegBands {
    float delta;
    float theta;
    float lowAlpha;
    float highAlpha;
    float lowBeta;
    float highBeta;
    float lowGamma;
    float highGamma;
};
}
#endif
