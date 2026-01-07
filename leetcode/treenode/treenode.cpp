#include "TreeNode.h"

namespace {

	TreeNode* find_node_int(TreeNode* root, int value) {
		if (value < root->val ) {
			if (root->left)
				return find_node_int(root->left, value);
		}
		else if (value > root->val) {
			if (root->right)
				return find_node_int(root->right, value);
		}
		return root;
	}

} /* namespace */

namespace tn {
	TreeNode* create_node( int value ) {
		return new TreeNode(value);
	}

	TreeNode* insert_node(TreeNode* root, int value) {
		TreeNode* res = find_node_int(root, value);
		if (value < res->val)
			return res->left = create_node(value);
		else if (value > res->val)
			return res->right = create_node(value);
		return res;
	}

	void delete_node(TreeNode* root, int value) {

	}

	void delete_tree(TreeNode* root) {

	}


	TreeNode* find_node(TreeNode* root, int value) {
		TreeNode* res = find_node_int(root, value);
		return res->val == value ? res : 0;
	}

	void print_tree(TreeNode* root) {

	}
}; /*namespace tn */
