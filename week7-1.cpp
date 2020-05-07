#include <iostream> // 2015112083 ������
#include <string>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;
#define RED 1
#define BLACK 2

struct node { // �⺻ ���
	int key;
	struct node* l;
	struct node* r;
	struct node* p;
	int color;
};
int Depth(struct node* head, struct node* want) { // �ش� �������� ���̸� ����
	struct node* tmp = head->r;
	int value = want->key;
	int depth = 1;
	while (tmp != head) {
		if (value == tmp->key) { return depth; } // �ش� ��� �߰��ϸ� �� ���� ����
		else if (value < tmp->key) { tmp = tmp->l; depth++; } // �ڽ����� ������ ������ ����+1
		else { tmp = tmp->r; depth++; }
	}
}
int Height(struct node* head, struct node* now) { // Ʈ���� ��ü ����, head->r���� ���̸� ��
	int height = 1; // ù ����� ���� 1
	int left = 0, right = 0;

	// �ֻ��� ������ recursive�ϰ� �¿��� ���̸� ����ؼ� max���� ����.
	if (now->l != head) left = Height(head, now->l);
	if (now->r != head) right = Height(head, now->r);

	return height += max(left, right);
}
void Left_Rotate(struct node* head, struct node* x) {
	struct node* y = x->r; // x����� ���� �ڽ� y���
	x->r = y->l; // y�� ���� ���� Ʈ���� x�� ������ ���� Ʈ���� �ű�
	if (y->l != head) // head = T.nil = null�� ����. y�� ���� �ڽ��� null �ƴϸ� y�� ���� �ڽ��� �θ�� ����
		y->l->p = x; // null�̸� ���� ������ �ʿ䰡 ����.

	y->p = x->p; // ���� x�� �θ� y�� �θ�� ����
	if (x->p == head) // ���� x�� �θ� head(T.nil)�̸� ���ο� y�� root��� ǥ�÷� head->r�� y�� ��������
		head->r = y;
	else if (x == x->p->l) // �θ� head�� �ƴ� ��쿡 ���ؼ� ���� �������� �θ��ڽ� ���踦 ��������
		x->p->l = y;
	else x->p->r = y;
	y->l = x; // y�� ���ʿ� x�� ����
	x->p = y; // x�� �θ�� y
}
void Right_Rotate(struct node* head, struct node* x) {
	struct node* y = x->l; // x����� ���� �ڽ� ��� y
	x->l = y->r; // y����� ���� ���� Ʈ���� x����� ������ ����
	if (y->r != head) // y����� ���� �ڽ��� null�� �ƴϸ� �ش� ����� �θ� x�� �缳��
		y->l->p = x;

	y->p = x->p; // ���� x�� �θ� y�� �θ�� ����
	if (x->p == head) // ���� x�� �θ� head(T.nil)�̸� ���ο� y�� root��� ǥ�÷� head->r�� y�� ��������
		head->r = y;
	else if (x == x->p->l) // �θ� head�� �ƴ� ��쿡 ���ؼ� ���� �������� �θ��ڽ� ���踦 ��������
		x->p->l = y;
	else x->p->r = y;
	y->r = x; // y�� �����ʿ� x�� ����
	x->p = y; // x�� �θ�� y
}
void Insert_Fix(struct node* head, struct node* z) {
	while (z->p->color == RED) { // ���� �ִ� ���� ������ RED�̱� ������ �θ� RED�� �� ������ ����
		if (z->p == z->p->p->l) { // z�� �θ� �� �θ��� ���� �ڽ�
			struct node* y = z->p->p->r; // ���� ��� y
			if (y->color == RED) { // case1. ���� ��尡 ����
				z->p->color = BLACK; // �θ�� �� sibling�� ������� �ٲٰ�, �� �θ�� �������� �ٲ۴�.
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p; // �������� z�� ���� ��ġ�� �÷��� �ٽ� ����
			}
			else if (z == z->p->r) { // case2. ���� ��尡 ���, z�� �θ��� ������ �ڽ�
				z = z->p;
				Left_Rotate(head, z); // ��ȸ���� ���ش�.
			}
			else { // case3. ���� ��尡 ���, z�� �θ��� ���� �ڽ�
				z->p->color = BLACK; // �θ� �������
				z->p->p->color = RED; // ���θ� �������� �ٲٰ�
				Right_Rotate(head, z->p->p); // ��ȸ���� ���ش�.
			}
		}
		else { // z�� �θ� �� �θ��� ������ �ڽ�
			struct node* y = z->p->p->l; // ���� ��� y
			if (y->color == RED) { // case1. ���� ��尡 ����
				z->p->color = BLACK; // �θ�� �� sibling�� ������� �ٲٰ�, �� �θ�� �������� �ٲ۴�.
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p; // �������� z�� ���� ��ġ�� �÷��� �ٽ� ����
			}
			else if (z == z->p->l) { // �� case2 ��Ī. ���� ��尡 ���, z�� �θ��� ���� �ڽ�
				z = z->p;
				Right_Rotate(head, z); // ��ȸ���� ���ش�.
			}
			else { // �� case3�� ��Ī. ���� ��尡 ���, z�� �θ��� ������ �ڽ�
				z->p->color = BLACK; // �θ� �������
				z->p->p->color = RED; // ���θ� �������� �ٲٰ�
				Left_Rotate(head, z->p->p); // ��ȸ���� ���ش�.
			}
		}
	}
	head->r->color = BLACK; // ��Ʈ�� ������ ������ ���(����� Ʈ���� 2�� Ư��)
}
void Insert(struct node* head, int value) {
	struct node* y = head; // T.nil
	struct node* x = head->r; // root ���
	struct node* z = (struct node*) malloc(sizeof * z); // ���� ���� ��� z
	z->color = RED; // insert ���� ����
	z->key = value;
	if (head->r == NULL) { // ó�� ��带 insert�� �� 
		head->r = z;
		z->l = head; z->r = head;
		z->p = head;
		Insert_Fix(head, z); // ����� Ʈ�� Ư�� ����
		return;
	}

	while (x != head) { // z�� ���� ��ġ�� ã��
		y = x; // y�� ���� ��ġ�� �θ���ġ�� �����
		if (z->key < x->key)
			x = x->l;
		else x = x->r;
	}
	z->p = y; // ã�� y��ġ�� z�� �θ���ġ�� ��
	if (y == head) // �θ� y�� T.nil�̶�� root�� z�� ��
		head->r = z;
	else if (z->key < y->key) // �ƴ϶�� �θ� y�� ���ؼ� �´� ��ġ�� z�� ����
		y->l = z;
	else y->r = z;

	z->l = head; z->r = head; // z�� ��, �츦 T.nil(head)�� ����
	Insert_Fix(head, z); // ����� Ʈ�� Ư�� ����
}
void Print(struct node* head) {
	cout << endl;
	if (head->r == NULL)
		cout << "Empty tree" << endl;
	else {
		int h = Height(head, head->r); // Ʈ�� ��ü�� ����
		int dep = 1; // ���� ����� ����
		int blank = pow(2, h - 1) - 1; // ������ ��ĭ

		queue<pair<struct node*, int>> q; // ���, �ش� ��尡 �� ��° �������
		q.push({ head->r , 1 }); // ù ��� �߰�
		vector<int> v; // ������ ��° ���� ����
		char token;
		bool isLeft, isRight; // ��, �� �ڽ� ��尡 �����ϴ���

		while (!q.empty()) {
			if (dep != Depth(head, q.front().first)) { // ���� �������� ����� ���̰� ���� ���̿� �޶����� �� �� ������ ��
				dep = Depth(head, q.front().first); // ���� �� ����
				h--; // �Ʒ��� ���̿����� blank�� �����ֱ� ���� h�� �ϳ� ����
				blank = pow(2, h - 1) - 1;
				v.clear(); // ���� ����ֱ�
				cout << endl;
			}
			struct node* tmp = q.front().first;
			int nowNum = q.front().second;
			v.push_back(nowNum);

			isLeft = false; isRight = false;
			if (tmp->l != head) { // ���� �ڽ� ��� �����
				q.push({ tmp->l, nowNum * 2 - 1 });
				isLeft = true;
			}
			if (tmp->r != head) { // ������ �ڽ� ��� �����
				q.push({ tmp->r, nowNum * 2 });
				isRight = true;
			}
			if (isLeft && isRight) // �� �� ����
				token = '^';
			else if (isLeft) // ���ʸ�
				token = '/';
			else if (isRight) // �����ʸ�
				token = '\\';
			else token = 'X'; // �ڽ� ��� ����

			for (int i = 0; i < blank; i++) // ���� ���� ��ĭ ���
				cout << "  ";
			int nblank = (blank + 1) * 2; // �߰��� �� ��ĭ ���� ���ϱ�

			if (v.size() == 1 && v.back() > 1) { // ù �����尡 1���� �ƴ� �� 
				int iter = v.back() - 1;
				for (int i = 0; i < iter; i++) { // ���� ��� ����ŭ ��ĭ ���
					cout << "  "; // ���� ��� ��ĭ
					for (int j = 0; j < nblank; j++) // ��� ���� ��ĭ
						cout << "  ";
				}
			}
			if (v.size() > 1) {
				int iter = v.back() - v[v.size() - 2]; // ���� ����� �������� ���̸�ŭ
				for (int i = 0; i < iter; i++) // ��ĭ ���
					for (int j = 0; j < nblank; j++) // ��� ���� ��ĭ
						cout << "  ";
				if (iter > 1) // ������ ��� �� ��ŭ ��ĭ ��� 
					for (int i = 0; i < iter - 1; i++)
						cout << "  ";
			}

			if (tmp->key != NULL) {
				cout << tmp->key; // Ű �� ���
				if (tmp->color == RED) // Į�� ���
					cout << "r";
				else cout << "b";
				cout << token; // �ڽ� ��� ���� ���
			}

			q.pop();
		}
	}
	cout << endl << endl;
}
int main() {
	cout << "Commands" << endl << "+key : Insert key" << endl << "Q : Quit the program" << endl << endl;
	// init tree
	struct node* head = (struct node*) malloc(sizeof * head); // T.nil ������ �ϴ� ���
	head->r = NULL; head->l = NULL; head->p = NULL; head->key = 0; head->color = BLACK;

	while (true) {
		Print(head);
		cout << "Input Command :";
		string com;
		cin >> com;

		string tmp;
		switch (com[0]) {
		case 'Q': // ���α׷� ����
		{
			cout << "Shutdown the program...";
			return 0;
			break;
		}
		case '+':
		{
			for (int i = 1; i < com.size(); i++)
				tmp += com[i];
			Insert(head, stoi(tmp));
			break;
		}
		}
	}
}