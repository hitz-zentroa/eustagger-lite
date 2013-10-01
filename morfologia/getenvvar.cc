#include <stdio.h>
#include <string>
#include <stdlib.h>

std::string getEnvVar(std::string const& key)
{
    char const* val = getenv(key.c_str()); 
    return val == NULL ? std::string() : std::string(val);
}

