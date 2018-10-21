#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_HEIGHT 1000
#define INFINITY (1<<20)

using namespace std;

struct tNode
{
	tNode* left;
	tNode* right;
	int iData;
};

void searchTree(tNode* pNode, int Data) // ��� �˻�
{
	if (pNode == NULL) // ��尡 ������� ���(�˻��� ���� �������� ���� ���)
		cout << "ã���ô� ���� ��忡 �������� �ʽ��ϴ�." << endl;

	else if (pNode->iData == Data) // �˻��� ���� ��尡 ���� ���
		cout << "�˻��Ͻ� �� " << Data << "��(��) ��忡 �����մϴ�." << endl;

	else if (Data < pNode->iData) // �˻��� ���� ���� ��尪���� ���� ���
		searchTree(pNode->left, Data);

	else if (Data > pNode->iData) // �˻��� ���� ���� ��尪���� Ŭ ���
		searchTree(pNode->right, Data);
}

tNode* insertTree(tNode* pNode, int Data) // ��� ����
{
	if (pNode == NULL) // ���� ��尡 NULL �϶�, ��� �����Ѵ�.
	{
		pNode = new tNode;
		pNode->left = pNode->right = NULL;
		pNode->iData = Data;
		return pNode;
	}
	else
	{
		if (Data < pNode->iData)
			pNode->left = insertTree(pNode->left, Data);
		else if (Data > pNode->iData)
			pNode->right = insertTree(pNode->right, Data);
		else
			cout << "���� ���� ���� ��忡 �����մϴ�." << endl;
		
		return pNode;
	}
}

tNode* deleteTree(tNode* pNode, int Data)
{
	tNode* TempNode = NULL;

	if (pNode == NULL)
		cout << "������ ��尡 �������� �ʽ��ϴ�." << endl;

	if (pNode->iData < Data)
		pNode->right = deleteTree(pNode->right, Data);
	else if (Data < pNode->iData)
		pNode->left = deleteTree(pNode->left, Data);
	else
	{
		if (pNode->left != NULL && pNode->right != NULL) // ������ ����� ����, ������ ��� �� ���� ���,
		{
			tNode* SuccP = pNode;
			tNode* Succ = pNode->right;
			
			while (Succ->left != NULL)
			{
				SuccP = Succ;
				Succ = Succ->left;
			}
			// �İ����� ���� �ڽ��� �����Ű�� �κ�
			if (SuccP->left == Succ)
				SuccP->left = Succ->right;
			else SuccP->right = Succ->right;

			// ���� ��忡 �İ��� ���� ����
			pNode->iData = Succ->iData;

			// �İ��� ��� �κ� ����
			delete Succ;
		}
		else if (pNode->left != NULL && pNode->right == NULL) // ������ ����� ���ʸ� ���� ���,
		{
			TempNode = pNode;
			pNode = pNode->left;
			delete TempNode;
		}
		else if (pNode->left == NULL && pNode->right != NULL) // ������ ����� �����ʸ� ���� ���,
		{
			TempNode = pNode;
			pNode = pNode->right;
			delete TempNode;
		}
		else // ������ ����� ����, ������ ������ ������,
		{
			delete pNode;
		}
	}
	return pNode;
}

void preorder(tNode* _pNode) // ���� ��ȸ
{
	if (_pNode != NULL)
	{
		cout << _pNode->iData << ' ';
		preorder(_pNode->left);
		preorder(_pNode->right);
	}
}

void inorder(tNode* _pNode) // ���� ��ȸ
{
	if (_pNode != NULL)
	{
		inorder(_pNode->left);
		cout << _pNode->iData << ' ';
		inorder(_pNode->right);
	}
}

void postorder(tNode* _pNode) // ���� ��ȸ
{
	if (_pNode != NULL)
	{
		postorder(_pNode->left);
		postorder(_pNode->right);
		cout << _pNode->iData << ' ';
	}
}

// =========================== ��� ==========================

typedef struct asciinode_struct asciinode;

struct asciinode_struct
{
	asciinode * left, *right;
	int edge_length;
	int height;
	int lablen;
	int parent_dir;
	char label[11];
};

struct tNode *ROOT;
struct tNode *NILL;
struct tNode *make_empty(struct tNode *t);
struct tNode *find_min(struct tNode *t);
struct tNode *find_max(struct tNode *t);
struct tNode *find(int elem, struct tNode *t);
struct tNode * pInsert(int value, struct tNode * t);
struct tNode * pDelete(int value, struct tNode * t);

int MIN(int X, int Y);
int MAX(int X, int Y);

asciinode * build_ascii_tree_recursive(struct node * t);
asciinode * build_ascii_tree(struct node * t);

void free_ascii_tree(asciinode *node);
void compute_lprofile(asciinode *node, int x, int y);
void compute_rprofile(asciinode *node, int x, int y);
void compute_edge_lengths(asciinode *node);
void print_level(asciinode *node, int x, int level);
void print_ascii_tree(struct node * t);

int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
int gap = 3;
int print_next;

