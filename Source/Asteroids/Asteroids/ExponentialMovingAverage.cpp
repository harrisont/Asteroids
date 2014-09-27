#include "AsteroidsPCH.h"
#include "ExponentialMovingAverage.h"

ExponentialMovingAverage::ExponentialMovingAverage(float decayRate)
    : mDecayRate(decayRate)
{
}

float ExponentialMovingAverage::Get()
{
    return mValue;
}
    
void ExponentialMovingAverage::AddSample(float sample)
{
    if (mHasAtLeastOneSample)
    {
        mValue = mDecayRate * sample + (1 - mDecayRate) * mValue;
    }
    else
    {
        mValue = sample;
        mHasAtLeastOneSample = true;
    }
}
