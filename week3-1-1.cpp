#include <iostream> // 2015112083 유성근
#include <vector>
using namespace std;

void Print(int* a) { // a배열을 출력하는 함수
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;
}

// recursive mergesort 
void Merge(int* a, int left, int mid, int right) { 
	int b[10]; // 버퍼로 사용될 배열. 제자리성이 지켜지지 않는다.
	int leftFind = left; // 맨 왼쪽 원소(left)부터 가운데(mid)까지 탐색
	int rightFind = mid + 1; // 오른쪽 처음 원소(mid+1)부터 맨 오른쪽 원소(right)까지 탐색
	int bufferFind = left; // 버퍼배열 b에 집어넣을 때 사용할 인덱스

	while (leftFind <= mid && rightFind <= right) { // 좌우 배열 중 하나라도 모두 탐색하면 탈출
		if (a[leftFind] < a[rightFind]) // 현재 탐색중인 좌우 원소 중 더 작은 값을 버퍼에 집어 넣고 인덱스 증가
			b[bufferFind++] = a[leftFind++];
		else 
			b[bufferFind++] = a[rightFind++];
	}

	if (leftFind > mid) // 후처리. 왼쪽을 모두 탐색했고 오른쪽에 남았다면
		for (int i = rightFind; i <= right; i++) // 남은 원소 차례대로 버퍼에 추가
			b[bufferFind++] = a[i];
	else // 반대의 경우
		for (int i = leftFind; i <= mid; i++)
			b[bufferFind++] = a[i];
	
	for (int i = left; i <= right; i++) // 버퍼에 저장한 순서대로 a에 다시 덮어 씌우기
		a[i] = b[i];
}

void MergeSort(int* a, int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2; // 중간값 mid를 계산
		MergeSort(a, left, mid); // 분할된 좌우 배열을 모두 recursive하게 계속 분할
		MergeSort(a, mid + 1, right);
		Merge(a, left, mid, right); // 정렬이 진행
		Print(a);
	}
}

int main() {
	int a[10] = { 30, 20, 40, 35, 5, 50, 45, 10, 25, 15 };
	MergeSort(a, 0, 9);
}