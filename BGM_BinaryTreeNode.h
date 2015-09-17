#ifndef ___BGM__BINARY_TREE_NODE__H___
#define ___BGM__BINARY_TREE_NODE__H___

#include "BGM_TreeNode.h"

namespace BGM
{
	namespace DataStructure
	{
		template <typename T>
		class BinaryTree;

		template <typename T>
		class BinaryTreeNode : public TreeNode<T>
		{
			friend class BinaryTree<T>;
		private:
			BinaryTreeNode *leftChild;
			BinaryTreeNode *rightChild;
		public:
			BinaryTreeNode();
			BinaryTreeNode(const T& data);
			BinaryTreeNode(BinaryTreeNode<T>* leftChld, const T& data, BinaryTreeNode<T>* rightChild);
			BinaryTreeNode(const BinaryTreeNode<T>& node);
			BinaryTreeNode* getLeftChildPtr();
			BinaryTreeNode* getRightChildPtr();
			bool isTerminal() const;
		};
	}
}
#endif


#ifndef ___BGM__BINARY_TREE_NODE__IMPLEMENT___
#define ___BGM__BINARY_TREE_NODE__IMPLEMENT___

namespace BGM
{
	namespace DataStructure
	{
		template <typename T>
		BinaryTreeNode<T>::BinaryTreeNode()
			: TreeNode<T>(), leftChild(0), rightChild(0)
		{
		}

		template <typename T>
		BinaryTreeNode<T>::BinaryTreeNode(const T& data)
			: TreeNode<T>(data), leftChild(0), rightChild(0)
		{
		}

		template <typename T>
		BinaryTreeNode<T>::BinaryTreeNode(BinaryTreeNode<T> *leftChild, const T& data, BinaryTreeNode<T> *rightChild)
			: TreeNode<T>(data), leftChild(leftChild), rightChild(rightChild)
		{
		}

		template <typename T>
		BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& node)
			: TreeNode<T>(node), leftChild(node.leftChild), rightChild(node.rightChild)
		{
		}

		template <typename T>
		BinaryTreeNode<T>* BinaryTreeNode<T>::getLeftChildPtr()
		{
			return leftChild;
		}

		template <typename T>
		BinaryTreeNode<T>* BinaryTreeNode<T>::getRightChildPtr()
		{
			return rightChild;
		}

		template <typename T>
		bool BinaryTreeNode<T>::isTerminal() const
		{
			return !(leftChild || rightChild);
		}
	}
}
#endif