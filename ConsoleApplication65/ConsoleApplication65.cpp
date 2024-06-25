#include <iostream>
#include <string>
#include "exprtk.hpp"

double derivative(exprtk::expression<double>& expr, double& x, exprtk::symbol_table<double>& symbol_table) {
    double h = 1e-7;
    x = x + h;
    double fxh1 = expr.value();
    x = x - 2 * h;
    double fxh2 = expr.value();
    x = x + h;  
    return (fxh1 - fxh2) / (2 * h);
}

int main() {
    std::string expression;
    double x0;

    std::cout << "Nhap bieu thuc ham so: ";
    std::getline(std::cin, expression);

    exprtk::symbol_table<double> symbol_table;
    double x;
    symbol_table.add_variable("x", x);

    exprtk::expression<double> expr;
    expr.register_symbol_table(symbol_table);

    exprtk::parser<double> parser;
    if (!parser.compile(expression, expr)) {
        std::cerr << "Error: " << parser.error() << std::endl;
        return 1;
    }

    std::cout << "Nh?p ti?p ?i?m x0: ";
    std::cin >> x0;
    x = x0; 

    double y0 = expr.value();
    double f_prime = derivative(expr, x, symbol_table);

    std::cout << "Phuong trinh tiep tuyen tai diem (" << x0 << ", " << y0 << "): y = "
        << f_prime << " * (x - " << x0 << ") + " << y0 << std::endl;

    std::cout << "Phuong trinh phap tuyen tai diem (" << x0 << ", " << y0 << "): y = "
        << -1 / f_prime << " * (x - " << x0 << ") + " << y0 << std::endl;

    return 0;
}
