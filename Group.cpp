#include "Group.h"
#include "User.h"

Group::Group(int id) : m_id(id), m_vip(false) , m_vipCount(0)
{
    for (int i = 0; i < NUMOFGENRES; i++)
    {
        m_genreViewCount[i] = 0;
        m_genreSumViewCount[i] = 0;
    }

}

const int& Group::getId() const {
    return m_id;
}

void Group::setId(int id) {
    m_id = id;
}

bool Group::isVip() const {
    if(m_vipCount >0)
    {
        return true;
    }
    else if (m_vipCount == 0)
    {
        return false;
    }
    else
    {
        throw std::runtime_error("Negative Number of Vip in group");
    }

}
void Group::incrementGenreCount(Genre genre)
{
    if(genre != Genre::NONE)
    {
        int genreNum = static_cast<int>(genre);
        m_genreViewCount[genreNum]++;
        m_genreSumViewCount[genreNum]+= this->getSize();
    }
    else
    {
        throw std::invalid_argument("None given to increment Genre In Group");
    }

}
void Group::incrementSumGenreCount(Genre genre)
{
    if(genre != Genre::NONE)
    {
        int genreNum = static_cast<int>(genre);
        m_genreSumViewCount[genreNum]++;
    }
    else
    {
        throw std::invalid_argument("None given to increment Genre In Group");
    }

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

int Group::getGenreSumViewCount(Genre genre) const
{
    if(genre != Genre::NONE)
    {
        return m_genreSumViewCount[static_cast<int>(genre)];
    }
    else
    {
        int sum=0;
        for (int i = 0; i < NUMOFGENRES; i++)
        {
            sum+= m_genreSumViewCount[i];
        }
        return sum;
    }
}

void Group::addUser(const std::shared_ptr<User> user)
{
    if(!(user->inGroup()))
    {
        if(user->isVip())
        {
            m_vip = true;
            m_vipCount++;
            //We are now a vip group
        }
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
    if(m_users.Find(userId).isVip())
    {
        m_vipCount--;
        if(m_vipCount == 0)
        {
            m_vip = false;
        }
    }
    m_users.RemoveElement(userId);

}
int Group::getSize()
{
    return m_users.getSize();
}
/*
Group::~Group()
{
    int* UsersIngroupId = m_users.GetKeysDescending();
    for (int i = 0; i < m_users.getSize(); i++)
    {
        m_users.Find(UsersIngroupId[i]).groupTerminated();
    }
}*/
Group::~Group()
{
    User** UsersIngroupId = m_users.GetDataPtrsDescending();
    for (int i = 0; i < m_users.getSize(); i++)
    {
        UsersIngroupId[i]->groupTerminated();
    }
    delete[] UsersIngroupId;
}