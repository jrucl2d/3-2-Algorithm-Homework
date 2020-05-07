#include <iostream> // 2015112083 유성근
#include <vector>
using namespace std;

void Print(int* a) {
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;
}

void MakeHeap(int* a, int root, int end) { // MaxHeap을 만드는 함수
	int p = root; // 부모
	int p_value = a[p]; // 부모의 값
	int c, leftc, rightc; // 자식, 왼쪽 자식, 오른쪽 자식
	leftc = 2 * p + 1; 
	rightc = leftc + 1;

	while (leftc <= end) { // 끝에 왼쪽 자식 하나만 남는 경우도 고려
		if (rightc <= end && a[leftc] < a[rightc])
			c = rightc; // 더 큰 자식을 변수 c에 넣음
		else c = leftc;
		
		if (p_value < a[c]) { // 부모의 값보다 자식의 값이 크면
			a[p] = a[c]; // 자식의 값을 부모 위치로 올린다.
			p = c; // 현재의 c를 다음 p로 삼는다.
			leftc = p * 2 + 1; // 다음 p에 맞는 좌우 자식을 설정
			rightc = leftc + 1;
		}
		else break; // 부모의 값이 자식 값보다 크면 바꿀 것 없으므로 탈출
	}
	a[p] = p_value; // 위에서 p의 값을 이전의 c로 삼았으므로 원래 부모의 값을 넣어줌으로써 교환
}

void Swap(int& a, int& b) { // 값 교환 함수
	int tmp = b;
	b = a;
	a = tmp;
}

void HeapSort(int *a) {
	for (int i = 10 / 2; i >= 0; i--) // 힙 생성 알고리즘으로 최초에 힙을 생성
		MakeHeap(a, i, 9);
	Print(a); // 최초 힙 생성 후 출력
	for (int i = 9; i > 0; i--) {
		Swap(a[0], a[i]); // 0과 끝 원소를 교환
		MakeHeap(a, 0, i - 1); // 끝 원소에는 최대값이 있으므로 나머지를 또 힙으로 재정비
		Print(a); // 재정비 할 때마다 출력
	}
}

int main() {
	int a[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	HeapSort(a);
}