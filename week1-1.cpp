#include<iostream> //2015112083 유성근
#include <vector>
#include <string>
using namespace std;

int main() {
	cout << "배열을 입력해주세요 :";
	string s;
	getline(cin,s); // 배열을 공백을 포함한 문자열 형태로 입력받음

	vector<int>v; // 입력받은 수들을 나누어 저장할 벡터
	string tmp; // 수를 저장할 임시 문자열
	for (int i = 0; i < s.size(); i++) {
		if (s[i] >= '0' && s[i] <= '9') // 문자열로 표현된 배열 s에서 숫자만 떼어냄
			tmp += s[i];
		if (s[i] == ' ') {
			v.push_back(stoi(tmp)); // 떼어낸 숫자를 int형으로 변환해서 벡터에 넣음
			tmp = ""; // 임시 문자열 초기화
		}	
	}
	v.push_back(stoi(tmp)); // 마지막 숫자도 벡터에 넣음
	
	cout << '\n' << "Avr 출력" << "\n";
	int sum = 0; // 누적 합을 저장할 변수
	for (int i = 0; i < v.size(); i++) {
		cout << " Avr[" << i << "]: ";
		sum += v[i]; // 반복문을 한 번 돌 때마다 벡터에 저장된 배열의 값을 더한다.
		cout << (double)sum / (i + 1) << "\n"; // i+1개의 원소들의 평균이므로 i+1로 나눈다.
	}
}