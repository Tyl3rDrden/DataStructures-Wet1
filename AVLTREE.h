#ifndef AVLTREE_H_
#define AVLTREE_H_


#define SENTINELNODE nullptr
#define SENTINEL_NODE_HEIHGT -1

#include <queue>
#include <exception>
#include <functional>
#include <sstream>
#include <memory>
#include <vector>
#include <ostream>
#include <exception>
#include <cassert>
#include <iostream>
//Public Functions needed for general Use
#include <queue>


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
            Node* GetLeftNodePtr() const
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

            void printNode() const 
            {
                std::cout << "Node data: " << *m_DataPtr << std::endl;
                std::cout << "Balance Factor: " << getBalanceFactor() << std::endl;
                if(m_leftNode != SENTINELNODE) 
                {
                    std::cout << "Left Child data: " << *(m_leftNode->m_DataPtr) << std::endl;
                }
                else 
                {
                    std::cout << "No left child." << std::endl;
                }
                if(m_rightNode != SENTINELNODE) 
                {
                    std::cout << "Right Child data: " << *(m_rightNode->m_DataPtr) << std::endl;
                }
                else 
                {
                    std::cout << "No right child." << std::endl;
                }
            }


    };
    //
    Node* m_root;
    //changed the root to be a pointer to a node that way it is interchangeable

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
        assert(root->GetRightNodePtr() && (root->GetRightNodePtr())->GetRightNodePtr());
        Node* newRoot = root->GetRightNodePtr();
        root->SetRightNodePtr(newRoot->GetLeftNodePtr());
        newRoot->SetLeftNodePtr(root);
        //this->printVisualHelper(newRoot, 0);
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



    Node* Insert(Node* currentNodePtr, Node* newNodePtr)
    {
        if(!currentNodePtr)
        {
            // We entered a null node
            return newNodePtr;
        }
        else if(m_RightIsBiggerThanLeft(currentNodePtr->getElementConst(), newNodePtr->getElementConst()))
        {
            // Go right
            currentNodePtr->SetRightNodePtr(Insert(currentNodePtr->GetRightNodePtr(), newNodePtr));

        }
        else
        {
            // Go left
            currentNodePtr->SetLeftNodePtr(Insert(currentNodePtr->GetLeftNodePtr(), newNodePtr));
        }
        currentNodePtr->updateHeight();
        int balanceFactor = currentNodePtr->getBalanceFactor();
        //Rebalancing part
        if(balanceFactor > 1 )
        {
            //Left Heavy!
            if(currentNodePtr->GetLeftNodePtr()->getBalanceFactor() >= 0 )
            {
                return LLrotateByPtr(currentNodePtr);
            }
            return LRrotateByPtr(currentNodePtr);
        }
        if(balanceFactor < -1 )
        {
            //Left Heavy!
            if(currentNodePtr->GetRightNodePtr()->getBalanceFactor() <= 0 )
            {
                return RRrotateByPtr(currentNodePtr);
            }
            return RLrotateByPtr(currentNodePtr);
        }
        return currentNodePtr;
    }

    
    void swapElements(Node* node1, Node* node2)
    {
        if (node1 == nullptr || node2 == nullptr)
        {
            throw std::invalid_argument("Null node pointer passed to swapElements");
        }
        node1->m_DataPtr.swap(node2->m_DataPtr);
    }
    Node* DeleteRecursive(Node* currentNode, const T& value)
    {
        if (currentNode == nullptr)
        {
            throw std::invalid_argument("Element Does not Exist");
        }
        if(currentNode->getElementConst() != value)
        {
            if (m_RightIsBiggerThanLeft(currentNode->getElementConst(), value))
            {
                // Value is in the right subtree
                currentNode->SetRightNodePtr(DeleteRecursive(currentNode->GetRightNodePtr(), value));
            }
            else
            {
                // Value is in the left subtree
                currentNode->SetLeftNodePtr(DeleteRecursive(currentNode->GetLeftNodePtr(), value));
            }

        }
        else
        {
            // This is the node to be deleted Remove using normal Binary search tree Algrothism
            if(!(currentNode->GetRightNodePtr()) || !(currentNode->GetLeftNodePtr()))
            {
                //A child node doesn't exist
                return currentNode->GetRightNodePtr() ? currentNode->GetRightNodePtr() : currentNode->GetLeftNodePtr();
                //Will also return nullptr if no child exists
            }
            //Both Nodes Exist
            Node* minRightSubTreeNode = getMinNode(currentNode->GetRightNodePtr());
           // std::cout << minRightSubTreeNode->getElementConst() <<"\n";
            swapElements(currentNode, minRightSubTreeNode);
            currentNode->SetRightNodePtr(DeleteRecursive(currentNode->GetRightNodePtr(), value));
        }


        // Update height of the current node
        currentNode->updateHeight();

        // Get the balance factor of this node
        int balance = currentNode->getBalanceFactor();

        // Check for unbalance and perform rotations
        // Left Left Case
        if (balance > 1 && currentNode->GetLeftNodePtr()->getBalanceFactor() >= 0)
        {
            return LLrotateByPtr(currentNode);
        }

        // Left Right Case
        if (balance > 1 && currentNode->GetLeftNodePtr()->getBalanceFactor() < 0)
        {
            return LRrotateByPtr(currentNode);
        }

        // Right Right Case
        if (balance < -1 && currentNode->GetRightNodePtr()->getBalanceFactor() <= 0)
        {
            return RRrotateByPtr(currentNode);
        }

        // Right Left Case
        if (balance < -1 && currentNode->GetRightNodePtr()->getBalanceFactor() > 0)
        {
            return RLrotateByPtr(currentNode);
        }

        return currentNode;
    }
    void printVisualHelper(const Node* node, int depth) const {
        if (node == nullptr || node->getElementPtr() == SENTINELNODE) {
            return;
        }

        // Increase the depth (indentation)
        depth += 4;

        // Process the right subtree first
        printVisualHelper(node->GetRightNodePtr(), depth);

        // Print the current node after spaces
        std::cout << std::endl;
        for (int i = 4; i < depth; i++) {
            std::cout << " ";
        }
        std::cout << node->getElementConst() << std::endl;

        // Process the left subtree
        printVisualHelper(node->GetLeftNodePtr(), depth);
    }
    Node* FindRecursive(Node* currentNode, const T& value) 
    {
        if (!currentNode) {
            return nullptr; // Not found
        }
        if(currentNode->getElementConst() == value)
        {
            return currentNode;

        }

        if (m_RightIsBiggerThanLeft(currentNode->getElementConst(), value))
        {
            // Go right
            return FindRecursive(currentNode->GetRightNodePtr(), value);
        }
        else
        {
            // Go left
            return FindRecursive(currentNode->GetLeftNodePtr(), value);
        }
    }
    Node* getMinNode(Node* CurrentNodePtr)
    {
        while (CurrentNodePtr->GetLeftNodePtr())
        {
            CurrentNodePtr = CurrentNodePtr->GetLeftNodePtr() ;
        }
        return CurrentNodePtr;
        

    }
    void RecursiveDelete(Node* currentNode)
    {
        if (m_root == SENTINELNODE)
        {
            return;
        }
        RecursiveDelete(currentNode->GetLeftNodePtr());
        RecursiveDelete(currentNode->GetRightNodePtr());
        delete currentNode;
    }
