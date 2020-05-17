#include "ComplexShuntingYard.hpp"
#include <stack>
#include <regex>
#include <exception>
#include <iostream>
 
int operator_precedence(char op){
    if(op == '+'||op == '-') return 1; 
    if(op == '*'||op == '/') return 2; 
    return 0;
} 

Complex<double> operation(Complex<double> a, Complex<double> b, char op){ 
	if (op == '+') return a + b;
	if (op == '-') return a - b; 
	if (op == '*') return a * b; 
	if (op == '/') return a / b;
	return 0;
}

Complex<double> call_func_by_name(Complex<double> a, std::string func_name){ 
	if (func_name == "abs") return abs(a);
	if (func_name == "arg") return arg(a);
	if (func_name == "norm") return norm(a);
	if (func_name == "conj") return conj(a);
	if (func_name == "cos") return cos(a);
	if (func_name == "cosh") return cosh(a);
	if (func_name == "sin") return sin(a);
	if (func_name == "sinh") return sinh(a);
	if (func_name == "tan") return tan(a);
	if (func_name == "tanh") return tanh(a);
	if (func_name == "exp") return exp(a);
	if (func_name == "log") return log(a);
	if (func_name == "log10") return log10(a);
	if (func_name == "sqrt") return sqrt(a);
	throw std::invalid_argument("NameError: name '" + func_name + "' is not defined");
}

bool is_complex(char ch) {
	return ch == 'i' || ch == 'j';
}

void ComplexShuntingYard::resolve_plus_minus() {
	auto token_it = tokens.begin();
	while(token_it != tokens.end()) {
		if ((*token_it == '+' || *token_it == '-')
		    && token_it+1 != tokens.end() && (*(token_it+1) == '+' || *(token_it+1) == '-'))
		{
			char op = *token_it;
			if (*(token_it+1) == '-') {
				op = (op == '-') ? '+' : '-';
		    }
			token_it = tokens.erase(token_it);
			*token_it = op;
		} else {
			++token_it;
		}
	}
}

void ComplexShuntingYard::replace_exponential() {
    std::regex exp_regex(R"(e\^[\+\-]{0,1}\d+\.{0,1}\d*[\*]{0,1}[ij]|e\^[ij][\*]{0,1}[\+\-]{0,1}\d+\.{0,1}\d*)");
    auto exp_begin = std::sregex_iterator(tokens.begin(), tokens.end(), exp_regex);
    auto exp_end = std::sregex_iterator();
    std::vector<std::string> matches;
 
    for (std::sregex_iterator i = exp_begin; i != exp_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
	    matches.push_back(match_str);
    }

	for (const auto& match : matches) {
        std::string phi_str = match.substr(2);
	    phi_str.erase(
		    std::remove_if(phi_str.begin(), phi_str.end(), [](char ch){ return ch == '*' || ch == 'i' || ch == 'j'; }),
		    phi_str.end());
			
		double phi = std::stod(phi_str);

		size_t start_pos = tokens.find(match);
		auto complex_replacement = Complex<double>::from_exponential({1, phi});
		tokens.replace(start_pos, match.length(), complex_replacement.str());
	}
}

void ComplexShuntingYard::subsitute_variables() {
	// execute twice to catch all variables e.g. a*a -> (<complex>)*a -> (<complex>)*(<complex>)
	for (int i = 0; i<2; ++i) {
        std::regex variable_regex(R"(([\(\*\/\+\-]|^)([^\d\(\)\+\*\/\-][^\(\)\+\*\/\-]*)([\)\*\/\+\-]|$))");
        auto variable_begin = std::sregex_iterator(tokens.begin(), tokens.end(), variable_regex);
        auto variable_end = std::sregex_iterator();
        std::vector<std::pair<std::string, std::size_t>> matches;
 
        for (std::sregex_iterator i = variable_begin; i != variable_end; ++i) {
            std::smatch match = *i;
	        matches.emplace_back(match[2].str(), match.position(2));
        }

        signed int pos_change = 0;
	    for (const auto& match : matches) {
	        if (variable_mapping.count(match.first) == 0) {
	    		throw std::invalid_argument("NameError: name '" + match.first + "' is not defined");
	    	}

		    auto complex_replacement = variable_mapping.at(match.first);
		    std::string replacement = complex_replacement.str();
		    tokens.replace(match.second+pos_change, match.first.length(), replacement);
		    pos_change += replacement.length() - match.first.length();
	    }
	}
}

