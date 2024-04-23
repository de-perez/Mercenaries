#include <iostream>
#include <unordered_map>
#include <queue> 
#include <iostream>

using namespace std;

template <class t1 , class t2>
class priorityQ
{
public:
    priorityQ();
    void push_back ( const t1 & , const t2 &);
    void pop_front ();
    void increaseKey ( const t1 & , const t2 &);
    t2 get_front_priority() const;
    t1 get_front_key () const;
    bool isEmpty () const;
private:
    struct priorityType
    {
        t1 key;
        t2 priority;
    };
    void bubbleUp(std::size_t);
    void bubbleDown(std::size_t);
    std::vector<priorityType> heapArray;
    std::unordered_map<t1, std::size_t> itemToPQ;
};


template <class t1, class t2>
priorityQ<t1, t2>::priorityQ()
{
    // sets up an empty priority queue, if you wish to have the root
    // start from index 1, then just have heapArray.resize(1) in the constructor’s body otherwise the
    // constructor’s body would be empty
    heapArray.resize(1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::push_back(const t1& key, const t2& value)
{
    // inserts a new priotityType object to the back of heapArray, 
    // maps this key to the last index of the heapArray and then calls
    // bubbleUp( heapArray.size() - 1 )
    priorityType pushThis;
    pushThis.key = key;
    pushThis.priority = value;

    // Push object into map
    itemToPQ[key] = heapArray.size() - 1;

    // Push object back into the heap array
    heapArray.push_back(pushThis);

    // Call bubbleUp
    bubbleUp(heapArray.size() - 1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::pop_front()
{
    // assigns the last element of heapArray and assigns it to the root position, updates 
    // the itemToPQ map accordingly, then call bubbleDown(1) or bubbleDown(0)
    // (depending on whether you designate 1 or 0 as the root)
    /*
    FUNCTION_IDENTIFIER: This function copies the last element of the heapArray into the root. It
    will then adjust the priority queue accordingly, then pop_back the last element of the heapArray.
    Last, it will call bubbleDown to find the new root's proper place according to value within the
    priority queue.
    Return Value: recurse
    */

    if (isEmpty())
    {
        return;
    }

    // Overwrite root w/ last element
    heapArray[1] = heapArray.back();

    //cout << "\nheapArray.back: " << heapArray.back().key << endl; // Debug

    // Update the unordered map
    itemToPQ[heapArray[1].key] = 1;

    // Remove last element
    heapArray.pop_back();    

    bubbleDown(1);
}

template <class t1, class t2>
void priorityQ<t1, t2>::increaseKey(const t1& key, const t2& value) 
{
    // using the itemToPQ map, update the value field of the element in the heapArray 
    // and then call bubbleUp using the index of where key parameter is in heapArray 
    /*
    FUNCTION_IDENTIFIER: This function will take a string name(key) and a mercType(value)
    and add it to its respective mercenary. It will do this by finding the mercenary's place
    within the heap (found using the unordered map), then add the parameter mercType to the
    key's mercType with += (overloaded).
    Return Value: recurse
    */
    // Find key in the heapArray
    size_t i = itemToPQ[key];
    //std::cout << key << "'s index in itemtoPQ is " << i << std::endl; // Debug

    // Add value to key's priority
    heapArray[i].priority += value;

    bubbleUp(i);
}

template <class t1, class t2>
t2 priorityQ<t1, t2>::get_front_priority() const
{
    // returns the priority field of the root element
    return heapArray[1].priority;
}

template <class t1, class t2>
t1 priorityQ<t1, t2>::get_front_key() const
{
    // returns the key field of the root element
    return heapArray[1].key;
}

template <class t1, class t2>
bool priorityQ<t1, t2>::isEmpty() const
{
    // returns true if there is nothing in the priority queue
    // and false otherwise

    return (heapArray.size() <= 1) ? true : false;
}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleUp(std::size_t index)
{
    // function that performs the standard bubble up procedure, 
    // compute the parent index (using the index parameter) and compare the parent and child’s 
    // value fields, and swap if necessary, and continue up the tree until you cannot bubble
    // up any further
    /*
    FUNCTION_IDENTIFIER: This function is called inside of increaseKey. Since increaseKey updates a merc's
    score, this function is called to adjust the merc within the heapArray and itemToPQ priority queue to
    make sure that they are both still in maxheap order. bubbleUp will see if the current merc's score
    is greater than its parent. If it is, it will switch then recurse until it is not the case.
    Return Value: recurse
    */

    // Base case: root element
    if (index <= 1)
    {
        return;
    }

    // Parent element index
    size_t parentIndex = index / 2;

    // If the current element's priority is greater than its parent's priority, swap them
    if (heapArray[index].priority > heapArray[parentIndex].priority)
    {
        // Update itemToPQ with new indices
        itemToPQ[heapArray[index].key] = parentIndex;
        itemToPQ[heapArray[parentIndex].key] = index;

        // Swap elements in heapArray
        std::swap(heapArray[index], heapArray[parentIndex]);

        // Recursively call bubbleUp on parent index
        bubbleUp(parentIndex);
    }

}

template <class t1, class t2>
void priorityQ<t1, t2>::bubbleDown(std::size_t index)
{
    // function that performs the standard bubble down procedure, using the parameter index, 
    // compute the left and right children indices and compare their value fields and swap 
    // the parent with the correct child and continue until you cannot bubble down any further
    // Used when doing a popfront
    /*
    FUNCTION_IDENTIFIER: This function is called inside of pop_front. Since pop_front overwrites the root
    element with the last as a way of deleting it, bubbleDown will move the new element at root down the
    maxheap tree, comparing it to its children to find the place in which it belongs.
    Return Value: recurse
    */
    size_t leftChild = 2 * index;
    size_t rightChild = 2 * index + 1;

    // Check if node has any children
    if (leftChild >= heapArray.size())
    {
        return;
    }

    size_t maxChildIndex = leftChild;
    if (rightChild < heapArray.size() && heapArray[rightChild].priority > heapArray[leftChild].priority)
    {
        maxChildIndex = rightChild;
    }

    // Swap with child if necessary
    if (heapArray[maxChildIndex].priority > heapArray[index].priority)
    {
        // Update itemToPQ map
        itemToPQ[heapArray[index].key] = maxChildIndex;
        itemToPQ[heapArray[maxChildIndex].key] = index;

        // Swap elements
        std::swap(heapArray[index], heapArray[maxChildIndex]);

        // Recursively call
        bubbleDown(maxChildIndex);
    }
    
}