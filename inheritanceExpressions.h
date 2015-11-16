#include<iostream>
#include <cmath>
#include <memory>
#include "counter.h"

class Expression : public Counter<Expression>
{
public:
    virtual double operator()(double x) const = 0;
    virtual std::shared_ptr<Expression> clone() const = 0;
    // Effective C++ recommends a virtual destructor if we want to be able to delete
    // derived class objects via a pointer to base class
    virtual ~Expression() {};
};

// The tutorial uses a refcounter to manage destruction, but we will use a 
// shared_ptr
struct Constant : public Expression, public Counter<Constant>
{
    Constant(const double d) : _d(d) 
    {
    }
    
    // copy constructor
    Constant(const Constant& obj)
    {
        _d = obj._d;
    }

    double operator()() const 
    {
        return _d;
    }
    // overload () operator to return the constant
    double operator()(double) const override
    {
        return _d;
    }

    std::shared_ptr<Expression> clone() const override
    {
        return std::make_shared<Constant>(Constant(*this));
    }
    
    ~Constant()
    {
    }

    double _d;
};

struct Variable : public Expression, public Counter<Variable>
{
    Variable()
    {
    }
    
    Variable(const Variable& obj) 
    {
    }

    std::shared_ptr<Expression> clone() const override
    {   
        return std::make_shared<Variable>(Variable(*this));    
    }

    double operator()(double x) const override
    {
        return x;
    }
    
    ~Variable() {}
};

// Operators
struct Add
{
    static double apply(double l, double r)
    {
        return l + r;
    }
};

struct Mult
{
    static double apply(double l, double r)
    {   
        return l * r;
    }
};

template <typename Op>
struct ComplexExpression : public Expression, public Counter<ComplexExpression<Op>>
{
    ComplexExpression(
        std::shared_ptr<Expression> left, 
        std::shared_ptr<Expression> right)
        : _left(left),
        _right(right)
    {   
    }

    // copy constructor
    ComplexExpression(const ComplexExpression& obj)
    {
        _left = obj._left;
        _right = obj._right;
    }

    std::shared_ptr<Expression> clone() const override
    {
        return std::make_shared<ComplexExpression<Op>>(ComplexExpression<Op>(*this));
    }

    // This forwards the application to the constituent left and right expressions,
    // which will get applied recursively
    double operator()(double d) const override
    {
        return Op::apply((*_left)(d), (*_right)(d));
    }

    std::shared_ptr<Expression> _left;
    std::shared_ptr<Expression> _right;
};

std::shared_ptr<Expression> operator * (
        double left,
        const std::shared_ptr<Expression>& right)
{
    return std::make_shared<ComplexExpression<Mult>>(
            ComplexExpression<Mult>(
                std::make_shared<Constant>(left), 
                right)
            );
}

std::shared_ptr<Expression> operator * (
        const std::shared_ptr<Expression>& left,
        double right)
{
    return std::make_shared<ComplexExpression<Mult>>(
            ComplexExpression<Mult>(
                left, 
                std::make_shared<Constant>(right))
            );
}

// operator overloads on Expressions
std::shared_ptr<Expression> operator * (
        const std::shared_ptr<Expression>& left, 
        const std::shared_ptr<Expression>& right)
{
    return std::make_shared<ComplexExpression<Mult>>(
            ComplexExpression<Mult>(
                left, 
                right)
            );
}

std::shared_ptr<Expression> operator + (
        double left,
        const std::shared_ptr<Expression>& right)
{
    return std::make_shared<ComplexExpression<Add>>(
            ComplexExpression<Add>(
                std::make_shared<Constant>(left), 
                right)
            );
}

std::shared_ptr<Expression> operator + (
        const std::shared_ptr<Expression>& left,
        double right)
{
    return std::make_shared<ComplexExpression<Add>>(
            ComplexExpression<Add>(
                left, 
                std::make_shared<Constant>(right))
            );
}

// operator overloads on Expressions
std::shared_ptr<Expression> operator + (
        const std::shared_ptr<Expression>& left, 
        const std::shared_ptr<Expression>& right)
{
    return std::make_shared<ComplexExpression<Add>>(
            ComplexExpression<Add>(
                left, right)
            );
}
