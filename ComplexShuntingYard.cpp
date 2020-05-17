#include "ComplexShuntingYard.hpp"
#include <stack>
#include <regex>
#include <exception>
 
int operator_precedence(char op){ 
    if(op == '+'||op == '-') return 1; 
    if(op == '*'||op == '/') return 2; 
    return 0; 
} 

Complex<double> operation(Complex<double> a, Complex<double> b, char op){ 
    switch(op){ 
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': return a / b; 
    } 
  return 0;
}

bool is_Complex(char ch) {
	return ch == 'i' || ch == 'j';
}

std::string resolve_plus_minus(std::string tokens) {
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

	return tokens;
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
		std::string replacement = "(" + complex_replacement.str() + ")";
		tokens.replace(start_pos, match.length(), replacement);
	}
}

void ComplexShuntingYard::replace_variables(const std::unordered_map<std::string, Complex<double>>& variable_mapping) {
    std::regex variable_regex(R"([^\d\(\)\.\+\*\/\x2d]{2,}|[^\dij\(\)\.\+\*\/\x2d])");
    auto variable_begin = std::sregex_iterator(tokens.begin(), tokens.end(), variable_regex);
    auto variable_end = std::sregex_iterator();
    std::vector<std::string> matches;
 
    for (std::sregex_iterator i = variable_begin; i != variable_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
	    matches.push_back(match_str);
    }

	for (const auto& match : matches) {
	    if (variable_mapping.count(match) == 0) {
			throw std::invalid_argument("NameError: name '" + match + "' is not defined");
		}

		size_t start_pos = tokens.find(match);
		auto complex_replacement = variable_mapping.at(match);
		std::string replacement = "(" + complex_replacement.str() + ")";
		tokens.replace(start_pos, match.length(), replacement);
	}
}


Complex<double> ComplexShuntingYard::evaluate(){
	tokens.erase(
		std::remove_if(tokens.begin(), tokens.end(), [](char x){ return std::isspace(x); }),
		tokens.end());
	
	tokens = resolve_plus_minus(tokens);

    // store numbers and operators in stack
	std::stack<Complex<double>> numbers;  
    std::stack<char> ops;

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
		// find sign of number
        signed int sign = 1;
		if (token_it != tokens.begin()) {
			char prev_token = *(token_it-1);
			if ((ops.empty() || ops.top() != '-') && prev_token == '-') {
				sign = -1;
			}
		}

		std::size_t sz;
		double val = std::stod(tokens.substr(std::distance(tokens.begin(), token_it)),&sz);
		token_it +=sz-1;

        // apply correct sign
		val *= sign;

		if (token_it+1 != tokens.end() && is_Complex(*(token_it+1))) {
			// skip i/j
			++token_it;
			return Complex<double>(0, val); 
		} else {
            return Complex<double>(val); 
		}
	};

    for (auto token_it = tokens.begin(); token_it != tokens.end(); ++token_it) {
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
				if (token_it == tokens.begin()) continue;
				auto last_elem = *(token_it-1);
			    if (last_elem == '*' || last_elem == '/' || last_elem == '(') {
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