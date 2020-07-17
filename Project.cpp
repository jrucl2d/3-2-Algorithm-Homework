#include <iostream>
#include <vector>
#include <ctime>
#include <string>
#include <fstream>
#include <random>
#include <set>

#define MAXNUM 500000
using namespace std;
char DNA[4] = { 'T', 'A', 'G', 'C' };
int x = 5;
int y = 3;
int seqHashTable[MAXNUM][4] = { 0, }; // seqHash의 값을 테이블에 저장

int GetRand(int min, int max) {
	random_device rn;
	mt19937_64 rnd(rn());
	uniform_int_distribution<int> range(min, max);

	return range(rnd);
}
void MakeSequence(string& rseq) {
	string fName = "rseq.txt";
	ofstream wFile(fName.data());

	// 랜덤 시퀀스 생성
	for (int i = 0; i < MAXNUM; i++) {
		int random = GetRand(0, 3);
		rseq += DNA[random];
	}
	// 파일에 쓰기
	if (wFile.is_open()) {
		wFile << rseq;
		wFile.close();
	}
}
string MakeMySequence(string rseq, int k) {
	set<int> dup_check_set;
	string fName = "mseq.txt";
	ofstream wFile(fName.data());
	string myseq = rseq;
	// 달라야 하는 base 갯수
	int should_diff = MAXNUM * x / 100;
	int rsize = rseq.size();

	for (int i = 0; i < should_diff; i++) {
		// 랜덤으로 바꿀 부분의 위치를 뽑는다.
		int pos = GetRand(0, rsize - 1);
		// set을 이용해서 이번에 뽑힌 위치를 바꾼 적 있는지 확인한다
		// 만약에 없다면 set에 추가하고, 그렇지 않다면 
		// 뽑은 적 없는 위치가 나올 때 까지 반복한다.
		while (dup_check_set.find(pos) != dup_check_set.end()) {
			pos = GetRand(0, rsize - 1);
		}
		dup_check_set.insert(pos);
		// 해당하는 위치의 base를 새로운 base로 바꾼다.
		char theChar = myseq[pos];
		int newChar = GetRand(0, 3);
		while (DNA[newChar] == theChar) // 기존과 다른 문자 나올 때까지 반복
			newChar = GetRand(0, 3);
		myseq[pos] = DNA[newChar];
	}
	// 파일에 쓰기
	if (wFile.is_open()) {
		wFile << myseq;
		wFile.close();
	}
	return myseq;
}

void MakeShortRead(string seq, int k, int n) {
	int random;
	int maxIndex = MAXNUM - k - 1; // 첫 인덱스가 될 수 있는 최대 수
	string shortseq = "";
	string fName = "shortread.txt";
	ofstream wFile(fName.data());

	if (wFile.is_open()) {
		for (int i = 0; i < n; i++) {
			random = rand() % (maxIndex + 1);
			shortseq = "";
			for (int j = random; j < random + k; j++) // 해당 인덱스부터 k개의 문자열을 잘라서 파일에 저장
				shortseq += seq[j];
			wFile << shortseq << endl;
		}
		wFile.close();
	}
}
void Trivial(string& seq, string read) {
	int count = y; // 다른 문자 허용 개수
	int seqSize = seq.size();
	int readSize = read.size();
	for (int i = 0; i <= seqSize - readSize; i++) {
		int j = 0;
		count = y;
		for (; j < readSize; j++) {
			if (seq[i + j] != read[j]) { // seq의 특정 위치 문자가 read의 특정 위치 문자와 같지 않다면
				count--; // 다르면 count 감소
				if (count < 0) // 허용된 개수를 초과하면 반복 탈출
					break;
			}
		}
		if (count >= 0) { // 틀린 개수가 0 이상이면 위치를 찾은 것.
			for (int k = i; k < i + readSize; k++)
				seq[k] = read[k - i]; // read로 덮어 씌우기
			break;
		}
	}
}

