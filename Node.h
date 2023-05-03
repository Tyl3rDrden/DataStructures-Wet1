template <class T>
class Node
{
    T m_Data;
    Node* m_leftnode;
    Node* m_rightnode;
    Node* m_parentnode;
    int m_balancefactor;

    public:
    Node* GetLeftNodePtr() const 
    {
        return m_leftnode;
    }



    Node* GetRightNodePtr() const
    {
        return m_rightnode;
    }

    int GetBalanceFactor() const
    {
        return m_balancefactor;
    }

    //Todo Setters!


};