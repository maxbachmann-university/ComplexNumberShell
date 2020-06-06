# Complex Number Shell


## Compile

```bash
g++ main.cpp src/ComplexShuntingYard.cpp src/CLI.cpp src/widthstream.cpp src/CliFuncs/HelpFunc.cpp src/CliParser.cpp src/Utils.cpp src/CliFunc.cpp src/XmlCommandLogger.cpp extern/tinyxml2/tinyxml2.cpp -o ComplexNumberShell -std=c++17 -I include -I extern
./ComplexNumberShell
```

## Usage
### Calculations
Calculations can use the operators *, /, +, - and brackets to calculate complex numbers.
For the complex numbers the cartesian form (&lt;a&gt;+&lt;b&gt;i), the euler form (&lt;r&gt;*e^i&lt;phi&gt;),
or a variable holding a complex number can be used. It is possible to use j instead of i for complex numbers

Example:
```console
> 1+1j
(1+1j)
> (1+1i) + (1 - 1i)
(2+0j)
> a = 1 + 1j
> (a - 1i) * 4 * (1 - 1i)
(4-4j)
```

### Assignments

It is possible to assign the results of calculations to variables.
Operators (e.g. *) can not be used in variable names
It is possible to save a complex number into two variables in the form (a,b)
where the real part is stored in a and the imaginary part in b

Example:
```console
> example_var1 = real, complex = 1+1j
> example_var1
(1+1j)
> real
(1+0j)
> complex
1j
```

### Commands
These commands can be used inside expressions

Example:
```console
> real(2 + 1i) * abs(1+1i)
(2.828428+0.000000j)
```

#### real(&lt;complex number&gt;)
Return real component of the complex number
#### imag(&lt;complex number&gt;)
Return imaginary component of the complex number
#### abs(&lt;complex number&gt;)
Return magnitude
#### arg(&lt;complex number&gt;)
Return phase angle
#### norm(&lt;complex number&gt;)
Return squared magnitude (field norm)
#### conj(&lt;complex number&gt;)
Return Complex conjugate
#### cos(&lt;complex number&gt;)
Return Complex cosine
#### cosh(&lt;complex number&gt;)
Return Complex hyperbolic cosine
#### exp(&lt;complex number&gt;)
Return Complex base e exponential
#### log(&lt;complex number&gt;)
Return Complex natural logarithm
#### log10(&lt;complex number&gt;)
Return Complex base 10 logarithm
#### sin(&lt;complex number&gt;)
Return Complex sine
#### sinh(&lt;complex number&gt;)
Return Complex hyperbolic sine
#### sqrt(&lt;complex number&gt;)
Return Complex square root
#### tan(&lt;complex number&gt;)
Return Complex tangent
#### tanh(&lt;complex number&gt;)
Return Complex hyperbolic tangent

### Global Commands
These commands can not be used inside expressions
#### euler_print(&lt;complex number&gt;)
Print complex number in euler form

#### print(&lt;complex number&gt;)/cartesian_print(&lt;complex number&gt;)
Print complex number in cartesian form

#### quit()/exit()
Leave the application

#### help()
Output help text
