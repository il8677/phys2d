#include "../common/Contact.h"

namespace phys2d{
    void dispatchContact(Contact& contact);

    void circleCircle(Contact& contact);
    void circlePoly(Contact& contact);
    void polyPoly(Contact& contact);
    void PolygontoPolygon(Contact& c);
}