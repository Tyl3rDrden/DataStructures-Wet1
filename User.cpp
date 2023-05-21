#include "User.h"
#include "Group.h"

User::User(int id, bool vip) : m_groupPtr(nullptr)
        , m_id(id), m_vip(vip)
{
    for (int i = 0; i < NUMOFGENRES; i++)
    {
        m_preGroupViewCount[i] = 0;
        m_genreViewCount[i] = 0;
    }
}

const int& User::getId() const
{
    return m_id;
}

bool User::isVip() const
{
    return m_vip;
}

void User::setVip(bool vip)
{
    m_vip = vip;
}
void User::incrementViewsbyGenre(Genre genre)
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
bool User::inGroup()
{
    return (m_groupPtr != nullptr);
}
void User::joinGroup(Group* groupPtr)
{
    if(groupPtr)
    {
        m_groupPtr = groupPtr;
        //Changing the Pre Group view count
        for (int i = 0; i < NUMOFGENRES; i++)
        {
            m_preGroupViewCount[i] = groupPtr->getGenreViewCount(static_cast<Genre>(i));
        }
    }
    else
    {
        throw std::invalid_argument("Null Pointer Given to setGroup");
    }
}
int User::getViewsFromGroup(Genre genre)
{
    if(genre == Genre::NONE)
    {
        throw std::invalid_argument("Only Valid Genres Allowed");
    }
    int ViewsFromGroup =0;
    int genreNum  = static_cast<int>(genre);
    if(this->inGroup())
    {//increment View count From Group
        //Summing current view count
        ViewsFromGroup += m_groupPtr->getGenreViewCount(genre);
        //Deducting the join time views
        ViewsFromGroup -= m_preGroupViewCount[genreNum];
    }
    return ViewsFromGroup;


}

int User::getNumGenreViews(Genre genre)
{
    if(genre == Genre::NONE)
    {
        throw std::invalid_argument("Only Valid Genres Allowed");
    }
    int genreNum  = static_cast<int>(genre);
    return m_genreViewCount[genreNum] + getViewsFromGroup(genre);
    //Adding personal views to the Group Watched;

}

void User::groupTerminated()
{
    if(!(this->inGroup()))
    {
        throw std::runtime_error("Group termiantion called \n even though user isn't part of a group");
    }
    //We'll now incrmemnt the number of group views to the number of personal views

    for (int i = 0; i < NUMOFGENRES; i++)
    {
        m_genreViewCount[i] += (getViewsFromGroup(static_cast<Genre>(i)) - m_preGroupViewCount[i]);
    }
    //Now setting the preGroupJoin View count to 0
    for (int i = 0; i < NUMOFGENRES; i++)
    {
        m_preGroupViewCount[i] = 0;
    }
    //Setting pointer to group to nullptr
    this->m_groupPtr = nullptr;



}


Group* User::getGroupPtr()
{
    if(m_groupPtr)
    {
        return m_groupPtr;
    }
    throw std::runtime_error("Asked for nullptr! in user's pointer to group");
    return nullptr;
}