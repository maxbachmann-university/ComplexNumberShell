# Complex Number Shell


## Compile

Build ComplexNumberShell
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=RELEASE
cmake --build . --config Release
./ComplexNumberShell
```

Build Documentation (can be found online on [github pages](http://maxbachmann-university.github.io/ComplexNumberShell/))
```bash
doxygen Doxyfile
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
> (a - 1i) * 4 * ((1 - 1i) + 2 * e^8j)
(2.836000-11.914864j)
```

### Assignments

It is possible to assign the results of calculations to variables.
Operators (e.g. *) can not be used in variable names
Example:
```console
> a = b = 1+1j
> a
(1+1j)
> b
(1+1j)
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
