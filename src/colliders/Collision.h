#include "../common/Contact.h"

namespace phys2d{
    void dispatchContact(Contact& contact);

    void CircleCircle(Contact& contact);
    void CirclePoly(Contact& contact);
    void PolyPoly(Contact& contact);
}