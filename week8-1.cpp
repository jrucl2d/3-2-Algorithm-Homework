#include <iostream> // 2015112083 유성근
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;
#define MODNUM 13

int table[40]; // 최대 접두부 테이블

void BruteForce(char* text, int textlen, char* pattern, int patternlen) {
	int count = 0;
	vector<int>loc;
	for (int i = 0; i <= textlen - patternlen; i++) {
		int j = 0;
		for (; j < patternlen; j++) {
			if (text[i + j] != pattern[j]) { // text의 i부터 j가 pattern과 같지 않으면 반복 탈출
				break;
			}
		}
		if (j == patternlen) { // j를 끝까지 다 검색했다면 pattern의 길이와 j가 같다-> pattern을 찾은 것
			count++;
			loc.push_back(i);
		}
	}
	cout << "총 " << count << "개 발견, 위치 : ";
	if (count == 0) {
		cout << "해당 string 없음" << endl;
		return;
	}
	for (int i = 0; i < loc.size(); i++)
		cout << loc[i] << " ";
	cout << endl;
}
void MakeTable(char* string, int len) { // 최대 접두부 테이블 만드는 함수
	for (int i = 0; i < len; i++) // table 원소 0으로 초기화
		table[i] = 0;
	int j = 0;
	for (int i = 1; i < len; i++) { // i로 스트링을 두 번째 원소부터 끝까지 훑음
		while (j > 0 && string[i] != string[j]) { // 만약 이전에 j가 이동한 상태에서(j>0) 중간에 맞지 않으면
			j = table[j - 1]; // j를 table의 j-1에 저장된 인덱스로 이동(저장된 인덱스의 개수만큼은 접두사 접미사가 같다)
		}
		if (string[i] == string[j]) // i와 j에 같은 수를 발견하면 j+1 값을 테이블에 추가함.
			table[i] = ++j;
	}
}

void KMP(char* text, int textlen, char* pattern, int patternlen) {
	int count = 0;
	vector<int>loc;

	MakeTable(pattern, patternlen); // 패턴의 최대 접두부 테이블을 생성
	// 테이블 생성 알고리즘과 유사하게 작동
	int j = 0;
	for (int i = 0; i < textlen; i++) { // 패턴 내부에서 비교하던 것과 달리 패턴과 실제 text를 비교
		while (j > 0 && text[i] != pattern[j]) // 일치하지 않는 경우가 발생하면
			j = table[j - 1]; // 접두부 테이블에서 j-1이 가리키는 값으로 j를 옮긴다. (그만큼은 접두사와 접미사가 같다)
		if (text[i] == pattern[j]) {
			if (j == patternlen - 1) { // j는 패턴 문자열 내부를 움직이므로 j가 패턴의 끝 원소까지 다다르면 찾은 것이다.
				j = table[j]; // j를 테이블 j위치에 저장된 인덱스로 이동시켜서 뒤에 더 같은 것이 존재하는지 조사
				count++;
				loc.push_back(i - patternlen + 1);
			}
			else j++;
		}

	}
	cout << "총 " << count << "개 발견, 위치 : ";
	if (count == 0) {
		cout << "해당 string 없음" << endl;
		return;
	}
	for (int i = 0; i < loc.size(); i++)
		cout << loc[i] << " ";
	cout << endl;
}
int MOD(int num) { // mod 연산 수행 함수
	if (num < 0) { // 음수의 경우
		num = -num; // 음수를 양수로 생각하고
		num = num % MODNUM; // 모듈러 연산 수행
		num = MODNUM - num; // 이후 나누는 수에서 결과를 빼줌
		return num;
	}
	return num % MODNUM;
}
int HASH(char* string, int len) { // 해싱 함수(호너의 방법 사용)
	int hash = 0;
	for (int i = 0; i < len; i++) {
		if (string[i] >= 'A' && string[i] <= 'Z') // 알파벳 대문자의 경우 10부터 시작할 수 있도록 처리 -> A(65) - 55
			hash += (string[i] - 55) * pow(36, len - 1 - i);
		else
			hash += (string[i] - '0') * pow(36, len - 1 - i);
	}
	return hash;
}
void RabinKarp(char* text, int textlen, char* pattern, int patternlen) { // 0~9, A~Z의 36진법 사용
	int count = 0;
	vector<int>loc;

	int phash = HASH(pattern, patternlen); // pattern의 hash 값
	phash = MOD(phash); // 모듈러 연산을 적용한 phash 값

	char tmp[100]; // 패턴 길이만큼 임시 저장할 문자열
	for (int i = 0; i < patternlen; i++) // 최초 비교할 pattern길이 만큼의 text 부분 문자열 추출
		tmp[i] = text[i];
	int stringhash = HASH(tmp, patternlen); // 해싱 진행
	int beforehash = stringhash; // 모듈러 연산 진행 전의 hash 저장
	stringhash = MOD(stringhash);

	for (int i = 0; i <= textlen - patternlen; i++) {
		if (stringhash == phash) { // hash 값이 동일할 경우 위에서 사용한 직선적 방식으로 조사
			int j = 0;
			for (; j < patternlen; j++) {
				if (text[i + j] != pattern[j]) {
					break;
				}
			}
			if (j == patternlen) {
				count++;
				loc.push_back(i);
			}
		}
		stringhash = beforehash; // 모듈러 연산 전의 hash에 대해서 다음의 작업 수행
		if (i <= textlen - patternlen) {
			if (text[i] >= 'A' && text[i] <= 'Z') // high-order digit을 빼주고 자릿수 36을 곱해준다.
				stringhash -= (text[i] - 55) * pow(36, patternlen - 1);
			else stringhash -= (text[i] - '0') * pow(36, patternlen - 1);
			stringhash *= 36;
			if (text[i + patternlen] >= 'A' && text[i + patternlen] <= 'Z') // 다음 자리를 더해준다.
				stringhash += (text[i + patternlen] - 55);
			else stringhash += (text[i + patternlen] - '0');
			beforehash = stringhash; // 모듈러 취하기 전의 값을 넣어줌
			stringhash = MOD(stringhash); // 마지막에 모듈러 연산 취해준다.
		}
		
	}
	cout << "총 " << count << "개 발견, 위치 : ";
	if (count == 0) {
		cout << "해당 string 없음" << endl;
		return;
	}
	for (int i = 0; i < loc.size(); i++)
		cout << loc[i] << " ";
	cout << endl;
}

int main() {
	char textString[300], patternString[100];
	cout << "Input Text String : ";
	cin >> textString;
	cout << "Input Pattern String : ";
	cin >> patternString;
	cout << endl;

	clock_t start = clock(); // 시간 측정 시작
	BruteForce(textString, strlen(textString), patternString, strlen(patternString));
	clock_t end = clock(); // 시간 측정 종료
	cout << "BruteForce 수행 시간 : " << (double)(end - start) / CLOCKS_PER_SEC << "초" << endl << endl;
	
	start = clock(); // 시간 측정 시작
	KMP(textString, strlen(textString), patternString, strlen(patternString));
	end = clock(); // 시간 측정 종료
	cout << "KMP 수행 시간 : " << (double)(end - start) / CLOCKS_PER_SEC << "초" << endl << endl;

	start = clock(); // 시간 측정 시작
	RabinKarp(textString, strlen(textString), patternString, strlen(patternString));
	end = clock(); // 시간 측정 종료
	cout << "RabinKarp 수행 시간 : " << (double)(end - start) / CLOCKS_PER_SEC << "초" << endl;
}