#include "integrate.h"
#include "expr.h"

int main()
{
    std::shared_ptr<Variable> x = std::make_shared<Variable>();
    auto e = x*x*x + 2*x*x + x*3 + 55;
    std::cout << (*e)(5.0) << integrate(*e, 0, 10);
    return 0;
}
