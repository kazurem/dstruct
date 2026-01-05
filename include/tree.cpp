#include <algorithm>
#include <array>
#include <queue>
#include <stack>
#include <list>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <format>
#include <vector>
#include <concepts>


/*
Things learned:
- requires expression (ask the compiler whether a certain piece of code works or not)
It returns a bool
Example:
requires (int i) { ++i; } 		(Returns true since increment operation is defined for int)

This is usually used alongside templates
Example:
template<typename Type>
bool test_type() { requires (T var) { var++; }}

test_type<int> -> true
test_type<bool> -> ??

- if constexpr ()
To evaluate if conditions at compile time.



const Ptr* != Ptr const*
Pointer to Const (const Tree*): You cannot change the data the pointer points to. This is what you want for a "const getter."
Const Pointer (Tree* const): You can change the data, but you cannot point the pointer to a different address.

*/


/**
 * @brief Tree data structure
 * 
 * @tparam T 
 */
template<typename Type, size_t max_degree, template<typename...> class Container = std::list>
class Tree {
	using TreePtr = Tree<Type, max_degree, Container>*;
	using TreeConstPtr = const TreePtr;
	using TreeUniquePtr = std::unique_ptr<Tree<Type, max_degree, Container>>;
	using TreeUnqiuePtrList = Container<TreeUniquePtr>;

	public:
		/**
		 * @brief Default Constructor for Tree class
		 * 
		 * @param value the value that the root node stores.
		 * @param parent pointer to the parent of the root node (default is nullptr)
		 * @param reserved size of the reserved memory of the underlying data structure (default is 10 Trees)
		 */
		Tree(Type value = Type(), TreePtr parent = nullptr): value_(value), parent_(parent) {}


		virtual ~Tree() = default;
		Tree(const Tree&) = delete;		
		auto operator=(const Tree&) -> Tree& = delete;
		Tree(Tree&&) = default;
		auto operator=(Tree&&) -> Tree& = default;

		/**
		 * @brief Getter function for the value that the node stores (overload with no parameters)
		 * 
		 * @return T 
		 */
		auto value() const -> Type { return value_; }

		/**
		 * @brief Getter function for the value that the node stores (overload with 1 parameter)
		 * 
		 * @param new_value 
		 */
		auto value(Type new_value) -> void { value_ = new_value; }
		
		/**
		 * @brief Getter function for tree (overload with no parameters)
		 * 
		 * @return Tree<T>* 
		 */
		auto parent() const -> TreePtr { return parent_; }

		/**
		 * @brief Setter function for parent (overload with 1 param)
		 * 
		 * @param new_parent 
		 */
		auto parent(TreePtr new_parent) -> void { parent_ = new_parent; }

		/**
		 * @brief Const version of the children getter
		 * 
		 * @return const TreeList& 
		 */
		auto children() const -> const TreeUnqiuePtrList& { return children_; }

		/**
		 * @brief Non-Const version of the children_ getter
		 * 
		 * @return TreeList& 
		 */
		auto children() -> TreeUnqiuePtrList& { return children_; }

		/**
		 * @brief Returns the degree of the node
		 * 
		 * @return size_t 
		 */
		auto degree() const -> size_t { return children().size(); }


		// * Suggestion: Use C++23's "Deduced this" to write the logic for operator[] only once.
		// * Another way of doing it is using const_cast but it may be ugly
		/**
		 * @brief Returns the pointer to the child at the given index (0 based indexing)
		 * 
		 * @param idx index of the child
		 * @return Tree<T>* pointer to the child
		 */
		 auto operator[](size_t child_idx) -> TreePtr {
			if constexpr (requires { children()[child_idx]; }) {
				return children()[child_idx].get();
			} 	

			auto iter = children().begin();
			std::advance(iter, child_idx);
			return iter->get();
		 }

		/**
		 * @brief Returns the pointer to the child at the given index (0 based indexing)
		 * 
		 * @param idx index of the child
		 * @return const Tree<T>* pointer to the child
		 */
		auto operator[](size_t child_idx) const -> TreeConstPtr {
			if constexpr (requires { children()[child_idx]; }) {
				return children()[child_idx].get();
			}
			auto iter = children().begin();
			std::advance(iter, child_idx);
			return iter->get();
		}

		/**
		* @brief Returns the left child (index 0). Only available for Binary Trees.
		*/
		auto left() -> TreePtr requires (max_degree == 2) {
			if (degree() < 1) return nullptr;
			return (*this)[0];
		}

