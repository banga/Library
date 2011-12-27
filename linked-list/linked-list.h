#include <iostream>

template <class T>
class node {
	public:

	T data;
	node *next;

	node(T t) {
		data = t;
		next = 0;
	}

	static void prepend(node** pHead, node* n) {
		n->next = *pHead;
		*pHead = n;
	}

	static void append(node** pHead, node* n) {
		node *head = *pHead, *last = 0;
		while(head) {
			last = head;
			head = head->next;
		}

		if(last) {
			last->next = n;
		} else {
			*pHead = n;
		}
		n->next = 0;
	}

	static node* build_list(T* items, int count) {
		node<T>* head = 0;
		for(int i = count-1; i >= 0; i--)
			prepend(&head, new node<T>(items[i]));
		return head;
	}
};

template <class T>
std::ostream& operator << (std::ostream& o, node<T>* n) {
	o << '[';
	while(n) {
		o << n->data;
		n = n->next;
		if(n)
			o << ' ';
	}
	o << ']';
}
