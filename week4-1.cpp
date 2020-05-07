#include <iostream> // 2015112083 유성근
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int Minimum(int* arr, int n) {
	int min = arr[0]; // 최소값이 저장될 변수 min
	for (int i = 1; i < n; i++) { // arr 배열의 모든 원소에 대해
		if (min > arr[i]) // min에 저장된 최소값보다 더 작은 수가 나오면
			min = arr[i]; // 그 수로 min을 갱신
	}
	return min; // 찾은 min값 리턴
}
int Maximum(int* arr, int n) {
	int max = arr[0]; // 최대값이 저장될 변수 max
	for (int i = 1; i < n; i++) { // arr 배열의 모든 원소에 대해
		if (max < arr[i]) // max에 저장된 최대값보다 더 큰 수가 나오면
			max = arr[i]; // 그 수로 max를 갱신
	}
	return max; // 찾은 max값 리턴
}

void FindMinMax(int* arr, int n, int& min, int& max) {
	min = max = arr[0]; // min, max 값을 모두 첫 원소로 초기화

	int small, big;
	for (int i = 1; i < n - 1; i += 2) { // i를 동시에 두 개씩 증가
		// 두 개씩 조사. 작은 수를 small에, 큰 수를 big에 넣는다.
		if (arr[i] < arr[i + 1]) {
			big = arr[i + 1]; small = arr[i];
		}
		else {
			big = arr[i]; small = arr[i + 1];
		}
		if (small < min) // big은 어차피 small보다 크므로 최소값 후보자격 없음
			min = small; // 만약 small이 min보다 작으면 갱신
		if (big > max) // min과 같은 방식으로 max를 탐색
			max = big;
	}
}

int main() {
	int arr[1000];

	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		arr[i] = rand() % 100000 + 1; // 1~100000 범위 내의 난수 생성
	}

	cout << "Minimum, Maximum 함수 결과" << endl;
	cout << "최소값 : " << Minimum(arr, 1000) << endl << "최대값 : " << Maximum(arr, 1000) << endl;

	int min, max; // 최소, 최대를 저장할 변수
	cout << "FindMinMax 함수 결과" << endl;
	FindMinMax(arr, 1000, min, max); // 침조자로 파라미터를 넘겨 min, max값을 찾는다.
	cout << "최소값 : " << min << endl << "최대값 : " << max;
}