#ifndef _USER_H
#define _USER_H
#include <stdexcept>
#include "Wet1Exceptions.h"

#define NUMOFGENRES 4

class User
{
private:
    int m_id;
    bool m_vip;

public:
    User(int id, bool vip);

    int getId() const;
    void setId(int id);

    bool isVip() const;
    void setVip(bool vip);
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