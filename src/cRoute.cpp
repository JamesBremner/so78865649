#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cmath>

#include "cRoute.h"

std::vector<cRoute> cRoute::theRoutes;

std::vector<std::string>
ParseSpaceDelimited(
    const std::string &l)
{
    std::vector<std::string> token;
    std::stringstream sst(l);
    std::string a;
    while (getline(sst, a, ' '))
        token.push_back(a);

    // remove empty tokens
    token.erase(
        remove_if(
            token.begin(),
            token.end(),
            [](std::string t)
            {
                return (t.empty());
            }),
        token.end());

    return token;
}

void cRoute::read(const std::string &fname)
{
    theRoutes.clear();
    std::ifstream ifs(fname);
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open input file");
    std::string line;
    while (getline(ifs, line))
    {
        auto vtoken = ParseSpaceDelimited(line);
        int ri = atoi(vtoken[1].c_str());
        if (ri < theRoutes.size() - 1)
            theRoutes.resize(ri);
        switch (line[0])
        {
        case 'p':
            theRoutes[ri].myPoints.emplace_back(
                atof(vtoken[2].c_str()),
                atof(vtoken[3].c_str()));
            break;
        case 'b':
            theRoutes[ri].myBus = cxy(
                atof(vtoken[2].c_str()),
                atof(vtoken[3].c_str()));
            break;
        }
    }
}

void cRoute::nextBus(
    int iRoute,
    const cxy &stop)
{
    int ipBus = theRoutes[iRoute].nearest(iRoute,theRoutes[iRoute].myBus);
    int ipStop = theRoutes[iRoute].nearest(iRoute,stop);
    if (ipBus > ipStop)
        std::cout << "Bus has left\n";
    if (ipBus == ipStop)
        std::cout << "Bus at stop\n";
    double totaldistance = 0;
    for (int ip = ipBus;
         ip <= ipStop - 1;
         ip++)
    {
        totaldistance += sqrt(
            theRoutes[iRoute].myPoints[ip].dist2(theRoutes[iRoute].myPoints[ip + 1]));
    }
    std::cout << "Bus is " << totaldistance << " away\n";
}

int cRoute::nearest(
    int iRoute,
    const cxy &stop)
{
    double min = INT_MAX;
    int nearest;
    for( int ip = 0; ip < theRoutes[iRoute].myPoints.size(); ip++ ) {
        double d = stop.dist2( theRoutes[iRoute].myPoints[ip] );
        if( d < min ) {
            min = d;
            nearest = ip;
        }
    }
    return nearest;
}