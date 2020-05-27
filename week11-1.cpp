#include <iostream> // 2015112083 ������
#include <vector>
#include <string>
using namespace std;

vector<pair<int, string>> FillTheRest(string t) {
	vector<pair<int,string>> res; // index�� �ش� ��° string�� pair�� �־���
	int endIndex = t.size() - 1;
	string tmp = "";
	for (int i = endIndex; i >= 0; i--) { // $���� ù ���ڱ����� ù ���ڷ� �ؼ�
		tmp = "";
		for (int j = i; j <= endIndex; j++)  // �ش� ù ���ں��� ������ ���ڿ��� �߰��ϰ�
			tmp += t[j];
		for (int j = 0; j < i; j++) // ó������ �ش� ù ���� ������ ���ڿ��� �߰�
			tmp += t[j];
		res.push_back({ i, tmp }); // �ϼ��� ���ڿ��� index�� �Բ� ���Ϳ� �־���
	}
	return res;
}

void Sort(vector<pair<int, string>> &t) {
	bool sorted = false; // �ð� ������ ���� flag
	int size = t.size();
	int stringSize = t.size() - 1; // $�� ������ ������ ���� ���ڿ� ����
	for (int i = size - 1; i > 2; i--) {
		while (!sorted) { // ���� �ݺ����� �ٲ� ���� ������ sorted�� true�� �ǰ� �˰��� �ߴ�
			sorted = true;
			for (int j = 1; j < i; j++) { // i ���� ��� �ε��� j�� ���ؼ�, ù ���ڿ��� ������ $�̹Ƿ� ����
				bool change = false;
				for (int k = 0; k < stringSize; k++) { // ���ڿ� ��
					if (t[j].second[k] > t[j + 1].second[k]) { // ������ �� ũ�� change�� true��
						change = true;
						break;
					}
					else if (t[j].second[k] == t[j + 1].second[k]) // ������ ���� ���� ��
						continue;
					else { // ������ ������ ��ȯ�� �ʿ� �����Ƿ� change�� false��
						change = false;
						break;
					}
				}
				if (change) { // ���� ���� �� ũ��(change�� true�̸�) ��ȯ
					pair<int, string> tmp = t[j];
					t[j] = t[j + 1];
					t[j + 1] = tmp;
					sorted = false;
				}
			}
		}
	}
}

string Restore(vector<pair<int, string>>& t) {
	int stringSize;
	int back = stringSize = t.size() - 1; // ���ڿ� ���̴� ���� �������� $�� �ϳ� �� �Ͱ� ����
	int front = 0;
	string res = "";
	
	for (int i = stringSize; i > 0; i--) { // ������ $�� �����ϰ� ������ �ε����� �ش��ϴ� ���ڸ� �߰�
		for (int j = 0; j <= stringSize; j++) {
			if (t[j].first == i) { // �ش� �ε����� ���� �ִ� ���ڸ� �߰�
				res += t[j].second[back];
				break;
			}
		}	
	}
	string res2 = "";
	for (int i = stringSize - 1; i >= 0; i--)
		res2 += res[i]; // res�� ������ �Ųٷ� res2�� ����
	return res2;
}
int main() {
	string T = "missisippi";
	string T$ = T + "$";
	vector<pair<int, string>>ftr;
	ftr = FillTheRest(T$);
	cout << "[Fill the rest]" << endl;
	for (int i = 0; i < ftr.size(); i++) // Fill the rest ����� ���
		cout << ftr[i].first << " " << ftr[i].second << endl;
	Sort(ftr);
	cout << endl;
	cout << "[Sort result]" << endl;
	for (int i = 0; i < ftr.size(); i++) // Sort ����� ���
		cout << ftr[i].first << " " << ftr[i].second << endl;

	// ���� ����
	string res = "";
	res = Restore(ftr);
	cout << endl;
	cout << "[Resotred string]" << endl;
	cout << res << endl;
}