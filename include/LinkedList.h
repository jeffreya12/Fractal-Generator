#include <iostream>
#include <stdexcept>
using namespace std;

/* Linked List for a variable type E
	Clases defined: Node and LinkedList
 */
template <typename E>
class Node{
	public:
		E element;
		Node<E> * next;

		Node(E pElement, Node<E>* pNext = NULL){
		    element = pElement;
		    next = pNext;
		}

		Node(Node<E>* pNext = NULL){
		    next = pNext;
		}
};

template <typename E>
class LinkedList{
	private:
		Node<E>* head;
		Node<E>* tail;
		Node<E>* current;
		int size;

	public:

		Node<E>* searchPrevious(Node<E>* pNode) {
		    if (current == head)
		          return NULL;

		    Node<E> *res = head;
		    while (res->next != current)
		        res = res->next;

		    return res;
		}

		LinkedList() {
		    head = tail = current = new Node<E>();
		    size = 0;
		}

		~LinkedList() {
		    clear();
		    delete head;
		}

		void insert(E pElement) {
		    current->next = new Node<E>(pElement, current->next);
		    if (current == tail)
		        tail = tail->next;

		    size++;
		}

		void append(E pElement) {
		    tail->next = new Node<E>(pElement);
		    tail = tail->next;
		    size++;
		}
		void clear() {
		    current = head;
		    while (head != NULL) {
		        head = head->next;
		        delete current;
		        current = head;
		    }
		    head = tail = current = new Node<E>();
		    size = 0;
		}

		E remove() throw (runtime_error) {
		    if (current->next == NULL)
		        throw runtime_error("No element to remove.");

		    E result = current->next->element;
		    Node<E> *temp = current->next;
		    current->next == current->next->next;
		    if (temp == tail)
		        tail = current;

		    delete temp;
		    size--;
		    return result;
		}


		E getElement() throw (runtime_error) {
		    if (current->next == NULL)
		        throw runtime_error("No element to get.");

		    return current->next->element;
		}

		void goToStart() {
		    current = head;
		}

		void goToEnd() {
		    current = tail;
		}

		void goToPos(int nPos) throw (runtime_error) {
		    if ((nPos < 0) || (nPos > size))
		        throw runtime_error("Index out of bounds");

		    current = head;
		    for (int i = 0; i < nPos; i++)
		        current = current->next;

		}

		void previous() {
		    if (current != head)
		        current = searchPrevious(current);
		}

		void next() {
		    if (current != tail)
		        current = current->next;
		}

		int getPos() {
		    int pos = 0;
		    Node<E>* temp = head;
		    while (temp != current) {
		        pos++;
		        temp = temp->next;
		    }
		    return pos;
		}

		int getSize() {
		    return size;
		}

		void print(){
			for(goToStart(); getPos() < size; next()){
				cout << getElement();
			}
		}

};

