// -*- C++ -*-

#include  "Simplex.hpp"

void Simplex::make_degenerate_sample(container_type& con, int n)
{
    for(auto& v: con)
    {
        v = 0.0f;
    }
    con[n] = 1.0f;
}
    
void Simplex::scale_and_shift(container_type& con, float sum) const
{
    float norm  = ( 1.0f / sum ) * _d;
    for(auto& v: con)
    {
        v = _a + v * norm; // norm already have interval inclduded
    }
}

