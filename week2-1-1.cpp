#include <iostream> // 2015112083 유성근
#include <string>
#include <vector>
using namespace std;
bool dp[100][100]; // i부터 j까지가 팰린드롬인지 여부를 저장할 배열

 // 비순환방식 사용
void func(string s, int size) {
	// dp 초기화
	for (int i = 0; i < 100; i++)
		for (int j = 0; j < 100; j++)
			dp[i][j] = false;
	// 사전 작업
	for (int i = 0; i < size; i++) // 한 글자인 경우는 무조건 팰린드롬이다.
		dp[i][i] = true;
	for (int i = 0; i < size - 1; i++) // 두 글자인 경우 같으면 팰린드롬이다.
		if (s[i] == s[i + 1])
			dp[i][i + 1] = true;
	
	for (int intev = 2; intev < size; intev++) { // 간격을 의미하는 변수
		 // i의 범위 설정의 예로, size - 1이 7이면 최소 간격 2에 대해서 left가 0부터 5까지(7-3+1) 갈 수 있다. 
		for (int left = 0; left < size - intev; left++) {
			int right = left + intev; // 위의 예를 다시 들면, right는 7까지(4+3) 갈 수 있다.
			// left와 right의 끝단의 문자가 같고, 그 안도(left+1부터 right-1까지가) 팰린드롬이면 
			// left부터 right까지가 팰린드롬이라는 뜻이다.
			if (s[left] == s[right] && dp[left + 1][right - 1] == true)
				dp[left][right] = true;
		}
	}
}

int main() {
	FILE* fp = fopen("exam_palindrome.txt", "rt");
	char buff[20];
	vector<string>lines;
	if (fp) { // 파일에서 한 줄씩 읽어옴
		while (fgets(buff, sizeof(buff), fp) != NULL) {
			string tmp;
			for (int i = 0; i < 20; i++) { // 읽어온 한 줄에서 끝의 '\n'을 제거하는 과정
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
		if (dp[0][lines[i].size() - 1]) // 최종적으로 0부터 끝글자까지가 팰린드롬인지 출력
			cout << ": 팰린드롬입니다." << "\n";
		else cout << ": 팰린드롬이 아닙니다." << "\n";
	}
}