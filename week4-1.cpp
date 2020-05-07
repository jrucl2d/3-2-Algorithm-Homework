#include <iostream> // 2015112083 ������
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int Minimum(int* arr, int n) {
	int min = arr[0]; // �ּҰ��� ����� ���� min
	for (int i = 1; i < n; i++) { // arr �迭�� ��� ���ҿ� ����
		if (min > arr[i]) // min�� ����� �ּҰ����� �� ���� ���� ������
			min = arr[i]; // �� ���� min�� ����
	}
	return min; // ã�� min�� ����
}
int Maximum(int* arr, int n) {
	int max = arr[0]; // �ִ밪�� ����� ���� max
	for (int i = 1; i < n; i++) { // arr �迭�� ��� ���ҿ� ����
		if (max < arr[i]) // max�� ����� �ִ밪���� �� ū ���� ������
			max = arr[i]; // �� ���� max�� ����
	}
	return max; // ã�� max�� ����
}

void FindMinMax(int* arr, int n, int& min, int& max) {
	min = max = arr[0]; // min, max ���� ��� ù ���ҷ� �ʱ�ȭ

	int small, big;
	for (int i = 1; i < n - 1; i += 2) { // i�� ���ÿ� �� ���� ����
		// �� ���� ����. ���� ���� small��, ū ���� big�� �ִ´�.
		if (arr[i] < arr[i + 1]) {
			big = arr[i + 1]; small = arr[i];
		}
		else {
			big = arr[i]; small = arr[i + 1];
		}
		if (small < min) // big�� ������ small���� ũ�Ƿ� �ּҰ� �ĺ��ڰ� ����
			min = small; // ���� small�� min���� ������ ����
		if (big > max) // min�� ���� ������� max�� Ž��
			max = big;
	}
}

int main() {
	int arr[1000];

	srand(time(NULL));
	for (int i = 0; i < 1000; i++) {
		arr[i] = rand() % 100000 + 1; // 1~100000 ���� ���� ���� ����
	}

	cout << "Minimum, Maximum �Լ� ���" << endl;
	cout << "�ּҰ� : " << Minimum(arr, 1000) << endl << "�ִ밪 : " << Maximum(arr, 1000) << endl;

	int min, max; // �ּ�, �ִ븦 ������ ����
	cout << "FindMinMax �Լ� ���" << endl;
	FindMinMax(arr, 1000, min, max); // ħ���ڷ� �Ķ���͸� �Ѱ� min, max���� ã�´�.
	cout << "�ּҰ� : " << min << endl << "�ִ밪 : " << max;
}