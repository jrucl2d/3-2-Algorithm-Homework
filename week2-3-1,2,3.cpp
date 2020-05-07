#include <iostream> // 2015112083 ������
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
#define MAX 10000 // 10000������ ����
int n1[10];
int n2[10];
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
	cout << "���� n         : ";
	for (int i = 0; i < 10; i++) { // 1~10000�� ���ڸ� �����ϰ� 10�� �����ؼ� n�� ����(1�� �ذ�)
		n1[i] = n2[i] = rand() % MAX + 1; // n1�� ���� ����, n2�� �� ���ķ� �����ؼ� ��
		cout << n1[i] << " ";
	}

	BubbleSort(n1, 9); // ��� �Լ��� ����� ���� ���ķ� n1 �迭 �������� ����(2�� �ذ�)
	cout << "\n���� ���� �� n : ";
	for (int i = 0; i < 10; i++)
		cout << n1[i] << " ";

	QuickSort(n2, 0, 9); // ��� �Լ��� ������� ���� �� ���ķ� n2 �迭 �������� ����(3�� �ذ�)
	cout << "\n�� ���� �� n   : ";
	for (int i = 0; i < 10; i++) 
		cout << n2[i] << " ";
}