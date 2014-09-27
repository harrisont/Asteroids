#pragma once

// An exponentially weighted moving average.
class ExponentialMovingAverage
{
public:
    // decayRate must be in the range [0, 1].
    // A higher decayRate discounts old samples faster.
    ExponentialMovingAverage(float decayRate);

    float Get();
    void AddSample(float sample);

private:
    float mValue;
    float mDecayRate;  // Must be in the range [0, 1].
    bool mHasAtLeastOneSample = false;
};