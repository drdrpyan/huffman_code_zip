#ifndef ___BGM__DATA_STRUCTURE__TREE__H___
#define ___BGM__DATA_STRUCTURE__TREE__H___

#include "BGM_TreeNode.h"
#include <stdexcept>

namespace BGM
{
	namespace DataStructure
	{
		template <typename T, typename NodeType = TreeNode<T> >
		class Tree
		{
		private:
		protected:
			NodeType *root;
			virtual NodeType* copy(NodeType *thatRoot) = 0;
		public:
			Tree(NodeType *rootPtr = 0);
			Tree(const Tree& tree);
			virtual void clear();
			virtual void clear(NodeType *node) = 0;
			bool isEmpty() const;
			const T& getRootData() const;
			T& getRootData();
			NodeType* getRootPtr();
		};
	}
}

#endif


#ifndef ___BGM__DATA_STRUCTURE__TREE__IMPLEMENT___
#define ___BGM__DATA_STRUCTURE__TREE__IMPLEMENT___

namespace BGM
{
	namespace DataStructure
	{
		template <typename T, typename NodeType>
		Tree<T, NodeType>::Tree(NodeType *nodePtr) : root(nodePtr)
		{
		}

		template <typename T, typename NodeType>
		Tree<T, NodeType>::Tree(const Tree& tree)
		{
			root = copy(tree.root);
		}

		template <typename T, typename NodeType>
		void Tree<T, NodeType>::clear()
		{
			clear(root);
		}

		template <typename T, typename NodeType>
		bool Tree<T, NodeType>::isEmpty() const
		{
			return !root;
		}

		template <typename T, typename NodeType>
		const T& Tree<T, NodeType>::getRootData() const
		{
			if(isEmpty)
				throw runtime_error("You accessed empty tree.");
			return root->getData();
		}

		template <typename T, typename NodeType>
		T& Tree<T, NodeType>::getRootData()
		{
			if(isEmpty)
				throw runtime_error("You accessed empty tree.");
			return root->getData();
		}

		template <typename T, typename NodeType>
		NodeType* Tree<T, NodeType>::getRootPtr()
		{
			return root;
		}
	}
}

#endif
