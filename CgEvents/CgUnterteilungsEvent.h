#ifndef CGUNTERTEILUNGSEVENT_H
#define CGUNTERTEILUNGSEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"
#include <iostream>

class CgUnterteilungsEvent : public CgBaseEvent
{

public:

    CgUnterteilungsEvent();
    CgUnterteilungsEvent(Cg::EventType type,unsigned int mittel,unsigned int mode);
    ~CgUnterteilungsEvent(){};

    //inherited
    Cg::EventType getType();
    CgBaseEvent* clone();

    unsigned int mittel();
    unsigned int mode();

    friend std::ostream& operator <<(std::ostream& os, const CgUnterteilungsEvent& e);

private:
    Cg::EventType m_type;
    unsigned int m_mittel;
    unsigned int m_mode;
};

#endif // CGUNTERTEILUNGSEVENT_H
