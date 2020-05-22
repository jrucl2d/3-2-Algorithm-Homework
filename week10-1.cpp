#include <iostream> // 2015112083 ������
#include <string>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
using namespace std;
vector<string>s1;
vector<string>s2;
vector<string>s3;
vector<string>s4;
bool** graph;
bool* visited;

void GetInfo() { // �־��� ����
	s1.push_back("AGT"); s1.push_back("AAA"); s1.push_back("ACT"); s1.push_back("AAC");
	s1.push_back("CTT"); s1.push_back("GTA"); s1.push_back("TTT"); s1.push_back("TAA");

	s2.push_back("ATG"); s2.push_back("AGG"); s2.push_back("TGC"); s2.push_back("TCC");
	s2.push_back("GTC"); s2.push_back("GGT"); s2.push_back("GCA"); s2.push_back("CAG");

	s3.push_back("ATG"); s3.push_back("TGG"); s3.push_back("TGC"); s3.push_back("GTG");
	s3.push_back("GGC"); s3.push_back("GCA"); s3.push_back("GCG"); s3.push_back("CGT");

	s4.push_back("ATGC"); s4.push_back("TGCG"); s4.push_back("GCGG"); s4.push_back("CGGC");
	s4.push_back("GGCT"); s4.push_back("GGCT"); s4.push_back("GCTG"); s4.push_back("CTGT");
	s4.push_back("TGTA"); s4.push_back("GTAT"); s4.push_back("TATG"); s4.push_back("ATGG");
	s4.push_back("TGGT"); s4.push_back("GGTG");
}
void MakeGraph(vector<string>s, int snum, int slen) { // �׷��� ����
	for (int i = 0; i < snum; i++) {
		for (int j = 0; j < snum; j++) {
			graph[i][j] = false;
			bool same = true;
			if (i == j) // �ڱ� �ڽ��� ����
				continue;
			for (int k = 0; k < slen - 1; k++) {
				if (s[i][k + 1] != s[j][k]) { // i��° ������ ù�ܾ� ���� �޺κа� j��° ���� ���ܾ� ���� �պκ� ��
					same = false;
					break;
				}
			}
			if (same)
				graph[i][j] = true; // �������� ���� ��� true�� ����
		}
	}
}
void DFS(vector<string>s, int start, int snum, int slen) {
	visited[start] = true; // ���� ��ġ�� �湮�ߴٰ� ǥ��
	int level = 0; // ���� ��ġ�κ����� �Ÿ�
	stack<pair<int,int>>stack;
	stack.push({ start , 0}); // ù ��ġ, ���� 0���� ���� ����
	vector<pair<int,int>> v; // ����� ���� ����
	int beforelevel = -1; // ������ ������ ������ ����

	while (!stack.empty()) {
		start = stack.top().first; // ������ ���� top ���Ҹ� ����
		level = stack.top().second;
		v.push_back({ start,level });

		stack.pop();
		visited[start] = true; // �ش� ��Ҹ� �湮�ߴٰ� ǥ��

		if (level == snum - 1) { // ��� ������ �� �̵��� ���
			cout << "String Found!! : ";
			string ans = "";
			ans += s[v[0].first]; // ù �ܾ� ��ü �߰�
			for (int i = 1; i < v.size(); i++) { // ������ �ܾ� ������� �����ڸ� �߰�
				ans += s[v[i].first][slen - 1];
			}
			cout << ans << endl;
		}
		// DFS�� Ž�� �߿� ���� ��ġ���� ���̻� �� �� ��� �ٷ� �θ� ��ġ���� ���� ��ġ�� ���� ���
		if (beforelevel == level) { // ������ ������ ������ ����.
			visited[v[v.size() - 2].first] = false; // ���� ��带 �̹湮 ó���ϰ� 
			v.erase(v.end()-2, v.end() - 1); // �湮 �̷¿��� ����
		}
		// Ž���߿� �ٷ� ������ ���̻� �� �� ���� ��ġ�� �����ؼ� ���� ���� �ٸ� ��带 �������� ��
		if (beforelevel > level) {
			int deleteindex = 0; // �湮 �̷¿��� �����ؾ� �ϴ� ù �ε���
			for (int i = 0; i < v.size(); i++) {
				if (v[i].second >= level) { // �湮 �̷¿��� ���纸�� ������ ���ų� ū ���� ��� �̹湮ó��
					if (v[i].second == level && v[i].first != start)
						deleteindex = i;
					visited[v[i].first] = false;
				}
			}
			v.erase(v.begin() + deleteindex, v.end() - 1); // ������ �̹湮 ó���� ��ŭ ��� �湮 �̷¿��� ����
		}

		beforelevel = level;
		level++;
		for (int i = 0; i < snum; i++) { // ���� ��忡�� �̹湮�߰� �� �������� �ִ� ��带 ���ÿ� �߰�
			if (graph[start][i] && !visited[i]) {
				stack.push({ i, level });
			}
		}
	}
}
void Hamiltonian(vector<string>s) {
	// vertex ������ ���缭 �׷����� �迭 ���� �Ҵ�
	int snum = s.size();
	int slen = s[0].size(); // �� ������ ����
	graph = new bool*[snum];
	for (int i = 0; i < snum; i++)
		graph[i] = new bool[snum];
	MakeGraph(s, snum, slen); // �׷��� ����

	visited = new bool [snum]; // �湮 ���� ������ �迭
	for (int i = 0; i < snum; i++) {
		for (int j = 0; j < snum; j++)
			visited[j] = false;
		DFS(s, i, snum, slen); // �� vertex�� ���ؼ� ����
	}
	cout << endl;
	for (int i = 0; i < snum; i++) {
		delete[] graph[i];
	}
	delete[] graph;
	delete[] visited;
}


