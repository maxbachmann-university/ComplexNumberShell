#include <string>
#include <stack>
#include <iostream>
#include <algorithm>
#include "complex.h"

// Finding operators 
int operator_precedence(char op){ 
    if(op == '+'||op == '-') return 1; 
    if(op == '*'||op == '/') return 2; 
    return 0; 
} 

// The maths
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

// Returning value of expression
Complex<double> evaluate(std::string tokens){
	tokens.erase(
		std::remove_if(tokens.begin(), tokens.end(), [](char x){ return std::isspace(x); }),
		tokens.end());
	
	tokens = resolve_plus_minus(tokens);

    // store numbers and operators in stack
	std::stack<Complex<double>> numbers;  
    std::stack<char> ops; 

    for (auto token_it = tokens.begin(); token_it != tokens.end(); ++token_it) {
        // if token '(' add to stack
        if(*token_it == '('){ 
            ops.push(*token_it); 
        } 

        // if token is a number, add to stack
        else if(isdigit(*token_it)){
            signed int sign = 1;
			if (token_it != tokens.begin()) {
				char prev_token = *(token_it-1);
				if ((ops.empty() || ops.top() != '-') && prev_token == '-') {
					sign = -1;
				}
			}

            signed int val = *token_it-'0'; 

            // single or double digit number.
            while(token_it+1 != tokens.end() && isdigit(*(token_it+1))) 
            { 
				val *= 10;
				val += *(token_it+1)-'0';
                ++token_it; 
            }

            // apply correct sign
			val *= sign;

			if (token_it+1 != tokens.end() && is_Complex(*(token_it+1))) {
				++token_it;
				numbers.push(Complex<double>(0, val)); 
			} else {
                numbers.push(Complex<double>(val)); 
			}
        } 

        // if token ')', solve entire brace. 
        else if(*token_it == ')') 
        { 
            while(!ops.empty() && ops.top() != '(') 
            { 
                Complex<double> val2 = numbers.top(); 
                numbers.pop(); 

                Complex<double> val1 = numbers.top(); 
                numbers.pop(); 

                char op = ops.top(); 
                ops.pop(); 

                numbers.push(operation(val1, val2, op)); 
            } 

            ops.pop(); 
        } 
 
        else
        {   
			if (*token_it == '+' || *token_it == '-') {
				if (token_it == tokens.begin()) continue;
				auto last_elem = *(token_it-1);
			    if (last_elem == '*' || last_elem == '/' || last_elem == '(') {
					continue;
				}
			}

            while(!ops.empty() && operator_precedence(ops.top()) 
                                >= operator_precedence(*token_it)){ 
                Complex<double> val2 = numbers.top(); 
                numbers.pop(); 

                Complex<double> val1 = numbers.top(); 
                numbers.pop(); 

                char op = ops.top(); 
                ops.pop(); 

                numbers.push(operation(val1, val2, op)); 
            }
			

            ops.push(*token_it); 
        } 
    } 

    while(!ops.empty()){ 
        Complex<double> val2 = numbers.top(); 
        numbers.pop(); 

        Complex<double> val1 = numbers.top(); 
        numbers.pop(); 

        char op = ops.top(); 
        ops.pop(); 

        numbers.push(operation(val1, val2, op)); 
    } 

    // Top of 'numbers' contains result, return
    return numbers.top(); 
} 

int main() {
	while (true) {
    std::cout << "insert your caluclation here and press enter: ";
	std::string Complex_str;
	std::getline(std::cin, Complex_str);

    auto res = evaluate(Complex_str);
	std::cout << "the result is: " << res << "\n"<< res.to_exponential() << "\n";
	//std::cout << resolve_plus_minus(Complex_str) << std::endl;
	}


    return 0; 
}  