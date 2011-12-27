#include "linked-list.h"
#include <iostream>

using namespace std;

template <class T>
class node2 {
	public:
		T data;
		node2<T> *list;
		bool isList;
		node2<T> *next;

		node2(T t) {
			data = t;
			list = 0;
			isList = false;
			next = 0;
		}

		node2(node2 *nodes) {
			isList = true;
			list = nodes;
			next = 0;
		}


		static void prepend(node2<T>** pHead, node2<T>* n) {
			n->next = *pHead;
			*pHead = n;
		}

		static void append(node2** pHead, node2* n) {
			node2 *head = *pHead, *last = 0;
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

		static node2* build_list(T* items, int count) {
			node2<T>* head = 0;
			for(int i = count-1; i >= 0; i--)
				prepend(&head, new node2<T>(items[i]));
			return head;
		}

		static node2* build_list(node2<T>** nodes, int count) {
			node2<T>* head = 0;
			for(int i = count-1; i >= 0; i--)
				prepend(&head, new node2<T>(nodes[i]));
			return head;
		}
};

template <class T>
ostream& operator << (ostream& o, const node2<T>* n) {
	o << '[';
	while(n) {
		if(n->isList)
			o << n->list;
		else
			o << n->data;
		n = n->next;
		if(n)
			o << ' ';
	}
	o << ']';
}

template<class T>
node2<T>* flatten(node2<T>* head, node2<T>** last = NULL) {
	node2<T>* n = head, *prev = NULL;

	while(n) {
		if(n->isList) {
			node2<T>* last;
			node2<T>* nf = flatten(n->list, &last);
			if(prev) {
				prev->next = nf;
			} else {
				head = nf;
			}
			prev = last;
			n = n->next;
		} else {
			prev = n;
			n = n->next;
		}
	}

	if(last) *last = prev;
	return head; 
}

typedef node2<int> inode;

int main() {
	int items[] = {2, 5, 3, 1, 4, 6}, items2[] = {1,9,1}, items3[] = {8,0};

	inode* n1 = inode::build_list(items, 6), *n2 = inode::build_list(items2, 3), *n3 = inode::build_list(items3, 2);

	inode* inodes[] = {n1, n2, n3};
	inode* n = inode::build_list(inodes, 3);

	cout << n << endl;
	cout << flatten(n) << endl;

	return 0;
}
