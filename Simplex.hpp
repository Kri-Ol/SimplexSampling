// -*- C++ -*-

#pragma once

#include <cassert>
#include <cmath>
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

    public: Simplex(const Simplex& s):
        _a{s._a},
        _b{s._b},
        _d{s._d}
    {
    }

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
    private: void make_degenerate_sample(container_type& con, int n) const
    {
        for(size_t k = 0; k != con.size(); ++k)
        {
            con[k] = 0.0f;
        }
        con[n] = 1.0f;
    }
    
    private: void scale_and_shift(container_type& con, float sum) const
    {
        float norm  = 1.0f / sum;
        for(auto i = con.begin(); i != con.end(); ++i)
        {
            *i = _a + (*i) * norm * _d;
        }
    }

    public: template <typename RGEN> void sample(container_type& con, RGEN& rgen) const
    {
        assert(con.size() > 1);
        
        std::uniform_distribution<float> dist;
        
        float sum = 0.0f;
        for(size_t k = 0; k != con.size(); ++k)
        {
            float t = dist(rgen);
            if (t == 0.0f)
            {
                make_degenerate_sample(con, k);
                sum = 1.0f;
                goto scaling;
            }
            t = -log(t);
            con[k] = t;
            sum   += t;
        }
        
    scaling:
        scale_and_shift(con, sum);
    }
#pragma endregion
};

