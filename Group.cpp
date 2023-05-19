#include "Group.h"


Group::Group(int id) : m_id(id), m_vip(false) 
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
void Group::incrementGenreCount(Genre genre)
{
    if(genre != Genre::NONE)
    {
        int genreNum = static_cast<int>(genre);
        m_genreViewCount[genreNum]++;
    }
    else
    {
        throw std::invalid_argument("None given to increment Genre In Group");
    }

}

void Group::setVip(bool vip) {
    m_vip = vip;
}

int Group::getGenreViewCount(Genre genre)
{
    if(genre != Genre::NONE)
    {
        return m_genreViewCount[static_cast<int>(genre)];
    }
    else
    {
        int sum=0;
        for (int i = 0; i < NUMOFGENRES; i++)
        {
            sum+= m_genreViewCount[i];
        }
        return sum;
    }
}

void Group::addUser(const std::shared_ptr<User>& user)
{
    if(user.isVip())
    {
        m_vip = true;
        //We are now a vip group
    }
    std::shared_ptr<User> shredptr(user);
    m_users.InsertElement(user, &((*user).getId()));
    user.m_groupPtr = this;
    //I'm goin to get so many bugS!!!!!
    for (int i = 0; i < NUMOFGENRES; i++)
    {
        user.m_preGroupViewCount[i] = m_genreViewCount[i];
    }
    
}