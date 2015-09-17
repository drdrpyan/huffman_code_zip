#ifndef ___BGM__DATA_STRUCTURE__TREE_NODE__H___
#define ___BGM__DATA_STRUCTURE__TREE_NODE__H___

#include "BGM_Node.h"

namespace BGM
{
	namespace DataStructure
	{
		template <typename T, typename NodeType>
		class Tree;

		template <typename T>
		class TreeNode : public Node<T>
		{
			friend class Tree<T, TreeNode<T> >;
		private:
		public:
			TreeNode();
			TreeNode(const T& data);
			TreeNode(const TreeNode<T>& treeNode);
		};
	}
}

#endif


#ifndef ___BGM__DATA_STRUCTURE__TREE_NODE__IMPLEMENT___
#define ___BGM__DATA_STRUCTURE__TREE_NODE__IMPLEMENT___

namespace BGM
{
	namespace DataStructure
	{
		template <typename T>
		TreeNode<T>::TreeNode() : Node<T>()
		{
		}

		template <typename T>
		TreeNode<T>::TreeNode(const T& data) : Node<T>(data)
		{
		}

		template <typename T>
		TreeNode<T>::TreeNode(const TreeNode<T>& treeNode) : Node<T>(treeNode)
		{
		}
	}
}

#endif
