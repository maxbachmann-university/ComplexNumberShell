#include "ComplexShuntingYard.hpp"
#include <exception>
#include <iostream>
#include <regex>
#include <stack>

int operator_precedence(const char op)
{
  if (op == '+' || op == '-') return 1;
  if (op == '*' || op == '/') return 2;
  return 0;
}

Complex<double> operation(const Complex<double> a, const Complex<double> b, const char op)
{
  if (op == '+') return a + b;
  if (op == '-') return a - b;
  if (op == '*') return a * b;
  if (op == '/') return a / b;
  return 0;
}

bool is_complex(char ch)
{
  return ch == 'i' || ch == 'j';
}

void resolve_plus_minus(std::string& tokens)
{
  auto token_it = tokens.begin();
  while (token_it != tokens.end()) {
    if ((*token_it == '+' || *token_it == '-') &&
        token_it + 1 != tokens.end() &&
        (*(token_it + 1) == '+' || *(token_it + 1) == '-'))
    {
      char op = *token_it;
      if (*(token_it + 1) == '-') {
        op = (op == '-') ? '+' : '-';
      }
      token_it = tokens.erase(token_it);
      *token_it = op;
    }
    else {
      ++token_it;
    }
  }
}

void replace_exponential(std::string& tokens)
{
  std::regex exp_regex(
      R"(e\^[\+\-]{0,1}\d+\.{0,1}\d*[\*]{0,1}[ij]|e\^[ij][\*]{0,1}[\+\-]{0,1}\d+\.{0,1}\d*)");
  const auto exp_begin =
      std::sregex_iterator(tokens.begin(), tokens.end(), exp_regex);

  std::vector<std::string> matches;
  for (auto i = exp_begin; i != std::sregex_iterator(); ++i) {
    std::smatch match = *i;
    std::string match_str = match.str();
    matches.push_back(match_str);
  }

  for (const auto& match : matches) {
    std::string phi_str = match.substr(2);
    phi_str.erase(std::remove_if(phi_str.begin(), phi_str.end(),
                                 [](char ch) {
                                   return ch == '*' || ch == 'i' || ch == 'j';
                                 }),
                  phi_str.end());

    const double phi = std::stod(phi_str);

    const size_t start_pos = tokens.find(match);
    const auto complex_replacement = Complex<double>::from_exponential({1, phi});
    tokens.replace(start_pos, match.length(), complex_replacement.str());
  }
}

Complex<double> ComplexShuntingYard::evaluate(std::string tokens)
{
  tokens.erase(std::remove_if(tokens.begin(), tokens.end(),
                              [](char x) { return std::isspace(x); }),
               tokens.end());

  replace_exponential(tokens);
  resolve_plus_minus(tokens);

  std::stack<Complex<double>> numbers;
  std::stack<char> ops;
  signed int sign = 1;

  auto solve = [&]() {
    if (numbers.size() < 2) {
      throw std::invalid_argument(
          "Calculation failed: missing number to perform operation with");
    }
    Complex<double> val2 = numbers.top();
    numbers.pop();

    Complex<double> val1 = numbers.top();
    numbers.pop();

    char op = ops.top();
    ops.pop();

    numbers.push(operation(val1, val2, op));
  };

  // extract double/int with the correct sign
  auto extract_number = [&](auto& token_it) {
    std::size_t sz;
    double val =
        std::stod(tokens.substr(std::distance(tokens.begin(), token_it)), &sz);
    token_it += sz - 1;

    // apply correct sign
    val *= sign;

    Complex<double> num(0, 0);

    if (token_it + 1 != tokens.end() && is_complex(*(token_it + 1))) {
      // skip i/j
      ++token_it;
      num.imag(val);
    }
    else {
      num.real(val);
    }
    if (token_it + 1 != tokens.end()) {
      if (*(token_it + 1) == '(') {
        throw std::invalid_argument("TypeError: 'number' is not callable");
      }
    }
    return num;
  };

  for (auto token_it = tokens.begin(); token_it != tokens.end(); ++token_it) {
    // add '(' to ops stack
    if (*token_it == '(') {
      ops.push(*token_it);
    }

    // add number to number stack
    else if (isdigit(*token_it)) {
      numbers.push(extract_number(token_it));
    }

    // solve brace when the brackets end
    else if (*token_it == ')') {
      while (!ops.empty() && ops.top() != '(') {
        solve();
      }

      /* If the stack runs out without finding a left parenthesis, then there
       * are mismatched parentheses. */
      if (ops.empty()) {
        throw std::invalid_argument(
            "Calculation failed: mismatched parentheses");
      }
      ops.pop();
    }

    else {
      // skip when the +/- should be directly added to the next number
      if (*token_it == '+' || *token_it == '-') {
        if (token_it == tokens.begin()) {
          sign = (*token_it == '-') ? -1 : 1;
          continue;
        }
        auto last_elem = *(token_it - 1);
        if (last_elem == '*' || last_elem == '/' || last_elem == '(') {
          sign = (*token_it == '-') ? -1 : 1;
          continue;
        }
      }

      while (!ops.empty() &&
             operator_precedence(ops.top()) >= operator_precedence(*token_it))
      {
        solve();
      }

      ops.push(*token_it);
    }
  }

  /* After while loop, if operator stack not null, pop everything to output
   * queue */
  while (!ops.empty()) {
    /* If the operator token on the top of the stack is a parenthesis, then
     * there are mismatched parentheses. */
    if (ops.top() == '(' || ops.top() == ')') {
      throw std::invalid_argument("Calculation failed: mismatched parentheses");
    }
    solve();
  }

  if (numbers.empty()) {
    throw std::invalid_argument("SyntaxError: Empty calculation");
  }

  return numbers.top();
}