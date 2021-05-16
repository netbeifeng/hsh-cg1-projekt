#ifndef CGCOLORCHANGEEVENT_H
#define CGCOLORCHANGEEVENT_H

#include "../CgBase/CgBaseEvent.h"
#include "../CgBase/CgEnums.h"
#include <string>
#include <iostream>

class CgColorChangeEvent : public CgBaseEvent
{

public:

    CgColorChangeEvent();
    CgColorChangeEvent(Cg::EventType type, int r, int g, int b);
    ~CgColorChangeEvent(){};

    //inherited
    Cg::EventType  getType();
    CgBaseEvent* clone();

    unsigned int r();
    unsigned int g();
    unsigned int b();

    friend std::ostream& operator <<(std::ostream& os, const CgColorChangeEvent& e);

private:
    Cg::EventType m_type;
    unsigned int m_r;
    unsigned int m_g;
    unsigned int m_b;
};

#endif // CGCOLORCHANGEEVENT_H
