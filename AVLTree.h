#pragma once
#include<vector>
#include <stdexcept>
using std::runtime_error;
using namespace std;
const int MIN_BALANCED_FACTOR = -1;
const int MAX_BALANCED_FACTOR = 1;

// AVL Node Class
template <class K, class V>
class AVLTreeNode{
public:
	// parent - pointer to parent
	AVLTreeNode* parent;
	// left - pointer to left child
	AVLTreeNode* left;
	// right - pointer to right child
	AVLTreeNode* right;
	// key - node's key
	K key;
	// value - node's value
	V value;
	// height - node's height
	unsigned int height;

	// Desc:: Constructor
	// Post:: Set key and value to given parameters.
	AVLTreeNode(K new_key, V new_value){
		parent = nullptr;
		left = nullptr;
		right = nullptr;
		key = new_key;
		value = new_value;
		height = 0;
	}
};

// AVL Tree class
template <class K, class V>
class AVLTree{
private:
	// Root of the AVL tree.
	AVLTreeNode<K, V>* root;

	// Number of nodes in the tree.
	unsigned int number_of_nodes;

	// Desc:: Helper function for destructor.
	// Post:: De-allocate all nodes in the tree.
	void delete_node(AVLTreeNode<K, V>* node);

	// Desc:: Copy all-nodes of the other tree.
	// Post:: Return a new root of the tree with copy nodes.
	AVLTreeNode<K, V>* copy_tree(AVLTreeNode<K, V>* original_node);

	// Desc:: Helper function for values method.
	// Post:: Traverse the tree in pre-order and push the key to the vector.
	void keys_helper(AVLTreeNode<K, V>* node, vector<K>& result) const;

	// Desc:: Helper function for values method.
	// Post:: Traverse the tree in pre-order and push the value to the vector.
	void values_helper(AVLTreeNode<K, V>* node, vector<V>& result) const;

	// Desc:: Search the node by key.
	// Post:: Return a pointer of a node which has given key if it is found.
	// If it is not found, return null pointer.
	AVLTreeNode<K, V>* search_node(AVLTreeNode<K, V>* node, const K& target) const;

	// Desc:: Helper method for insert.
	// Post:: Return a new node of the tree.
	// If the key is found, return a null pointer.
	AVLTreeNode<K, V>* insert_helper(K new_key, V new_value);

	// Desc:: Calculate the balanced factor of a specific node.
	// Post:: Return the balanced factor of the node.
	// Height of right sub-tree - height of left sub-tree.
	int get_balanced_factor(AVLTreeNode<K, V>* node) const;

	// Desc:: Set the parent pointer for the node.
	// Post:: The node has a parent if it is not a nullptr.
	void set_parent(AVLTreeNode<K, V>* node, AVLTreeNode<K, V>* parent);

	// Desc:: Replace the child pointer by the key magnitude.
	// Post:: The node has a child either left or right by key magnitude.
	void replace_node(AVLTreeNode<K, V>* node, AVLTreeNode<K, V>* new_node);

	// Desc:: Update the height of node.
	// Post:: The node has a height which has maximum value
	// of left sub-tree height and right sub-tree height + 1.
	void update_height(AVLTreeNode<K, V>* node);

	// Desc:: Get the height of the node.
	// Post:: Return the height of the node.
	// If the node is a null pointer, return 0.
	int get_height(AVLTreeNode<K, V>* node) const;

	// Desc:: Execute the left rotation.
	void left_rotation(AVLTreeNode<K, V>* node);

	// Desc:: Execute the right rotation.
	void right_rotation(AVLTreeNode<K, V>* node);

	// Desc:: Update the AVL tree from the specific node after insersion.
	// Post:: Make the AVL tree balanced if it is not balanced.
	void update_tree_insert(AVLTreeNode<K, V>* node);

	// Desc:: Update the AVL tree from the specific node after remove.
	// Post:: Make the AVL tree balanced if it is not balanced.
	void update_tree_remove(AVLTreeNode<K, V>* node);

	// Desc:: Re-balance the tree for the insertion.
	// Post:: Exceute roations based on the balanced factor.
	void re_balance(AVLTreeNode<K, V>* node);

	// Desc:: Get the predecessor of the sub-tree from the node.
	// Pre:: Pass the left child of the node you are looking.
	// And the node should have two children.
	// Post:: Return the pointer of predecessor.
	AVLTreeNode<K, V>* get_predecessor(AVLTreeNode<K, V>* node) const;
public:

	// Desc:: Default constructor
	// Post:: Create a empty tree.
	AVLTree();

	// Desc:: Copy constructor
	// Post:: Create a deep copy of given tree.
	AVLTree(const AVLTree<K, V>& other);

