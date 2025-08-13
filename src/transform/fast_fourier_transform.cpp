#include "transform/fast_fourier_transform.hpp"

namespace transform {
    // TODO: Generate bit-reversal table at startup for efficiency.
    void FFT::reverseBits(ComplexVector& data) {
        size_t totalDataPoints = data.size(); 
        size_t mostSignificantBit = totalDataPoints >> 1; // Since totalDataPoints is a power of 2, we can use this to find the most significant bit.

        size_t inverseIndex = 0;
        for (size_t index = 1; index < totalDataPoints; ++index) { // Skip the first element because it's already in the correct position.
            size_t referenceBit = mostSignificantBit;
            while (inverseIndex & referenceBit) { // Find the position of the most significant bit that is set in the index.
                inverseIndex ^= referenceBit;
                referenceBit >>= 1;
            }
            inverseIndex ^= referenceBit; // Reset the bit in the inverse index that we used to check.
            if (index < inverseIndex) { // Swap the elements only if the current index is less than the inverse index. (Prevents double swapping)
                std::swap(data[index], data[inverseIndex]);
            }
        }
    }
}