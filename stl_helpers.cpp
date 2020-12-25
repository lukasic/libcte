#include "stdafx.h"
#include "stl_helpers.hpp"

std::string &ltrim(std::string &s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}


std::string &rtrim(std::string &s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}


std::string &trim(std::string &s)
{
    return ltrim(rtrim(s));
}


const std::string margin(int width)
{
    std::ostringstream oss;
    oss.clear();
    for (int i = 0; i < width; i++)
        oss << "  ";
    return oss.str();
}


bool replace(std::string& str, const std::string& from, const std::string& to)
{
    size_t start_pos = str.find(from);
    if(start_pos == std::string::npos)
        return false;

    str.replace(start_pos, from.length(), to);
    return true;
}


