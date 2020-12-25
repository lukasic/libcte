#pragma once

// obsahuje STL
#include "stdafx.h"

std::string &ltrim(std::string &s);
// trim from end
std::string &rtrim(std::string &s);
// trim from both ends
std::string &trim(std::string &s);

const std::string margin(int width = 1);

/**
 * Nahradenie substringu za iný string. Používať s std::string (C++ STL).
 *
 * Usage:
 *  std::string x = "date: $date";
 *  replace(x, "$date", "25.11.2015");
 *  // x -> "date: 25.11.2015"
 *
 */
bool replace(std::string& str, const std::string& from, const std::string& to);
