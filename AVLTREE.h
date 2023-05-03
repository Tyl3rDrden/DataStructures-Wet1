#include "Node.h"

#define SENTINELNODE nullptr

template <class T>
class AVLTREE
{
private:
    Node* root;
    //Maybee need to keep track biggest Node
public:

    void leftRightRotatation(Node* node);
    //Maybee i should pass a refrence insead!
    void RightLeftRotatation(Node* node);

    AVLTREE(/* args */);
    ~AVLTREE();
};
