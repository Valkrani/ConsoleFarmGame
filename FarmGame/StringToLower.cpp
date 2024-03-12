#include "StringToLower.h"

void StringToLower(std::string& outString)
{
    for (int i = 0; i < outString.size(); i++)
    {
        outString[i] = tolower(outString[i]);
    }
}