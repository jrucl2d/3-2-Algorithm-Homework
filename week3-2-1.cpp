#include <iostream> // 2015112083 ������
#include <vector>
using namespace std;

void Print(int* a) {
	for (int i = 0; i < 10; i++)
		cout << a[i] << " ";
	cout << endl;
}

void MakeHeap(int* a, int root, int end) { // MaxHeap�� ����� �Լ�
	int p = root; // �θ�
	int p_value = a[p]; // �θ��� ��
	int c, leftc, rightc; // �ڽ�, ���� �ڽ�, ������ �ڽ�
	leftc = 2 * p + 1; 
	rightc = leftc + 1;

	while (leftc <= end) { // ���� ���� �ڽ� �ϳ��� ���� ��쵵 ���
		if (rightc <= end && a[leftc] < a[rightc])
			c = rightc; // �� ū �ڽ��� ���� c�� ����
		else c = leftc;
		
		if (p_value < a[c]) { // �θ��� ������ �ڽ��� ���� ũ��
			a[p] = a[c]; // �ڽ��� ���� �θ� ��ġ�� �ø���.
			p = c; // ������ c�� ���� p�� ��´�.
			leftc = p * 2 + 1; // ���� p�� �´� �¿� �ڽ��� ����
			rightc = leftc + 1;
		}
		else break; // �θ��� ���� �ڽ� ������ ũ�� �ٲ� �� �����Ƿ� Ż��
	}
	a[p] = p_value; // ������ p�� ���� ������ c�� ������Ƿ� ���� �θ��� ���� �־������ν� ��ȯ
	Print(a);
}

int main() {
	int a[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };

	// �迭 ����/2�� ���� ���� �ִ� �θ����̴�. ���⼭���� �ϳ��� �ٿ����� ��� �θ��忡 ���ؼ� �˰��� ����
	for (int i = 10 / 2; i >= 0; i--)
		MakeHeap(a, i, 9); // �� ���� 9
}