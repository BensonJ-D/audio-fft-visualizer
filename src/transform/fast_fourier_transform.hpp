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
        FFT(size_t dataSize) : mDataSize(dataSize) {}
    private:
        size_t mDataSize;
        std::vector<size_t> mBitReversalTable;

        void generateBitReversalTable();
        void reverseBits(ComplexVector& data);
    };
}