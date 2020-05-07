#include <iostream> // 2015112083 ������
#include <vector>
using namespace std;

void Print(int* a) { // a�迭�� ����ϴ� �Լ�
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;
}

// recursive mergesort 
void Merge(int* a, int left, int mid, int right) { 
	int b[10]; // ���۷� ���� �迭. ���ڸ����� �������� �ʴ´�.
	int leftFind = left; // �� ���� ����(left)���� ���(mid)���� Ž��
	int rightFind = mid + 1; // ������ ó�� ����(mid+1)���� �� ������ ����(right)���� Ž��
	int bufferFind = left; // ���۹迭 b�� ������� �� ����� �ε���

	while (leftFind <= mid && rightFind <= right) { // �¿� �迭 �� �ϳ��� ��� Ž���ϸ� Ż��
		if (a[leftFind] < a[rightFind]) // ���� Ž������ �¿� ���� �� �� ���� ���� ���ۿ� ���� �ְ� �ε��� ����
			b[bufferFind++] = a[leftFind++];
		else 
			b[bufferFind++] = a[rightFind++];
	}

	if (leftFind > mid) // ��ó��. ������ ��� Ž���߰� �����ʿ� ���Ҵٸ�
		for (int i = rightFind; i <= right; i++) // ���� ���� ���ʴ�� ���ۿ� �߰�
			b[bufferFind++] = a[i];
	else // �ݴ��� ���
		for (int i = leftFind; i <= mid; i++)
			b[bufferFind++] = a[i];
	
	for (int i = left; i <= right; i++) // ���ۿ� ������ ������� a�� �ٽ� ���� �����
		a[i] = b[i];
}

void MergeSort(int* a, int left, int right) {
	int mid;
	if (left < right) {
		mid = (left + right) / 2; // �߰��� mid�� ���
		MergeSort(a, left, mid); // ���ҵ� �¿� �迭�� ��� recursive�ϰ� ��� ����
		MergeSort(a, mid + 1, right);
		Merge(a, left, mid, right); // ������ ����
		Print(a);
	}
}

int main() {
	int a[10] = { 30, 20, 40, 35, 5, 50, 45, 10, 25, 15 };
	MergeSort(a, 0, 9);
}