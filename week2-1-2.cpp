#include <iostream> // 2015112083 ������
#include <string>
#include <vector>
using namespace std;
bool dp[100][100]; // i���� j������ �Ӹ�������� ���θ� ������ �迭

 // ��ȯ��� ���
bool func(string s, int left, int right) {
	if (left >= right) // �������� left�� right�� �����ϸ� ���� �ٴٶ����Ƿ� true ����. 
		return true; // ��͸� �ٽ� �������� Ż���ϸ� �� ���̶� �Ӹ������ �ƴϸ� false�� �ٲ�� ��ü�� �Ӹ�����̸� true ����

	if (dp[left][right]) // ���ߴ� left���� right������ �Ӹ�����̸� true, �ƴϸ� false ����
		return dp[left][right];

	if (s[left] != s[right]) // ���� left�� right�� ���� ������ �Ӹ������ �ƴϹǷ� false ����
		return dp[left][right] = false;
	return func(s, left + 1, right - 1); // ���ٸ� �³��� ���� ���ڿ� �쳡�� ���� ���ڸ� ��
}

int main() {
	FILE* fp = fopen("exam_palindrome.txt", "rt");
	char buff[20];
	vector<string>lines;
	if (fp) { // ���Ͽ��� �� �پ� �о��
		while (fgets(buff, sizeof(buff), fp) != NULL) {
			string tmp;
			for (int i = 0; i < 20; i++) { // �о�� �� �ٿ��� ���� '\n'�� �����ϴ� ����
				if (buff[i] == '\n' || buff[i] == NULL)
					break;
				else tmp += buff[i];
			}
			lines.push_back(tmp);
		}
	}
	fclose(fp);
	for (int i = 0; i < lines.size(); i++) {
		cout << lines[i];
		if (func(lines[i], 0, lines[i].size() - 1)) // �ʱ� left�� 0�̰� right�� ��ü ������-1 �̴�.
			cout << ": �Ӹ�����Դϴ�." << "\n";
		else cout << ": �Ӹ������ �ƴմϴ�." << "\n";
	}
}