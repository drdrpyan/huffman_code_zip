#ifndef ___BGM__DATA_STRUCTURE__BINARY_TREE__H___
#define ___BGM__DATA_STRUCTURE__BINARY_TREE__H___

#include "BGM_Tree.h"
#include "BGM_BinaryTreeNode.h"

namespace BGM
{
	namespace DataStructure
	{
		template <typename T>
		class BinaryTree : public Tree<T, BinaryTreeNode<T> >
		{
		protected:
			virtual BinaryTreeNode<T>* copy(BinaryTreeNode<T> *thatRootPtr);
			virtual void clear(BinaryTreeNode<T> *node);
		public:
			BinaryTree(BinaryTreeNode<T> *node = 0);
			BinaryTree(BinaryTree<T>& leftSubTree, T& rootData, BinaryTree<T>& rightSubTree);
			virtual void clear(void);
		};
	}
}

#endif


#ifndef ___BGM__DATA_STRUCTURE__BINARY_TREE__IMPLEMENT___
#define ___BGM__DATA_STRUCTURE__BINARY_TREE__IMPLEMENT___

namespace BGM
{
	namespace DataStructure
	{
		template <typename T>
		BinaryTree<T>::BinaryTree(BinaryTreeNode<T>* rootPtr) : Tree<T, BinaryTreeNode<T> >(rootPtr)
		{
		}

		template <typename T>
		BinaryTree<T>::BinaryTree(BinaryTree<T>& leftSubTree, T& rootData, BinaryTree<T>& rightSubTree)
		{

		}

		template <typename T>
		BinaryTreeNode<T>* BinaryTree<T>::copy(BinaryTreeNode<T> *thatRootPtr)
		{
			if(!thatRootPtr)
				return 0;

			return new BinaryTreeNode<T>(copy(thatRootPtr->leftChild), thatRootPtr->getData(), copy(thatRootPtr->rightChild));
		}

		template <typename T>
		void BinaryTree<T>::clear(BinaryTreeNode<T>* node)
		{
			if(!node)
				return;

			clear(node->leftChild);
			delete node->leftChild;
			clear(node->rightChild);
			delete node->rightChild;
		}

		template <typename T>
		void BinaryTree<T>::clear(void)
		{
			clear(this->getRootPtr());
		}
	}
}
#endif
