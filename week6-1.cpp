#include <iostream> // 2015112083 유성근
#include <string>
#include <queue>
#include <cmath>
#include <vector>
using namespace std;

struct node { // 기본 노드
	int key;
	struct node* l;
	struct node* r;
};
int Depth(struct node* head, struct node* want) { // 해당 노드까지의 깊이를 리턴
	struct node* tmp = head->r;
	int value = want->key; 
	int depth = 1; 
	while (tmp != NULL) {
		if (value == tmp->key) { return depth; } // 해당 노드 발견하면 그 깊이 리턴
		else if (value < tmp->key) { tmp = tmp->l; depth++; } // 자식으로 내려갈 때마다 깊이+1
		else { tmp = tmp->r; depth++; }
	}
}
int Height(struct node* now) { // 트리의 전체 높이, head->r부터 높이를 셈
	int height = 1; // 첫 노드의 높이 1
	int left = 0, right = 0;

	// 최상위 노드부터 recursive하게 좌우의 높이를 계산해서 max값을 리턴.
	if (now->l != NULL) left = Height(now->l);
	if (now->r != NULL) right = Height(now->r);

	return height += max(left, right);
}
struct node* Search(struct node* head, int value) {
	struct node* tmp; // 임시 노드(검색에 사용)
	tmp = head->r; // 첫 노드는 head의 오른쪽에 붙어있다.
	while (tmp != NULL) { // tmp로 탐색
		if (value == tmp->key) return tmp; // tmp에 원하는 값이 존재
		else if (value < tmp->key) tmp = tmp->l; // 원하는 값이 현재 값보다 작으면 왼쪽 탐색
		else tmp = tmp->r; // 반대의 경우
	}
	return NULL; // 원하는 값 못찾고 tmp 탐색이 끝나면(NULL) NULL 리턴
}
void Insert(struct node* head, int value) {
	struct node* p; // 원하는 값을 넣은 새 노드의 부모노드
	struct node* tmp; // 원하는 값을 넣을 노드
	p = head; tmp = p->r;
	while (tmp != NULL) { // Search와 같은 방식으로 넣을 자리를 찾음
		p = tmp; // tmp를 한 칸 아래로 내려가서 탐색하므로 p도 한 칸 내려줌
		if (value == tmp->key) return; // 이미 넣고 싶은 값이 존재하면 그냥 리턴
		else if (value < tmp->key) tmp = tmp->l;
		else tmp = tmp->r;
	}
	tmp = (struct node*) malloc(sizeof *tmp); // tmp노드 동적 할당
	tmp->key = value; // 값을 넣어줌
	tmp->l = NULL; tmp->r = NULL; // 좌우를 NULL로 초기화
	if (value < p->key) p->l = tmp; // 부모노드와 비교해서 맞는 자리에 넣어줌
	else p->r = tmp;
}
void Delete(struct node* head, int value) {
	struct node *p, *c, *tmp, *del;
	p = head; del = head->r; // 삭제될 노드의 부모노드와 삭제할 노드
	while (del != NULL) {
		if (value == del->key) { break; } // value를 갖는 노드 del을 찾으면 탈출
		else if (value < del->key) { p = del; del = del->l; } // p는 이전 del 위치, del은 그 자식으로 내려감
		else { p = del; del = del->r; }
	}
	if (del == NULL) { cout << "There's no such value" << endl; return; } // 삭제할 노드 존재하지 않으면 그냥 리턴
	else tmp = del; // tmp 노드에 del 위치 복사
	// 1. 오른쪽 자식이 없는 경우 : 해당 노드의 왼쪽 자식을 해당 노드 자리로 올려버림(부모노드와 노드의 왼쪽 자식 연결시킴)
	if (tmp->r == NULL) del = tmp->l;
	else if (tmp->r->l == NULL) {
		// 2. 오른쪽 자식의 왼쪽 자식이 없는 경우 : 부모노드와 해당 노드의 오른쪽 자식을 연결
		// 그 후 새로 올라온 '해당 노드의 오른쪽 자식'의 왼쪽 자식에 원래 노드의 왼쪽 자식을 붙여줌
		del = tmp->r; del->l = tmp->l;
	}
	else { // 3. 나머지 모든 경우에 대해서
		c = del->r; // 삭제할 노드의 오른쪽 부분 나무 중에서
		while (c->l->l != NULL) // 'c->l'값이 가장 작은 값 찾기. 왼쪽에 무조건 작은 값이 저장되므로 l만 검색
			c = c->l;
		del = c->l; // del에 가장 작은 값(c->l)을 잠시 복사
		c->l = c->l->r; // 가장 작은 값(c->l)의 오른쪽에 붙어있던 값(c->l->r)을 c->l에 붙여넣음
		del->l = tmp->l; // 새로 del이 바뀌었으므로 복사해둔 tmp에서 l, r값 가져와 붙여넣기
		del->r = tmp->r;
	}
	if (value < p->key) p->l = del; // p와 비교해서 맞는 위치에 변한 del노드 삽입
	else p->r = del;
}
void Print(struct node* head) {
	cout << endl;
	if (head->r == NULL)
		cout << "Empty tree" << endl;
	else {
		int h = Height(head->r); // 트리 전체의 높이
		int dep = 1; // 현재 노드의 깊이
		int blank = pow(2, h - 1) - 1; // 최초의 빈칸
		
		queue<pair<struct node*, int>> q; // 노드, 해당 노드가 몇 번째 노드인지
		q.push({ head->r , 1}); // 첫 노드 추가
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
			if (tmp->l != NULL) { // 왼쪽 자식 노드 존재시
				q.push({ tmp->l, nowNum * 2 - 1 });
				isLeft = true;
			}
			if (tmp->r != NULL) { // 오른쪽 자식 노드 존재시
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
				cout << token; // 자식 노드 상태 출력
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