#include "integrate.h"
#include "inheritanceExpressions.h"
#include "templatedExpressions.h"
#include <chrono>

int main()
{
    std::shared_ptr<Variable> x = std::make_shared<Variable>();
    
    auto e = x*x*x + 2*x*x + x*3 + 55;
 
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (int i = 0; i < 20; ++i)
    {
        integrate(*e, 0, 10);
    }

    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() <<std::endl;
    
    return 0;
}
