#include<iostream>
#include<memory>
#include<cassert>

struct Square
{
    double operator()(double x) const
    {
        return x*x; 
    }
};

// template to calculate integral of a function.
template <typename Func>
double integrate(Func f, double low, double high, double epsilon = 0.0000001)
{
    assert(low <= high);
    double areaUnderCurveLB = 0, areaUnderCurveUpperBound = 0;
    double running_x = low;

    while(running_x < high)
    {
        areaUnderCurveLB += f(running_x) * epsilon;
        running_x += epsilon;
    }

    return areaUnderCurveLB; 
}

int main()
{
    auto f = Square();
    std::cout << integrate(f, 0, 4);
}
