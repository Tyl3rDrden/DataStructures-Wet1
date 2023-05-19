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
	friend Group;
	// Makes it alot easier to add and remove Users from the group 

    int m_id;
    bool m_vip;
	int m_genreViewCount[NUMOFGENRES];
	//This is the personal list of the users watchlist!

	const Group* m_groupPtr;
	int m_preGroupViewCount[NUMOFGENRES];
	//This is an array of the user's group watchlist at the time he joined

public:
    User(int id, bool vip);

    const int& getId() const;

    bool isVip() const;
    void setVip(bool vip);
	void incrementViewsbyGenre(Genre genre);
	bool inGroup();
	void joinGroup(const Group* groupPtr);
	int getNumGenreViews(Genre genre); // Returns the personal number of views


};

//I can probably make this doing a template.. But i don't want to risk it!
	struct CompareUserIDFunctor {
		bool operator()(const User& a, const User& b) {
			if (a.getId() == b.getId()) {
				throw IdAlreadyExists("Identical Id's");
			}
			return a.getId() < b.getId();
            //Return Right is bigger than left!
		}
	};

#endif