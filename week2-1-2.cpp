#include <iostream> // 2015112083 유성근
#include <string>
#include <vector>
using namespace std;
bool dp[100][100]; // i부터 j까지가 팰린드롬인지 여부를 저장할 배열

 // 순환방식 사용
bool func(string s, int left, int right) {
	if (left >= right) // 마지막에 left와 right가 교차하면 끝에 다다랐으므로 true 리턴. 
		return true; // 재귀를 다시 역순으로 탈출하며 한 번이라도 팰린드롬이 아니면 false로 바뀌고 전체가 팰린드롬이면 true 리턴

	if (dp[left][right]) // 구했던 left부터 right까지가 팰린드롬이면 true, 아니면 false 리턴
		return dp[left][right];

	if (s[left] != s[right]) // 만약 left와 right가 같지 않으면 팰린드롬이 아니므로 false 리턴
		return dp[left][right] = false;
	return func(s, left + 1, right - 1); // 같다면 좌끝단 다음 문자와 우끝단 이전 문자를 비교
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
		if (func(lines[i], 0, lines[i].size() - 1)) // 초기 left는 0이고 right는 전체 사이즈-1 이다.
			cout << ": 팰린드롬입니다." << "\n";
		else cout << ": 팰린드롬이 아닙니다." << "\n";
	}
}