#include "CgUnterteilungsEvent.h"

CgUnterteilungsEvent::CgUnterteilungsEvent():
m_type(Cg::CgUnterteilungsEvent),
m_mittel(1),
m_mode(1)
{

}

CgUnterteilungsEvent::CgUnterteilungsEvent(Cg::EventType type,unsigned int mittel, unsigned int mode):
m_type(type),
m_mittel(mittel),
m_mode(mode)
{

}

CgBaseEvent* CgUnterteilungsEvent::clone()
{
    return new CgUnterteilungsEvent(m_type,m_mittel,m_mode);
}

Cg::EventType  CgUnterteilungsEvent::getType()
{
    return m_type;
}

unsigned int CgUnterteilungsEvent::mittel()
{
    return m_mittel;
}

unsigned int CgUnterteilungsEvent::mode()
{
    return m_mode;
}

std::ostream& operator<<(std::ostream& os,const CgUnterteilungsEvent& e)
{
    os << "CgUnterteilungsEvent of Type: "<< e.m_type <<", mittel:" << e.m_mittel << ", mode:" << e.m_mode << std::endl;
    return os;
}
