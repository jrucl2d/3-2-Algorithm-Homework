#include <iostream> // 2015112083 ������
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAX 10000 // 10000������ ����
int k1[1000];
int k2[1000];
bool sorted = false; // �ð� ������ ���� flag, false�� �ʱ�ȭ

void Swap(int& a, int& b) { // �� �� ��ȯ�ϴ� �Լ�
	int tmp = a;
	a = b;
	b = tmp;
}
// ��͸� ����� ���� ����
void BubbleSort(int* v, int index) {
	if (!sorted) { // ���� �ݺ����� �ٲ� ���� ������ ��� �˰��� ����
		sorted = true;
		for (int i = 0; i < index; i++) {
			if (v[i] < v[i + 1]) { // ���� ���� ���ʿ� ������ ��ȯ.
				Swap(v[i], v[i + 1]);
				sorted = false; // ��ȯ�� �̷�������� sorted�� false�� ����
			}
		}
	}
	else return; // ���� �ݺ����� �ٲ� ���� ������ sorted�� true�� �ǹǷ� �˰��� �ߴ�
	BubbleSort(v, index - 1);
}
// ��͸� ������� ���� �� ����
int Partition(int* v, int left, int right) {
	int pivot = v[left]; // �迭�� ���� ���� ���Ҹ� �ǹ����� ��´�.
	int low = left;
	int high = right + 1;
	do {
		do {} while (v[++low] > pivot); // low�� left+1���� Ž���ϸ� ���ʿ��� �ǹ����� ���� ���� ã��
		do {} while (v[--high] < pivot); // high�� right���� Ž���ϸ� �����ʿ��� �ǹ����� ū ���� ã��
		if (low < high) { 
			// ���� low�� high�� �������� �ʾҴµ� ���ʿ��� �ǹ����� ���� ���ҿ�
			// �����ʿ��� �ǹ����� ū ���Ҹ� ã���� ���� ��ȯ���ش�.
			Swap(v[low], v[high]);
		}
	} while (low < high);
	Swap(v[left], v[high]); // ��� ��ȯ�� �������� high ��ġ�� ���� �ǹ� left ��ġ�� ���� ��ȯ���ش�.
	return high; // �׸��� �ǹ��� ��ġ�� high�� ��ȯ���ش�.
}
void QuickSort(int *v, int left, int right) {
	vector<int> stack; // ����ó�� ����� ����

	stack.push_back(left); // ���ÿ� ���� �� left, right ������� �ִ´�.
	stack.push_back(right);

	while (!stack.empty()) { // ������ ������� ���� �� �ݺ�
		right = stack.back(); // ���� ���� �ݴ�� right, left �� ������.
		stack.pop_back();
		left = stack.back();
		stack.pop_back();
		int pivot = Partition(v, left, right); // �ǹ��� ��ġ�� ã�´�.

		if (pivot - 1 > left) { // left�� pivot-1���� ���� ������ ���� �� ���� ����
			stack.push_back(left); // ���ÿ� ���� ���� left, right ������� �ִ´�.
			stack.push_back(pivot - 1);
		}
		if (pivot + 1 < right) { // ������ ���������� ��� ���� �����ϸ� �����Ѵ�.
			stack.push_back(pivot + 1);
			stack.push_back(right);
		}
	}
}

int main() {
	srand((unsigned int)time(NULL)); // ���� ����
	for (int i = 0; i < 1000; i++) { // 1~10000�� ���ڸ� �����ϰ� 1000�� �����ؼ� k�� ����
		k1[i] = k2[i] = rand() % MAX + 1; // n1�� ���� ����, k2�� �� ���ķ� �����ؼ� ��
	}
	clock_t start1, end1; // �ð� ������ ���� ����
	double res1; // ���� ���Ŀ� �ɸ� �ð� ����

	start1 = clock(); // �ð� ���� ����
	BubbleSort(k1, 999); // ��� �Լ��� ����� ���� ���ķ� k1 �迭 �������� ����
	end1 = clock();
	res1 = (double)(end1 - start1) / CLOCKS_PER_SEC; // ���� ���Ŀ� �ɸ� �ð�

	clock_t start2, end2;
	double res2; // �� ���Ŀ� �ɸ� �ð� ����

	start2 = clock(); // �ð� ���� ����
	QuickSort(k2, 0, 999); // ��� �Լ��� ������� ���� �� ���ķ� k2 �迭 �������� ����
	end2 = clock();
	res2 = (double)(end2 - start2) / CLOCKS_PER_SEC; // �� ���Ŀ� �ɸ� �ð�
	
	bool same = true;
	for (int i = 0; i < 1000; i++) {
		if (k1[i] != k2[i]) // �� ���̶� ���� �迭�� �ٸ��ٸ� same�� false�� ���� ������.
			same = false;
	}
	if (same)
		cout << "���� �� ����� �����ϴ�.\n";
	else cout << "���� �� ����� �ٸ��ϴ�.\n";
	cout << "���� ���Ŀ� �ɸ� �ð��� " << res1 << "�̰�, �� ���Ŀ� �ɸ� �ð��� " << res2 << "�Դϴ�.";
}