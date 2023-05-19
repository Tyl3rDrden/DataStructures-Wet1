#include "User.h"
#include "Group.h"

User::User(int id, bool vip) : m_groupPtr(nullptr)
    , m_id(id), m_vip(vip) 
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
void User::joinGroup(std::shared_ptr<Group> groupPtr)
{
    if(groupPtr)
    {
        m_groupPtr = groupPtr;
        //Changing the Pre Group view count
        for (int i = 0; i < NUMOFGENRES; i++)
        {
            m_genreViewCount[i] = groupPtr->getGenreViewCount(static_cast<Genre>(i));
        } 
    }
    else
    {
        throw std::invalid_argument("Null Pointer Given to setGroup");
    }
}

int User::getNumGenreViews(Genre genre)
{
    int ViewsFromGroup =0;
    int genreNum  = static_cast<int>(genre);
    if(this->inGroup())
    {//increment View count From Group
        //Summing current view count
        ViewsFromGroup += m_groupPtr->getGenreViewCount(genre);
        //Deducting the join time views 
        ViewsFromGroup -= m_preGroupViewCount[genreNum];
    }
    return m_genreViewCount[genreNum] + ViewsFromGroup;
    //Adding personal views to the Group Watched; 

}