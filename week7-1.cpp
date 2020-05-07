#include <iostream> // 2015112083 유성근
#include <string>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;
#define RED 1
#define BLACK 2

struct node { // 기본 노드
	int key;
	struct node* l;
	struct node* r;
	struct node* p;
	int color;
};
int Depth(struct node* head, struct node* want) { // 해당 노드까지의 깊이를 리턴
	struct node* tmp = head->r;
	int value = want->key;
	int depth = 1;
	while (tmp != head) {
		if (value == tmp->key) { return depth; } // 해당 노드 발견하면 그 깊이 리턴
		else if (value < tmp->key) { tmp = tmp->l; depth++; } // 자식으로 내려갈 때마다 깊이+1
		else { tmp = tmp->r; depth++; }
	}
}
int Height(struct node* head, struct node* now) { // 트리의 전체 높이, head->r부터 높이를 셈
	int height = 1; // 첫 노드의 높이 1
	int left = 0, right = 0;

	// 최상위 노드부터 recursive하게 좌우의 높이를 계산해서 max값을 리턴.
	if (now->l != head) left = Height(head, now->l);
	if (now->r != head) right = Height(head, now->r);

	return height += max(left, right);
}
void Left_Rotate(struct node* head, struct node* x) {
	struct node* y = x->r; // x노드의 우측 자식 y노드
	x->r = y->l; // y의 왼쪽 서브 트리를 x의 오른쪽 서브 트리로 옮김
	if (y->l != head) // head = T.nil = null의 역할. y의 왼쪽 자식이 null 아니면 y가 왼쪽 자식의 부모로 설정
		y->l->p = x; // null이면 따로 설정할 필요가 없다.

	y->p = x->p; // 기존 x의 부모를 y의 부모로 설정
	if (x->p == head) // 만약 x의 부모가 head(T.nil)이면 새로운 y가 root라는 표시로 head->r을 y로 설정해줌
		head->r = y;
	else if (x == x->p->l) // 부모가 head가 아닌 경우에 대해서 좌측 우측관련 부모자식 관계를 정리해줌
		x->p->l = y;
	else x->p->r = y;
	y->l = x; // y의 왼쪽에 x를 놓음
	x->p = y; // x의 부모는 y
}
void Right_Rotate(struct node* head, struct node* x) {
	struct node* y = x->l; // x노드의 좌측 자식 노드 y
	x->l = y->r; // y노드의 우측 서브 트리를 x노드의 좌측에 붙임
	if (y->r != head) // y노드의 우측 자식이 null이 아니면 해당 노드의 부모를 x로 재설정
		y->l->p = x;

	y->p = x->p; // 기존 x의 부모를 y의 부모로 설정
	if (x->p == head) // 만약 x의 부모가 head(T.nil)이면 새로운 y가 root라는 표시로 head->r을 y로 설정해줌
		head->r = y;
	else if (x == x->p->l) // 부모가 head가 아닌 경우에 대해서 좌측 우측관련 부모자식 관계를 정리해줌
		x->p->l = y;
	else x->p->r = y;
	y->r = x; // y의 오른쪽에 x를 놓음
	x->p = y; // x의 부모는 y
}
void Insert_Fix(struct node* head, struct node* z) {
	while (z->p->color == RED) { // 새로 넣는 노드는 무조건 RED이기 때문에 부모가 RED일 때 문제가 생김
		if (z->p == z->p->p->l) { // z의 부모가 그 부모의 왼쪽 자식
			struct node* y = z->p->p->r; // 삼촌 노드 y
			if (y->color == RED) { // case1. 삼촌 노드가 적색
				z->p->color = BLACK; // 부모와 그 sibling은 흑색으로 바꾸고, 그 부모는 적색으로 바꾼다.
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p; // 다음으로 z를 조부 위치로 올려서 다시 조사
			}
			else if (z == z->p->r) { // case2. 삼촌 노드가 흑색, z가 부모의 오른쪽 자식
				z = z->p;
				Left_Rotate(head, z); // 좌회전을 해준다.
			}
			else { // case3. 삼촌 노드가 흑색, z가 부모의 왼쪽 자식
				z->p->color = BLACK; // 부모를 흑색으로
				z->p->p->color = RED; // 조부를 적색으로 바꾸고
				Right_Rotate(head, z->p->p); // 우회전을 해준다.
			}
		}
		else { // z의 부모가 그 부모의 오른쪽 자식
			struct node* y = z->p->p->l; // 삼촌 노드 y
			if (y->color == RED) { // case1. 삼촌 노드가 적색
				z->p->color = BLACK; // 부모와 그 sibling은 흑색으로 바꾸고, 그 부모는 적색으로 바꾼다.
				y->color = BLACK;
				z->p->p->color = RED;
				z = z->p->p; // 다음으로 z를 조부 위치로 올려서 다시 조사
			}
			else if (z == z->p->l) { // 위 case2 대칭. 삼촌 노드가 흑색, z가 부모의 왼쪽 자식
				z = z->p;
				Right_Rotate(head, z); // 우회전을 해준다.
			}
			else { // 위 case3의 대칭. 삼촌 노드가 흑색, z가 부모의 오른쪽 자식
				z->p->color = BLACK; // 부모를 흑색으로
				z->p->p->color = RED; // 조부를 적색으로 바꾸고
				Left_Rotate(head, z->p->p); // 좌회전을 해준다.
			}
		}
	}
	head->r->color = BLACK; // 루트의 색깔은 무조건 흑색(레드블랙 트리의 2번 특성)
}
void Insert(struct node* head, int value) {
	struct node* y = head; // T.nil
	struct node* x = head->r; // root 노드
	struct node* z = (struct node*) malloc(sizeof * z); // 새로 넣을 노드 z
	z->color = RED; // insert 노드는 적색
	z->key = value;
	if (head->r == NULL) { // 처음 노드를 insert할 때 
		head->r = z;
		z->l = head; z->r = head;
		z->p = head;
		Insert_Fix(head, z); // 레드블랙 트리 특성 복구
		return;
	}

	while (x != head) { // z를 넣은 위치를 찾기
		y = x; // y에 넣을 위치의 부모위치가 저장됨
		if (z->key < x->key)
			x = x->l;
		else x = x->r;
	}
	z->p = y; // 찾은 y위치를 z의 부모위치로 함
	if (y == head) // 부모 y가 T.nil이라면 root를 z로 함
		head->r = z;
	else if (z->key < y->key) // 아니라면 부모 y와 비교해서 맞는 위치에 z를 넣음
		y->l = z;
	else y->r = z;

	z->l = head; z->r = head; // z의 좌, 우를 T.nil(head)로 설정
	Insert_Fix(head, z); // 레드블랙 트리 특성 복구
}
void Print(struct node* head) {
	cout << endl;
	if (head->r == NULL)
		cout << "Empty tree" << endl;
	else {
		int h = Height(head, head->r); // 트리 전체의 높이
		int dep = 1; // 현재 노드의 깊이
		int blank = pow(2, h - 1) - 1; // 최초의 빈칸

		queue<pair<struct node*, int>> q; // 노드, 해당 노드가 몇 번째 노드인지
		q.push({ head->r , 1 }); // 첫 노드 추가
		vector<int> v; // 노드들의 번째 수를 저장
		char token;
		bool isLeft, isRight; // 좌, 우 자식 노드가 존재하는지

		while (!q.empty()) {
			if (dep != Depth(head, q.front().first)) { // 현재 조사중인 노드의 깊이가 이전 깊이와 달라지면 한 층 내려간 것
				dep = Depth(head, q.front().first); // 현재 층 갱신
				h--; // 아래층 높이에서의 blank를 구해주기 위해 h를 하나 줄임
				blank = pow(2, h - 1) - 1;
				v.clear(); // 벡터 비워주기
				cout << endl;
			}
			struct node* tmp = q.front().first;
			int nowNum = q.front().second;
			v.push_back(nowNum);

			isLeft = false; isRight = false;
			if (tmp->l != head) { // 왼쪽 자식 노드 존재시
				q.push({ tmp->l, nowNum * 2 - 1 });
				isLeft = true;
			}
			if (tmp->r != head) { // 오른쪽 자식 노드 존재시
				q.push({ tmp->r, nowNum * 2 });
				isRight = true;
			}
			if (isLeft && isRight) // 둘 다 존재
				token = '^';
			else if (isLeft) // 왼쪽만
				token = '/';
			else if (isRight) // 오른쪽만
				token = '\\';
			else token = 'X'; // 자식 노드 없음

			for (int i = 0; i < blank; i++) // 가장 왼쪽 빈칸 출력
				cout << "  ";
			int nblank = (blank + 1) * 2; // 중간에 들어갈 빈칸 개수 구하기

			if (v.size() == 1 && v.back() > 1) { // 첫 등장노드가 1번이 아닐 때 
				int iter = v.back() - 1;
				for (int i = 0; i < iter; i++) { // 없는 노드 수만큼 빈칸 출력
					cout << "  "; // 없는 노드 빈칸
					for (int j = 0; j < nblank; j++) // 노드 사이 빈칸
						cout << "  ";
				}
			}
			if (v.size() > 1) {
				int iter = v.back() - v[v.size() - 2]; // 이전 노드의 순번과의 차이만큼
				for (int i = 0; i < iter; i++) // 빈칸 출력
					for (int j = 0; j < nblank; j++) // 노드 사이 빈칸
						cout << "  ";
				if (iter > 1) // 생략된 노드 수 만큼 빈칸 출력 
					for (int i = 0; i < iter - 1; i++)
						cout << "  ";
			}

			if (tmp->key != NULL) {
				cout << tmp->key; // 키 값 출력
				if (tmp->color == RED) // 칼라 출력
					cout << "r";
				else cout << "b";
				cout << token; // 자식 노드 상태 출력
			}

			q.pop();
		}
	}
	cout << endl << endl;
}
int main() {
	cout << "Commands" << endl << "+key : Insert key" << endl << "Q : Quit the program" << endl << endl;
	// init tree
	struct node* head = (struct node*) malloc(sizeof * head); // T.nil 역할을 하는 노드
	head->r = NULL; head->l = NULL; head->p = NULL; head->key = 0; head->color = BLACK;

	while (true) {
		Print(head);
		cout << "Input Command :";
		string com;
		cin >> com;

		string tmp;
		switch (com[0]) {
		case 'Q': // 프로그램 종료
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