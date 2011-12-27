#include "linked-list.h"
#include <iostream>

using namespace std;

typedef node<int> inode;

inode* find_loop(inode* head) {
	inode *a = head, *b = head;

	if(!a->next) return NULL;
	a = a->next; b = b->next->next;

	while(a && b && b->next && a != b && a != b->next) {
		a = a->next;
		b = b->next->next;
	}

	if(a == b || a == b->next)
		return a;

	return NULL;
}

inode* find_Y(inode* na, inode* nb) {
	int la = 0, lb = 0;
	inode *n = na;
	while(n) {
		la++;
		n = n->next;
	}
	n = nb;
	while(n) {
		lb++;
		n = n->next;
	}

	if(la > lb) {
		while(la > lb) {
			la--;
			na = na->next;
		}
	} else {
		while(lb > la) {
			lb--;
			nb = nb->next;
		}
	}

	while(na != nb) {
		na = na->next;
		nb = nb->next;
	}

	return na;
}

int main() {
	int a[] = {1,2,3,4,5,6,7,8,9}, b[] = {1,2,3};
	
	inode* na = inode::build_list(a, 9), *nb = inode::build_list(b, 3);

	nb->next->next->next = nb;
	inode* n = find_loop(nb);
	if(n)
		cout << n->data << endl;

	nb->next->next->next = na->next->next->next->next->next;
	cout << na << endl << nb << endl;
	cout << find_Y(na, nb) << endl;
	//cout << nb;
}
