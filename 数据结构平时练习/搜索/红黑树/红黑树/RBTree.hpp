#pragma once

#ifndef _RBTREE_H_
#define _RBTREE_H_

/*
��չ�����������ӵ�����
*/

#include <iostream>
using namespace std;

/*
��������ʣ�
1��ÿ���ڵ㲻�Ǻ�ɫ�����Ǻ�ɫ
2�������ֻ���Ǻ�ɫ
3�������ǰ�ڵ�ʱ��ɫ����ô�����������ӽڵ�ֻ���Ǻ�ɫ����û�������ĺ�ɫ��
4������ÿ���ڵ㣬�Ӹý�㵽����Ҷ�ӽ��ļ�·���ϣ���������ͬ��Ŀ�ĺ�ɫ�ڵ㣨ÿ��·���Ϻ�ɫ�ڵ��������ȣ�
�������ʣ����ս����Կ����Ǻ�ɫ�ģ�
*/

enum COLOR { RED, BLACK };

//������ڵ�
template <typename K, typename V>
struct RBTreeNode
{
	RBTreeNode(const K& key, const V& value, COLOR color = RED)
		: _pParent(nullptr)
		, _pLeft(nullptr)
		, _pRight(nullptr)
		, _key(key)
		, _value(value)
		, _color(color)//�ڵ�Ĭ���Ǻ�ɫ�ģ���Ϊά������3��ά������4����
	{}

	RBTreeNode<K, V>* _pParent;
	RBTreeNode<K, V>* _pLeft;
	RBTreeNode<K, V>* _pRight;

	K _key;
	V _value;
	COLOR _color;
};

//�����
template <typename K, typename V>
class RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	RBTree()
		: _pRoot(nullptr)
	{}

public:
	//�������
	bool Insert(const K& key, const V& value, COLOR color = RED);

	//�������
	void InOrder()
	{
		cout << "���������" << endl;
		_InOrder(_pRoot);
		cout << endl;
	}

	//����Ƿ���Ϻ��������
	bool CheckRBTree();

private:
	//����
	void _TotalL(Node* pParent);

	//�ҵ���
	void _TotalR(Node* pParent);

	//�������
	void _InOrder(Node* pRoot);

	//����Ƿ���Ϻ��������
	//blackCount��ʾ���У�ÿ�����·���Ϻ�ɫ������k������ǰ����ýڵ��·���ϣ���ɫ�ڵ���������㱾�ڵ�ĺ�ɫ��
	bool _CheckRBTree(const Node* pRoot, const size_t blackCount, size_t k);

private:
	Node* _pRoot;
};

