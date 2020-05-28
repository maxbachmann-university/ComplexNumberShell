#pragma once

constexpr const char* pow_docstring =
R"(pow(<base complex number>, <exponent complex number>)
   Returns base^exponent
)";

constexpr const char * real_docstring =
R"(real(<complex number>)
    Return real component of the complex number
)";

constexpr const char * imag_docstring =
R"(imag(<complex number>)
    Return imaginary component of the complex number
)";

constexpr const char * abs_docstring =
R"(abs(<complex number>)
    Return magnitude
)";

constexpr const char * arg_docstring =
R"(arg(<complex number>)
    Return phase angle
)";

constexpr const char * norm_docstring =
R"(norm(<complex number>)
    Return squared magnitude (field norm)
)";

constexpr const char * conj_docstring =
R"(conj(<complex number>)
    Return Complex conjugate
)";

constexpr const char * cos_docstring =
R"(cos(<complex number>)
    Return Complex cosine
)";

constexpr const char * cosh_docstring =
R"(cosh(<complex number>)
    Return Complex hyperbolic cosine
)";

constexpr const char * exp_docstring =
R"(exp(<complex number>)
    Return Complex base e exponential
)";

constexpr const char * log_docstring =
R"(log(<complex number>)
    Return Complex natural logarithm
)";

constexpr const char * log10_docstring =
R"(exp(<complex number>)
    Return Complex base 10 logarithm
)";

constexpr const char * sin_docstring =
R"(sin(<complex number>)
    Return Complex sine
)";

constexpr const char * sinh_docstring =
R"(sinh(<complex number>)
    Return Complex hyperbolic sine
)";

constexpr const char * sqrt_docstring =
R"(sqrt(<complex number>)
    Return Complex square root
)";

constexpr const char * tan_docstring =
R"(tan(<complex number>)
    Return Complex tangent
)";

constexpr const char * tanh_docstring =
R"(tanh(<complex number>)
    Return Complex hyperbolic tangent
)";

constexpr const char * euler_print_docstring =
R"(euler_print(<complex number>)
    print complex number in euler form
    can not be used inside expressions
)";

constexpr const char * print_docstring =
R"(print(<complex number>)/cartesian_print(<complex number>)
    print complex number in cartesian form
    can not be used inside expressions
)";

constexpr const char * quit_docstring =
R"(quit()/exit()
    leave the application
    can not be used inside expressions
)";

constexpr const char * help_docstring =
R"(help()/help(<function name>)
    output help text for object or complete help
    can not be used inside expressions
)";

constexpr const char * calculations_docstring =
R"(Calculations
    Calculations can use the operators *, /, +, - and brackets to calculate complex numbers
    For the complex numbers the cartesian form (<a>+<b>i), the euler form (<r>*e^i<phi>),
    or a variable holding a complex number can be used. It is possible to use j instead of i for complex numbers

    Example:
        >>> 1+1j
        (1+1j)
        >>> (1+1i) + (1 - 1i)
        (2+0j)
        >>> a = 1 + 1j
        >>> (a - 1i) * 4 * (1 - 1i)
        (4-4j)
)";

constexpr const char * assignments_docstring =
R"(Assignments:
    It is possible to assign the results of calculations to variables
    Operators (e.g. *) can not be used in variable names
    It is possible to save a complex number into two variables in the form (a,b)
    where the real part is stored in a and the imaginary part in b
    Example:
        >>> example_var1 = real, complex = 1+1j
        >>> example_var1
        (1+1j)
        >>> real
        (1+0j)
        >>> complex
        1j
)";

constexpr const char * credits_docstring =
R"(credits()
    output credits
    can not be used inside expressions
)";