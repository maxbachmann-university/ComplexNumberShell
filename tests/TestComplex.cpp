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

TEST_CASE( "basic complex functions", "[complex]" ) {

    SECTION( "magnitude abs()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = abs(cartNumber);
        REQUIRE( result == Approx(5.830951) );
    }

    SECTION( "phase angle arg()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = arg(cartNumber);
        REQUIRE( result == Approx(1.030376) );
    }

    SECTION( "squared magnitude (field norm) norm()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = norm(cartNumber);
        REQUIRE( result == Approx(34) );
    }

    SECTION( "Complex conjugate conj()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = conj(cartNumber);
        REQUIRE( result.real() == Approx(3) );
        REQUIRE( result.imag() == Approx(-5) );
    }

    SECTION( "Complex cosine cos()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = cos(cartNumber);
        REQUIRE( result.real() == Approx(-73.467292) );
        REQUIRE( result.imag() == Approx(-10.471557) );
    }

    SECTION( "Complex hyperbolic cosine cosh()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = cosh(cartNumber);
        REQUIRE( result.real() == Approx(2.855815) );
        REQUIRE( result.imag() == Approx(-9.606383) );
    }

    SECTION( "Complex base e exponential exp()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = exp(cartNumber);
        REQUIRE( result.real() == Approx(5.697507) );
        REQUIRE( result.imag() == Approx(-19.260508) );
    }

    SECTION( "Complex natural logarithm log()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = log(cartNumber);
        REQUIRE( result.real() == Approx(1.763180) );
        REQUIRE( result.imag() == Approx(1.030376) );
    }

    SECTION( "Complex base 10 logarithm log10()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = log10(cartNumber);
        REQUIRE( result.real() == Approx(0.765739) );
        REQUIRE( result.imag() == Approx(0.447486) );
    }

    SECTION( "Tx to the y'th power pow(complex, double)" ) {
        
        Complex<double> cartNumber(3,5);
        double number = 3.1;
        auto result = pow(cartNumber, number);
        REQUIRE( result.real() == Approx(-236.152098) );
        REQUIRE( result.imag() == Approx(-12.427269) );
    }

    SECTION( "Tx to the y'th power pow(complex, complex)" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = pow(cartNumber, cartNumber);
        REQUIRE( result.real() == Approx(0.907045) );
        REQUIRE( result.imag() == Approx(-0.703001) );
    }

    SECTION( "Tx to the y'th power pow(double, complex)" ) {
        
        Complex<double> cartNumber(3,5);
        double number = 3.1;
        auto result = pow(number, cartNumber);
        REQUIRE( result.real() == Approx(24.138908) );
        REQUIRE( result.imag() == Approx(-17.459002) );
    }

    SECTION( "Complex sine sin()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = sin(cartNumber);
        REQUIRE( result.real() == Approx(10.472508) );
        REQUIRE( result.imag() == Approx(-73.460621) );
    }

    SECTION( "Complex hyperbolic sine sinh()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = sinh(cartNumber);
        REQUIRE( result.real() == Approx(2.841692) );
        REQUIRE( result.imag() == Approx(-9.654125) );
    }

    SECTION( "Complex square root sqrt()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = sqrt(cartNumber);
        REQUIRE( result.real() == Approx(2.101303) );
        REQUIRE( result.imag() == Approx(5) );
    }

    SECTION( "Complex tangent tan()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = tan(cartNumber);
        REQUIRE( result.real() == Approx(-0.0000253687) );
        REQUIRE( result.imag() == Approx(0.999912) );
    }

    SECTION( "Complex hyperbolic tangent tanh()" ) {
        
        Complex<double> cartNumber(3,5);
        auto result = tanh(cartNumber);
        REQUIRE( result.real() == Approx(1.004164) );
        REQUIRE( result.imag() == Approx(-0.0027082358) );
    }
}