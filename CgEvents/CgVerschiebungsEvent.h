#ifndef CGVERSCHIEBUNGSEVENT_H
#define CGVERSCHIEBUNGSEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"
#include <iostream>

class CgVerschiebungsEvent : public CgBaseEvent
{

public:

    CgVerschiebungsEvent();
    CgVerschiebungsEvent(Cg::EventType type,float dx,float dy,float dz);
    ~CgVerschiebungsEvent(){};

    //inherited
    Cg::EventType getType();
    CgBaseEvent* clone();

    float dx();
    float dy();
    float dz();

    friend std::ostream& operator <<(std::ostream& os, const CgVerschiebungsEvent& e);

private:
    Cg::EventType m_type;
    float m_dx;
    float m_dy;
    float m_dz;
};

#endif // CGVERSCHIEBUNGSEVENT_H
