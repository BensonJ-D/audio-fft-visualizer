#include "transform/fast_fourier_transform.hpp"

namespace transform {
    void FFT::generateBitReversalTable() {
        size_t mostSignificantBit = mDataSize >> 1; // Since totalDataPoints is a power of 2, we can use this to find the most significant bit.
        mBitReversalTable.resize(mDataSize);

        // Initialize the bit-reversal table
        for(size_t i = 0; i < mDataSize; ++i) {
            mBitReversalTable[i] = i;
        }

        // Perform bit-reversal on the table
        size_t inverseIndex = 0;
        for (size_t index = 1; index < mDataSize; ++index) { // Skip the first element because it's already in the correct position.
            size_t referenceBit = mostSignificantBit;
            while (inverseIndex & referenceBit) { // Find the position of the most significant bit that is set in the index.
                inverseIndex ^= referenceBit;
                referenceBit >>= 1;
            }
            inverseIndex ^= referenceBit; // Reset the bit in the inverse index that we used to check.
            if (index < inverseIndex) { // Swap the elements only if the current index is less than the inverse index. (Prevents double swapping)

                // TODO: This could be optimized further by using a pair to skip every other element, only being O(n/2) instead of O(n) and a full traversal?
                std::swap(mBitReversalTable[index], mBitReversalTable[inverseIndex]);
            }
        }
    }

    void FFT::reverseBits(ComplexVector& data) {
        if(data.size() != mDataSize) {
            throw std::runtime_error("Data size does not match FFT size.");
        }
        
        for (size_t index = 1; index < mDataSize; ++index) {
            size_t inverseIndex = mBitReversalTable[index];
            if (index < inverseIndex) { // Swap the elements only if the current index is less than the inverse index. (Prevents double swapping)
                std::swap(data[index], data[inverseIndex]);
            }
        }
    }
}