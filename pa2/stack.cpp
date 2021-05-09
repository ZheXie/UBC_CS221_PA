/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 */

/**
 * Adds the parameter object to the top of the Stack. 
 *
 * @note This function must be O(1)!
 *
 * @param newItem The object to be added to the Stack.
 */
template<class T>
void Stack<T>::push(T newItem)
{
    /**
     * @todo Your code here!
     */
    myStack.pushR(newItem);
}

/**
 * Removes the object on top of the Stack, and returns it. 
 * You may assume this function
 * is only called when the Stack is not empty.
 *
 * @note This function must be O(1)!
 *
 * @return The element that used to be at the top of the Stack.
 */
template <class T>
T Stack<T>::pop()
{
    /**
     * @todo Your code here! 
     */
    return myStack.popR();
}

/**
 * Finds the object on top of the Stack, and returns it to the caller.
 * Unlike pop(), this operation does not alter the Stack itself. 
 * You may assume this function is only
 * called when the Stack is not empty.
 *
 * @return The value of the element at the top of the Stack.
 */
template <class T>
T Stack<T>::peek()
{
    /**
     * @todo Your code here! 
     */
    return myStack.peekR();
}

/**
 * Determines if the Stack is empty.
 *
 * @note This function must be O(1)! 
 *
 * @return Whether or not the stack is empty (bool).
 */
template <class T>
bool Stack<T>::isEmpty() const
{
    /**
     * @todo Your code here!
     */
    return myStack.isEmpty();
}
