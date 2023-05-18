#include "Group.h"

Group::Group(int id) : m_id(id), m_vip(false), m_numVipUsers(0) 
{
    for (int i = 0; i < NUMOFGENRES; i++)
    {
        m_genreViewCount[i] = 0;
    }
    
}

int Group::getId() const {
    return m_id;
}

void Group::setId(int id) {
    m_id = id;
}

bool Group::isVip() const {
    return m_vip;
}

void Group::setVip(bool vip) {
    m_vip = vip;
}