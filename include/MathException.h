#ifndef MATH_EXCEPTION_H
#define MATH_EXCEPTION_H

#include <exception>
#include <string>

class MathException : public std::exception {
    std::string mesaj;
public:
    explicit MathException(std::string m) : mesaj(std::move(m)) {}
    [[nodiscard]] const char* what() const noexcept override { return mesaj.c_str(); }
};

class DivisionByZeroException : public MathException {
public:
    DivisionByZeroException()
        : MathException("Eroare: împărțire la zero detectată în timpul evaluării.") {}
    explicit DivisionByZeroException(const std::string& detalii)
        : MathException("Eroare: împărțire la zero (" + detalii + ").") {}
};

class ParseException : public MathException {
public:
    explicit ParseException(const std::string& detalii)
        : MathException("Eroare de parsare: " + detalii) {}
};

#endif