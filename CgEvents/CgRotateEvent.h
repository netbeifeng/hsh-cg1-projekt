#ifndef CGROTATEEVENT_H
#define CGROTATEEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"
#include <iostream>

class CgRotateEvent : public CgBaseEvent
{

public:

    CgRotateEvent();
    CgRotateEvent(Cg::EventType type, unsigned int grad);
    ~CgRotateEvent(){};

    //inherited
    Cg::EventType getType();
    CgBaseEvent* clone();

    unsigned int grad();

    friend std::ostream& operator <<(std::ostream& os, const CgRotateEvent& e);

private:
    Cg::EventType m_type;
    unsigned int m_grad;
};

#endif // CGROTATEEVENT