	// Desc:: Destructor
	// Post:: All nodes in dynamic memory will be de-allocated.
	~AVLTree();

	// Desc:: The assignment operator overloading.
	// Post:: Return a deep copy of AVLTree.
	AVLTree<K, V>& operator=(const AVLTree<K, V>& other);

	// Desc:: Search the value by key and return it in the tree.
	// Pre:: The key is already in the tree.
	// Post:: Return the value if it is in the tree. Throw an error if it is not.
	V search(const K& target) const;

	// Desc:: Return all keys in ascending by key in the tree. 
	// Post:: If the tree is empty, return an empty vector.
	vector<K> keys() const;

	// Desc:: Return all values in ascending by key in the tree. 
	// Post:: If the tree is empty, return an empty vector.
	vector<V> values() const;

	// Desc:: Return number of nodes in the tree.
	unsigned int size() const;

	// Desc:: Insert a new node to the tree.
	// Post:: Return true if the new node is inserted.
	// Return false if the key is already in the tree.
	bool insert(K new_key, V new_value);

	// // Desc:: Remove a node which has a given key from the tree.
	// // Post:: If deletion is done, return true.
	// // Return false, if the given key is not found.
	bool remove(K target_key);

	// Desc::Returns a pointer to the tree's root node.
	void* getRoot() const { return root; };
};

// Desc:: Helper function for destructor.
template <class K, class V> 
void AVLTree<K, V>::delete_node(AVLTreeNode<K, V>* node){
	// If the node is a null pointer, stop.
	if (node == nullptr){
		return;
	}
	// Delete for left sub-tree.
	delete_node(node->left);
	// Delete for right sub-tree.
	delete_node(node->right);
	// Delete node memory.
	delete node;
}

// Desc:: Copy all-nodes of the other tree.
template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::copy_tree(AVLTreeNode<K, V>* original_node){
	// If the node is a null pointer, return nullptr.
	if (original_node == nullptr){
		return nullptr;
	}

	// Make a new copy of node in dynamic memory.
	AVLTreeNode<K, V>* new_node = new AVLTreeNode<K, V>(original_node->key, original_node->value);
	new_node->height = original_node->height;

	// Copy the left sub-tree and set the parent.
	new_node->left = copy_tree(original_node->left);
	set_parent(new_node->left, new_node);
	
	// Copy the right sub-tree and set the parent.
	new_node->right = copy_tree(original_node->right);
	set_parent(new_node->right, new_node);

	return new_node;
}

// Desc:: Set the parent pointer to the node.
template <class K, class V>
void AVLTree<K, V>::set_parent(AVLTreeNode<K, V>* node, AVLTreeNode<K, V>* parent){
	if (node != nullptr){
		node->parent = parent; 
	}
}

// Desc:: Replace the nodes by the other node.
template <class K, class V>
void AVLTree<K, V>::replace_node(AVLTreeNode<K, V>* node, AVLTreeNode<K, V>* new_node){
	AVLTreeNode<K, V>* parent = node->parent;
	
	// When node is a root.
	if (node == root){
		root = new_node;
	}
	// Node is a left child.
	else if (parent->left == node){
		parent->left = new_node;
	}
	// Node is a right child.
	else{
		parent->right = new_node;
	}
	set_parent(new_node, parent);
}

// Desc:: Helper function for values method.
template <class K, class V>
void AVLTree<K, V>::keys_helper(AVLTreeNode<K, V>* node, vector<K>& result)const{
	// If the node is a null pointer, stop.
	if (node == nullptr){
		return;
	}
	
	// Traverse for left sub-tree.
	keys_helper(node->left, result);
	// Push back the key to the vector.
	result.push_back(node->key);
	// Traverse for right sub-tree.
	keys_helper(node->right, result);
}

// Desc:: Helper function for values method.
template <class K, class V>
void AVLTree<K, V>::values_helper(AVLTreeNode<K, V>* node, vector<V>& result) const{
	// If the node is a null pointer, stop.
	if (node == nullptr){
		return;
	}

	// Traverse for left sub-tree.
	values_helper(node->left, result);
	// Push back the value to the vector.
	result.push_back(node->value);
	// Traverse for right sub-tree.
	values_helper(node->right, result);
}

// Desc:: Search the node by key.
template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::search_node(AVLTreeNode<K, V>* node, const K& target) const{
	// If the node is a null pointer or the target, stop.
	if (node == nullptr || node->key == target){
		return node;
	}

	// Search the tree based on the magnitude of the tree.
	if (node->key > target){
		return search_node(node->left, target);
	}else{
		return search_node(node->right, target);
	}
}

