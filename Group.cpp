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

int Group::getGenreViewCount(Genre genre) const
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

void Group::addUser(const std::shared_ptr<User> user)
{
    if(user->inGroup())
    {
        if(user->isVip())
        {
            m_vip = true;
            //We are now a vip group
        }
        std::shared_ptr<User> shredptr(user);
        m_users.InsertElement(user, &(user->getId()));
        user->joinGroup(this);
        
        
    }
    else
    {
        throw std::invalid_argument("Adding user to group twice!");
    }

}
void Group::deleteUser(int userId)
{
    if(!m_users.ElementInTree(userId))
    {
        throw std::runtime_error("User not it group Can't be deleted");
    }
    m_users.RemoveElement(userId);

}

Group::~Group()
{
    //Its probably better to do it with an iterator!
    int* UsersIngroupId = m_users.GetKeysDescending();
    for (int i = 0; i < m_users.getSize(); i++)
    {
        m_users.Find(UsersIngroupId[i]).groupTerminated();
    }
    delete[] m_genreViewCount;
    
}