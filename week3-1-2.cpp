#include <iostream> // 2015112083 ������
#include <vector>
using namespace std;

void Print(int* a) { // a�迭�� ����ϴ� �Լ�
	for (int i = 1; i <= 10; i++) // ù ��° ������ dummy data�� 0�� ���Ƿ� ��� �� ��
		cout << a[i] << " ";
	cout << endl;
}

// not recursive mergesort 
void Merge(int* a, int left, int mid, int right) { 
	int b[11]; // ���۷� ���� �迭. ���ڸ����� �������� �ʴ´�.
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
	for (int i = 1; i < 10; i *= 2) {
		left = 1; // �׻� ó�� �ε������� Ȯ���ؾ� ��
		while (left <= 10) { // left�� �� �ε����� �������� �ʴ� ��
			right = left + 2 * i - 1; // ����� ũ�Ⱑ 2, 4, 8.. �̷������� �ǵ��� right�� ���� ����
			// ����� ũ�Ⱑ Ŀ���鼭 ������ ����� ���� ��� ũ�⸸ŭ �� �� �� �ִ�. �׷� ��� �ִ밪�� 10���� �缳��
			if (right > 10) right = 10; 

			mid = left + i - 1; // right�� left+2*i-1 �̶�� ������ mid���� �� ����� left+i-1�� �����ϴ�.
			if (mid <= 10) // mid�� �ִ밪�� �Ѿ ���� �̹� ���� i ��Ȳ���� ������ �Ϸ�� �迭�̴�.
				Merge(a, left, mid, right); // ���� ����
			left = right + 1; // ���� left�� ���� right�� ���ķ� ����
			Print(a);
		}
	}
}

int main() {
	// ù ���� dummy data�� 0���� ����
	int a[11] = { 0, 30, 20, 40, 35, 5, 50, 45, 10, 25, 15 }; 
	MergeSort(a, 1, 10); // 1~10�� ��ġ�� ���ҵ��� ����
}