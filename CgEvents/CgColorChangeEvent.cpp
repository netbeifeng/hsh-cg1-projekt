#include "CgColorChangeEvent.h"

CgColorChangeEvent::CgColorChangeEvent():
m_type(Cg::CgColorChangeEvent),
m_r(0),
m_g(0),
m_b(0)
{

}

CgColorChangeEvent::CgColorChangeEvent(Cg::EventType type,int r, int g, int b):
m_type(type),
m_r(r),
m_g(g),
m_b(b)
{
//std::cout << g << std::endl;
}

CgBaseEvent* CgColorChangeEvent::clone()
{
    return new CgColorChangeEvent(m_type,m_r,m_g,m_b);
}

Cg::EventType  CgColorChangeEvent::getType()
{
    return m_type;
}

unsigned int CgColorChangeEvent::r()
{
    return m_r;
}

unsigned int CgColorChangeEvent::g()
{
    return m_g;
}

unsigned int CgColorChangeEvent::b()
{
    return m_b;
}

std::ostream& operator<<(std::ostream& os,const CgColorChangeEvent& e)
{
    os << "ColorChange-Event of Type: "<< e.m_type <<", r:" << e.m_r << ",g:" << e.m_g << ",b:" << e.m_b << std::endl;
    return os;
}
