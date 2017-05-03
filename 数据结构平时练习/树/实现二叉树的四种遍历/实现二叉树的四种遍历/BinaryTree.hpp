/*
���������������ԣ�����ͨ���ݹ����Ϻõ�ʵ��������ع���
����ջ���洢·��
*/
#pragma once
#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_

#include <iostream>
#include <queue>
#include <stack>
using namespace std;

template <typename T>
struct BinaryTreeNode
{
	BinaryTreeNode(const T& data)
		:m_data(data)
		, m_pLeft(NULL)
		, m_pRight(NULL)
	{}
	T m_data;
	BinaryTreeNode<T>* m_pLeft;//����
	BinaryTreeNode<T>* m_pRight;//�Һ���
};

template <typename T>
class BinaryTree//����Ա������ʵ�ֽ��м򵥵ķ�װ���û�ֻ����ʾ���ù����ӿ�
{
	typedef BinaryTreeNode<T> Node;
public:
	BinaryTree()//�޲ι��캯��
		:m_pRoot(NULL)
	{}
	BinaryTree(const T array[], size_t size, const T& invalid)//���ι��캯��
	{
		size_t index = 0;
		_CreateTree(m_pRoot, array, size, index, invalid);
	}
	BinaryTree(const BinaryTree<T>& t)//�������캯��
	{
		m_pRoot = _CopyBinaryTree(t.m_pRoot);
	}
	BinaryTree<T>& operator=(const BinaryTree<T>& t)//��ֵ��������س�Ա����
	{
		_Destroy(m_pRoot);
		m_pRoot = _CopyBinaryTree(t.m_pRoot);
		return *this;
	}
	~BinaryTree()//��������
	{
		_Destroy(m_pRoot);
	}
	void PreOrder()//ǰ�����
	{
		cout << "ǰ�������";
		_PreOrder_2(m_pRoot);
		cout << endl;
	}
	void InOrder()//�������
	{
		cout << "�������";
		_InOrder_2(m_pRoot);
		cout << endl;
	}
	void PostOrder()//�������
	{
		cout << "�������";
		_PostOrder(m_pRoot);
		cout << endl;
	}
	void LevelOrder()//�������
	{
		cout << "�������";
		_LevelOrder(m_pRoot);
		cout << endl;
	}

	Node* GetParent(Node* x)//��ȡ�ý���˫�׽��
	{
		return _GetParent(m_pRoot, x);
	}

	Node* Find(const T& value)//�ҵ�ֵΪvalue�Ľ��
	{
		return _Find(m_pRoot, value);
	}

	Node* GetLeftChild(Node* pCur)//��������
	{
		if (pCur)
			return pCur->m_pLeft;
		return nullptr;
	}

	Node* GetRightChild(Node* pCur)//�����Һ���
	{
		if (pCur)
			return pCur->m_pRight;
		return nullptr;
	}

	size_t Height()//��ȡ���ĸ߶�
	{
		return _Height(m_pRoot);
	}

	size_t GetLeefNode()//��ȡҶ�ӽ�����
	{
		return _GetLeefNode(m_pRoot);
	}

	size_t GetKLevelNode(size_t k)//��ȡĳһ�������
	{
		return _GetKLevelNode(m_pRoot, k);
	}

private:
	void _CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid);//������
	Node* _CopyBinaryTree(Node* pRoot);//������
	void _Destroy(Node*& pRoot);//�����

	void _PreOrder_1(Node* pRoot);//�ݹ�ʵ�֣��������
	void _PreOrder_2(Node* pRoot);//�ǵݹ�ʵ�֣��������
	void _InOrder_1(Node* pRoot);//�ݹ�ʵ�֣��������
	void _InOrder_2(Node* pRoot);//�ѵݹ�ʵ�֣��������
	void _PostOrder(Node* pRoot);//�������
	void _LevelOrder(Node* pRoot);//�������

	Node* _GetParent(Node* pRoot, Node* x);//��ȡ˫�׽��
	Node* _Find(Node* pRoot, const T& value);//�ҵ�ֵΪvalue�Ľ��
	size_t _Height(Node* pRoot);//��ȡ���ĸ߶�
	size_t _GetLeefNode(Node* pRoot);//��ȡҶ�ӽ�����
	size_t _GetKLevelNode(Node* pRoot, size_t k);//��ȡĳһ�������

