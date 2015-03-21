#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "std_LCG_PLE63.hpp"
#include "uniform_distribution.hpp"
#include "Simplex.hpp"

int main(int argc, char* argv[])
{
    std::linear_congruential_engine<uint64_t, 2806196910506780709ULL, 1ULL, (1ULL<<63ULL)> ugen;

    float a = 0.0f;
    float b = 1.0f;

    Simplex s(a, b);

    Simplex::container_type v(3, 0.0f);

    for(int k = 0; k != 300; ++k)
    {
        s.sample(v, ugen);

        std::cout << std::scientific << std::setw(15) << std::setprecision(4) << v[0]
                  << std::scientific << std::setw(15) << std::setprecision(4) << v[1]
                  << std::scientific << std::setw(15) << std::setprecision(4) << v[2]
                  << std::endl;
    }    

    return 0;
}
