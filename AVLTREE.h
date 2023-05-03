
#define SENTINELNODE nullptr
#include <memory>
#include <exception>


template <class T, class KEY>
class AVLTREE
{
private:
    class Node
    {
        const std::Shared_ptr<KEY> key; //check const
        const std::Shared_ptr<T> m_Data; //check const
        Node* m_leftNode;
        Node* m_rightNode;
        int m_height;
    
        public:

        Node(const std::Shared_ptr<T> Data ,const std::Shared_ptr<KEY> key): m_data(data), key(key) 
        {
            m_leftNode = SENTINELNODE;
            m_rightNode = SENTINELNODE;
            m_hight = 0;
            //Creating a new leaf!
        }
        Node* GetLeftNodePtr() const 
        {
            return m_leftNode;
        }

        Node* GetRightNodePtr() const
        {
            return m_rightNode;
        }

        int GetBalanceFactor() const
        {
           //
        }

        //Todo Setters!


    };

    //

    Node root;
    Node* LLrotate(Node* source);
    Node* RRrotate(Node* source);
    Node* LRrotate(Node* source);
    Node* RLrotate(Node* source);





    //Maybee need to keep track biggest Node
public:

    void InsertElement(const std::shared_ptr<T> data ,const std::Shared_ptr<KEY> key); //check const place...
    void DeleteElement(const std::Shared_ptr<KEY> key);
    const std::shared_ptr<T> getDataPtr(const std::Shared_ptr<KEY> key);

    AVLTREE(const T& data): root(Node(data)){};
    //I think the syntas is correct
    ~AVLTREE();
    //Recursivly dealloc all nodes


    //We used normal pointers need to recursivly dealloc all Nodes
};
