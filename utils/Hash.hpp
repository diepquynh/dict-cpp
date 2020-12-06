#include <string>

#ifndef __HASH_HDR__
#define __HASH_HDR__

unsigned int DJBHash(std::string str)
{
    unsigned int hash = 5381;

    for (std::size_t i = 0; i < str.length(); i++)
    {
        hash = ((hash << 5) + hash) + str[i];
    }
    return hash;
}

#endif /* __HASH_HDR__ */