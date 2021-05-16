#ifndef CGSPECIALEVENT_H
#define CGSPECIALEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"
#include <string>
#include <iostream>

class CgSpecialEvent : public CgBaseEvent
{

public:
    CgSpecialEvent();
    CgSpecialEvent(Cg::EventType type, int signal);
    ~CgSpecialEvent(){};

    //inherited
    Cg::EventType  getType();
    CgBaseEvent* clone();

    int signal();

    friend std::ostream& operator <<(std::ostream& os, const CgSpecialEvent& e);
private:
    Cg::EventType m_type;
    int m_signal;
};
#endif // CGSPEICALEVENT_H
