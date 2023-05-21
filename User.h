#ifndef _USER_H
#define _USER_H
#include <stdexcept>
#include "Wet1Exceptions.h"
#include "wet1util.h"
#include <memory>
class Group;
//Forward Declation for Group class so not to make a circular inclusion

#define NUMOFGENRES 4

class User
{
private:
    // Makes it alot easier to add and remove Users from the group

    int m_id;
    bool m_vip;
    int m_genreViewCount[NUMOFGENRES];
    //This is the personal list of the users watchlist!

    Group* m_groupPtr;
    int m_preGroupViewCount[NUMOFGENRES];
    //This is an array of the user's group watchlist at the time he joined
    friend Group;
    void joinGroup(Group* groupPtr);
    void groupTerminated();
    int getViewsFromGroup(Genre genre);
    //Only group can call these Methods !

public:
    User(int id, bool vip);

    const int& getId() const;

    bool isVip() const;
    void setVip(bool vip);
    void incrementViewsbyGenre(Genre genre);
    bool inGroup();
    Group* getGroupPtr();
    int getNumGenreViews(Genre genre); // Returns the personal number of views


};
#endif

#ifndef _CompareUserIDFunctor
#define  _CompareUserIDFunctor
struct CompareUserIDFunctor {
    bool operator()(const int& a, const int& b) {
        if (a == b) {
            throw IdAlreadyExists("Identical Id's");
        }
        return a < b;
        //Return Right is bigger than left!
    }
};

#endif
//I can probably make this doing a template.. But i don't want to risk it!