private:
	BinaryTreeNode<T>* m_pRoot;//�����
};

template <typename T>//������
void BinaryTree<T>::_CreateTree(Node*& pRoot, const T array[], size_t size, size_t& index, const T& invalid)
{
	if ((array[index] != invalid) && (index < size))
	{
		pRoot = new Node(array[index]);
		_CreateTree(pRoot->m_pLeft, array, size, ++index, invalid);
		_CreateTree(pRoot->m_pRight, array, size, ++index, invalid);
	}
}

template <typename T>//������
BinaryTreeNode<T>* BinaryTree<T>::_CopyBinaryTree(Node* pRoot)
{
	Node* pNewRoot = NULL;
	if (pRoot)
	{
		pNewRoot = new Node(pRoot->m_data);
		pNewRoot->m_pLeft = _CopyBinaryTree(pRoot->m_pLeft);
		pNewRoot->m_pRight = _CopyBinaryTree(pRoot->m_pRight);
	}
	return pNewRoot;
}

template <typename T>
void BinaryTree<T>::_Destroy(Node*& pRoot)//�����
{
	if (pRoot)
	{	
		_Destroy(pRoot->m_pLeft);
		_Destroy(pRoot->m_pRight);
		delete pRoot;
		pRoot = nullptr;
	}
}

template <typename T>
void BinaryTree<T>::_PreOrder_1(Node* pRoot)//�ݹ�ʵ�֣�ǰ�����
{
	if (pRoot)
	{
		cout << pRoot->m_data << " ";
		_PreOrder_1(pRoot->m_pLeft);
		_PreOrder_1(pRoot->m_pRight);
	}
}
template <typename T>
void BinaryTree<T>::_PreOrder_2(Node* pRoot)//�ǵݹ�ʵ�֣�ǰ�����������ջʵ�֣�
{
	if (nullptr == pRoot)//����
		return ;
	stack<Node*> s;
	s.push(pRoot);

	while (!s.empty())
	{
		Node* pTemp = s.top();
		cout << pTemp->m_data << " ";
		s.pop();//pop����push֮ǰ������ջ��LIFO����

		if (pTemp->m_pRight)
			s.push(pTemp->m_pRight);//һ��Ҫ�ȴ��������������������������Ϊջ��LIFO����
		if (pTemp->m_pLeft)
			s.push(pTemp->m_pLeft);
	}
}

template <typename T>
void BinaryTree<T>::_InOrder_1(Node* pRoot)//�ݹ�ʵ�֣��������
{
	if (pRoot)
	{
		_InOrder_1(pRoot->m_pLeft);
		cout << pRoot->m_data << " ";
		_InOrder_1(pRoot->m_pRight);
	}
}
template <typename T>
void BinaryTree<T>::_InOrder_2(Node* pRoot)//�ǵݹ�ʵ�֣��������(1,�ҵ�������ߵĽڵ㣬������·�� 2�����ʵ�ǰ�ڵ㣬��������������Ϊ���ڵ㡣3���ظ�12)
{	
	if (nullptr == pRoot)
		return;

	stack<Node*> s;
	Node* pCur = pRoot;

	while (!s.empty() || pCur)//ע�⣺�������������Ϊ����������������ڵ��ջ֮�󣬻������������
	{
		while (pCur)//�ҵ�����ߵ�Ҷ�ӽ�㣬��·���Ͻ����ջ
		{
			s.push(pCur);
			pCur = pCur->m_pLeft;
		}

		Node* pTemp = s.top();
		cout << pTemp->m_data << " ";
		s.pop();

		pCur = pTemp->m_pRight;//����������
	}
}

template <typename T>
void BinaryTree<T>::_PostOrder(Node* pRoot)//�������
{
	if (pRoot)
	{
		_PostOrder(pRoot->m_pLeft);
		_PostOrder(pRoot->m_pRight);
		cout << pRoot->m_data << " ";
	}
}

