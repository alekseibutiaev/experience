#include "../treenode/treenode.h"

int main() {

	TreeNode* root = tn::create_node(50);
	tn::insert_node(root, 30);
	tn::insert_node(root, 70);
	tn::insert_node(root, 40);
	tn::insert_node(root, 80);
	tn::insert_node(root, 25);
	return 0;
}
