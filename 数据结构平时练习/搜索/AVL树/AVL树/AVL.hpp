#pragma once

#ifndef _AVL_H_
#define _AVL_H_

template <typename K, typename V>
struct AVLTreeNode
{
	AVLTreeNode(const K& key, const V& value)
		:_pParent(nullptr)
		,_pRight(nullptr)
		,_pLeft(nullptr)
		,_key(key)
		,_value(value)
		,_bf(0)//ƽ������Ĭ��Ϊ0(�������߶� - �������߶�)
	{}
	AVLTreeNode<K, V>* _pParent;
	AVLTreeNode<K, V>* _pRight;
	AVLTreeNode<K, V>* _pLeft;
	K _key;
	V _value;
	int _bf;//ƽ������
};

template <typename K, typename V>
class AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	AVLTree()
		:_pRoot(nullptr)
	{}

	bool Insert(const K& key, const V& value);

	//�������
	void InOrder()
	{
		cout << "InOrder:";
		_InOrder(_pRoot);
		cout << endl;
	}
	//�ж����Ƿ���ƽ����
	bool IsBalanceTree()
	{
		return _IsBalanceTree(_pRoot);
	}
private:
	//�ж����Ƿ���ƽ����
	bool _IsBalanceTree(Node* pRoot);
	//��ȡ���ĸ߶�
	size_t _Height(Node* pRoot);
	//�������
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_key << " ";
			_InOrder(pRoot->_pRight);
		}
	}
	//����
	void _RotateL(Node* pParent);
	//�ҵ���
	void _RotateR(Node* pParent);
	//���Һ�����ת
	void _RotateRL(Node* pParent);
	//���������ת
	void _RotateLR(Node* pParent);

private:
	Node* _pRoot;
};


template <typename K, typename V>
bool AVLTree<K, V>::Insert(const K& key, const V& value)
{
	/*
	˼·��
	1������
	2���ǿ��������뵽��Ӧλ�ã����޸�˫�׵�ƽ�����ӡ��Ӳ���Ľڵ����ϵ�����㣬�ж��Ƿ��в�����AVL�����ʵĽڵ���ڣ�������
	*/

	if (nullptr == _pRoot)
	{
		_pRoot = new Node(key, value);
		return true;
	}

	Node* pCur = _pRoot;//����ڵ��λ��
	Node* pParent = nullptr;//����ڵ��˫��

	//�ҵ��ڵ�Ӧ�ò����λ��
	while (pCur)
	{
		if (key == pCur->_key)//������ͬ�ڵ㣬����ʧ�ܣ�����false
		{
			return false;
		}
		else if (key < pCur->_key)
		{
			pParent = pCur;
			pCur = pCur->_pLeft;
		}
		else
		{
			pParent = pCur;
			pCur = pCur->_pRight;
		}
	}

	//�����½ڵ�
	Node* pNewNode = new Node(key, value);
	if (key < pParent->_key)//�������
		pParent->_pLeft = pNewNode;
	else  //�����ұ�
		pParent->_pRight = pNewNode;
	pNewNode->_pParent = pParent;
	pCur = pNewNode;

	while (pParent)//������ѭ�������ڵ�ʱ���˳�ѭ��
	{
		if (1 == pParent->_bf)
		{
			if (pParent->_pLeft == pCur)
			{
				++pParent->_bf;//��ʱpParent->_bf = 2����߽ϸߣ�,��Ҫ������ת
				// ..............
				Node* subL = pCur;
				if (1 == subL->_bf)//subL��߸� ���ҵ��������
				{
					_RotateR(pParent);
				}
				else //-1 == subL->_bf,��û��0 == subL->_bf�Ŀ��ܣ� subL�ұ߽ϸ�, ����˫�������
				{
					_RotateLR(pParent);
				}
			}
			else
			{
				--pParent->_bf;//��ʱpParent->_bf = 0;û�����һ�㣬ֱ���˳�
				break;
			}
		}
		else if (-1 == pParent->_bf)
		{
			if (pParent->_pLeft == pCur)
			{
				++pParent->_bf;//��ʱpParent->_bf = 0;û�����һ�㣬ֱ���˳�
				break;
			}
			else
			{
				--pParent->_bf;//��ʱpParent->_bf = -2���ұ߽ϸߣ�,��Ҫ������ת
				//........
				Node* subR = pCur;

				if (1 == subR->_bf)//subL��߽ϸߣ� ���������
				{
					_RotateL(pParent);
				}
				else // -1 == subR->_bf. subL�ұ߽ϸߣ�û��0 == subL->_bf�Ŀ��ܣ��� ���ҵ��������
				{
					_RotateLR(pParent);
				}
			}
		}
		else //(0 == pParent->_bf)
		{
			if (pParent->_pLeft == pCur)
				++pParent->_bf;//��ʱpParent->_bf = 1
			else
				--pParent->_bf;//��ʱpParent->_bf = -1

			//�ɵ�ǰ�ڵ�����������
			pCur = pParent;
			pParent = pParent->_pParent;
		}
	}

	return true;
}

//����
template <typename K, typename V>
void AVLTree<K, V>::_RotateL(Node* pParent)
{
	Node* subR = pParent->_pLeft;
	Node* subRL = subR->_pLeft;

	Node* pGrandParent = pParent->_pParent;//�鿴pParent�Ƿ��Ǹ����

	pParent->_pRight = subRL;
	subRL->_pParent = pParent;

	subR->_pLeft = pParent;
	pParent->_pParent = subR;

	if (pGrandParent)//���pParent����˫�׽�㣨�����Ǹ���㣩
	{	//��pParent��˫�׽������ָ��subR
		if (pParent == pGrandParent->_pLeft)
			pParent->_pLeft = subR;
		else
			pParent->_pRight = subR;
	}	
	//subR��˫��ָ��pParent��˫��
	subR->_pParent = pGrandParent;

	//����ת֮��pParent��subR��ƽ��������Ϊ0
	pParent->_bf = 0;
	subR->_bf = 0;
}

//�ҵ���
template <typename K, typename V>
void AVLTree<K, V>::_RotateR(Node* pParent)
{
	Node* subL = pParent->_pLeft;
	Node* subLR = subL->_pRight;

	Node* pGrandParent = pParent->_pParent;//�鿴pParent�Ƿ��Ǹ����

	pParent->_pLeft = subLR;
	subLR->_pParent = pParent;

	subL->_pRight = pParent;
	pParent->_pParent = subL;

	if (pGrandParent)//���pParent����˫�׽�㣨�����Ǹ���㣩
	{	//��pParent��˫�׽������ָ��subL
		if (pParent == pGrandParent->_pLeft)
			pParent->_pLeft = subL;
		else
			pParent->_pRight = subL;
	}
	//subR��˫��ָ��pParent��˫��
	subL->_pParent = pGrandParent;

	//����ת֮��pParent��subR��ƽ��������Ϊ0
	pParent->_bf = 0;
	subL->_bf = 0;
}

//���Һ�����ת
template <typename K, typename V>
void AVLTree<K, V>::_RotateRL(Node* pParent)
{
	_RotateR(pParent->_pRight);
	_RotateL(pParent);
}

//���������ת
template <typename K, typename V>
void AVLTree<K, V>::_RotateLR(Node* pParent)
{
	_RotateR(pParent->_pRight);
	_RotateL(pParent);
}

#endif //_AVL_H_