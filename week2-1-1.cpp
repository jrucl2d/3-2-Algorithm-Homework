#include <iostream> // 2015112083 ������
#include <string>
#include <vector>
using namespace std;
bool dp[100][100]; // i���� j������ �Ӹ�������� ���θ� ������ �迭

 // ���ȯ��� ���
void func(string s, int size) {
	// dp �ʱ�ȭ
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			dp[i][j] = false;
	// ���� �۾�
	for (int i = 0; i < size; i++) // �� ������ ���� ������ �Ӹ�����̴�.
		dp[i][i] = true;
	for (int i = 0; i < size - 1; i++) // �� ������ ��� ������ �Ӹ�����̴�.
		if (s[i] == s[i + 1])
			dp[i][i + 1] = true;
	
	for (int intev = 2; intev < size; intev++) { // ������ �ǹ��ϴ� ����
		 // i�� ���� ������ ����, size - 1�� 7�̸� �ּ� ���� 2�� ���ؼ� left�� 0���� 5����(7-3+1) �� �� �ִ�. 
		for (int left = 0; left < size - intev; left++) {
			int right = left + intev; // ���� ���� �ٽ� ���, right�� 7����(4+3) �� �� �ִ�.
			// left�� right�� ������ ���ڰ� ����, �� �ȵ�(left+1���� right-1������) �Ӹ�����̸� 
			// left���� right������ �Ӹ�����̶�� ���̴�.
			if (s[left] == s[right] && dp[left + 1][right - 1] == true)
				dp[left][right] = true;
		}
	}
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
		func(lines[i], lines[i].size());
		if (dp[0][lines[i].size() - 1]) // ���������� 0���� �����ڱ����� �Ӹ�������� ���
			cout << ": �Ӹ�����Դϴ�." << "\n";
		else cout << ": �Ӹ������ �ƴմϴ�." << "\n";
	}
}