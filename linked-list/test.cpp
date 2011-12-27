#include "linked-list.h"

typedef node<int> inode;

int main() {
	int items[] = {2, 5, 3, 1, 4, 6};

	inode* n = inode::build_list(items, 6);
	inode::print_list(n);

	return 0;
}
