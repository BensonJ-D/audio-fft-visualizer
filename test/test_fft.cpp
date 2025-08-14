#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "transform/fast_fourier_transform.hpp"

namespace transform{
    class FFTTest {
    public:
        static void generateBitReversalTable(transform::FFT& fft) {
            fft.generateBitReversalTable();
        }

        static void callReverseBits(transform::FFT& fft, ComplexVector& data) {
            fft.reverseBits(data);
        }

        static std::vector<size_t>& getBitReversalTable(transform::FFT& fft) {
            return fft.mBitReversalTable;
        }
    };
}

TEST_CASE("Bit-reversal size-8", "[fft]") {
    transform::FFT fft(8); 
    
    transform::FFTTest::generateBitReversalTable(fft);
    auto& bitReversalTable = transform::FFTTest::getBitReversalTable(fft);
    
    REQUIRE(bitReversalTable[0] == 0);
    REQUIRE(bitReversalTable[1] == 4);
    REQUIRE(bitReversalTable[2] == 2);
    REQUIRE(bitReversalTable[3] == 6);
    REQUIRE(bitReversalTable[4] == 1);
    REQUIRE(bitReversalTable[5] == 5);
    REQUIRE(bitReversalTable[6] == 3);
    REQUIRE(bitReversalTable[7] == 7);

    transform::ComplexVector data = { 19, 21, 113, 41, 57, 63, 71, 88 };
    transform::FFTTest::callReverseBits(fft, data);

    REQUIRE(data[0] == transform::ComplexFloat(19, 0));
    REQUIRE(data[1] == transform::ComplexFloat(57, 0));
    REQUIRE(data[2] == transform::ComplexFloat(113, 0));
    REQUIRE(data[3] == transform::ComplexFloat(71, 0));
    REQUIRE(data[4] == transform::ComplexFloat(21, 0));
    REQUIRE(data[5] == transform::ComplexFloat(63, 0));
    REQUIRE(data[6] == transform::ComplexFloat(41, 0));
    REQUIRE(data[7] == transform::ComplexFloat(88, 0));
}

TEST_CASE("Bit-reversal size-16", "[fft]") {
    transform::FFT fft(16); 
    
    transform::FFTTest::generateBitReversalTable(fft);
    auto& bitReversalTable = transform::FFTTest::getBitReversalTable(fft);
    
    // Check if the data is reversed correctly
    REQUIRE(bitReversalTable[0] == 0);
    REQUIRE(bitReversalTable[1] == 8);
    REQUIRE(bitReversalTable[2] == 4);
    REQUIRE(bitReversalTable[3] == 12);
    REQUIRE(bitReversalTable[4] == 2);
    REQUIRE(bitReversalTable[5] == 10);
    REQUIRE(bitReversalTable[6] == 6);
    REQUIRE(bitReversalTable[7] == 14);
    REQUIRE(bitReversalTable[8] == 1);
    REQUIRE(bitReversalTable[9] == 9);
    REQUIRE(bitReversalTable[10] == 5);
    REQUIRE(bitReversalTable[11] == 13);
    REQUIRE(bitReversalTable[12] == 3);
    REQUIRE(bitReversalTable[13] == 11);
    REQUIRE(bitReversalTable[14] == 7);
    REQUIRE(bitReversalTable[15] == 15);

    transform::ComplexVector data = { 19, 21, 113, 41, 57, 63, 71, 88, 
                                      29, 31, 119, 49, 67, 73, 97, 104 };
    transform::FFTTest::callReverseBits(fft, data);

    REQUIRE(data[0] == transform::ComplexFloat(19, 0));
    REQUIRE(data[1] == transform::ComplexFloat(29, 0));
    REQUIRE(data[2] == transform::ComplexFloat(57, 0));
    REQUIRE(data[3] == transform::ComplexFloat(67, 0));
    REQUIRE(data[4] == transform::ComplexFloat(113, 0));
    REQUIRE(data[5] == transform::ComplexFloat(119, 0));
    REQUIRE(data[6] == transform::ComplexFloat(71, 0));
    REQUIRE(data[7] == transform::ComplexFloat(97, 0));
    REQUIRE(data[8] == transform::ComplexFloat(21, 0));
    REQUIRE(data[9] == transform::ComplexFloat(31, 0));
    REQUIRE(data[10] == transform::ComplexFloat(63, 0));
    REQUIRE(data[11] == transform::ComplexFloat(73, 0));
    REQUIRE(data[12] == transform::ComplexFloat(41, 0));
    REQUIRE(data[13] == transform::ComplexFloat(49, 0));
    REQUIRE(data[14] == transform::ComplexFloat(88, 0));
    REQUIRE(data[15] == transform::ComplexFloat(104, 0));
}