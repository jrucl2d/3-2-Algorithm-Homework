#include<iostream> //2015112083 ������
#include <vector>
using namespace std;

int main() {
	int m; // ���� �� �հ�
	int d; // coin�� ����
	vector<int>c; // coin�� ����
	vector<int>k; // ������ ����� ����
	int tmp; // �ٿ뵵 �ӽ� ����

	cout << "���� �� �հ� �Է� :";
	cin >> m;
	cout << "������ ���� �Է� :";
	cin >> d;
	cout << "������ ���� �Է� :";
	
	for (int i = 0; i < d; i++) {
		cin >> tmp; // �ӽú����� �̿��ؼ� ���� ���� �Է� ����
		c.push_back(tmp); // �Է¹��� ������ ������ ����
	}

	for (int i = 0; i < d; i++) {
		tmp = m / c[i]; // ��ü ���� ���� �������� ������. �� ���� �ش� ������ �ִ�� �� �� �� �� �ִ���(k��)
		m -= tmp * c[i]; // �ش� ������ �ִ�� �� ��ŭ�� ���� ��ü ������ ���ش�.
		k.push_back(tmp);
	}
	
	cout << "��� : ";
	for (int i = 0; i < k.size(); i++)
		cout << k[i] << " ";
}