#include <iostream> // 2015112083 유성근
#include <vector>
#include <fstream>
#include <string>
using namespace std;
#define NOWAY -1
vector<pair<int, int>>updatedpath; // 순서대로 지나온 행, 열을 pair로 넣음
vector<pair<int, int>>ans; // 정답을 넣을 벡터
int dp[5][5]; // 출발지에서 (i,j)까지 가는데 본 최대 관광지 개수 저장

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

void Bruteforce(map **tour) { // O(n^2) 시간복잡도

	// 사전 정보 입력(최적의 길을 찾는 경우의 수가 딱 1개밖에 없는 경우)
	dp[0][0] = 0;
	for (int i = 1; i < 5; i++) {
		dp[i][0] = dp[i - 1][0] + tour[i - 1][0].down;
		dp[0][i] = dp[0][i - 1] + tour[0][i - 1].right;
	}

	// 모든 노드에 대해 반복
	for (int i = 1; i < 5; i++) {
		for (int j = 1; j < 5; j++) {
			// 가능한 이전 노드(좌측 or 위)에서 현 노드로 이동했을 때 더 큰값을 가지는 경우를 현 노드 dp값으로 설정
			// 반복하며 dp가 변한 경우(모든 가능한 이동 후보)를 updatepath벡터에 위치 저장
			if (dp[i - 1][j] + tour[i - 1][j].down > dp[i][j - 1] + tour[i][j - 1].right) {
				dp[i][j] = dp[i - 1][j] + tour[i - 1][j].down;
				updatedpath.push_back({ i - 1,j });
			}	
			else {
				dp[i][j] = dp[i][j - 1] + tour[i][j - 1].right;
				updatedpath.push_back({ i,j - 1 });
			}		
		}
	}

	ans.push_back({ 0, 0 }); // 시작점(0,0) 넣어줌
	for (int i = 0; i < updatedpath.size(); i++) {
		bool skip = false;
		// 첫 번째 조건 : 우측이나 아래로 한 칸만 이동 가능
		// 행이 1 커지고 열이 똑같거나 열이 1 커지고 행이 똑같거나
		if (updatedpath[i].first == ans.back().first + 1 && updatedpath[i].second == ans.back().second ||
			updatedpath[i].first == ans.back().first && updatedpath[i].second == ans.back().second + 1) {
			// 두 번째 조건 : 현재 확인 중인 위치가 이후에 또 등장하면 해당 노드가 이후에 모든 이동 경로에 있어서
			// 더 최적의 길을 찾는데 다시 이용되었다는 뜻이므로 현재부터 다시 등장하기 전까지의 이동은 최적 경로
			// 탐색에 영향을 못 주므로 skip 플래그를 세워서 제외
			for (int j = i + 1; j < updatedpath.size(); j++) {
				if (updatedpath[i].first == updatedpath[j].first && updatedpath[i].second == updatedpath[j].second) {
					skip = true; break;
				}
			}
			if (skip) continue;
			// 최종적으로 최적의 길만을 ans 벡터에 넣어줌
			ans.push_back({ updatedpath[i].first, updatedpath[i].second });
		}
	}
	ans.push_back({ 4,4 }); // end 지점 넣어줌
}

int main() {
	map **tour = new map*[5]; // map 이차원 배열 동적 할당
	for (int i = 0; i < 5; i++)
		tour[i] = new map[5];
	GetInfo(tour); // 파일에서 정보를 입력받음
	Bruteforce(tour); // 알고리즘 수행
	
	for(int i = 0 ; i < ans.size(); i++) // 정답을 출력
		cout << "Map[" << ans[i].first << "][" << ans[i].second << "] ";
}