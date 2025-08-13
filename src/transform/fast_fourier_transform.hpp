#pragma once
#include <vector>
#include <complex>
#include <cmath>

namespace transform {
    typedef std::complex<float> ComplexFloat;
    typedef std::vector<ComplexFloat> ComplexVector;

    class FFT {
        friend class FFTTest;
    public:
        FFT() {}
    private:
        void reverseBits(ComplexVector& data);
    };
}