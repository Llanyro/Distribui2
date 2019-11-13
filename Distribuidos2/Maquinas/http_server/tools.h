#ifndef TOOLS_H
#define TOOLS_H
#include <iostream>

class Tools
{
    public:
        Tools();
        std::string execute(std::string cmd) const;
        std::string generarHash(std::string pass) const;
        std::string deleteSobrante(std::string str) const;
};

#endif // TOOLS_H
