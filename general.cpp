#include "general.h"

using namespace std;

// Divide the input in words
void Split(const string& input, vector<string>& divided)
{
	const char* line = input.c_str();

	do
	{
		const char* start = line;
		
		while (*line != ' ' && *line) 
			line++;

		divided.push_back(string(start, line));
	} 
	while (*line++ != NULL);
}

// Get a random int between a min and a max
int Random(const int& min, const int& max)
{
	if (max <= 0)
		return 0;

	else if (max == min)
		return min;

	else
		return rand() % (max - min) + min;
}