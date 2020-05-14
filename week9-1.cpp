#include <iostream> // 2015112083 ������
#include <vector>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>
#define MAXNUM 500000
using namespace std;
char DNA[4] = { 'A', 'C', 'G', 'T' };
int x = 50; // 50% Ȯ��
int y = 2; // 2������ ���

void BruteForce(string& seq, string read) {
	int count = y; // �ٸ� ���� ��� ����
	for (int i = 0; i <= seq.size() - read.size(); i++) {
		int j = 0;
		count = y;
		for (; j < read.size(); j++) {
			if (seq[i + j] != read[j]) { // seq�� Ư�� ��ġ ���ڰ� read�� Ư�� ��ġ ���ڿ� ���� �ʴٸ�
				count--; // �ٸ��� count ����
				if(count < 0) // ���� ������ �ʰ��ϸ� �ݺ� Ż��
					break;
			}
		}
		if (count >= 0) { // Ʋ�� ������ 0 �����̸� ��ġ�� ã�� ��.
			for (int k = i; k < i + read.size(); k++) 
				seq[k] = read[k - i]; // read�� �E���̱�
		}
	}
}
void MakeSequence(string &rseq) {
	string fName = "rseq.txt";
	ofstream wFile(fName.data());

	// ���� ������ ����
	int random = rand() % 4;
	int before = random;
	rseq += DNA[random]; // ù ���� �ֱ�
	for (int i = 1; i < MAXNUM; i++) {
		random = rand() % 4;
		while (random == before) { // �ٸ� �� ���� ������ �ݺ�
			random = rand() % 4;
		}
		rseq += DNA[random];
		before = random;	
	}
	// ���Ͽ� ����
	if (wFile.is_open()) {
		wFile << rseq;
		wFile.close();
	}
}
string MakeMySequence(string rseq, int k) { // k ���̷� read�� ������� �� x�� Ȯ���� y�� ���ڰ� �޶�� �Ѵ�.
	string myseq = "";
	bool changed = false;
	int i = 0;
	for (; i <= MAXNUM - k; i+=k) {
		string sliced = "";
		for (int j = i; j < i + k; j++) // i���� k���� ��ŭ �߶󳻱�
			sliced += rseq[j];
		int point = k / y;
		int cnt = y;
		for (int j = 0; j < k; j += point) { // k������ ���ڿ��� �� y���� ������ �� �������� x�ۼ�Ʈ Ȯ���� �ٸ� ���ڰ� �����ϵ���
			if (cnt > 0) {
				int changeIndex = rand() % point + j; // j~(j+point) ������ �ε��� �� �ϳ� ����

				int canChange = rand() % 100 + 1; // 1~100 ������ 100�� �� �� ���� �� ����
				if (canChange < x) { // �������� x���� ������(x�� Ȯ����)
					int anotherChar = rand() % 4;
					char noThis = sliced[changeIndex];
					while (DNA[anotherChar] == noThis) { // ���� ���ڿ� �ٸ� ���ڸ� ����
						anotherChar = rand() % 4;
					}
					sliced[changeIndex] = DNA[anotherChar]; // x�� Ȯ���� �ش� �ε����� ����
				}
			}
			cnt--;
		}
		myseq += sliced;
	}
	for (int j = i; j < MAXNUM; j++) // ���� ó�� ���� ���� �߰�
		myseq += rseq[j];
	return myseq;
}
void MakeShortRead(string seq, int k, int n) {
	int random;
	int maxIndex = MAXNUM - k; // ù �ε����� �� �� �ִ� �ִ� ��
	string shortseq = "";
	string fName = "shortread.txt";
	ofstream wFile(fName.data());

	if (wFile.is_open()) {
		for (int i = 0; i < n; i++) {
			random = rand() % maxIndex; // ������ �ε���
			shortseq = "";
			for (int j = random; j < random + k; j++) // �ش� �ε������� k���� ���ڿ��� �߶� ���Ͽ� ����
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
	
	// ���� ����
	cout << "Calculate Difference between Rsequence and Msequence..." << endl;
	string fseq = rseq; // rseq�κ��� �����ؾ� �ϴ� fseq
	string shortreadFname = "shortread.txt";
	ifstream oFile(shortreadFname.data());

	clock_t start = clock(); // �ð� ���� ����
	if (oFile.is_open()) {
		string tmp;

		while (getline(oFile, tmp)) {

			BruteForce(fseq, tmp);
		}

		oFile.close();
	}
	clock_t end = clock(); // �ð� ���� ����
	cout << "Done" << endl << endl;

	// ��� ���
	int count = 0;
	for (int i = 0; i < fseq.size(); i++)
		if (rseq[i] != fseq[i])
			count++;
	cout << "Difference Count : ";
	cout << count << endl;
	cout << "Executing Time : ";
	cout << (double)(end - start) / CLOCKS_PER_SEC << "second";
}