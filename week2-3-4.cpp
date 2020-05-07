#include <iostream> // 2015112083 유성근
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAX 10000 // 10000까지의 숫자
int k1[1000];
int k2[1000];
bool sorted = false; // 시간 단축을 위한 flag, false로 초기화

void Swap(int& a, int& b) { // 두 수 교환하는 함수
	int tmp = a;
	a = b;
	b = tmp;
}
// 재귀를 사용한 버블 정렬
void BubbleSort(int* v, int index) {
	if (!sorted) { // 이전 반복에서 바뀐 것이 있으면 계속 알고리즘 동작
		sorted = true;
		for (int i = 0; i < index; i++) {
			if (v[i] < v[i + 1]) { // 작은 수가 왼쪽에 있으면 교환.
				Swap(v[i], v[i + 1]);
				sorted = false; // 교환이 이루어졌으면 sorted를 false로 변경
			}
		}
	}
	else return; // 이전 반복에서 바뀐 것이 없으면 sorted가 true가 되므로 알고리즘 중단
	BubbleSort(v, index - 1);
}
// 재귀를 사용하지 않은 퀵 정렬
int Partition(int* v, int left, int right) {
	int pivot = v[left]; // 배열의 가장 왼쪽 원소를 피벗으로 삼는다.
	int low = left;
	int high = right + 1;
	do {
		do {} while (v[++low] > pivot); // low로 left+1부터 탐색하며 왼쪽에서 피벗보다 작은 원소 찾기
		do {} while (v[--high] < pivot); // high로 right부터 탐색하며 오른쪽에서 피벗보다 큰 원소 찾기
		if (low < high) { 
			// 아직 low와 high가 교차하지 않았는데 왼쪽에서 피벗보다 작은 원소와
			// 오른쪽에서 피벗보다 큰 원소를 찾으면 둘이 교환해준다.
			Swap(v[low], v[high]);
		}
	} while (low < high);
	Swap(v[left], v[high]); // 모든 교환이 끝났으면 high 위치의 값과 피벗 left 위치의 값을 교환해준다.
	return high; // 그리고 피벗의 위치인 high를 반환해준다.
}
void QuickSort(int *v, int left, int right) {
	vector<int> stack; // 스택처럼 사용할 벡터

	stack.push_back(left); // 스택에 넣을 때 left, right 순서대로 넣는다.
	stack.push_back(right);

	while (!stack.empty()) { // 스택이 비어있지 않은 한 반복
		right = stack.back(); // 넣은 순서 반대로 right, left 값 꺼낸다.
		stack.pop_back();
		left = stack.back();
		stack.pop_back();
		int pivot = Partition(v, left, right); // 피벗의 위치를 찾는다.

		if (pivot - 1 > left) { // left가 pivot-1보다 작은 동안은 아직 더 분할 가능
			stack.push_back(left); // 스택에 넣을 때는 left, right 순서대로 넣는다.
			stack.push_back(pivot - 1);
		}
		if (pivot + 1 < right) { // 우측도 마찬가지로 계속 분할 가능하면 분할한다.
			stack.push_back(pivot + 1);
			stack.push_back(right);
		}
	}
}

int main() {
	srand((unsigned int)time(NULL)); // 난수 생성
	for (int i = 0; i < 1000; i++) { // 1~10000의 숫자를 랜덤하게 1000번 생성해서 k에 저장
		k1[i] = k2[i] = rand() % MAX + 1; // n1은 버블 정렬, k2는 퀵 정렬로 정렬해서 비교
	}
	clock_t start1, end1; // 시간 측정을 위한 변수
	double res1; // 버블 정렬에 걸린 시간 저장

	start1 = clock(); // 시간 측정 시작
	BubbleSort(k1, 999); // 재귀 함수를 사용한 버블 정렬로 k1 배열 내림차순 정렬
	end1 = clock();
	res1 = (double)(end1 - start1) / CLOCKS_PER_SEC; // 버블 정렬에 걸린 시간

	clock_t start2, end2;
	double res2; // 퀵 정렬에 걸린 시간 저장

	start2 = clock(); // 시간 측정 시작
	QuickSort(k2, 0, 999); // 재귀 함수를 사용하지 않은 퀵 정렬로 k2 배열 내림차순 정렬
	end2 = clock();
	res2 = (double)(end2 - start2) / CLOCKS_PER_SEC; // 퀵 정렬에 걸린 시간
	
	bool same = true;
	for (int i = 0; i < 1000; i++) {
		if (k1[i] != k2[i]) // 한 번이라도 원소 배열이 다르다면 same은 false의 값을 가진다.
			same = false;
	}
	if (same)
		cout << "정렬 후 결과가 같습니다.\n";
	else cout << "정렬 후 결과가 다릅니다.\n";
	cout << "버블 정렬에 걸린 시간은 " << res1 << "이고, 퀵 정렬에 걸린 시간은 " << res2 << "입니다.";
}