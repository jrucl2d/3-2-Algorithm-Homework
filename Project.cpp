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
int seqHashTable[MAXNUM][4] = { 0, }; // seqHash�� ���� ���̺� ����

int GetRand(int min, int max) {
	random_device rn;
	mt19937_64 rnd(rn());
	uniform_int_distribution<int> range(min, max);

	return range(rnd);
}
void MakeSequence(string& rseq) {
	string fName = "rseq.txt";
	ofstream wFile(fName.data());

	// ���� ������ ����
	for (int i = 0; i < MAXNUM; i++) {
		int random = GetRand(0, 3);
		rseq += DNA[random];
	}
	// ���Ͽ� ����
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
	// �޶�� �ϴ� base ����
	int should_diff = MAXNUM * x / 100;
	int rsize = rseq.size();

	for (int i = 0; i < should_diff; i++) {
		// �������� �ٲ� �κ��� ��ġ�� �̴´�.
		int pos = GetRand(0, rsize - 1);
		// set�� �̿��ؼ� �̹��� ���� ��ġ�� �ٲ� �� �ִ��� Ȯ���Ѵ�
		// ���࿡ ���ٸ� set�� �߰��ϰ�, �׷��� �ʴٸ� 
		// ���� �� ���� ��ġ�� ���� �� ���� �ݺ��Ѵ�.
		while (dup_check_set.find(pos) != dup_check_set.end()) {
			pos = GetRand(0, rsize - 1);
		}
		dup_check_set.insert(pos);
		// �ش��ϴ� ��ġ�� base�� ���ο� base�� �ٲ۴�.
		char theChar = myseq[pos];
		int newChar = GetRand(0, 3);
		while (DNA[newChar] == theChar) // ������ �ٸ� ���� ���� ������ �ݺ�
			newChar = GetRand(0, 3);
		myseq[pos] = DNA[newChar];
	}
	// ���Ͽ� ����
	if (wFile.is_open()) {
		wFile << myseq;
		wFile.close();
	}
	return myseq;
}

void MakeShortRead(string seq, int k, int n) {
	int random;
	int maxIndex = MAXNUM - k - 1; // ù �ε����� �� �� �ִ� �ִ� ��
	string shortseq = "";
	string fName = "shortread.txt";
	ofstream wFile(fName.data());

	if (wFile.is_open()) {
		for (int i = 0; i < n; i++) {
			random = rand() % (maxIndex + 1);
			shortseq = "";
			for (int j = random; j < random + k; j++) // �ش� �ε������� k���� ���ڿ��� �߶� ���Ͽ� ����
				shortseq += seq[j];
			wFile << shortseq << endl;
		}
		wFile.close();
	}
}
void Trivial(string& seq, string read) {
	int count = y; // �ٸ� ���� ��� ����
	int seqSize = seq.size();
	int readSize = read.size();
	for (int i = 0; i <= seqSize - readSize; i++) {
		int j = 0;
		count = y;
		for (; j < readSize; j++) {
			if (seq[i + j] != read[j]) { // seq�� Ư�� ��ġ ���ڰ� read�� Ư�� ��ġ ���ڿ� ���� �ʴٸ�
				count--; // �ٸ��� count ����
				if (count < 0) // ���� ������ �ʰ��ϸ� �ݺ� Ż��
					break;
			}
		}
		if (count >= 0) { // Ʋ�� ������ 0 �̻��̸� ��ġ�� ã�� ��.
			for (int k = i; k < i + readSize; k++)
				seq[k] = read[k - i]; // read�� ���� �����
			break;
		}
	}
}

