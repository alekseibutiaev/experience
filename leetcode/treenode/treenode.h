#pragma once


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(0), right() {}
};

namespace tn {
	TreeNode* create_node(int value = 0);
	TreeNode* insert_node(TreeNode* root, int value);
	void delete_node(TreeNode* root, int value);
	void delete_tree(TreeNode* root);
	TreeNode* find_node(TreeNode* root, int value);
	void print_tree(TreeNode* root);
}; /*namespace tn */
