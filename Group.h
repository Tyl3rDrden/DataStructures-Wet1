#ifndef _GROUP_H
#define _GROUP_H
#include <stdexcept>
#include "Wet1Exceptions.h"
#include "wet1util.h"
#include "AVLTREE.h"
#include "User.h"
//#include "Linkedlist.h"

class User;

class Group
{
private:
    int m_id;
    bool m_vip;
    int m_vipCount;
    AVLTREE<User, CompareUserIDFunctor, int> m_users; 
    //I need to use a linked list for complexity concerns when deleting a user can't do it in Nlog(n)
    int m_genreViewCount[NUMOFGENRES];
    //This is the counter for the group view 

    int m_genreSumViewCount[NUMOFGENRES];
    //This is the counter for the group views summed up in total !


public:
    Group(int id);

    const int& getId() const;
    void setId(int id);
    //Fuck! i do need a count for the number of vip Users!
    //Make Sure to add it!
    bool isVip() const;
    void incrementGenreCount(Genre genre);
    void incrementSumGenreCount(Genre genre);
    int getGenreViewCount(Genre genre) const;
    
    void addUser(const std::shared_ptr<User> user);
    void deleteUser(int userId);

    int getSize();

    ~Group();
};
//I can probably make this doing a template.. But i don't want to risk it!
	struct CompareGroupIDFunctor {
		bool operator()(const Group& a, const Group& b) {
			if (a.getId() == b.getId()) {
				throw IdAlreadyExists("Identical Id's");
			}
			return a.getId() < b.getId();
            //Return Right is bigger than left!
		}
	};

#endif