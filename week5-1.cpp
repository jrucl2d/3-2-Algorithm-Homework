#include <iostream> // 2015112083 ������
#include <vector>
#include <fstream>
#include <string>
using namespace std;
#define NOWAY -1
int dp[5][5]; // ��������� (i,j)���� ���µ� �� �ִ� ������ ���� ����

struct map {
	int right;
	int down;
};
void GetInfo(map** tour) {
	ifstream file; // �Է� ��Ʈ��
	file.open("map_info.txt"); // ���� ����

	// �� ���� �Է¹ޱ�
	char info[50]; // 5*5 = 25���� �ʿ� ���ؼ� right, down ���� �Է�
	int index = 0;
	while (!file.eof()) {
		string s;
		getline(file, s); // �� ���� �о��. 
		info[index++] = s[0]; // s[0]���� right�� ����
		info[index++] = s[2]; // s[2]���� down�� ������ ����ִ�.
	}
	index = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			char tmp1 = info[index++];
			char tmp2 = info[index++];
			if (tmp1 >= '0' && tmp1 <= '9') // right ������ �����̸� ����ְ�
				tour[i][j].right = tmp1 - '0';
			else // ���� ���ٴ� ������ 'n'�� �� ������ -1 �־���
				tour[i][j].right = NOWAY;

			if (tmp2 >= '0' && tmp2 <= '9')
				tour[i][j].down = tmp2 - '0';
			else
				tour[i][j].down = NOWAY;
		}
	}
}

void DP(map** tour) { // O(n^2) �ð����⵵
	// ���� ���� �Է�(������ ���� ã�� ����� ���� �� 1���ۿ� ���� ���)
	dp[0][0] = 0;
	for (int i = 1; i < 5; i++) {
		dp[i][0] = dp[i - 1][0] + tour[i - 1][0].down;
		dp[0][i] = dp[0][i - 1] + tour[0][i - 1].right;
	}
	// ��� ��忡 ���� �ݺ�
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			// ������ ���� ���(���� or ��)���� �� ���� �̵����� �� �� ū���� ������ ��츦 �� ��� dp������ ����
			if (dp[i - 1][j] + tour[i - 1][j].down > dp[i][j - 1] + tour[i][j - 1].right)
				dp[i][j] = dp[i - 1][j] + tour[i - 1][j].down;
			else dp[i][j] = dp[i][j - 1] + tour[i][j - 1].right;
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++)
			cout << dp[i][j] << "\t";
		cout << endl;
	}
}

int main() {
	map** tour = new map * [5]; // map ������ �迭 ���� �Ҵ�
	for (int i = 0; i < 5; i++)
		tour[i] = new map[5];
	GetInfo(tour); // ���Ͽ��� ������ �Է¹���
	DP(tour); // �˰��� ����
}