//�������
template <typename K, typename V>
bool RBTree<K, V>::Insert(const K& key, const V& value, COLOR color)
{
	/*
	cur����ʾ����Ľڵ�
	p��˫�׽��
	g���游ĸ�ڵ�
	u������ڵ�

	���������
	1������
	2��p->color = black��ֱ�Ӳ���
	3, p->color = red, (u && u->color = red)��p��u��ɫ��Ϊblack��g��ɫ��Ϊred
	4��p->color = red, (u = nullptr || u->color = black),cur,p,g��ͬһ��ֱ�ߣ�������Ӧ��/�ҵ�ѡ����g��Ϊ��������Ȼ��ԭ��p g��ɫ����
	5��p->color = red, (u = nullptr || u->color = black),cur,p,g����ͬһ��ֱ�ߣ�������Ӧ��/�ҵ�ѡ��p��Ϊ����������Ϊ���4����
	*/

	//���������һ
	if (nullptr == _pRoot)
	{
		_pRoot = new Node(key, value, BLACK);//��ָ���µĽڵ㣬���ڵ��Ǻ�ɫ��
		return true;
	}

	//�����գ��ҵ������λ��

	Node* pCur = _pRoot;//Ӧ�ò����λ�� cur
	Node* pParent = nullptr;//����ڵ��˫�׽ڵ� p

	while (pCur)
	{
		if (key == pCur->_key)
			return false;//�ڵ��Ѵ��ڣ�����ʧ��
		else if (key < pCur->_key)//��pCur����������Ѱ��
		{
			pParent = pCur;//pParent��pCur�仯ǰ���£����ܺ���һ���˳��㷴��
			pCur = pCur->_pLeft;
		}
		else // key > pCur->_key ��pCur����������Ѱ��
		{
			pParent = pCur;
			pCur = pCur->_pRight;
		}
	}

	//����ӣ��ڿ��ǵ����������������������ѭ�����������򱾴���������������
	Node* pNewNode = new Node(key, value);//�����µĽڵ�
	pNewNode->_pParent = pParent;//����˫��ָ��
	if (key < pParent->_key)	//�½ڵ�Ӧ�ò��뵽���
		pParent->_pLeft = pNewNode;
	else						//�½ڵ�Ӧ�ò��뵽�ұ�
		pParent->_pRight = pNewNode;

	pCur = pNewNode;//��ס��Ҫ��ʱ����ָ��������ѭ���д���

	while (pParent && (RED == pParent->_color))
	{
		Node* pGrandParent = pParent->_pParent;//�游ĸ�ڵ�g

		if (pParent == pGrandParent->_pLeft)//p��g�����
		{
			Node* pUncle = pGrandParent->_pRight;//cur������ڵ�u

			if (pUncle && (RED == pUncle->_color)) //�������pUncle��������ɫΪ��
			{	//p��u����ΪBLACK��g����ΪRED
				pParent->_color = BLACK;
				pUncle->_color = BLACK;
				pGrandParent->_color = RED;

				pCur = pGrandParent;//���ϵ�����Ϊ�´�ѭ����׼��
				pParent = pCur->_pParent;//���ϵ�����pParentָ���µĸ����pCur��˫��
			}
			else //nullptr == pUncle || BLACK == pUncle->_color   pUncle�����ڻ��ߴ�������ɫΪ��
			{
				//�������5����ת��Ϊ���4�����Խ���������ϲ���һ��ѭ����

				if (pCur == pParent->_pRight)//cur, p, g����ͬһ��ֱ����	//�����
				{
					_TotalL(pParent);//���� 

									 //��ʱ���ý�����ɫ����Ϊ ����ģ������洦��

					std::swap(pParent, pCur);//ע�⽻����pParent��pCur�����ݣ��������4����
				}

				_TotalR(pGrandParent);//�ҵ����� cur��p�����ڸ���˫�׵���������cur, p, g��ͬһ��ֱ�ߣ�//�����

				//p��g��ɫ����
				pParent->_color = BLACK;
				pGrandParent->_color = RED;

				//�������Ӧ��ֱ���˳�����ǰ�����Ѿ������������ʣ���������������������������������ʣ����ԣ�ֱ���˳���----���԰��죩
				//pCur = pParent;//���ϵ�����Ϊ�´�ѭ����׼����ָ���µĸ����
				//pParent = pCur->_pParent;//���ϵ�����pParentָ���µĸ����pCur��˫�� 
				//�������������,���п���pParent��˫�׽����ɫ��red����������ѭ������������Ԥ�ϵ�����

				break;
				//�޸�֮ǰ�Ĵ��룬����������ֳ�����ѭ������
				//�޸�֮����һ��ѭ���д���
				//	if (pCur == pParent->_pLeft)//cur��p�����ڸ���˫�׵���������cur, p, g��ͬһ��ֱ�ߣ�//�����
				//	{
				//		_TotalR(pGrandParent);//�ҵ���

				//		//p��g��ɫ����
				//		pParent->_color = BLACK;
				//		pGrandParent->_color = RED;

				//		//�������Ӧ��ֱ���˳�����ǰ�����Ѿ������������ʣ���������������������������������ʣ����ԣ�ֱ���˳���----���԰��죩
				//		//pCur = pParent;//���ϵ�����Ϊ�´�ѭ����׼����ָ���µĸ����
				//		//pParent = pCur->_pParent;//���ϵ�����pParentָ���µĸ����pCur��˫�� 
				//		//�������������,���п���pParent��˫�׽����ɫ��red����������ѭ������������Ԥ�ϵ�����

				//		return true;
				//	}
				//	else //pCur == pParent->_pRight.  cur,p,g����ͬһ��ֱ����	//�����
				//	{
				//		_TotalL(pParent);//���� 

				//		 //��ʱ���ý�����ɫ����Ϊ ����ģ����´�ѭ���д���

				//		std::swap(pParent, pCur);//ע�⽻����pParent��pCur�����ݣ��������4����
				//	}
			}

		}
		else	//p��g���ұ�
		{
			Node* pUncle = pGrandParent->_pLeft;//cur������ڵ�u

			if (pUncle && (RED == pUncle->_color)) //�����
			{	//p��u����ΪBLACK��g����ΪRED
				pParent->_color = BLACK;
				pUncle->_color = BLACK;
				pGrandParent->_color = RED;

				pCur = pGrandParent;			//���ϵ�����Ϊ�´�ѭ����׼��
				pParent = pCur->_pParent;//���ϵ�����pParentָ���µĸ����pCur��˫��
			}
			else //pUncle = nullptr || BLACK == pUncle->_color
			{
				//�������5����ת��Ϊ���4�����Խ���������ϲ���һ��ѭ����

				// cur,p,g����ͬһ��ֱ����	//�����
				if (pCur = pParent->_pLeft)
				{
					_TotalR(pParent); //�ҵ���
					 //��ʱ���ý�����ɫ����Ϊ ����ģ����´�ѭ���д���
					std::swap(pParent, pCur);////ע�⽻����pParent��pCur�����ݣ��������4����
				}

				//cur��p�����ڸ���˫�׵���������cur, p, g��ͬһ��ֱ�ߣ�//�����
				_TotalL(pGrandParent);		//����

					//p��g��ɫ����
				pParent->_color = BLACK;
				pGrandParent->_color = RED;

				//�˳�ԭ�򣬼����� ���4����
				break;
			}

		}
	}

	_pRoot->_color = BLACK;//������ô���������ڵ�ʼ���Ǻ�ɫ�����Һ�ɫ��������

	return true;
}

