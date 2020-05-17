# Complex Number Shell


## Compile

```bash
g++ main.cpp ComplexShuntingYard.cpp CLI.cpp -o ComplexNumberShell
./ComplexNumberShell
```

## Usage
### Calculations
Calculations can use the operators *, /, +, - and brackets to calculate complex numbers
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

It is possible to assign the results of calculations to variables
Operators (e.g. *) and numbers can not be used in variable names
and it is not possible to use the literals i/j for variables, since they are used for complex numbers
It is possible to save a complex number into two variables in the form (a,b)
where the real part is stored in a and the imaginary part in b

Example:
```console
> example_var = real, complex = 1+1j
> example_var
(1+1j)
> real
(1+0j)
> complex
1j
```

### Commands
#### euler_print(&lt;complex number&gt;)
Print complex number in euler form

#### cartesian_print(&lt;complex number&gt;)
Print complex number in cartesian form

#### quit()/exit()
Leave the application

#### help()
Output help text
