#include <iostream> // 2015112083 ������
#include <fstream>
#include <string>
using namespace std;
#define NOWAY -1

struct map{
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

void Greedy(map **tour, int i, int j) { // ������ �ּ��� ������ ��
	while (true) {
		if (i == 4 && j == 4) // end ������ �����ϸ� Ż��
			break;
		if (tour[i][j].right > tour[i][j].down) j++; // �������� ���� ���� �� ������ �������� �̵�
		else i++; // ���� ���� ���� -1 ���̹Ƿ� ���ʿ� ��� ����� �ƴϴ�.
		cout << "Map[" << i << "][" << j << "] ";
	}
}

int main() {
	map **tour = new map*[5]; // map ������ �迭 ���� �Ҵ�
	for (int i = 0; i < 5; i++)
		tour[i] = new map[5];
	GetInfo(tour); // ���Ͽ��� ������ �Է¹���

	cout << "Map[0][0] ";
	Greedy(tour, 0, 0);
}