void MakeTable(string seq, int rsize) { // seqHash�� ��ó��, HashTable�� ����
	int ssize = seq.size();
	int tmp = 0;
	for (int i = 0; i < rsize; i++) { // 0�� �ε����� �ؽ� ��
		tmp = (seq[i] - '0' - 15) % 5 - 1;
		seqHashTable[0][tmp]++;
	}

	for (int i = 1; i <= ssize - rsize; i++) { // �ݺ��� ������ �Ź� �ϴ� ���� ���⼭ �̸� �� ��������
		int tmp1 = (seq[i - 1] - '0' - 15) % 5 - 1; // �����ϴ� ù ����
		int tmp2 = (seq[i + rsize - 1] - '0' - 15) % 5 - 1; // �߰��ؾ� �ϴ� ������ ����
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
		readHash[(read[i] - '0' - 15) % 5 - 1]++; // �ش� ��� ������ ���ؼ� T->0, A->1, G->2, C->3���� ���� �� ����
	}

	for (int i = 0; i <= ssize - rsize; i++) {
		int diff = 0;
		for (int j = 0; j < 4; j++) {
			int tmp = 0;
			tmp = readHash[j] - seqHashTable[i][j]; // ���� T,A,G,C�� ���� ���� ��
			tmp = tmp > 0 ? tmp : -tmp;
			diff += tmp;
		}

		if (diff <= y * 2) { // A->C�� �ٲ�� A�� �ϳ� �پ��� C�� �ϳ� �þ�鼭 2�� ���̰� ��. �� �� ���ڴ� �� �� ���̰� ����
			int count = y;
			int* diffLoc = new int[y + 1];
			int index = 0;
			for (int j = 0; j < rsize; j++) { // �ؽð��� ��� ������ ��쿡 ���ؼ� trivial �˰��� ����
				if (seq[i + j] != read[j]) {
					count--;
					diffLoc[index++] = i + j; // �ش� ��ġ ���
					if (count < 0)
						break;
				}
			}
			if (count >= 0) { // Ʋ�� ������ 0 �̻��̸� ��ġ�� ã�� ��.
				// ���� �޴� �ؽ� ���̺� ����
				for (int j = 0; j < index; j++) {
					int cLoc = diffLoc[j]; // ���� ��ġ cLoc
					for (int k = cLoc - rsize + 1; k <= cLoc && k >= 0 && k <= ssize - rsize; k++) { // cLoc�� �����ִ� ��� ���̺� ���ҵ鿡 ���ؼ�
						seqHashTable[k][(seq[cLoc] - '0' - 15) % 5 - 1]--; // ���� ������ ������ ���̰�
						seqHashTable[k][(read[cLoc - i] - '0' - 15) % 5 - 1]++; // �ٲ� ������ ������ ����
					}
				}
				// read�� ���� �����
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

	// ������ ������ ���� �κ� �ּ� ó��
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

	// ���۷��� ������ �ҷ����� �κ�
	string reference = "";
	string SeqFname = "test_ref_1000.txt";
	ifstream seqFile(SeqFname.data());
	if (seqFile.is_open()) {
		getline(seqFile, reference);
	}
	seqFile.close();
	string remakeseq = reference;

	// MyDNA ������ �ҷ����� �κ�
	string MyFname = "Mydna_1000.txt";
	ifstream seqFile2(MyFname.data());
	if (seqFile2.is_open()) {
		getline(seqFile2, mseq);
	}
	seqFile2.close();

	// ��Ʈ���� �ҷ����� �κ�
	string shortreadFname = "shortread_1000.txt";

	// Trivial �˰��� �ּ�ó��
	/*
	// Trivial ���� ����
	cout << "Calculate Difference between Rsequence and Msequence..." << endl;
	string fseq = reference; // rseq�κ��� �����ؾ� �ϴ� fseq
	ifstream oFile(shortreadFname.data());
	clock_t start = clock(); // �ð� ���� ����
	if (oFile.is_open()) {
		string tmp;
		while (getline(oFile, tmp)) {
			Trivial(fseq, tmp);
		}
		oFile.close();
	}
	clock_t end = clock(); // �ð� ���� ����
	cout << "Done" << endl << endl;

	// Trivial ��� ���
	cout << "<Trivial �˰��� ���>" << endl;
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

	// Rabin Karp �˰��� ���� ����
	ifstream o2File(shortreadFname.data());
	clock_t startr = clock(); // �ð� ���� ����
	string tmp;
	getline(o2File, tmp); // �� ���� ����
	k = tmp.size();
	MakeTable(remakeseq, k); // HashTable ��ó��
	RabinKarp(remakeseq, tmp); // ���� �� ���忡 ���ؼ� ó��

	if (o2File.is_open()) {
		while (getline(o2File, tmp)) {
			RabinKarp(remakeseq, tmp);
		}
		o2File.close();
	}
	clock_t endr = clock(); // �ð� ���� ����

	// ���� ��� ���Ϸ� ����
	string fName = "repair_dna_1000.txt";
	ofstream wFile(fName.data());
	if (wFile.is_open()) {
		wFile << remakeseq;
		wFile.close();
	}

	cout << endl << "Done" << endl;
	cout << endl << "<My �˰��� ���>" << endl;
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