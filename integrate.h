#include<iostream>
#include<memory>
#include<cassert>

// template to calculate integral of a function.
template <typename Func>
double integrate(Func& f, double low, double high, double epsilon = 0.00001)
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