template <typename T>
void BinaryTree<T>::_LevelOrder(Node* pRoot)//�������(���ö���ʵ��)
{	/*
	��ͼ��⣺
	1���Ƚ����ڵ�����У�
	2������ѭ�������׽������У������ֵ��
	3���������Һ��ӽڵ�����У�
	4������2-3ѭ����ֱ������Ϊ��
	*/
	if (!pRoot)
		return;

	queue<Node*> q;
	q.push(pRoot);

	while (!q.empty())
	{
		Node* pCur = q.front();
		q.pop();
		cout << pCur->m_data << " ";
		
		if (pCur->m_pLeft)
			q.push(pCur->m_pLeft);

		if (pCur->m_pRight)
			q.push(pCur->m_pRight);
	}
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::_GetParent(Node* pRoot, Node* x)//�ݹ�ʵ�֣���ȡ˫�׽��
{
	if ((nullptr == pRoot) || (pRoot == x))//�������߸ý���Ǹ���㣬û��˫�׽�㣬����nullptr
		return nullptr;

	if ((pRoot->m_pLeft == x) || (pRoot->m_pRight == x))//��x�Ǹ��������Һ��ӣ����ظø����
		return pRoot;
	//���������ж�����ǵݹ����
	
	//���õݹ飬�������Ϊ������������Ѱ��x��˫�׽��
	Node* parent = nullptr;
	if (parent = _GetParent(pRoot->m_pLeft, x))//��������Ѱ��
		return parent;
	if (parent = _GetParent(pRoot->m_pRight, x))//��������Ѱ��
		return parent;

	return nullptr;//������������δ�ҵ�x��˫�׽�㡣
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::_Find(Node* pRoot, const T& value)//�ݹ�ʵ�֣��ҵ�ֵΪvalue�Ľ��
{
	if (nullptr == pRoot)//������ս��
		return nullptr;
	
	if (pRoot->m_data == value)
		return pRoot;
	//������������ǵݹ����

	//���õݹ飬�������Ϊ������������Ѱ��ֵΪvalue�Ľڵ�
	Node* p_node = nullptr;
	if (p_node = _Find(pRoot->m_pLeft, value))//��������Ѱ��
		return p_node;
	if (p_node = _Find(pRoot->m_pRight, value))//��������Ѱ��
		return p_node;

	return nullptr;//������������δ�ҵ�ֵΪvalue�Ľ�㡣
}

template <typename T>
size_t BinaryTree<T>::_Height(Node* pRoot)//�ݹ�ʵ�֣���ȡ���ĸ߶�
{
	if (nullptr == pRoot)//������սڵ�
		return 0;
	//�������Ϊ�ݹ����

	//���õݹ飺��ȡ���������ĸ߶ȣ��������������ĸ߶��нϴ�ĸ߶ȼ�1�����أ���ǰ����pRoot��Ϊ�գ����Լ�1��
	size_t h_left = _Height(pRoot->m_pLeft);//����������߶�
	size_t h_right = _Height(pRoot->m_pRight);//����������߶�

	return h_left > h_right ? h_left + 1 : h_right + 1;//�������ĸ߶�
}

template <typename T>
size_t BinaryTree<T>::_GetLeefNode(Node* pRoot)//�ݹ�ʵ�֣���ȡҶ�ӽ�����
{
	if (nullptr == pRoot)//������ս��
		return 0;
	if ((nullptr == pRoot->m_pLeft) && (nullptr == pRoot->m_pRight))//��ǰ�ڵ�ʱҶ�ӽ��
		return 1;
	//���������ж�����ǵݹ����

	//���õݹ飬��ȡ����������Ҷ�ӽ�����
	size_t leaves_left = _GetLeefNode(pRoot->m_pLeft);//��ȡ������Ҷ�ӽ����
	size_t leaves_right = _GetLeefNode(pRoot->m_pRight);//��ȡ������Ҷ�ӽ����

	return leaves_left + leaves_right;//������������Ҷ�ӽ��֮��
}

template <typename T>
size_t BinaryTree<T>::_GetKLevelNode(Node* pRoot, size_t k)//�ݹ�ʵ�֣���ȡĳһ�������
{
	if ((nullptr == pRoot) || (1 > k))//������ս�㡢kС��1
		return 0;
	if (1 == k)//k=1��ʾ��ǰ���
		return 1;
	//���������ж�����ǵݹ����

	//���õݹ飬��ȡ���������д���k-1�������
	size_t nodes_left = _GetKLevelNode(pRoot->m_pLeft, k - 1);//��ȡ��������k-1�������
	size_t nodes_right = _GetKLevelNode(pRoot->m_pRight, k - 1);//��ȡ��������k-1�������

	return nodes_left + nodes_right;
}

#endif //_BINARYTREE_H_