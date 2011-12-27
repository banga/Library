#include "linked-list.h"
#include <iostream>

using namespace std;

typedef node<int> inode;

inode* find_k_from_last(inode* head, int k) {
	inode *n = head, *nk = head;
	while(k && nk) {
		nk = nk->next;
		k--;
	}

	if(k) return NULL;

	while(nk) {
		n = n->next;
		nk = nk->next;
	}

	return n;
}

/*
 * Rearrange list so that all even numbers are stored after odd numbers
 */
inode* rearrange_even_odd(inode* head) {
	inode* ne = NULL, *no = NULL, *nohead = NULL, *next;

	while(head) {
		next = head->next;
		int x = head->data;
		if(x & 1) {
			if(!nohead)
				nohead = head;
			if(no) {
				no->next = head;
				no = no->next;
			} else
				no = head;
		} else {
			head->next = ne;
			ne = head;
		}
		head = next;
	}

	if(no)
		no->next = ne;

	if(nohead)
		return nohead;
	return ne;
}

int main() {
	int a[] = {2,4,6,8,0};
	
	inode* na = inode::build_list(a, 5);

	cout << rearrange_even_odd(na);
	//cout << nb;
}