		auto left() const -> TreeConstPtr requires (max_degree == 2) {
			if (degree() < 1) return nullptr;
			return (*this)[0];
		}


		/**
		* @brief Returns the right child (index 1). Only available for Binary Trees.
		*/
		auto right() -> TreePtr requires (max_degree == 2) {
			if (degree() < 2) return nullptr;
			return (*this)[1];
		}

		auto right() const -> TreeConstPtr requires (max_degree == 2) {
			if (degree() < 2) return nullptr;
			return (*this)[1];
		}


		/**
		 * @brief Checks if node is the root node or not
		 * 
		 * @return true if node is root (parent is null)
		 * @return false  if node is not root (parent is not null)
		 */
		auto is_root() const -> bool { return (parent() == nullptr); }

		/**
		 * @brief Checks if node is leaf node or not
		 * 
		 * @return true if node is lead node (degree == 0)
		 * @return false if node is not leaf (degree > 0)
		 */
		auto is_leaf() const -> bool { return (degree() == 0); }

		/**
		 * @brief Returns the number of nodes in the tree
		 */
		auto size() const -> size_t {
			size_t size = 1;
			for(const auto& child : children()) size += child->size();
			return size;
		}

		//find the maximum depth
		auto height() const -> size_t {
			size_t tree_height = 0;
			for(const auto& child : children()) {
				tree_height = std::max(tree_height, 1 + child->height());
			}
			return tree_height;
		}


		/**
		 * @brief Creates(in heap) and adds a child to the tree
		 * 
		 * @param value The value the new child will store
		 */
		auto add_child(Type value) -> void { 
			if(degree() > max_degree) {
				throw std::runtime_error(std::format("Node already has max_degree ({}) children", max_degree));
			}
			children().push_back(std::make_unique<Tree<Type, max_degree, Container>>(value, this)); 
		}

		/**
		 * @brief Attaches a already existing tree to the current tree
		 * 
		 * @param tree pointer to the already existing tree
		 */
		auto attach(TreePtr tree) -> void {
			if(not tree) return;
			if(not tree->is_root()) tree->detach();
			children().push_back(tree);
			tree->parent(this);
		}

		/**
		 * @brief Deattaches the child subtree from the current tree
		 * 
		 */
		auto detach() -> void {
			if(is_root()) return;
			auto& pchildren = parent()->children();
			const auto& erase_range = std::ranges::remove(pchildren, this); // ! might be problematic
			pchildren.erase(erase_range.begin(), erase_range.end());
			parent(nullptr);
		}


		/**
		 * @brief Prints the tree using BFS (Breadth-First Search)
		 * 
		 */
		auto bfs_walk()-> void {
			std::queue<TreePtr> queue;
			queue.push(this);

			while(not queue.empty()) {
				auto curr = queue.front();
				queue.pop();
				std::cout << curr->value() << " ";
				for(const auto& child : curr->children()) queue.push(child.get());
			}
		}

		/**
		 * @brief Prints the tree using DFS (Depth First Search)
		 * 
		 */
		auto dfs_walk() -> void {
			std::cout << value() << " ";
			for(const auto& child : children()) {
				child->dfs_walk();
			}
		}

		auto inorder_walk(TreePtr root) -> void requires (max_degree == 2) {
			if(not root) return;
			inorder_walk(root->left());
			std::cout << root->value() << " ";
			inorder_walk(root->right());
		}

		auto postorder_walk(TreePtr root) -> void requires (max_degree == 2) {
			if(not root) return;
			inorder_walk(root->left());
			inorder_walk(root->right());
			std::cout << root->value() << " ";
		}

		auto preorder_walk(TreePtr root) -> void requires (max_degree == 2) {
			if(not root) return;
			std::cout << root->value() << " ";
			inorder_walk(root->left());
			inorder_walk(root->right());
		}

	private:
		/**
		 * @brief The value that the root node of the tree stores
		 */
		Type value_;

		
		/**
		* @brief The pointer to the parent of the root node of the tree.
		*/
		TreePtr parent_;

		/**
		 * @brief List of children
		 */
		TreeUnqiuePtrList children_;
};

template<typename Type, size_t max_degree = 2, template<typename ...> class Container = std::vector>
using BinaryTree = Tree<Type, max_degree, Container>;

auto main() -> int {
	BinaryTree<int> bt(5);
	bt.add_child(2);
	bt.add_child(7);
	bt.left()->add_child(1);
	bt.left()->add_child(3);
	bt.right()->add_child(6);
	bt.right()->add_child(8);

	// bt.preorder_walk(&bt);
	std::cout << bt.height() << "\n";
}
