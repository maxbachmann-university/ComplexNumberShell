#include "catch2/catch.hpp"
#include "ComplexShuntingYard.hpp"
#include "Complex.hpp"

// Testing ComplexShuntingYard

TEST_CASE( "evaluate two cartesian complex numbers", "[evaluate]" ) {

    SECTION( "add two cartesian complex numbers" ) {
        
        std::string inputString = "(14+5j) + (5-6i)";
        auto result = ComplexShuntingYard::evaluate(inputString);
        REQUIRE( result.real() == Approx(19) );
        REQUIRE( result.imag() == Approx(-1) );
    }

    SECTION( "subtract two cartesian complex numbers" ) {
        
        std::string inputString = "(11+7j) - (3-2i)";
        auto result = ComplexShuntingYard::evaluate(inputString);
        REQUIRE( result.real() == Approx(8) );
        REQUIRE( result.imag() == Approx(9) );
    }

    SECTION( "multiply two cartesian complex numbers" ) {
        
        std::string inputString = "(8+7j) * (4-6i)";
        auto result = ComplexShuntingYard::evaluate(inputString);
        REQUIRE( result.real() == Approx(74) );
        REQUIRE( result.imag() == Approx(-20) );
    }

    SECTION( "divide two cartesian complex numbers" ) {
        
        std::string inputString = "(8+12j) / (4-6i)";
        auto result = ComplexShuntingYard::evaluate(inputString);
        REQUIRE( result.real() == Approx(-0.769230) );
        REQUIRE( result.imag() == Approx(1.846153) );
    }
}

TEST_CASE( "evaluate two exponential complex numbers", "[evaluate]" ) {

    SECTION( "add two exponential complex numbers" ) {
        
        std::string inputString = "(5*e^i4) + (7*e^i7)";
        auto result = ComplexShuntingYard::evaluate(inputString);
        REQUIRE( result.real() == Approx(2.009094) );
        REQUIRE( result.imag() == Approx(8.382919) );
    }

    SECTION( "subtract two exponential complex numbers" ) {
        
        std::string inputString = "(6*e^i7) - (3*e^i2)";
        auto result = ComplexShuntingYard::evaluate(inputString);
        REQUIRE( result.real() == Approx(5.771853) );
        REQUIRE( result.imag() == Approx(6.669813) );
    }

    SECTION( "multiply two exponential complex numbers" ) {
        
        std::string inputString = "(4*e^i9) * (3*e^i4)";
        auto result = ComplexShuntingYard::evaluate(inputString);
        REQUIRE( result.real() == Approx(-10.889356) );
        REQUIRE( result.imag() == Approx(5.041998) );
    }

    SECTION( "divide two exponential complex numbers" ) {
        
        std::string inputString = "(12*e^i8) / (6*e^i4)";
        auto result = ComplexShuntingYard::evaluate(inputString);
        REQUIRE( result.real() == Approx(1.307286) );
        REQUIRE( result.imag() == Approx(-1.513605) );
    }
}

TEST_CASE( "evaluate two different complex numbers", "[evaluate]" ) {

    SECTION( "add exponential to cartesian complex number" ) {
        
        std::string inputString = "(5*e^i4) + (7+7i)";
        auto result = ComplexShuntingYard::evaluate(inputString);
        REQUIRE( result.real() == Approx(-10.26822) );
        REQUIRE( result.imag() == Approx(-3.21599) );
    }
}