void MakeTable(string seq, int rsize) { // seqHash의 선처리, HashTable을 만듦
	int ssize = seq.size();
	int tmp = 0;
	for (int i = 0; i < rsize; i++) { // 0번 인덱스의 해시 값
		tmp = (seq[i] - '0' - 15) % 5 - 1;
		seqHashTable[0][tmp]++;
	}

	for (int i = 1; i <= ssize - rsize; i++) { // 반복문 끝에서 매번 하는 일을 여기서 미리 다 끝내버림
		int tmp1 = (seq[i - 1] - '0' - 15) % 5 - 1; // 빼야하는 첫 글자
		int tmp2 = (seq[i + rsize - 1] - '0' - 15) % 5 - 1; // 추가해야 하는 마지막 글자
		for (int j = 0; j < 4; j++) {
			seqHashTable[i][j] = seqHashTable[i - 1][j];
		}
		seqHashTable[i][tmp1]--;
		seqHashTable[i][tmp2]++;
	}
}
void RabinKarp(string& seq, string read) {
	int ssize = seq.size();
	int rsize = read.size();
	int readHash[4] = { 0, };

	for (int i = 0; i < rsize; i++) {
		readHash[(read[i] - '0' - 15) % 5 - 1]++; // 해당 계산 과정을 통해서 T->0, A->1, G->2, C->3으로 만들 수 있음
	}

	for (int i = 0; i <= ssize - rsize; i++) {
		int diff = 0;
		for (int j = 0; j < 4; j++) {
			int tmp = 0;
			tmp = readHash[j] - seqHashTable[i][j]; // 개수 T,A,G,C의 개수 차이 비교
			tmp = tmp > 0 ? tmp : -tmp;
			diff += tmp;
		}

		if (diff <= y * 2) { // A->C로 바뀌면 A가 하나 줄어들고 C가 하나 늘어나면서 2개 차이가 남. 즉 한 글자당 두 배 차이가 생김
			int count = y;
			int* diffLoc = new int[y + 1];
			int index = 0;
			for (int j = 0; j < rsize; j++) { // 해시값이 허용 가능한 경우에 한해서 trivial 알고리즘 실행
				if (seq[i + j] != read[j]) {
					count--;
					diffLoc[index++] = i + j; // 해당 위치 기억
					if (count < 0)
						break;
				}
			}
			if (count >= 0) { // 틀린 개수가 0 이상이면 위치를 찾은 것.
				// 영향 받는 해시 테이블 갱신
				for (int j = 0; j < index; j++) {
					int cLoc = diffLoc[j]; // 변한 위치 cLoc
					for (int k = cLoc - rsize + 1; k <= cLoc && k >= 0 && k <= ssize - rsize; k++) { // cLoc에 걸쳐있는 모든 테이블 원소들에 대해서
						seqHashTable[k][(seq[cLoc] - '0' - 15) % 5 - 1]--; // 기존 문자의 개수를 줄이고
						seqHashTable[k][(read[cLoc - i] - '0' - 15) % 5 - 1]++; // 바뀔 문자의 개수를 증가
					}
				}
				// read로 덮어 씌우기
				for (int k = 0; k < rsize; k++) {
					seq[k + i] = read[k];
				}
				delete[] diffLoc;
				return;
			}
			delete[] diffLoc;
		}
	}
}

int main() {
	srand((unsigned int)time(0));
	string rseq = "";
	string mseq = "";
	int k, n;

	// 기존의 시퀀스 생성 부분 주석 처리
	/*
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
	*/

	// 레퍼런스 시퀀스 불러오는 부분
	string reference = "";
	string SeqFname = "test_ref_1000.txt";
	ifstream seqFile(SeqFname.data());
	if (seqFile.is_open()) {
		getline(seqFile, reference);
	}
	seqFile.close();
	string remakeseq = reference;

	// MyDNA 시퀀스 불러오는 부분
	string MyFname = "Mydna_1000.txt";
	ifstream seqFile2(MyFname.data());
	if (seqFile2.is_open()) {
		getline(seqFile2, mseq);
	}
	seqFile2.close();

	// 쇼트리드 불러오는 부분
	string shortreadFname = "shortread_1000.txt";

	// Trivial 알고리즘 주석처리
	/*
	// Trivial 복원 과정
	cout << "Calculate Difference between Rsequence and Msequence..." << endl;
	string fseq = reference; // rseq로부터 복원해야 하는 fseq
	ifstream oFile(shortreadFname.data());
	clock_t start = clock(); // 시간 측정 시작
	if (oFile.is_open()) {
		string tmp;
		while (getline(oFile, tmp)) {
			Trivial(fseq, tmp);
		}
		oFile.close();
	}
	clock_t end = clock(); // 시간 측정 종료
	cout << "Done" << endl << endl;

	// Trivial 결과 출력
	cout << "<Trivial 알고리즘 결과>" << endl;
	int count = 0;
	for (int i = 0; i < fseq.size(); i++)
		if (mseq[i] != fseq[i])
			count++;
	cout << "Difference Count : ";
	cout << count << endl;
	cout << "Accuracy : ";
	cout.precision(4);
	cout << ((double)(MAXNUM - count) / MAXNUM) * 100 << "%" << endl;
	cout << "Executing Time : ";
	cout << (double)(end - start) / CLOCKS_PER_SEC << "second";
	cout << endl;
	*/

	// Rabin Karp 알고리즘 복원 과정
	ifstream o2File(shortreadFname.data());
	clock_t startr = clock(); // 시간 측정 시작
	string tmp;
	getline(o2File, tmp); // 한 문장 빼옴
	k = tmp.size();
	MakeTable(remakeseq, k); // HashTable 선처리
	RabinKarp(remakeseq, tmp); // 빼온 한 문장에 대해서 처리

	if (o2File.is_open()) {
		while (getline(o2File, tmp)) {
			RabinKarp(remakeseq, tmp);
		}
		o2File.close();
	}
	clock_t endr = clock(); // 시간 측정 종료

	// 복원 결과 파일로 저장
	string fName = "repair_dna_1000.txt";
	ofstream wFile(fName.data());
	if (wFile.is_open()) {
		wFile << remakeseq;
		wFile.close();
	}

	cout << endl << "Done" << endl;
	cout << endl << "<My 알고리즘 결과>" << endl;
	int countr = 0;
	for (int i = 0; i < reference.size(); i++)
		if (mseq[i] != remakeseq[i])
			countr++;
	cout << "Difference Count : ";
	cout << countr << endl;
	cout << "Accuracy : ";
	cout.precision(4);
	cout << ((double)(reference.size() - countr) / reference.size()) * 100 << "%" << endl;
	cout << "Executing Time : ";
	cout << (double)(endr - startr) / CLOCKS_PER_SEC << "second";
}