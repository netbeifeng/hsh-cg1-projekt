#include "CgSpecialEvent.h"

CgSpecialEvent::CgSpecialEvent():
m_type(Cg::CgSpecialEvent),
m_signal(1)
{

}

CgSpecialEvent::CgSpecialEvent(Cg::EventType type, int singal):
m_type(type),
m_signal(singal)
{

}

CgBaseEvent* CgSpecialEvent::clone()
{
    return new CgSpecialEvent(m_type,m_signal);
}

Cg::EventType  CgSpecialEvent::getType()
{
    return m_type;
}

int CgSpecialEvent::signal()
{
    return m_signal;
}

std::ostream& operator<<(std::ostream& os,const CgSpecialEvent& e)
{
    os << "Sp-Event of Type: "<< e.m_type <<", signal:" << e.m_signal << std::endl;
    return os;
}
