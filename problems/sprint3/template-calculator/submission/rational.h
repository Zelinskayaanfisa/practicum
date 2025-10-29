#pragma once
#include <iostream>
#include <cmath>
#include <numeric>
#include <cstdlib>
#include <cstdint>
#include <compare>
class Rational {
public:
    //Конструкторы класса Rational:
    Rational() = default;

    Rational(int numerator) : numerator_(numerator) {};

    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        if (denominator_==0){
            std::abort();
        }
        Reduction();
    };

    Rational(const Rational& r) : numerator_(r.numerator_), denominator_(r.denominator_) {};

    //Функции для получения числителя, наменателя, перевернутой дроби:
    int GetNumerator() const {
        return numerator_;
    };
    int GetDenominator() const {
        return denominator_;
    };

    Rational Inv() const {
        return Rational{denominator_, numerator_};
    };

    //Функции сложения, вычитания, умножения, деления:
    Rational& operator=(const Rational& other) {
        if (this != &other) {
            numerator_ = other.numerator_;
            denominator_ = other.denominator_;
        }
        return *this;
    }

    Rational operator+(const Rational& r2 ) const {
        Rational other{*this};
        other.numerator_=(other.numerator_*r2.denominator_)+(other.denominator_*r2.numerator_);
        other.denominator_*=r2.denominator_;
        other.Reduction();
        return other;
    };

    Rational operator-(const Rational& r2 ) const {
        Rational other{*this};
        other.numerator_=(other.numerator_*r2.denominator_)-(other.denominator_*r2.numerator_);
        other.denominator_*=r2.denominator_;
        other.Reduction();
        return other;
    };

    Rational operator*(const Rational& r2 ) const {
        Rational other{*this};
        other.numerator_*=r2.numerator_;
        other.denominator_*=r2.denominator_;
        other.Reduction();
        return other;
    };

    Rational operator/(const Rational& r2 ) const {
        Rational other{*this};
        other.numerator_*=r2.denominator_;
        other.denominator_*=r2.numerator_;
        other.Reduction();
        return other;
    };


    //Функции присваивающих арифметических операций:
    Rational& operator+=(const Rational& r2){
        numerator_=(numerator_*r2.denominator_)+(denominator_*r2.numerator_);
        denominator_*=r2.denominator_;
        Reduction();
        return *this;
    };

    Rational& operator-=(const Rational& r2){
        numerator_=(numerator_*r2.denominator_)-(denominator_*r2.numerator_);
        denominator_*=r2.denominator_;
        Reduction();
        return *this;
    };

    Rational& operator*=(const Rational& r2){
        numerator_*=r2.numerator_;
        denominator_*=r2.denominator_;
        Reduction();
        return *this;
    };

    Rational& operator/=(const Rational& r2){
        numerator_*=r2.denominator_;
        denominator_*=r2.numerator_;
        Reduction();
        return *this;
    };

    //Унарный плюс и минус:
    Rational operator+()const{
        return *this;
    };
    Rational operator-() const {
        return Rational{-numerator_, denominator_};
    }

    friend std::istream& operator>>(std::istream& is, Rational& r);
    friend std::ostream& operator<<(std::ostream& os, const Rational& r);


    bool operator==(const Rational& other) const {
        return static_cast<std::int64_t>(GetNumerator())*other.GetDenominator() == static_cast<std::int64_t>(GetDenominator())*other.GetNumerator();
    };

    std::strong_ordering operator<=>(const Rational& other) const {
        return static_cast<std::int64_t>(GetNumerator())*other.GetDenominator() <=> static_cast<std::int64_t>(GetDenominator())*other.GetNumerator();
    };
private:
    void Reduction(){
        if(denominator_<0){
            numerator_=-numerator_;
            denominator_=-denominator_;
        }

        const int divisor = std::gcd(numerator_, denominator_);
        numerator_/=divisor;
        denominator_/=divisor;
    };

    int numerator_=0;
    int denominator_=1;
};

//Функции ввода и вывода:
inline std::istream& operator>>(std::istream& is, Rational& r){
    int n,d;
    char div;
    if (!(is>>n)) {
        return is;
    }
    else if(!(is>>std::ws>>div)){
        r=Rational(n,1);
        is.clear();
        return is;
    }
    else if(div!='/'){
        r=Rational(n,1);
        is.unget();
        return is;
    }
    else if(!(is>>d) || (d==0)){
        is.setstate(std::ios::failbit);
        return is;
    }
    r=Rational(n,d);
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Rational& r){
    if(r.GetDenominator()==1){
        return os<<r.GetNumerator();
    }
    return os<<r.GetNumerator()<<" / "<<r.GetDenominator();
}

