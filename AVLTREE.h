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
#include "Wet1Exceptions.h"
//Public Functions needed for general Use
#include <queue>


template <class T, class FUNCTOR, class KEY>
class AVLTREE
{
private:
    class Node
    {
        friend AVLTREE;
        std::shared_ptr<T> m_DataPtr; // Not const for the assignment operator!
        const KEY* m_key;
        Node* m_leftNode;
        Node* m_rightNode;
        int m_height;
        //Private Methods


        //~~~~~`
        //Interface
        public:
            //Creates a general lead node! for general use!
            //No children
            Node(const std::shared_ptr<T> DataPtr, const KEY* KeyPtr): m_DataPtr(DataPtr),m_key(KeyPtr)
            {
                if(!KeyPtr || !DataPtr)
                {
                    throw std::invalid_argument("Bad Pointers Given");

                }
                m_leftNode = SENTINELNODE;
                m_rightNode = SENTINELNODE;
                m_height = 0;
                //Creating a new leaf!
            }
            Node(const Node& other):
                m_DataPtr(other.m_DataPtr),
                m_key(other.m_key),
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
                std::cout << "Key Data: " << *m_key << std::endl;
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
            const KEY& getKey()
            {
                return *m_key;
            }


    };
    //
    Node* m_root;
    int m_count;
    //changed the root to be a pointer to a node that way it is interchangeable

    FUNCTOR m_RightIsBiggerThanLeft;
    
    // LL rotation function
    Node* LLrotateByPtr(Node* root)
    {
        //Updating pointers
        Node* newRoot = root->GetLeftNodePtr();
        root->SetLeftNodePtr(newRoot->GetRightNodePtr());
        newRoot->SetRightNodePtr(root);

        // Updating heights of the nodes
        root->updateHeight();
        newRoot->updateHeight();

        return newRoot;
    }
    Node* RRrotateByPtr(Node* root)
    {
        assert(root->GetRightNodePtr());
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
        if(m_RightIsBiggerThanLeft(currentNodePtr->getKey(), newNodePtr->getKey()))
        {
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
        const KEY* tempkey = node2->m_key;
        node2->m_key = node1->m_key;
        node1->m_key = tempkey; 
    }
    Node* DeleteRecursive(Node* currentNode, const T& keyValue)
    {
        //std::cout << "Deleting " << keyValue << "\n"; 
        if (currentNode == nullptr)
        {
            //std::cout << keyValue << " IS being deleted\n"; 
            throw DeleteNonexistentElement("Element Does not Exist");
        }
        if(currentNode->getKey() != keyValue)
        {
            if (m_RightIsBiggerThanLeft(currentNode->getKey(), keyValue))
            {
                // Value is in the right subtree
                //std::cout <<  "Going right!\n"; 
                currentNode->SetRightNodePtr(DeleteRecursive(currentNode->GetRightNodePtr(), keyValue));
            }
            else
            {
                // Value is in the left subtree
                //std::cout << "Going Left\n";
                currentNode->SetLeftNodePtr(DeleteRecursive(currentNode->GetLeftNodePtr(), keyValue));
            }

        }
        else
        {
            // This is the node to be deleted Remove using normal Binary search tree Algrothism
            if(!(currentNode->GetRightNodePtr()) || !(currentNode->GetLeftNodePtr()))
            {
                //std::cout << "Activated"; 
                //A child node doesn't exist
                Node* newChildNode = currentNode->GetRightNodePtr() ? currentNode->GetRightNodePtr() : currentNode->GetLeftNodePtr();
                delete currentNode;
                return newChildNode;
                //Will also return nullptr if no child exists
            }
            //Both Nodes Exist
            Node* minRightSubTreeNode = getMinNode(currentNode->GetRightNodePtr());
           // std::cout << minRightSubTreeNode->getElementConst() <<"\n";
            swapElements(currentNode, minRightSubTreeNode);
            currentNode->SetRightNodePtr(DeleteRecursive(currentNode->GetRightNodePtr(), keyValue));
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
        depth += 12;

        // Process the right subtree first
        printVisualHelper(node->GetRightNodePtr(), depth);

        // Print the current node after spaces
        std::cout << std::endl;
        for (int i = 4; i < depth; i++) {
            std::cout << " ";
        }
        std::cout << node->getElementConst() << "," << *(node->m_key) <<std::endl;

        // Process the left subtree
        printVisualHelper(node->GetLeftNodePtr(), depth);
    }
    Node* FindRecursive(Node* currentNode, const KEY& keyValue) 
    {
        if (!currentNode) {
            return nullptr; // Not found
        }
        if(currentNode->getKey() == keyValue)
        {
            return currentNode;

        }
        if (m_RightIsBiggerThanLeft(currentNode->getKey(), keyValue))
        {
            // Go right
            return FindRecursive(currentNode->GetRightNodePtr(), keyValue);
        }
        else
        {
            // Go left
            return FindRecursive(currentNode->GetLeftNodePtr(), keyValue);
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
    void FillArrayDescending(Node* currentNode, KEY* &array, int &currentIndex)
    {
        if (currentNode == nullptr) {
            return;
        }

        // First, process right subtree
        FillArrayDescending(currentNode->GetRightNodePtr(), array, currentIndex);

        // Then, save current node's key
        array[currentIndex] = currentNode->getKey();
        currentIndex++;

        // Finally, process left subtree
        FillArrayDescending(currentNode->GetLeftNodePtr(), array, currentIndex);
    }
public:
    KEY* GetKeysDescending()
    {
        if (m_count == 0) {
            return nullptr; // Tree is empty
        }

        KEY* keysArray = new KEY[m_count]; // Array to store keys
        int currentIndex = 0; // Starting index
        FillArrayDescending(m_root, keysArray, currentIndex);
        return keysArray;
    }
    AVLTREE(): m_root(SENTINELNODE), m_count(0)
    {
        FUNCTOR RightIsBiggerThanLeft;
        //Initializes an instance of the Functor
        m_RightIsBiggerThanLeft = RightIsBiggerThanLeft;
        

    }
    //Creates an empty tree!
    void printVisual()
    {
        printVisualHelper(m_root, 0);
    }
    
    void InsertElement(std::shared_ptr<T> dataPtr, const KEY* KeyPtr)
    {
        if(!dataPtr.get() || !KeyPtr)
        {
            throw std::invalid_argument("Null pointe, r passed to Insert Element");
            //Throw Exception Bad pointer
        }
        m_count++;
        Node* newNodePtr = new Node(dataPtr, KeyPtr);
        //newNodePtr->printNode();
        //std::cout << newNodePtr->getElement() << "  " << newNodePtr->getKey();
        //Creating a Node from our data pointer
            //Node allocated on the heap!
        m_root = Insert(m_root, newNodePtr);
        //Now call the recursive function the find the relevant position

    } //chec/k const place...

    T& Find(const KEY& Keyvalue) 
    {//Has to be const To not destroy structur
        Node* resultNodePtr =  FindRecursive(m_root, Keyvalue);
        if(!resultNodePtr)
        {
            throw ElementNotFound();
        }
        return resultNodePtr->getElement();
    }


    void RemoveElement(const KEY& value)
    {
        m_count--;
        m_root = DeleteRecursive(m_root, value);
    }

    bool ElementInTree(const KEY& Keyvalue)
    {
        try
        {   //std::cout << "Hello\n"; 
            Find(Keyvalue);
        }
        catch(const ElementNotFound& e)
        {
            //std::cout << "Hello"; 
            return false;
        }
        return true;
        

    }

    int getSize()
    {
        return m_count;
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