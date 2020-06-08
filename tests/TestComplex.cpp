#include "catch2/catch.hpp"
#include "Complex.hpp"
#include "Exponential.hpp"

TEST_CASE( "convert complex number", "[complex]" ) {

    SECTION( "convert to exponential" ) {
        
        Complex<double> cartNumber(1,1);
        auto result = cartNumber.to_exponential();
        REQUIRE( result.r == Approx(1.414213) );
        REQUIRE( result.phi == Approx(0.785398) );
    }

    SECTION( "convert from exponential" ) {
        
        Complex<double> cartNumber(1,1);
        Exponential<double> expNumber(4,7);
        auto result = cartNumber.from_exponential(expNumber);
        REQUIRE( result.real() == Approx(3.015609) );
        REQUIRE( result.imag() == Approx(2.627946) );
    }
}