//�ҵ���
template <typename K, typename V>
void RBTree<K, V>::_TotalR(Node* pParent)
{
	Node* pSubL = pParent->_pLeft;
	Node* pSubLR = pSubL->_pRight;

	pParent->_pLeft = pSubLR;
	pSubL->_pRight = pParent;

	if (pSubLR)
		pSubLR->_pParent = pParent;

	Node* pGrandParent = pParent->_pParent;
	pParent->_pParent = pSubL;
	pSubL->_pParent = pGrandParent;
	if (pGrandParent)
	{
		if (pGrandParent->_pLeft == pParent)//ע�⣬ʹ��==����Ҫ����д��=�����԰��죩
			pGrandParent->_pLeft = pSubL;
		else
			pGrandParent->_pRight = pSubL;
	}
	else
		_pRoot = pSubL;

}

//����
template <typename K, typename V>
void RBTree<K, V>::_TotalL(Node* pParent)
{
	Node* pSubR = pParent->_pRight;
	Node* pSubRL = pSubR->_pLeft;

	pParent->_pRight = pSubRL;
	pSubR->_pLeft = pParent;

	if (pSubRL)
		pSubRL->_pParent = pParent;

	Node* pGrandParent = pParent->_pParent;
	pParent->_pParent = pSubR;
	pSubR->_pParent = pGrandParent;
	if (pGrandParent)
	{
		if (pGrandParent->_pLeft == pParent)//ע�⣬ʹ��==����Ҫ����д��=
			pGrandParent->_pLeft = pSubR;
		else
			pGrandParent->_pRight = pSubR;
	}
	else
		_pRoot = pSubR;
}

//�ݹ�ʵ���������
template <typename K, typename V>
void RBTree<K, V>::_InOrder(Node* pRoot)
{
	if (nullptr == pRoot)
		return;

	_InOrder(pRoot->_pLeft);

	cout << pRoot->_key << " ";

	_InOrder(pRoot->_pRight);
}

template <typename K, typename V>
bool RBTree<K, V>::CheckRBTree()
{
	//������������������
	if (nullptr == _pRoot)
		return true;

	//������Ǻ�ɫ�ģ�Υ������2
	if (RED == _pRoot->_color)
	{
		cout << "������Ǻ�ɫ�ģ�Υ������2" << endl;
		return false;
	}

	size_t blackCount = 0;//����һ���Ӹ���㵽Ҷ�ӽ���Ϻ�ɫ�ڵ�ĸ���
	Node* pCur = _pRoot;
	while (pCur)
	{
		if (BLACK == pCur->_color)
			++blackCount;
		pCur = pCur->_pLeft;
	}
	//������ݹ麯���У��������3������4
	return _CheckRBTree(_pRoot, blackCount, 0);
}

//�ж��Ƿ�������������3������4
//blackCount��ʾ���У�ÿ�����·���Ϻ�ɫ������k������ǰ����ýڵ��·���ϣ���ɫ�ڵ���������㱾�ڵ�ĺ�ɫ��
template <typename K, typename V>
bool RBTree<K, V>::_CheckRBTree(const Node* pRoot, size_t blackCount, size_t k)
{	
	//ע�⣺k����ͨ���������������ã���Ϊ�ݹ��У�ÿ���ڵ���k����һ�����ݹ鷵�غ���Ҫ��ǰ�ڵ�kֵ�����¼��㣬�����ڱ�����У����ı�

	if (nullptr == pRoot)//���������Ϻ������������
		return true;

	if (BLACK == pRoot->_color)//��ǰ�ڵ���ɫ�Ǻ�ɫ
		++k;
	else			//��ǰ�ڵ��Ǻ�ɫ
	{
		if (RED == pRoot->_pParent->_color) //�жϺ�ɫ�ڵ��Ƿ�����
		{
			cout << "�������ĺ�ɫ�ڵ㣬����������3" << endl;
			return false;
		}
	}

	if ((nullptr == pRoot->_pLeft) && (nullptr == pRoot->_pRight))//Ҷ�ӽ��
	{
		if (blackCount == k)//�жϵ�ǰ·���ϵĺ�ɫ�ڵ��Ƿ�ͱ��·���Ͻ�����
			return true;
		else
		{
			cout << "�����ÿ�����·���Ϻ�ɫ�ڵ������ͬ������������4" << endl;
			return false;
		}
	}

	//�����Ҷ�ӽ������������������Ҳ����������������
	return (_CheckRBTree(pRoot->_pLeft, blackCount, k) && _CheckRBTree(pRoot->_pRight, blackCount, k));
}


#endif //_RBTREE_H_

