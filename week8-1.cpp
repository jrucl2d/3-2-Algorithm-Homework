#include <iostream> // 2015112083 ������
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;
#define MODNUM 13

int table[40]; // �ִ� ���κ� ���̺�

void BruteForce(char* text, int textlen, char* pattern, int patternlen) {
	int count = 0;
	vector<int>loc;
	for (int i = 0; i <= textlen - patternlen; i++) {
		int j = 0;
		for (; j < patternlen; j++) {
			if (text[i + j] != pattern[j]) { // text�� i���� j�� pattern�� ���� ������ �ݺ� Ż��
				break;
			}
		}
		if (j == patternlen) { // j�� ������ �� �˻��ߴٸ� pattern�� ���̿� j�� ����-> pattern�� ã�� ��
			count++;
			loc.push_back(i);
		}
	}
	cout << "�� " << count << "�� �߰�, ��ġ : ";
	if (count == 0) {
		cout << "�ش� string ����" << endl;
		return;
	}
	for (int i = 0; i < loc.size(); i++)
		cout << loc[i] << " ";
	cout << endl;
}
void MakeTable(char* string, int len) { // �ִ� ���κ� ���̺� ����� �Լ�
	for (int i = 0; i < len; i++) // table ���� 0���� �ʱ�ȭ
		table[i] = 0;
	int j = 0;
	for (int i = 1; i < len; i++) { // i�� ��Ʈ���� �� ��° ���Һ��� ������ ����
		while (j > 0 && string[i] != string[j]) { // ���� ������ j�� �̵��� ���¿���(j>0) �߰��� ���� ������
			j = table[j - 1]; // j�� table�� j-1�� ����� �ε����� �̵�(����� �ε����� ������ŭ�� ���λ� ���̻簡 ����)
		}
		if (string[i] == string[j]) // i�� j�� ���� ���� �߰��ϸ� j+1 ���� ���̺� �߰���.
			table[i] = ++j;
	}
}

void KMP(char* text, int textlen, char* pattern, int patternlen) {
	int count = 0;
	vector<int>loc;

	MakeTable(pattern, patternlen); // ������ �ִ� ���κ� ���̺��� ����
	// ���̺� ���� �˰���� �����ϰ� �۵�
	int j = 0;
	for (int i = 0; i < textlen; i++) { // ���� ���ο��� ���ϴ� �Ͱ� �޸� ���ϰ� ���� text�� ��
		while (j > 0 && text[i] != pattern[j]) // ��ġ���� �ʴ� ��찡 �߻��ϸ�
			j = table[j - 1]; // ���κ� ���̺��� j-1�� ����Ű�� ������ j�� �ű��. (�׸�ŭ�� ���λ�� ���̻簡 ����)
		if (text[i] == pattern[j]) {
			if (j == patternlen - 1) { // j�� ���� ���ڿ� ���θ� �����̹Ƿ� j�� ������ �� ���ұ��� �ٴٸ��� ã�� ���̴�.
				j = table[j]; // j�� ���̺� j��ġ�� ����� �ε����� �̵����Ѽ� �ڿ� �� ���� ���� �����ϴ��� ����
				count++;
				loc.push_back(i - patternlen + 1);
			}
			else j++;
		}

	}
	cout << "�� " << count << "�� �߰�, ��ġ : ";
	if (count == 0) {
		cout << "�ش� string ����" << endl;
		return;
	}
	for (int i = 0; i < loc.size(); i++)
		cout << loc[i] << " ";
	cout << endl;
}
int MOD(int num) { // mod ���� ���� �Լ�
	if (num < 0) { // ������ ���
		num = -num; // ������ ����� �����ϰ�
		num = num % MODNUM; // ��ⷯ ���� ����
		num = MODNUM - num; // ���� ������ ������ ����� ����
		return num;
	}
	return num % MODNUM;
}
int HASH(char* string, int len) { // �ؽ� �Լ�(ȣ���� ��� ���)
	int hash = 0;
	for (int i = 0; i < len; i++) {
		if (string[i] >= 'A' && string[i] <= 'Z') // ���ĺ� �빮���� ��� 10���� ������ �� �ֵ��� ó�� -> A(65) - 55
			hash += (string[i] - 55) * pow(36, len - 1 - i);
		else
			hash += (string[i] - '0') * pow(36, len - 1 - i);
	}
	return hash;
}
void RabinKarp(char* text, int textlen, char* pattern, int patternlen) { // 0~9, A~Z�� 36���� ���
	int count = 0;
	vector<int>loc;

	int phash = HASH(pattern, patternlen); // pattern�� hash ��
	phash = MOD(phash); // ��ⷯ ������ ������ phash ��

	char tmp[100]; // ���� ���̸�ŭ �ӽ� ������ ���ڿ�
	for (int i = 0; i < patternlen; i++) // ���� ���� pattern���� ��ŭ�� text �κ� ���ڿ� ����
		tmp[i] = text[i];
	int stringhash = HASH(tmp, patternlen); // �ؽ� ����
	int beforehash = stringhash; // ��ⷯ ���� ���� ���� hash ����
	stringhash = MOD(stringhash);

	for (int i = 0; i <= textlen - patternlen; i++) {
		if (stringhash == phash) { // hash ���� ������ ��� ������ ����� ������ ������� ����
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
		stringhash = beforehash; // ��ⷯ ���� ���� hash�� ���ؼ� ������ �۾� ����
		if (i <= textlen - patternlen) {
			if (text[i] >= 'A' && text[i] <= 'Z') // high-order digit�� ���ְ� �ڸ��� 36�� �����ش�.
				stringhash -= (text[i] - 55) * pow(36, patternlen - 1);
			else stringhash -= (text[i] - '0') * pow(36, patternlen - 1);
			stringhash *= 36;
			if (text[i + patternlen] >= 'A' && text[i + patternlen] <= 'Z') // ���� �ڸ��� �����ش�.
				stringhash += (text[i + patternlen] - 55);
			else stringhash += (text[i + patternlen] - '0');
			beforehash = stringhash; // ��ⷯ ���ϱ� ���� ���� �־���
			stringhash = MOD(stringhash); // �������� ��ⷯ ���� �����ش�.
		}
		
	}
	cout << "�� " << count << "�� �߰�, ��ġ : ";
	if (count == 0) {
		cout << "�ش� string ����" << endl;
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

	clock_t start = clock(); // �ð� ���� ����
	BruteForce(textString, strlen(textString), patternString, strlen(patternString));
	clock_t end = clock(); // �ð� ���� ����
	cout << "BruteForce ���� �ð� : " << (double)(end - start) / CLOCKS_PER_SEC << "��" << endl << endl;
	
	start = clock(); // �ð� ���� ����
	KMP(textString, strlen(textString), patternString, strlen(patternString));
	end = clock(); // �ð� ���� ����
	cout << "KMP ���� �ð� : " << (double)(end - start) / CLOCKS_PER_SEC << "��" << endl << endl;

	start = clock(); // �ð� ���� ����
	RabinKarp(textString, strlen(textString), patternString, strlen(patternString));
	end = clock(); // �ð� ���� ����
	cout << "RabinKarp ���� �ð� : " << (double)(end - start) / CLOCKS_PER_SEC << "��" << endl;
}