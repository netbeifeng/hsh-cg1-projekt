#include "CgRotateEvent.h"

CgRotateEvent::CgRotateEvent():
m_type(Cg::CgRotateEvent),
m_grad(1)
{

}

CgRotateEvent::CgRotateEvent(Cg::EventType type, unsigned grad):
m_type(type),
m_grad(grad)
{

}

CgBaseEvent* CgRotateEvent::clone()
{
    return new CgRotateEvent(m_type,m_grad);
}

Cg::EventType CgRotateEvent::getType()
{
    return m_type;
}

unsigned int CgRotateEvent::grad()
{
    return m_grad;
}

std::ostream& operator<<(std::ostream& os,const CgRotateEvent& e)
{
    os << "CgRotateEvent of Type: "<< e.m_type <<", grad:" << e.m_grad << std::endl;
    return os;
}
