#include "User.h"

User::User(int id, bool vip)
    : m_id(id), m_vip(vip) 
    {
            for (int i = 0; i < NUMOFGENRES; i++)
            {
                m_genreViewCount[i] = 0;
            }
    }

int User::getId() const
{   
    return m_id;
}

void User::setId(int id)
{
    m_id = id;
}

bool User::isVip() const
{
    return m_vip;
}

void User::setVip(bool vip)
{
    m_vip = vip;
}