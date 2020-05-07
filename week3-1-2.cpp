#include <iostream> // 2015112083 유성근
#include <vector>
using namespace std;

void Print(int* a) { // a배열을 출력하는 함수
	for (int i = 1; i <= 10; i++) // 첫 번째 값에는 dummy data인 0이 들어가므로 출력 안 함
		cout << a[i] << " ";
	cout << endl;
}

// not recursive mergesort 
void Merge(int* a, int left, int mid, int right) { 
	int b[11]; // 버퍼로 사용될 배열. 제자리성이 지켜지지 않는다.
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
	for (int i = 1; i < 10; i *= 2) {
		left = 1; // 항상 처음 인덱스부터 확인해야 함
		while (left <= 10) { // left가 끝 인덱스에 도달하지 않는 한
			right = left + 2 * i - 1; // 블록의 크기가 2, 4, 8.. 이런식으로 되도록 right의 값을 설정
			// 블록의 크기가 커지면서 오른쪽 블록이 왼쪽 블록 크기만큼 안 될 수 있다. 그럴 경우 최대값인 10으로 재설정
			if (right > 10) right = 10; 

			mid = left + i - 1; // right가 left+2*i-1 이라는 점에서 mid값은 그 가운데인 left+i-1이 적합하다.
			if (mid <= 10) // mid가 최대값을 넘어선 경우는 이미 전의 i 상황에서 정렬이 완료된 배열이다.
				Merge(a, left, mid, right); // 정렬 수행
			left = right + 1; // 다음 left는 이전 right의 이후로 설정
			Print(a);
		}
	}
}

int main() {
	// 첫 값을 dummy data인 0으로 설정
	int a[11] = { 0, 30, 20, 40, 35, 5, 50, 45, 10, 25, 15 }; 
	MergeSort(a, 1, 10); // 1~10에 위치한 원소들을 정렬
}