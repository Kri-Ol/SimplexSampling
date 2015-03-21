// -*- C++ -*-

#pragma once

#include <cassert>
#include <cmath>
#include <cstddef>
#include <vector>

#include "uniform_distribution.hpp"

class Simplex
{
#pragma region typedefs
    public: using container_type = std::vector<float>;
#pragma endregion

#pragma region Data
    private: float _a;
    private: float _b;
    
    private: float _d; // delta
#pragma endregion

#pragma region Ctor/Dtor/ops
    public: Simplex(float a = 0.0f, float b = 1.0f):
        _a{a},
        _b{b},
        _d{_b - _a}
    {
        assert(a < b);
    }

    public: Simplex(const Simplex& s) = default;
    
    public: Simplex(Simplex&& s) = default;

    public: Simplex& operator=(const Simplex& s) = default;

    public: Simplex& operator=(Simplex&& s) = default;
    
    public: ~Simplex()
    {
    }
#pragma endregion

#pragma region Observers
    public: float a() const
    {
        return _a;
    }

    public: float b() const
    {
        return _b;
    }
#pragma endregion

#pragma region Sampling
    private: static void make_degenerate_sample(container_type& con, int n);
    
    private: void scale_and_shift(container_type& con, float sum) const;

    public: template <typename RGEN> void sample(container_type& con, RGEN& rgen) const;
#pragma endregion
};

template <typename RGEN> void Simplex::sample(container_type& con, RGEN& rgen) const
{
    assert(con.size() > 1);
        
    std::uniform_distribution<float> dist;
        
    float sum = 0.0f;
    for(size_t k = 0; k != con.size(); ++k)
    {
        float t = dist(rgen); // uniform float in [0...1) range
        if (t == 0.0f)
        {
            make_degenerate_sample(con, k);
            sum = 1.0f;
            break;
        }
        t = -log(t);
        con[k] = t;
        sum   += t;
    }
        
    scale_and_shift(con, sum);
}

