#ifndef __RELAY_H_INCLUDED
#define __RELAY_H_INCLUDED

#include <cmath>
#include "matrix.h"

class Relay
{
private:
    double Error, Reference, Sample, SampleTime, peakRelayOutput, peakSystemOutput, kp, ki, kd, toleranceError;
    Matrix<double> relayOutput, systemOutput;

    void relayCalc();

public:
    Relay();

    void setReference(double ref);
    void setToleranceError(double tolerance);
    double relayLoop(double output);
};

#endif // RELAY_H
