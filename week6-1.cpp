#include <iostream> // 2015112083 ������
#include <string>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;

struct node { // �⺻ ���
	int key;
	struct node* l;
	struct node* r;
};
int Depth(struct node* head, struct node* want) { // �ش� �������� ���̸� ����
	struct node* tmp = head->r;
	int value = want->key; 
	int depth = 1; 
	while (tmp != NULL) {
		if (value == tmp->key) { return depth; } // �ش� ��� �߰��ϸ� �� ���� ����
		else if (value < tmp->key) { tmp = tmp->l; depth++; } // �ڽ����� ������ ������ ����+1
		else { tmp = tmp->r; depth++; }
	}
}
int Height(struct node* now) { // Ʈ���� ��ü ����, head->r���� ���̸� ��
	int height = 1; // ù ����� ���� 1
	int left = 0, right = 0;

	// �ֻ��� ������ recursive�ϰ� �¿��� ���̸� ����ؼ� max���� ����.
	if (now->l != NULL) left = Height(now->l);
	if (now->r != NULL) right = Height(now->r);

	return height += max(left, right);
}
struct node* Search(struct node* head, int value) {
	struct node* tmp; // �ӽ� ���(�˻��� ���)
	tmp = head->r; // ù ���� head�� �����ʿ� �پ��ִ�.
	while (tmp != NULL) { // tmp�� Ž��
		if (value == tmp->key) return tmp; // tmp�� ���ϴ� ���� ����
		else if (value < tmp->key) tmp = tmp->l; // ���ϴ� ���� ���� ������ ������ ���� Ž��
		else tmp = tmp->r; // �ݴ��� ���
	}
	return NULL; // ���ϴ� �� ��ã�� tmp Ž���� ������(NULL) NULL ����
}
void Insert(struct node* head, int value) {
	struct node* p; // ���ϴ� ���� ���� �� ����� �θ���
	struct node* tmp; // ���ϴ� ���� ���� ���
	p = head; tmp = p->r;
	while (tmp != NULL) { // Search�� ���� ������� ���� �ڸ��� ã��
		p = tmp; // tmp�� �� ĭ �Ʒ��� �������� Ž���ϹǷ� p�� �� ĭ ������
		if (value == tmp->key) return; // �̹� �ְ� ���� ���� �����ϸ� �׳� ����
		else if (value < tmp->key) tmp = tmp->l;
		else tmp = tmp->r;
	}
	tmp = (struct node*) malloc(sizeof *tmp); // tmp��� ���� �Ҵ�
	tmp->key = value; // ���� �־���
	tmp->l = NULL; tmp->r = NULL; // �¿츦 NULL�� �ʱ�ȭ
	if (value < p->key) p->l = tmp; // �θ���� ���ؼ� �´� �ڸ��� �־���
	else p->r = tmp;
}
void Delete(struct node* head, int value) {
	struct node *p, *c, *tmp, *del;
	p = head; del = head->r; // ������ ����� �θ���� ������ ���
	while (del != NULL) {
		if (value == del->key) { break; } // value�� ���� ��� del�� ã���� Ż��
		else if (value < del->key) { p = del; del = del->l; } // p�� ���� del ��ġ, del�� �� �ڽ����� ������
		else { p = del; del = del->r; }
	}
	if (del == NULL) { cout << "There's no such value" << endl; return; } // ������ ��� �������� ������ �׳� ����
	else tmp = del; // tmp ��忡 del ��ġ ����
	// 1. ������ �ڽ��� ���� ��� : �ش� ����� ���� �ڽ��� �ش� ��� �ڸ��� �÷�����(�θ���� ����� ���� �ڽ� �����Ŵ)
	if (tmp->r == NULL) del = tmp->l;
	else if (tmp->r->l == NULL) {
		// 2. ������ �ڽ��� ���� �ڽ��� ���� ��� : �θ���� �ش� ����� ������ �ڽ��� ����
		// �� �� ���� �ö�� '�ش� ����� ������ �ڽ�'�� ���� �ڽĿ� ���� ����� ���� �ڽ��� �ٿ���
		del = tmp->r; del->l = tmp->l;
	}
	else { // 3. ������ ��� ��쿡 ���ؼ�
		c = del->r; // ������ ����� ������ �κ� ���� �߿���
		while (c->l->l != NULL) // 'c->l'���� ���� ���� �� ã��. ���ʿ� ������ ���� ���� ����ǹǷ� l�� �˻�
			c = c->l;
		del = c->l; // del�� ���� ���� ��(c->l)�� ��� ����
		c->l = c->l->r; // ���� ���� ��(c->l)�� �����ʿ� �پ��ִ� ��(c->l->r)�� c->l�� �ٿ�����
		del->l = tmp->l; // ���� del�� �ٲ�����Ƿ� �����ص� tmp���� l, r�� ������ �ٿ��ֱ�
		del->r = tmp->r;
	}
	if (value < p->key) p->l = del; // p�� ���ؼ� �´� ��ġ�� ���� del��� ����
	else p->r = del;
}
void Print(struct node* head) {
	cout << endl;
	if (head->r == NULL)
		cout << "Empty tree" << endl;
	else {
		int h = Height(head->r); // Ʈ�� ��ü�� ����
		int dep = 1; // ���� ����� ����
		int blank = pow(2, h - 1) - 1; // ������ ��ĭ
		
		queue<pair<struct node*, int>> q; // ���, �ش� ��尡 �� ��° �������
		q.push({ head->r , 1}); // ù ��� �߰�
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
			if (tmp->l != NULL) { // ���� �ڽ� ��� �����
				q.push({ tmp->l, nowNum * 2 - 1 });
				isLeft = true;
			}
			if (tmp->r != NULL) { // ������ �ڽ� ��� �����
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
				cout << token; // �ڽ� ��� ���� ���
			}

			q.pop();
		}
	}
	cout << endl << endl;
}
int main() {
	cout << "Commands" << endl << "+key : Insert key" << endl << "?key : Search key" << endl;
	cout << "-key : Delete key" << endl << "Q : Quit the program" << endl << endl;
	// init tree
	struct node* head = (struct node*) malloc(sizeof * head);
	head->r = NULL; head->l = NULL; head->key = 0;

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
		case '?':
		{
			for (int i = 1; i < com.size(); i++)
				tmp += com[i];
			struct node* tnode = Search(head, stoi(tmp));
			if (tnode) {
				cout << "Searched : " << tnode->key << endl;
				cout << "Left Child : ";
				if (tnode->l) cout << tnode->l->key << endl;
				else cout << "none" << endl;
				cout << "Right Child : ";
				if (tnode->r) cout << tnode->r->key << endl;
				else cout << "none" << endl;
			}
			else cout << "There's no such value" << endl;
			break;
		}
		case '-':
		{
			for (int i = 1; i < com.size(); i++)
				tmp += com[i];
			Delete(head, stoi(tmp));
			break;
		}
		}
	}
}