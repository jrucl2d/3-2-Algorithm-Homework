#include<iostream> //2015112083 ������
#include <vector>
#include <string>
using namespace std;

int main() {
	cout << "�迭�� �Է����ּ��� :";
	string s;
	getline(cin,s); // �迭�� ������ ������ ���ڿ� ���·� �Է¹���

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
	
	cout << '\n' << "Avr ���" << "\n";
	int sum = 0; // ���� ���� ������ ����
	for (int i = 0; i < v.size(); i++) {
		cout << " Avr[" << i << "]: ";
		sum += v[i]; // �ݺ����� �� �� �� ������ ���Ϳ� ����� �迭�� ���� ���Ѵ�.
		cout << (double)sum / (i + 1) << "\n"; // i+1���� ���ҵ��� ����̹Ƿ� i+1�� ������.
	}
}