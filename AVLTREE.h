
#define SENTINELNODE nullptr
#define SENTINEL_NODE_HEIHGT -1

#include <exception>
#include <functional>
#include <sstream>
#include <memory>
#include <vector>
#include <ostream>
#include <exception>
#include <cassert>
//Public Functions needed for general Use



template <class T, class FUNCTOR>
class AVLTREE
{
private:
    class Node
    {
        friend AVLTREE;
        std::shared_ptr<T> m_DataPtr; // Not const for the assignment operator!

        Node* m_leftNode;
        Node* m_rightNode;
        int m_height;
        //Private Methods


        //~~~~~`
        //Interface
        public:
            //Creates a general lead node! for general use!
            //No children
            Node(const std::shared_ptr<T> DataPtr): m_DataPtr(DataPtr) 
            {
                m_leftNode = SENTINELNODE;
                m_rightNode = SENTINELNODE;
                m_height = 0;
                //Creating a new leaf!
            }
            Node(const Node& other):
                m_DataPtr(other.m_DataPtr),
                m_leftNode(other.m_leftNode),
                m_rightNode(other.m_rightNode),
                m_height(other.m_height)
                    {}
            //Maybe another contructor needed for
            Node& operator=(const Node& other)
            {
                if (this != &other)
                {
                    m_DataPtr = other.m_DataPtr;
                    m_leftNode = other.m_leftNode;
                    m_rightNode = other.m_rightNode;
                    m_height = other.m_height;
                }
                return *this;
            }
            //Assignment operator 


            Node& GetLeftNode() const 
            {
                assert(m_leftNode);
                return *m_leftNode;
            }

            Node& GetRightNode() const
            {
                assert(m_rightNode);
                return *m_rightNode;
            }
            
            Node* GetRightNodePtr() const
            {
                return m_rightNode;
            }
            Node* GetLeftNodePtr()
            {
                return m_leftNode;
            }
            void SetRightNodePtr(Node* newRightNodePtr)
            {
                m_rightNode = newRightNodePtr;

            }
            void SetLeftNodePtr(Node* newLeftNodePtr)
            {
                m_leftNode = newLeftNodePtr;
            }

            void SetElementPtr(std::shared_ptr<T> elementPtr)
            {
                m_DataPtr = elementPtr;
            }
            int getHeight() const
            {
                return m_height;

            }
            int getBalanceFactor() const
            {
                //Left Subtree height minus right
                int leftheight = m_leftNode ? GetLeftNode().m_height : SENTINEL_NODE_HEIHGT ;
                int rightheight = m_rightNode ? GetRightNode().m_height : SENTINEL_NODE_HEIHGT ;
                return leftheight - rightheight;
            //
            }
            void updateHeight()
            {
                //We'll use max on both the left and right heights then add one
                int leftheight = m_leftNode ? GetLeftNode().m_height : SENTINEL_NODE_HEIHGT;
                int rightheight = m_rightNode ? GetRightNode().m_height : SENTINEL_NODE_HEIHGT ;
                m_height = std::max(leftheight, rightheight) +1;
                //Using the recursive definition of the height!
            }
            std::shared_ptr<T> getElementPtr() const
            {
                return m_DataPtr;
            }
            T& getElement()
            {
                assert(m_DataPtr);
                return *m_DataPtr;
            }
            const T& getElementConst() const
            {
                assert(m_DataPtr);
                return *m_DataPtr;
            }

        //Todo Setters!
    };
    //
    Node m_root;


    FUNCTOR m_RightIsBiggerThanLeft;
    
    // LL rotation function
    Node* LLrotateByPtr(Node* root)
    {
        //Updating pointers
        Node* newRoot = root->GetLeftNodePtr();
        root->SetLeftNodePtr(newRoot->GetLeftNodePtr());
        newRoot->SetRightNodePtr(root);


        // Updating heights of the nodes
        root->updateHeight();
        newRoot->updateHeight();

        return newRoot;
    }

    /*Node* RRrotateByPtr(Node* root)
    {
        Node* newRoot = root->m_rightNode;
        root->m_rightNode = newRoot->m_leftNode;
        newRoot->m_leftNode = root;

        root->updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }*/
    Node* RRrotateByPtr(Node* root)
    {
        Node* newRoot = root->GetRightNodePtr();
        root->SetRightNodePtr(newRoot->GetLeftNodePtr());
        newRoot->SetLeftNodePtr(root);

        root->updateHeight();
        newRoot->updateHeight();
        return newRoot;
    }

    //Now the difficult ones : (


