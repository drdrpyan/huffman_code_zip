#ifndef ___BGM__DATA_STRUCTURE__NODE__H___
#define ___BGM__DATA_STRUCTURE__NODE__H___

namespace BGM
{
	namespace DataStructure
	{
		template <typename T>
		class Node
		{
		protected:
			T data;
		public:
			Node();
			Node(const T& data);
			Node(const Node& node);
			const T& getData() const;
			T& getData();
			void setData(const T& data);
			bool operator<(const Node<T>& node) const;
		};
	}
}

#endif

#ifndef ___BGM__DATA_STRUCTURE__NODE__IMPLEMENT___
#define ___BGM__DATA_STRUCTURE__NODE__IMPLEMENT___

using namespace std;

namespace BGM
{
	namespace DataStructure
	{
		template <typename T>
		Node<T>::Node()
		{
		}

		template <typename T>
		Node<T>::Node(const T& data) : data(data)
		{
		}

		template <typename T>
		Node<T>::Node(const Node& node) : data(node.data)
		{
		}

		template <typename T>
		const T& Node<T>::getData() const
		{
			return data;
		}

		template <typename T>
		T& Node<T>::getData()
		{
			return const_cast<T&>(static_cast<const Node<T>*>(this)->getData());
		}

		template <typename T>
		void Node<T>::setData(const T& data)
		{
			this->data = data;
		}

		template <typename T>
		bool Node<T>::operator<(const Node<T>& node) const
		{
			return data < node.data;
		}
	}
}

#endif