// Desc:: Set the height of node.
template <class K, class V>
void AVLTree<K, V>::update_height(AVLTreeNode<K, V>* node){
	if (node == nullptr){
		return;
	}

	if (get_height(node->left) > get_height(node->right)){
		node->height = get_height(node->left) + 1;
	}else{
		node->height = get_height(node->right) + 1;
	}
}

// Desc:: Helper method for insert.
template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::insert_helper(K new_key, V new_value){
	AVLTreeNode<K, V>* parent = nullptr;
	AVLTreeNode<K, V>* node = root;

	// Traverse the tree.
	while (node != nullptr){
		parent = node;
		if (node->key == new_key){
			return nullptr;	
		}else if (node->key > new_key){
			node = node->left;
		}else{
			node = node->right;
		}
	}

	// Make a new node.
	AVLTreeNode<K, V>* new_node = new AVLTreeNode<K, V>(new_key, new_value);
	
	// Update the parent and height.
	set_parent(new_node, parent);
	update_height(new_node);

	// Insert the new node.
	if (parent == nullptr){
		root = new_node;
	}else if (parent->key > new_key){
		parent->left = new_node;
	}else{
		parent->right = new_node;
	}
	return new_node;
}

// Desc:: Default constructor
template <class K, class V>
AVLTree<K, V>::AVLTree(){
	root = nullptr;
	number_of_nodes = 0;
}

// Desc:: Copy constructor
template <class K, class V>
AVLTree<K, V>::AVLTree(const AVLTree<K, V>& other){
	root = copy_tree(other.root);
	number_of_nodes = other.number_of_nodes;
}

// Desc:: Destructor
template <class K, class V>
AVLTree<K, V>::~AVLTree(){
	delete_node(root);
}

// Desc:: The assignment operator overloading.
template <class K, class V>
AVLTree<K, V>& AVLTree<K, V>::operator=(const AVLTree<K, V>& other){
	// If the other is not itself.
	if (this != &other){
		delete_node(root);
		root = copy_tree(other.root);
		number_of_nodes = other.number_of_nodes;
	}
	return *this;
}

// Desc:: Search the value by key and return it in the tree.
template <class K, class V>
V AVLTree<K, V>::search(const K& target) const{
	// Search the node.
	AVLTreeNode<K, V>* node = search_node(root, target);
	
	// If key is not found, thorow an error.
	if (node == nullptr){
		throw runtime_error("Key is not found.");
	}else{
		return node->value;
	}
}

// Desc:: Return all keys in ascending by key in the tree. 
template <class K, class V>
vector<K> AVLTree<K, V>::keys() const{
	vector<K> result;
	keys_helper(root, result);
	return result;
}

// Desc:: Return all values in ascending by key in the tree.
template <class K, class V>
vector<V> AVLTree<K, V>::values() const{
	vector<V> result;
	values_helper(root, result);
	return result;
}

// Desc:: Return number of nodes in the tree.
template <class K, class V>
unsigned int AVLTree<K, V>::size() const{
	return number_of_nodes;
}

// Desc:: Insert a new node to the tree.
template <class K, class V>
bool AVLTree<K, V>::insert(K new_key, V new_value){
	AVLTreeNode<K, V>* new_node = insert_helper(new_key, new_value);
	// If there is a same key already, return false
	if (new_node == nullptr){
		return false;	
	}

	// Re-balance the tree.
	update_tree_insert(new_node);
	
	// Increment a size.
	number_of_nodes++;
	return true;
}

// Desc:: Remove a node which has a given key from the tree.
template <class K, class V>
bool AVLTree<K, V>::remove(K target_key){
	AVLTreeNode<K, V>* delete_node = search_node(root, target_key);

	// If the delete node is a null pointer, the key is not found in the tree
	if (delete_node == nullptr){
		return false;
	}
	
	// The delete node is a leaf.
	if (delete_node->left == nullptr && delete_node->right == nullptr){
		replace_node(delete_node, nullptr);
	}

	// The node has a left node.
	else if (delete_node->right == nullptr){
		replace_node(delete_node, delete_node->left);
	}

	// The node has a right child.
	else if (delete_node->left == nullptr){
		replace_node(delete_node, delete_node->right);
	}

	// The node has two children.
	else{
		AVLTreeNode<K, V>* predecesor = get_predecessor(delete_node->left);
		replace_node(predecesor, predecesor->left);
		delete_node->key = predecesor->key;
		delete_node->value = predecesor->value;
		delete_node = predecesor;
	}
	
	update_tree_remove(delete_node);
	delete delete_node;
	// Decrement the size.
	number_of_nodes--;
	return true;
}

// Desc:: Get the height of the node.
template <class K, class V>
int AVLTree<K, V>::get_height(AVLTreeNode<K, V>* node) const{
	if (node == nullptr){
		return -1;
	}else{
		return node->height;	
	}
}

