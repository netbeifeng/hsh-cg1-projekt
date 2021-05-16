#include "CgVerschiebungsEvent.h"

CgVerschiebungsEvent::CgVerschiebungsEvent():
m_type(Cg::CgVerschiebungsEvent),
m_dx(0),
m_dy(0),
m_dz(0)
{

}

CgVerschiebungsEvent::CgVerschiebungsEvent(Cg::EventType type,float dx,float dy,float dz):
m_type(type),
m_dx(dx),
m_dy(dy),
m_dz(dz)
{
//std::cout << g << std::endl;
}

CgBaseEvent* CgVerschiebungsEvent::clone()
{
    return new CgVerschiebungsEvent(m_type,m_dx,m_dy,m_dz);
}

Cg::EventType  CgVerschiebungsEvent::getType()
{
    return m_type;
}

float CgVerschiebungsEvent::dx()
{
    return m_dx;
}

float CgVerschiebungsEvent::dy()
{
    return m_dy;
}

float CgVerschiebungsEvent::dz()
{
    return m_dz;
}

std::ostream& operator<<(std::ostream& os,const CgVerschiebungsEvent& e)
{
    os << "Verschiebung-Event of Type: "<< e.m_type <<", dx:" << e.m_dx << ",dy:" << e.m_dy << ",dz:" << e.m_dz << std::endl;
    return os;
}