Complex<double> ComplexShuntingYard::evaluate_impl(std::string str) {
	std::stack<Complex<double>> numbers;  
    std::stack<char> ops;
	signed int sign = 1;

	auto solve = [&]() {
		if (numbers.size() < 2) {
            throw std::invalid_argument("Calculation failed: missing number to perform operation with");
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
		double val = std::stod(str.substr(std::distance(str.begin(), token_it)),&sz);
		token_it +=sz-1;

        // apply correct sign
		val *= sign;

		Complex<double> num(0,0);

		if (token_it+1 != str.end() && is_complex(*(token_it+1))) {
			// skip i/j
			++token_it;
			num.imag(val);
		} else {
			num.real(val); 
		}
		if (token_it+1 != str.end()) {
			char next_elem = *(token_it+1);
			if (next_elem == '(') {
                throw std::invalid_argument("TypeError: 'number' is not callable");
			}
		}
		return num;
	};

    for (auto token_it = str.begin(); token_it != str.end(); ++token_it) {
        // add '(' to ops stack
        if(*token_it == '(') { 
            ops.push(*token_it); 
        } 

        // add number to number stack
        else if(isdigit(*token_it)) {
			numbers.push(extract_number(token_it));
        } 

        // solve brace when the brackets end 
        else if(*token_it == ')') 
        { 
            while(!ops.empty() && ops.top() != '(') { 
				solve();
            }

			/* If the stack runs out without finding a left parenthesis, then there are mismatched parentheses. */
            if (ops.empty()) {
                throw std::invalid_argument("Calculation failed: mismatched parentheses");
			}
            ops.pop(); 
        } 
 
        else
        {   
			// skip when the +/- should be directly added to the next number
			if (*token_it == '+' || *token_it == '-') {
				if (token_it == str.begin()) {
					sign = (*token_it == '-') ? -1 : 1;
					continue;
				}
				auto last_elem = *(token_it-1);
			    if (last_elem == '*' || last_elem == '/' || last_elem == '(') {
					sign = (*token_it == '-') ? -1 : 1;
					continue;
				}
			}

            while(!ops.empty() && operator_precedence(ops.top()) >= operator_precedence(*token_it)) { 
				solve();
            }
			
            ops.push(*token_it); 
        } 
    } 

    /* After while loop, if operator stack not null, pop everything to output queue */
    while(!ops.empty()) {
		/* If the operator token on the top of the stack is a parenthesis, then there are mismatched parentheses. */
		if (ops.top() == '(' || ops.top() == ')') {
			throw std::invalid_argument("Calculation failed: mismatched parentheses");
		}
		solve();
    }

    return numbers.top(); 

}

std::vector<std::pair<std::string, std::string>> find_method_calls(const std::string& str) {
	std::regex variable_regex(R"([^\s\d\(\)\+\*\/\-][^\s\(\)\+\*\/\-]*\([ij\.\d\+\*\-\+\(\)]*\))");
    auto variable_begin = std::sregex_iterator(str.begin(), str.end(), variable_regex);
    auto variable_end = std::sregex_iterator();
    std::vector<std::string> matches;

    for (std::sregex_iterator i = variable_begin; i != variable_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
	    matches.push_back(match_str);
    }
	std::vector<std::pair<std::string, std::string>> ops;
	for (auto match : matches) {
		auto found=match.find("(");
		std::string op = match.substr(0, found);
		std::size_t brackets = 1;
		std::size_t bracket_end = found+1;
		for (; bracket_end < match.length() && brackets != 0; ++bracket_end) {
			if (match[bracket_end] == ')') {
				brackets -= 1;
			} else if (match[bracket_end] == '(') {
				brackets += 1;
			}
		}
        if (brackets != 0) {
			throw std::invalid_argument("Calculation failed: mismatched parentheses");
		}

		match = match.substr(0, bracket_end);
		std::string calc = match.substr(found+1, bracket_end-found-2);
		ops.emplace_back(op, calc);
	}

	return ops;
}

Complex<double> ComplexShuntingYard::evaluate(){
	tokens.erase(
		std::remove_if(tokens.begin(), tokens.end(), [](char x){ return std::isspace(x); }),
		tokens.end());
	
	replace_exponential();
	resolve_plus_minus();
	subsitute_variables();

    std::vector<std::pair<std::string, std::string>> method_calls;
	do {
		method_calls = find_method_calls(tokens);
		for (const auto& method_call : method_calls) {
			auto op_result = call_func_by_name(evaluate_impl(method_call.second), method_call.first);
			std::string full_match = method_call.first + "(" + method_call.second + ")";

		    size_t start_pos = tokens.find(full_match);
		    tokens.replace(start_pos, full_match.length(), op_result.str());
	    }
	} while (!method_calls.empty());

    return evaluate_impl(tokens);
}