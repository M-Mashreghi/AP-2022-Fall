#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Consts.hpp"


typedef std::vector<std::string> line;

line read_command();

line split_string(std::string str, std::string format);

std::string IsInteger(std::string input);
