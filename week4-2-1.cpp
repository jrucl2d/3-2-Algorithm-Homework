#include <iostream> // 2015112083 유성근
#include <fstream>
#include <string>
using namespace std;
#define NOWAY -1

struct map{
	int right;
	int down;
};
void GetInfo(map** tour) {
	ifstream file; // 입력 스트림
	file.open("map_info.txt"); // 파일 열기

	// 맵 정보 입력받기
	char info[50]; // 5*5 = 25개의 맵에 대해서 right, down 정보 입력
	int index = 0;
	while (!file.eof()) {
		string s;
		getline(file, s); // 한 줄을 읽어옴. 
		info[index++] = s[0]; // s[0]에는 right의 정보
		info[index++] = s[2]; // s[2]에는 down의 정보가 들어있다.
	}
	index = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			char tmp1 = info[index++];
			char tmp2 = info[index++];
			if (tmp1 >= '0' && tmp1 <= '9') // right 정보가 숫자이면 집어넣고
				tour[i][j].right = tmp1 - '0';
			else // 길이 없다는 뜻으로 'n'이 들어가 있으면 -1 넣어줌
				tour[i][j].right = NOWAY;

			if (tmp2 >= '0' && tmp2 <= '9')
				tour[i][j].down = tmp2 - '0';
			else
				tour[i][j].down = NOWAY;
		}
	}
}

void Greedy(map **tour, int i, int j) { // 순간의 최선의 선택을 함
	while (true) {
		if (i == 4 && j == 4) // end 지점에 도달하면 탈출
			break;
		if (tour[i][j].right > tour[i][j].down) j++; // 우측으로 가는 것이 더 나으면 우측으로 이동
		else i++; // 길이 없는 경우는 -1 값이므로 애초에 고려 대상이 아니다.
		cout << "Map[" << i << "][" << j << "] ";
	}
}

int main() {
	map **tour = new map*[5]; // map 이차원 배열 동적 할당
	for (int i = 0; i < 5; i++)
		tour[i] = new map[5];
	GetInfo(tour); // 파일에서 정보를 입력받음

	cout << "Map[0][0] ";
	Greedy(tour, 0, 0);
}