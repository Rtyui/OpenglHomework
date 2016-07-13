#include "Helpers.h"
#include <sstream>

float StringToFloat(const std::string &source)
{
	std::stringstream ss(source.c_str());
	float result;
	ss >> result;
	return result;
}

uint StringToUInt(const std::string &source)
{
	std::stringstream ss(source.c_str());
	uint result;
	ss >> result;
	return result;
}

int StringToInt(const std::string &source)
{
	std::stringstream ss(source.c_str());
	int result;
	ss >> result;
	return result;
}

void StringTokenize(const std::string &source, std::vector<std::string> &tokens)
{
	tokens.clear();
	std::string aux = source;
	for (unsigned int i = 0; i<aux.size(); i++) if (aux[i] == '\t' || aux[i] == '\n') aux[i] = ' ';
	std::stringstream ss(aux, std::ios::in);
	while (ss.good()){
		std::string s;
		ss >> s;
		if (s.size()>0) tokens.push_back(s);
	}
}

void FaceTokenize(const std::string &source, std::vector<std::string> &tokens)
{
	std::string aux = source;
	for (unsigned int i = 0; i<aux.size(); i++) if (aux[i] == '\\' || aux[i] == '/') aux[i] = ' ';
	StringTokenize(aux, tokens);
}