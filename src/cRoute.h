#include "cxy.h"

class cRoute
{
    static std::vector< cRoute > theRoutes;
    std::vector<cxy> myPoints;
    cxy myBus;

    public:

    void read( const std::string& fname );

    void nextBus(
        int iRoute,
        const cxy& stop    );

    int nearest(
        int iRoute,
        const cxy& stop     );
};