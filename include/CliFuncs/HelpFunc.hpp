#pragma once
#include "CliFunc.hpp"
#include "ComplexShuntingYard.hpp"
#include "widthstream.hpp"
#include <memory>
#include <string>
#include <vector>

/**
 * @brief Output of docstring for every CLIfuncs function.
 */
class HelpFunc : public CliFunc {
public:
  HelpFunc(std::vector<std::shared_ptr<CliFunc>> calc_commands,
           std::vector<std::shared_ptr<CliFunc>> global_commands)
      : CliFunc("help", 0, 1),
        calc_commands(calc_commands),
        global_commands(global_commands)
  {}

  /**
   * Output of docstrings for every function.
   */
  call_result call(arg_list args, const var_mapping&) const override;

  std::string docstring() const override;

private:
  std::vector<std::shared_ptr<CliFunc>> calc_commands;
  std::vector<std::shared_ptr<CliFunc>> global_commands;

  static constexpr const char* calculations_docstring =
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

  static constexpr const char* assignments_docstring =
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
};