// Desc:: Calculate the balanced factor of a specific node.
template <class K, class V>
int AVLTree<K, V>::get_balanced_factor(AVLTreeNode<K, V>* node) const{
	if (node == nullptr){
		return 0;
	}
	// Calculate the balanced factor.
	return get_height(node->right) - get_height(node->left);
}

// Desc:: Execute the left rotation.
template <class K, class V>
void AVLTree<K, V>::left_rotation(AVLTreeNode<K, V>* node){
	// Right child of node.
	AVLTreeNode<K, V>* right_child = node->right;
	
	// The left child of right child of the node.
	AVLTreeNode<K, V>* left_grand_child = right_child->left;
	
	// Update the relations.
	node->right = left_grand_child;
	set_parent(left_grand_child, node);
	set_parent(right_child, node->parent);

	// When the node is root.
	if (node->parent == nullptr){
		root = right_child;
	}else if (node == node->parent->left){
		node->parent->left = right_child;
	}else{
		node->parent->right = right_child;
	}

	right_child->left = node;
	set_parent(node, right_child);

	// Update the height.
	update_height(node);
	update_height(right_child);
}

// Desc:: Execute the right rotation.
template <class K, class V>
void AVLTree<K, V>::right_rotation(AVLTreeNode<K, V>* node){
	// Left child of node.
	AVLTreeNode<K, V>* left_child = node->left;
	// The right child of left child of the node.
	AVLTreeNode<K, V>* right_grand_child = left_child->right;

	// Update the relations.
	node->left = right_grand_child;
	set_parent(right_grand_child, node);
	set_parent(left_child, node->parent);

	// When the node is root.
	if (node->parent == nullptr){
		root = left_child;
	}else if (node == node->parent->left){
		node->parent->left = left_child;
	}else{
		node->parent->right = left_child;
	}

	left_child->right = node;
	set_parent(node, left_child);

	// Update the height.
	update_height(node);
	update_height(left_child);
}

// Desc:: Update the AVL tree from the specific node.
template<class K, class V>
void AVLTree<K, V>::update_tree_insert(AVLTreeNode<K, V>* node){
	// Get the balanced factor.
	int balanced_factor = get_balanced_factor(node);
	
	// Check the balanced factor when the tree is un-balanced or not.
	// After finishing re-balance, finish updating.
	if (MIN_BALANCED_FACTOR > balanced_factor || MAX_BALANCED_FACTOR < balanced_factor){
		re_balance(node);
		return;
	}
	
	// Check whether the node is a root or not.
	if (node->parent != nullptr){
		// Update the height of the parent node.
		update_height(node->parent);
		if (get_balanced_factor(node->parent) != 0){
			update_tree_insert(node->parent);	
		}
	}
}

// Desc:: Update the AVL tree from the specific node.
template<class K, class V>
void AVLTree<K, V>::update_tree_remove(AVLTreeNode<K, V>* node){
	// Get the balanced factor.
	int balanced_factor = get_balanced_factor(node);
	
	// Check the balanced factor when the tree is un-balanced or not.
	// After finishing re-balance, finish updating.
	if (MIN_BALANCED_FACTOR > balanced_factor || MAX_BALANCED_FACTOR < balanced_factor){
		re_balance(node);
	}
	
	// Check whether the node is a root or not.
	if (node->parent != nullptr){
		// Update the height of the parent node.
		update_height(node->parent);
		update_tree_remove(node->parent);
	}
}

// Desc:: Re-balance the tree.
template<class K, class V>
void AVLTree<K, V>::re_balance(AVLTreeNode<K, V>* node){
	// Balanced factor
	// Height of right sub-tree - Height of left sub-tree
	// If this is greater than 0, it menas Right Heavy.
	// If this is less than 0, it means Left Heavy.

	// Right Heavy.
	if (get_balanced_factor(node) > 0){
		// Right Heavy.
		// RR case.
		if (get_balanced_factor(node->right) >= 0){
			// Single left rotation
			left_rotation(node);
		}
		// Left Heavy.
		// RL case.
		else{
			right_rotation(node->right);
			left_rotation(node);
		}
	}
	
	// Left Heavy.
	else if (get_balanced_factor(node) < 0){
		// Left Heavy.
		// LL case.
		if (get_balanced_factor(node->left) <= 0){
			right_rotation(node);
		}
		// Right Heavey.
		// LR case.
		else{
			left_rotation(node->left);
			right_rotation(node);
		}
	}
}

// Desc:: Get the predecessor of the sub-tree from the node.
template <class K, class V>
AVLTreeNode<K, V>* AVLTree<K, V>::get_predecessor(AVLTreeNode<K, V>* node) const{
	if (node->right == nullptr){
		return node;
	}
	return get_predecessor(node->right);
}