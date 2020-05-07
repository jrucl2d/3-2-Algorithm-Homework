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
	string s;
	getline(cin, s); // ���� ������ ������ ���ڿ� ���·� �Է¹���

	vector<int>v; // �Է¹��� ������ ������ ������ ����
	string tmp; // ���� ������ �ӽ� ���ڿ�
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= '0' && s[i] <= '9') // ���ڿ��� ǥ���� �迭 s���� ���ڸ� ���
			tmp += s[i];
		if (s[i] == ' ') {
			v.push_back(stoi(tmp)); // ��� ���ڸ� int������ ��ȯ�ؼ� ���Ϳ� ����
			tmp = ""; // �ӽ� ���ڿ� �ʱ�ȭ
		}
	}
	v.push_back(stoi(tmp)); // ������ ���ڵ� ���Ϳ� ����
	cout << "�ִ� ������� : " << func(v, v.size());
}