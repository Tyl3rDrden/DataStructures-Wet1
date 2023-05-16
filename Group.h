#ifndef _GROUP_H
#define _GROUP_H
#include <stdexcept>
#include "Wet1Exceptions.h"
class Group
{
private:
    int m_id;
    bool m_vip;
    //I'll need to add some data structure for keeping track of the users


public:
    Group(int id): m_id(id){};

    int getId() const;
    void setId(int id);

    bool isVip() const;
    void setVip(bool vip);
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