    /*
    Node* LRrotateByPtr(Node* root)
    {
        root->m_leftNode = RRrotate(root->m_leftNode);
        return LLrotate(root);
        //Defining using 
    }
    Node* RLrotateByPtr(Node* root)
    {
        root->m_leftNode = LLrotate(root->m_rightNode);
        return RRrotate(root);

    }*/
    Node* LRrotateByPtr(Node* root)
    {
        Node* leftNode = root->GetLeftNodePtr();
        root->SetLeftNodePtr(RRrotateByPtr(leftNode));
        return LLrotateByPtr(root);
    }

    Node* RLrotateByPtr(Node* root)
    {
        Node* rightNode = root->GetRightNodePtr();
        root->SetRightNodePtr(LLrotateByPtr(rightNode));
        return RRrotateByPtr(root);
    }



    void Insert(Node& currentNode, Node& newNode)
    {
        //!!!!!!!!!!!!!!!!!The functor has to take care of exceptions where two elements are the same!


        //Recursive part
        if(m_RightIsBiggerThanLeft(currentNode.getElementConst(), newNode.getElementConst())) // The functor should only accept const refrences!
        {
            //Go right!
            //_____________________
            //Making sure Right Exists
            if(currentNode.GetRightNodePtr())
            {
                Insert(currentNode.GetRightNode(), newNode);
            }
            else
            {
                //Right Node doesn't exist We need to append it
                currentNode.SetRightNodePtr(&newNode);
            }
            //Appending Node To the Right! 
        }
        else
        {
            if(currentNode.GetLeftNodePtr())
            {//Left Node Exists
                //Go Left
                Insert(currentNode.GetLeftNode(), newNode);
            }
            else
            {
                currentNode.SetLeftNodePtr(&newNode);
            }
        }
        currentNode.updateHeight();
        int balanceFactor = currentNode.getBalanceFactor();
        if(balanceFactor > 1)
        {
            //We are left heavy therefor left node exists
            if(currentNode.GetLeftNode().getBalanceFactor() >= 0)
            {//If the left tree is balanced or is left 
                LLrotateByPtr(&currentNode);
            }
            LRrotateByPtr(&currentNode);
        }
        if(balanceFactor < -1)
        {//We are right Heavy!
            if(currentNode.GetRightNode().getBalanceFactor() <=0)
            {
                //Right node is right heavy/Balanced
                RRrotateByPtr(&currentNode);
            }
            RLrotateByPtr(&currentNode);
        }




    }



public:
    AVLTREE(FUNCTOR RightIsBiggerThanLeft): m_RightIsBiggerThanLeft(RightIsBiggerThanLeft) , m_root(SENTINELNODE){};
    //Creates an empty tree!


    void InsertElement(const std::shared_ptr<T> dataPtr)
    {
        if(!dataPtr)
        {
            throw std::invalid_argument("Null pointer passed to InsertElement");
            //Throw Exception Bad pointer
        }
        Node* newNodePtr = new Node(dataPtr);
        //Creating a Node from our data pointer
        if(m_root.getElementPtr() == SENTINELNODE)
        {//Our root is empty 
            //First node in the AVL tree
            m_root = *newNodePtr;
            //sets the element to be the root
            return;
            //Ends Function
        }
            //Node allocated on the heap!
        Insert(m_root, *newNodePtr);
        //Now call the recursive function the find the relevant position

    } //chec/k const place...

    std::shared_ptr<T> Find(const T& value) 
    {
        return Find(m_root, value);
    }

    std::shared_ptr<T> Find(Node& currentNode, const T& value) 
    {
        if (currentNode.getElementPtr() == SENTINELNODE) {
            return nullptr; // Not found
        }

        if (m_RightIsBiggerThanLeft(value, currentNode.getElementConst())) {
            // Go right
            return Find(currentNode.GetRightNode(), value);
        } else if (m_RightIsBiggerThanLeft(currentNode.getElementConst(), value)) {
            // Go left
            return Find(currentNode.GetLeftNode(), value);
        } else {
            // Found the value
            return currentNode.getElementPtr();
        }
    }

    void DeleteElement(const std::shared_ptr<T> dataPtr);
    //const std::shared_ptr<T> getDataPtr(const std::shared_ptr<KEY> key);

    //I think the syntas is correct
    ~AVLTREE()
    {
        RecursiveDelete(&m_root);
    }

    void RecursiveDelete(Node* currentNode)
    {
        if (currentNode == SENTINELNODE)
        {
            return;
        }
        RecursiveDelete(currentNode->GetLeftNodePtr());
        RecursiveDelete(currentNode->GetRightNodePtr());
        delete currentNode;
    }
        //Recursivly dealloc all nodes


        //We used normal pointers need to recursivly dealloc all Nodes
};



