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
					return true;
				}
				else //-1 == subL->_bf,��û��0 == subL->_bf�Ŀ��ܣ� subL�ұ߽ϸ�, ����˫�������
				{
					_RotateLR(pParent);
					return true;
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

				if (1 == subR->_bf)//subL��߽ϸߣ�����������
				{
					//����ڵ���sub�����ӽڵ�����ӽڵ㣨����˫����
					_RotateRL(pParent);
					return true;
				}
				else // -1 == subR->_bf. subL�ұ߽ϸߣ�û��0 == subL->_bf�Ŀ��ܣ�
				{
					//����ڵ���sub�����ӽڵ�����ӽڵ㣨������
					_RotateL(pParent);
					return true;
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
	Node* pSubR = pParent->_pRight;
	Node* pSubRL = pSubR->_pLeft;

	pParent->_pRight = pSubRL;
	pSubR->_pLeft = pParent;
	if (pSubRL)//���subRL����
		pSubRL->_pParent = pParent;

	Node* pGrandParent = pParent->_pParent;//�鿴pParent�Ƿ��Ǹ����
	pParent->_pParent = pSubR;

	//subR��˫��ָ��pParent��˫��
	pSubR->_pParent = pGrandParent;
	if (pGrandParent)//���pParent����˫�׽�㣨�����Ǹ���㣩
	{	//��pParent��˫�׽������ָ��subR
		if (pParent == pGrandParent->_pLeft)
			pGrandParent->_pLeft = pSubR;
		else
			pGrandParent->_pRight = pSubR;
	}
	else
	{
		_pRoot = pSubR;
	}

	//����ת֮��pParent��subR��ƽ��������Ϊ0
	pParent->_bf = 0;
	pSubR->_bf = 0;
}

//�ҵ���
template <typename K, typename V>
void AVLTree<K, V>::_RotateR(Node* pParent)
{
	Node* pSubL = pParent->_pLeft;
	Node* pSubLR = pSubL->_pRight;

	pParent->_pLeft = pSubLR;
	pSubL->_pRight = pParent;


	if(pSubLR)//���subLR����
		pSubLR->_pParent = pParent;

	Node* pGrandParent = pParent->_pParent;//�鿴pParent�Ƿ��Ǹ����
	pParent->_pParent = pSubL;

	//subR��˫��ָ��pParent��˫��
	pSubL->_pParent = pGrandParent;
	if (pGrandParent)//���pParent����˫�׽�㣨�����Ǹ���㣩
	{	//��pParent��˫�׽������ָ��subL
		if (pParent == pGrandParent->_pLeft)
			pGrandParent->_pLeft = pSubL;
		else
			pGrandParent->_pRight = pSubL;
	}
	else
	{
		_pRoot = pSubL;
	}
	//����ת֮��pParent��subR��ƽ��������Ϊ0
	pParent->_bf = 0;
	pSubL->_bf = 0;
}

//���Һ�����ת
template <typename K, typename V>
void AVLTree<K, V>::_RotateRL(Node* pParent)
{
	/*����ʹ��k1,k2,k3��ǡ��ο������ݽṹ���㷨����C++���������桷*/
	Node* subR = pParent->_pRight;
	Node* subRL = subR->_pLeft;

	int flag = 0;//��¼pNewNode��subRL�Ĺ�ϵ

	if (0 == subRL->_bf)//subRL�Ǹղ���Ľڵ�pNewNode
		flag = 0;
	else if (1 == subRL->_bf)//pNewNode��subRL����������
		flag = 1;
	else //-1 == subRL->_bf pNewNode��subRL����������
		flag = -1;

	_RotateR(subR);
	_RotateL(pParent);

	//����ƽ�����ӣ�����Ҫ����subRL����Ϊ�ڵ���ת֮����ƽ������Ϊ0������ı䣩
	if (0 == flag)//subRL�Ǹղ���Ľڵ�pNewNode
	{
		subR->_bf = 0;
		pParent->_bf = 0;
	}
	else if (1 == flag)//pNewNode��subRL����������
	{
		subR->_bf = -1;
		pParent->_bf = 0;
	}
	else //-1 == flag pNewNode��subRL����������
	{
		subR->_bf = 0;
		pParent->_bf = 1;
	}
}

//���������ת
template <typename K, typename V>
void AVLTree<K, V>::_RotateLR(Node* pParent)
{
	/*����ʹ��k1,k2,k3��ǡ��ο������ݽṹ���㷨����C++���������桷*/
	Node* subL = pParent->_pLeft;
	Node* subLR = subL->_pRight;

	int flag = 0;//��¼pNewNode��subLR�Ĺ�ϵ

	if (0 == subLR->_bf)//subLR�Ǹղ���Ľڵ�pNewNode
		flag = 0;
	else if (1 == subLR->_bf)//pNewNode��subLR����������
		flag = 1;
	else //-1 == subRL->_bf pNewNode��subLR����������
		flag = -1;


	_RotateL(subL);
	_RotateR(pParent);


	//����ƽ�����ӣ�����Ҫ����subLR����Ϊ�ڵ���ת֮����ƽ������Ϊ0������ı䣩
	if (0 == flag)//subLR�Ǹղ���Ľڵ�pNewNode
	{
		subL->_bf = 0;
		pParent->_bf = 0;
	}
	else if (1 == flag)//pNewNode��subLR����������
	{
		subL->_bf = -1;
		pParent->_bf = 0;
	}
	else //-1 == flag pNewNode��subLR����������
	{
		subL->_bf = -1;
		pParent->_bf = 1;
	}
}


//�ж����Ƿ���ƽ����
template <typename K, typename V>
bool AVLTree<K, V>::_IsBalanceTree(Node* pRoot)
{
	if (nullptr == pRoot)//�ս�㣬��ƽ���
		return true;

	size_t leftHeight = _Height(pRoot->_pLeft);
	size_t rightHeight = _Height(pRoot->_pRight);

	if (((leftHeight - rightHeight) != pRoot->_bf) || (abs(pRoot->_bf) > 1))
		return false;

	return (_IsBalanceTree(pRoot->_pLeft) && _IsBalanceTree(pRoot->_pRight));
}

//��ȡ���ĸ߶�
template <typename K, typename V>
size_t AVLTree<K, V>::_Height(Node* pRoot)
{
	if (nullptr == pRoot)//����
		return 0;

	if ((nullptr == pRoot->_pLeft) && (nullptr == pRoot->_pRight))//Ҷ�ӽ��
		return 1;

	size_t leftHeight = _Height(pRoot->_pLeft);//�������߶�
	size_t rightHeight = _Height(pRoot->_pRight);//�������߶�

	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;//�������������е����ֵ+1
}

#endif //_AVL_H_