struct tNode *make_empty(struct tNode *t)
{
	if (t != NULL)
	{
		make_empty(t->left);
		make_empty(t->right);
		free(t);
	}

	return NULL;
}

struct tNode *find_min(struct tNode *t)
{
	if (t == NILL)
	{
		return NULL;
	}
	else if (t->left == NILL)
	{
		return t;
	}
	else
	{
		return find_min(t->left);
	}
}

struct tNode *find_max(struct tNode *t)
{
	if (t == NILL)
	{
		return NULL;
	}
	else if (t->right == NILL)
	{
		return t;
	}
	else
	{
		return find_max(t->right);
	}
}

struct tNode *find(int elem, struct tNode *t)
{
	if (t == NILL)
	{
		return NULL;
	}

	if (elem < t->iData)
	{
		return find(elem, t->left);
	}
	else if (elem > t->iData)
	{
		return find(elem, t->right);
	}
	else
	{
		return t;
	}
}


struct tNode * pInsert(int value, struct tNode * t)
{
	struct tNode * new_node;

	if (t == NILL)
	{
		new_node = (struct tNode *)malloc(sizeof(struct tNode));
		if (new_node == NULL)
		{
			return t;
		}

		new_node->iData = value;

		new_node->left = new_node->right = NULL;
		return new_node;
	}

	if (value < t->iData)
	{
		t->left = pInsert(value, t->left);
	}
	else if (value > t->iData)
	{
		t->right = pInsert(value, t->right);
	}
	else
	{
		return t;
	}
	return t;
}

struct tNode * pDelete(int value, struct tNode * t)
{
	//struct tNode * x;
	struct tNode *tmp_cell;

	if (t == NILL) return NULL;

	if (value < t->iData)
	{
		t->left = pDelete(value, t->left);
	}
	else if (value > t->iData)
	{
		t->right = pDelete(value, t->right);
	}
	else if (t->left && t->right)
	{
		tmp_cell = find_min(t->right);
		t->iData = tmp_cell->iData;
		t->right = pDelete(t->iData, t->right);
	}
	else
	{
		tmp_cell = t;
		if (t->left == NILL)
			t = t->right;
		else if (t->right == NILL)
			t = t->left;
		free(tmp_cell);
	}

	return t;
}


int MIN(int X, int Y)
{
	return ((X) < (Y)) ? (X) : (Y);
}

int MAX(int X, int Y)
{
	return ((X) > (Y)) ? (X) : (Y);
}

asciinode * build_ascii_tree_recursive(struct tNode * t)
{
	asciinode * tNode;

	if (t == NILL) return NULL;

	tNode = (asciinode *)malloc(sizeof(asciinode));
	tNode->left = build_ascii_tree_recursive(t->left);
	tNode->right = build_ascii_tree_recursive(t->right);

	if (tNode->left != NULL)
	{
		tNode->left->parent_dir = -1;
	}

	if (tNode->right != NULL)
	{
		tNode->right->parent_dir = 1;
	}

	sprintf(tNode->label, "%d", t->iData);
	tNode->lablen = strlen(tNode->label);

	return tNode;
}

asciinode * build_ascii_tree(struct tNode * t)
{
	asciinode *tNode;
	if (t == NILL) return NULL;
	tNode = build_ascii_tree_recursive(t);
	tNode->parent_dir = 0;
	return tNode;
}

void free_ascii_tree(asciinode *tNode)
{
	if (tNode == NULL) return;
	free_ascii_tree(tNode->left);
	free_ascii_tree(tNode->right);
	free(tNode);
}

void compute_lprofile(asciinode *tNode, int x, int y)
{
	int i, isleft;
	if (tNode == NULL) return;
	isleft = (tNode->parent_dir == -1);
	lprofile[y] = MIN(lprofile[y], x - ((tNode->lablen - isleft) / 2));
	if (tNode->left != NULL)
	{
		for (i = 1; i <= tNode->edge_length && y + i < MAX_HEIGHT; i++)
		{
			lprofile[y + i] = MIN(lprofile[y + i], x - i);
		}
	}
	compute_lprofile(tNode->left, x - tNode->edge_length - 1, y + tNode->edge_length + 1);
	compute_lprofile(tNode->right, x + tNode->edge_length + 1, y + tNode->edge_length + 1);
}

void compute_rprofile(asciinode *tNode, int x, int y)
{
	int i, notleft;
	if (tNode == NULL) return;
	notleft = (tNode->parent_dir != -1);
	rprofile[y] = MAX(rprofile[y], x + ((tNode->lablen - notleft) / 2));
	if (tNode->right != NULL)
	{
		for (i = 1; i <= tNode->edge_length && y + i < MAX_HEIGHT; i++)
		{
			rprofile[y + i] = MAX(rprofile[y + i], x + i);
		}
	}
	compute_rprofile(tNode->left, x - tNode->edge_length - 1, y + tNode->edge_length + 1);
	compute_rprofile(tNode->right, x + tNode->edge_length + 1, y + tNode->edge_length + 1);
}

