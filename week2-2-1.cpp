#include <iostream> // 2015112083 ������
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ���ȯ��� ���
int func(vector<int>v, int size) {
	int res = 1; // ��� ������ ����
	int minNum = 9999; // v�� ����� �� �� ���� ���� �� ����
	int count = 0;

	for (int i = 0; i < size; i++)
		minNum = min(v[i], minNum); // v�� ����� �� �߿��� ���� ���� �� ã��

	for (int i = 2; i <= minNum; i++) { // ���� ���� ���� i�� ����� ���̴�. 
		count = 0;
		for (int j = 0; j < size; j++) { // j�� ���͸� ��ȸ�ϸ� ��� i�� ��������.
			if (v[j] % i == 0) // ���� �� ������ count ����
				count++;
		}
		if (count == size) // ���ͳ� ��� ���� i�� ������ �� ������ �ִ������� i�� ����
			res = i; // i�� minNum���� ��� ������ ���̹Ƿ� ���������� �ִ������� ����ȴ�.
	}
	return res;
}

int main() {
	vector<int>v;

	v.push_back(24);
	v.push_back(16);
	v.push_back(32);
	v.push_back(56);
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << "\n�ִ� ������� : " << func(v, v.size());
}
