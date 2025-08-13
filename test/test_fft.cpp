#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "transform/fast_fourier_transform.hpp"

namespace transform{
    class FFTTest {
    public:
        static void callReverseBits(transform::FFT& fft, ComplexVector& data) {
            fft.reverseBits(data);
        }
    };
}

TEST_CASE("Bit-reversal size-8", "[transform]") {
    transform::FFT fft; 
    transform::ComplexVector data = {0, 1, 2, 3, 4, 5, 6, 7};
    
    transform::FFTTest::callReverseBits(fft, data);
    
    // Check if the data is reversed correctly
    REQUIRE(data[0] == transform::ComplexFloat(0, 0));
    REQUIRE(data[1] == transform::ComplexFloat(4, 0));
    REQUIRE(data[2] == transform::ComplexFloat(2, 0));
    REQUIRE(data[3] == transform::ComplexFloat(6, 0));
    REQUIRE(data[4] == transform::ComplexFloat(1, 0));
    REQUIRE(data[5] == transform::ComplexFloat(5, 0));
    REQUIRE(data[6] == transform::ComplexFloat(3, 0));
    REQUIRE(data[7] == transform::ComplexFloat(7, 0));
}

TEST_CASE("Bit-reversal size-16", "[transform]") {
    transform::FFT fft; 
    transform::ComplexVector data = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    
    transform::FFTTest::callReverseBits(fft, data);
    
    // Check if the data is reversed correctly
    REQUIRE(data[0] == transform::ComplexFloat(0, 0));
    REQUIRE(data[1] == transform::ComplexFloat(8, 0));
    REQUIRE(data[2] == transform::ComplexFloat(4, 0));
    REQUIRE(data[3] == transform::ComplexFloat(12, 0));
    REQUIRE(data[4] == transform::ComplexFloat(2, 0));
    REQUIRE(data[5] == transform::ComplexFloat(10, 0));
    REQUIRE(data[6] == transform::ComplexFloat(6, 0));
    REQUIRE(data[7] == transform::ComplexFloat(14, 0));
    REQUIRE(data[8] == transform::ComplexFloat(1, 0));
    REQUIRE(data[9] == transform::ComplexFloat(9, 0));
    REQUIRE(data[10] == transform::ComplexFloat(5, 0));
    REQUIRE(data[11] == transform::ComplexFloat(13, 0));
    REQUIRE(data[12] == transform::ComplexFloat(3, 0));
    REQUIRE(data[13] == transform::ComplexFloat(11, 0));
    REQUIRE(data[14] == transform::ComplexFloat(7, 0));
    REQUIRE(data[15] == transform::ComplexFloat(15, 0));
}