vector<string> MakeSpectrum(string s, int slen) {
	vector<string>res;
	int stringlen = s.size();
	string tmp = "";
	vector<string>res2;
	for (int i = 0; i <= stringlen - slen; i++) { // ������� slen���� �������� ���
		tmp = "";
		for (int j = i; j < i + slen; j++) {
			tmp += s[j];
		}
		res.push_back(tmp); // res ���Ϳ� ����
	}
	int resSize = res.size();

	bool* tmpTable; // �ߺ��� �˻��� ���̺�
	tmpTable = new bool[resSize];
	for (int i = 0; i < resSize; i++)
		tmpTable[i] = false;
	srand((unsigned int)time(NULL));
	int cnt;
	int mod = cnt = resSize;
	while (cnt > 0) {
		int index = rand() % mod;
		if (!tmpTable[index]) { // ����� ���ڰ� �ƴϸ�
			tmpTable[index] = true; // ���� ���� ǥ��
			res2.push_back(res[index]); // res2�� ������ ������ ���� ����
			cnt--;
		}
	}
	return res2;
}
void MakeMine() {
	string mstring = "";
	int slen = 0;
	cout << "Input String : ";
	cin >> mstring;
	cout << "Input Length of Pieces : ";
	cin >> slen;
	vector<string>s;
	s = MakeSpectrum(mstring, slen); // string �Է¹ް� ����Ʈ�� ����
	cout << "My Spectrum : ";
	for (int i = 0; i < s.size(); i++)
		cout << s[i] << " ";
	cout << endl;
	Hamiltonian(s); // hamiltonian �˰��� ����
}

int main() {
	GetInfo();
	cout << "Spectrum S1" << endl;
	Hamiltonian(s1);
	cout << "Spectrum S2" << endl;
	Hamiltonian(s2);
	cout << "Spectrum S3" << endl;
	Hamiltonian(s3);
	cout << "Spectrum S4" << endl;
	Hamiltonian(s4);
	cout << "My Spectrum" << endl;
	MakeMine();
	cout << "end";
}