public:
    
    AVLTREE(FUNCTOR RightIsBiggerThanLeft): m_RightIsBiggerThanLeft(RightIsBiggerThanLeft) , m_root(SENTINELNODE){};
    //Creates an empty tree!
    void printVisual()
    {
        printVisualHelper(m_root, 0);
    }
    
    void InsertElement(const std::shared_ptr<T> dataPtr)
    {
        if(!dataPtr.get())
        {
            throw std::invalid_argument("Null pointer passed to Insert Element");
            //Throw Exception Bad pointer
        }
        Node* newNodePtr = new Node(dataPtr);
        //Creating a Node from our data pointer
            //Node allocated on the heap!
        m_root = Insert(m_root, newNodePtr);
        //Now call the recursive function the find the relevant position

    } //chec/k const place...

    const T& Find(const T& value) 
    {//Has to be const To not destroy structur
        Node* resultNodePtr =  FindRecursive(m_root, value);
        const T& result = resultNodePtr->getElementConst();
        
        return result;
    }


    void RemoveElement(const T& value)
    {
        m_root = DeleteRecursive(m_root, value);
    }

    


    //const std::shared_ptr<T> getDataPtr(const std::shared_ptr<KEY> key);

    //I think the syntas is correct
    ~AVLTREE()
    {
        RecursiveDelete(m_root);
    }

        //Recursivly dealloc all nodes


        //We used normal pointers need to recursivly dealloc all Nodes
    
};
#endif