#include <iostream> // 2015112083 ������
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// ��ȯ��� ���
// �ſ� ������ gcd �˰����� ���.
// a�� b�� �ִ� ������� ū �� a�� ���� �� b�� ���� �� a�� b�� ���� �������� r�̶�� �ϸ�
// a�� b�� �ִ� ������� b�� r�� �ִ������� ���ٴ� ���� �̿��ؼ� ���� �� �ִ�.
int gcd(int a, int b) {
	if (b == 0) // ������ a%b�� 0�̸� ������ a�� �ִ������̴�.
		return a;
	else return gcd(b, a % b); // b�� r(a%b)�� �ִ������� ���ٴ� ���� �̿�
}

// �迭�� ������������ �����ϱ� ���� ���� ���� ���
void sort(vector<int>v, int size) {
	bool sorted = false; // �ð� ������ ���� flag
	for (int i = size - 1; i > 0; i--) {
		while (!sorted) { // ���� �ݺ����� �ٲ� ���� ������ sorted�� true�̹Ƿ� ���� �Ϸ�� �˰��� �ߴ�
			sorted = true;
			for (int j = 0; j < i; j++) { // i������ ��� �ε��� j�� ���ؼ�
				if (v[j] < v[j + 1]) { // ���� ���� ���ʿ� ������ ��ȯ(��������)
					int tmp = v[j];
					v[j] = v[j + 1];
					v[j + 1] = tmp;
					sorted = false; // ��ȯ�� �־��ٸ� sorted�� false
				}
			}
		}
	}
}

int main() {
	vector<int>v;

	v.push_back(24);
	v.push_back(16);
	v.push_back(32);
	v.push_back(56);

	// gcd(a,b,c)�� gcd(gcd(a,b),c)��� Ư�� �̿��� ���ε�, ū ���� ���� �� �ʿ� �;� �ϹǷ� �������� ������ ������ �־�� �Ѵ�.
	sort(v, v.size());

	int res = gcd(v[0], v[1]); // ó�� �� ���� �̿��� ���� �ִ� ������� res�� ����
	for (int i = 2; i < v.size(); i++) {
		res = gcd(res, v[i]); // ���ĺ��� gcd(gcd(a,b),c)�� ������� res�� gcd ���� ����
	}
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << "\n�ִ� ������� : " << res;
}