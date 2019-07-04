#include "Interval.h"
#include <limits>
#include <algorithm>
#include <vector> 
#include <array>
#include <iostream>
#include <list>


Interval::Interval()
{   
    begin = 1;
    end = -1;
}

Interval::Interval(double begin_, double end_)
{
    begin = begin_;
    end = end_;
}


bool Interval::IsEmpty_or_singleton()
{
    return begin >= end;  
}

void Interval::operator&=(Interval const& interval_to_intesect)
{
    begin = std::max(begin, interval_to_intesect.begin);
    end = std::min(end, interval_to_intesect.end);
}

bool Interval::Compare_begin(Interval const& interval1, Interval const& interval2)
{
    return interval1.begin<interval2.begin;
}
 
bool Interval::Compare_end(Interval const& interval1, Interval const& interval2)
{
    return interval1.end<interval2.end;
}

double Interval::Get_begin()
{
    return begin;
}

double Interval::Get_end()
{
    return end;
}

void Interval::Set_begin(double begin_)
{
    begin = begin_;
}

void Interval::Set_end(double end_)
{
    end = end_;
}