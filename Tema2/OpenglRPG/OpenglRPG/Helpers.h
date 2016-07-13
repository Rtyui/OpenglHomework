#pragma once
#include <string>
#include <vector>
#include "Defines.h"

float		StringToFloat(const std::string &source);
uint		StringToUInt(const std::string &source);
int			StringToInt(const std::string &source);
void		StringTokenize(const std::string &source, std::vector<std::string> &tokens);
void		FaceTokenize(const std::string &source, std::vector<std::string> &tokens);