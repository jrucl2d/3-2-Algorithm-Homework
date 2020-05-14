#include <iostream> // 2015112083 유성근
#include <vector>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>
#define MAXNUM 500000
using namespace std;
char DNA[4] = { 'A', 'C', 'G', 'T' };
int x = 50; // 50% 확률
int y = 2; // 2개까지 허용

void BruteForce(string& seq, string read) {
	int count = y; // 다른 문자 허용 개수
	for (int i = 0; i <= seq.size() - read.size(); i++) {
		int j = 0;
		count = y;
		for (; j < read.size(); j++) {
			if (seq[i + j] != read[j]) { // seq의 특정 위치 문자가 read의 특정 위치 문자와 같지 않다면
				count--; // 다르면 count 감소
				if(count < 0) // 허용된 개수를 초과하면 반복 탈출
					break;
			}
		}
		if (count >= 0) { // 틀린 개수가 0 이하이면 위치를 찾은 것.
			for (int k = i; k < i + read.size(); k++) 
				seq[k] = read[k - i]; // read로 덭붙이기
		}
	}
}
void MakeSequence(string &rseq) {
	string fName = "rseq.txt";
	ofstream wFile(fName.data());

	// 랜덤 시퀀스 생성
	int random = rand() % 4;
	int before = random;
	rseq += DNA[random]; // 첫 원소 넣기
	for (int i = 1; i < MAXNUM; i++) {
		random = rand() % 4;
		while (random == before) { // 다른 것 나올 때까지 반복
			random = rand() % 4;
		}
		rseq += DNA[random];
		before = random;	
	}
	// 파일에 쓰기
	if (wFile.is_open()) {
		wFile << rseq;
		wFile.close();
	}
}
string MakeMySequence(string rseq, int k) { // k 길이로 read를 만들었을 때 x의 확률로 y개 문자가 달라야 한다.
	string myseq = "";
	bool changed = false;
	int i = 0;
	for (; i <= MAXNUM - k; i+=k) {
		string sliced = "";
		for (int j = i; j < i + k; j++) // i부터 k길이 만큼 잘라내기
			sliced += rseq[j];
		int point = k / y;
		int cnt = y;
		for (int j = 0; j < k; j += point) { // k길이의 문자열을 또 y개로 나눠서 각 조각마다 x퍼센트 확률로 다른 문자가 존재하도록
			if (cnt > 0) {
				int changeIndex = rand() % point + j; // j~(j+point) 사이의 인덱스 중 하나 선택

				int canChange = rand() % 100 + 1; // 1~100 사이의 100개 수 중 랜덤 수 생성
				if (canChange < x) { // 랜덤수가 x보다 작으면(x의 확률로)
					int anotherChar = rand() % 4;
					char noThis = sliced[changeIndex];
					while (DNA[anotherChar] == noThis) { // 기존 문자와 다른 문자를 생성
						anotherChar = rand() % 4;
					}
					sliced[changeIndex] = DNA[anotherChar]; // x의 확률로 해당 인덱스를 변경
				}
			}
			cnt--;
		}
		myseq += sliced;
	}
	for (int j = i; j < MAXNUM; j++) // 뒤의 처리 못한 문자 추가
		myseq += rseq[j];
	return myseq;
}
void MakeShortRead(string seq, int k, int n) {
	int random;
	int maxIndex = MAXNUM - k; // 첫 인덱스가 될 수 있는 최대 수
	string shortseq = "";
	string fName = "shortread.txt";
	ofstream wFile(fName.data());

	if (wFile.is_open()) {
		for (int i = 0; i < n; i++) {
			random = rand() % maxIndex; // 랜덤한 인덱스
			shortseq = "";
			for (int j = random; j < random + k; j++) // 해당 인덱스부터 k개의 문자열을 잘라서 파일에 저장
				shortseq += seq[j];
			wFile << shortseq << endl;
		}
		wFile.close();
	}
}

int main() {
	srand((unsigned int)time(0));
	string rseq = "";
	string mseq = "";
	int k, n;

	cout << "Making Reference DNA Sequence..." << endl;
	MakeSequence(rseq);
	cout << "Done" << endl << endl;
	cout << "Input length of shortRead :";
	cin >> k;
	cout << "Input number of shortRead :";
	cin >> n;
	cout << endl;
	cout << "Making ShortRead File..." << endl;
	mseq = MakeMySequence(rseq, k);
	MakeShortRead(mseq, k, n);
	cout << "Done" << endl << endl;
	
	// 복원 과정
	cout << "Calculate Difference between Rsequence and Msequence..." << endl;
	string fseq = rseq; // rseq로부터 복원해야 하는 fseq
	string shortreadFname = "shortread.txt";
	ifstream oFile(shortreadFname.data());

	clock_t start = clock(); // 시간 측정 시작
	if (oFile.is_open()) {
		string tmp;

		while (getline(oFile, tmp)) {

			BruteForce(fseq, tmp);
		}

		oFile.close();
	}
	clock_t end = clock(); // 시간 측정 종료
	cout << "Done" << endl << endl;

	// 결과 출력
	int count = 0;
	for (int i = 0; i < fseq.size(); i++)
		if (rseq[i] != fseq[i])
			count++;
	cout << "Difference Count : ";
	cout << count << endl;
	cout << "Executing Time : ";
	cout << (double)(end - start) / CLOCKS_PER_SEC << "second";
}