void compute_edge_lengths(asciinode *tNode)
{
	int h, hmin, i, delta;
	if (tNode == NULL) return;
	compute_edge_lengths(tNode->left);
	compute_edge_lengths(tNode->right);

	if (tNode->right == NULL && tNode->left == NULL)
	{
		tNode->edge_length = 0;
	}
	else
	{
		if (tNode->left != NULL)
		{
			for (i = 0; i<tNode->left->height && i < MAX_HEIGHT; i++)
			{
				rprofile[i] = -INFINITY;
			}
			compute_rprofile(tNode->left, 0, 0);
			hmin = tNode->left->height;
		}
		else
		{
			hmin = 0;
		}
		if (tNode->right != NULL)
		{
			for (i = 0; i<tNode->right->height && i < MAX_HEIGHT; i++)
			{
				lprofile[i] = INFINITY;
			}
			compute_lprofile(tNode->right, 0, 0);
			hmin = MIN(tNode->right->height, hmin);
		}
		else
		{
			hmin = 0;
		}
		delta = 4;
		for (i = 0; i<hmin; i++)
		{
			delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
		}

		if (((tNode->left != NULL && tNode->left->height == 1) ||
			(tNode->right != NULL && tNode->right->height == 1)) && delta>4)
		{
			delta--;
		}

		tNode->edge_length = ((delta + 1) / 2) - 1;
	}

	h = 1;
	if (tNode->left != NULL)
	{
		h = MAX(tNode->left->height + tNode->edge_length + 1, h);
	}
	if (tNode->right != NULL)
	{
		h = MAX(tNode->right->height + tNode->edge_length + 1, h);
	}
	tNode->height = h;
}

void print_level(asciinode *tNode, int x, int level)
{
	int i, isleft;
	if (tNode == NULL) return;
	isleft = (tNode->parent_dir == -1);
	if (level == 0)
	{
		for (i = 0; i<(x - print_next - ((tNode->lablen - isleft) / 2)); i++)
		{
			printf(" ");
		}
		print_next += i;
		printf("%s", tNode->label);
		print_next += tNode->lablen;
	}
	else if (tNode->edge_length >= level)
	{
		if (tNode->left != NULL)
		{
			for (i = 0; i<(x - print_next - (level)); i++)
			{
				printf(" ");
			}
			print_next += i;
			printf("/");
			print_next++;
		}
		if (tNode->right != NULL)
		{
			for (i = 0; i<(x - print_next + (level)); i++)
			{
				printf(" ");
			}
			print_next += i;
			printf("\\");
			print_next++;
		}
	}
	else
	{
		print_level(tNode->left,
			x - tNode->edge_length - 1,
			level - tNode->edge_length - 1);
		print_level(tNode->right,
			x + tNode->edge_length + 1,
			level - tNode->edge_length - 1);
	}
}

void print_ascii_tree(struct tNode * t)
{
	asciinode *proot;
	int xmin, i;
	if (t == NILL) return;
	proot = build_ascii_tree(t);
	compute_edge_lengths(proot);
	for (i = 0; i<proot->height && i < MAX_HEIGHT; i++)
	{
		lprofile[i] = INFINITY;
	}
	compute_lprofile(proot, 0, 0);
	xmin = 0;
	for (i = 0; i < proot->height && i < MAX_HEIGHT; i++)
	{
		xmin = MIN(xmin, lprofile[i]);
	}
	for (i = 0; i < proot->height; i++)
	{
		print_next = 0;
		print_level(proot, -xmin, i);
		printf("\n");
	}
	if (proot->height >= MAX_HEIGHT)
	{
		printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
	}
	free_ascii_tree(proot);
}

int main()
{
	srand((unsigned int)time(0));

	tNode* tHead = NULL;

	for(int i=0;i< 20;++i)
		tHead = insertTree(tHead, rand() % 100);

	int Select;
	int Num;

	while (true)
	{
		system("cls");
		print_ascii_tree(tHead);
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "3. �˻�" << endl;
		cout << "4.���� ��ȸ" << endl;
		cout << "5.���� ��ȸ" << endl;
		cout << "6.���� ��ȸ" << endl;
		cout << "�޴��� �����ϼ���(q�Է½� ����) : ";
		cin >> Select;

		switch (Select)
		{
		case 1:
			cout << "���� ���� �Է� : ";
			cin >> Num;
			tHead = insertTree(tHead, Num);
			system("pause");
			break;
		case 2:
			cout << "������ �� �Է�: ";
			cin >> Num;
			tHead = deleteTree(tHead, Num);
			system("pause");
			break;
		case 3:
			cout << "�˻��� �� �Է�: ";
			cin >> Num;
			searchTree(tHead, Num);
			system("pause");
			break;
		case 4:
			cout << "���� ��ȸ" << endl;
			preorder(tHead);
			cout << endl;
			system("pause");
			break;
		case 5:
			cout << "���� ��ȸ" << endl;
			inorder(tHead);
			cout << endl;
			system("pause");
			break;
		case 6:
			cout << "���� ��ȸ" << endl;
			postorder(tHead);
			cout << endl;
			system("pause");
			break;
		}
	}

	delete tHead;
}