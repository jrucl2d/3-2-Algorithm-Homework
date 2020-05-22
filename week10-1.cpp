#include <iostream> // 2015112083 유성근
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

void GetInfo() { // 주어진 정보
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
void MakeGraph(vector<string>s, int snum, int slen) { // 그래프 생성
	for (int i = 0; i < snum; i++) {
		for (int j = 0; j < snum; j++) {
			graph[i][j] = false;
			bool same = true;
			if (i == j) // 자기 자신은 생략
				continue;
			for (int k = 0; k < slen - 1; k++) {
				if (s[i][k + 1] != s[j][k]) { // i번째 조각의 첫단어 제외 뒷부분과 j번째 조각 끝단어 제외 앞부분 비교
					same = false;
					break;
				}
			}
			if (same)
				graph[i][j] = true; // 연결점이 있을 경우 true로 설정
		}
	}
}
void DFS(vector<string>s, int start, int snum, int slen) {
	visited[start] = true; // 시작 위치는 방문했다고 표시
	int level = 0; // 시작 위치로부터의 거리
	stack<pair<int,int>>stack;
	stack.push({ start , 0}); // 첫 위치, 레벨 0으로 집어 넣음
	vector<pair<int,int>> v; // 출력을 위한 벡터
	int beforelevel = -1; // 이전의 레벨을 저장할 변수

	while (!stack.empty()) {
		start = stack.top().first; // 스택의 제일 top 원소를 빼냄
		level = stack.top().second;
		v.push_back({ start,level });

		stack.pop();
		visited[start] = true; // 해당 장소를 방문했다고 표시

		if (level == snum - 1) { // 모든 레벨을 다 이동한 경우
			cout << "String Found!! : ";
			string ans = "";
			ans += s[v[0].first]; // 첫 단어 전체 추가
			for (int i = 1; i < v.size(); i++) { // 나머지 단어 순서대로 끝글자만 추가
				ans += s[v[i].first][slen - 1];
			}
			cout << ans << endl;
		}
		// DFS로 탐색 중에 이전 위치에서 더이상 갈 수 없어서 바로 부모 위치에서 현재 위치로 왔을 경우
		if (beforelevel == level) { // 이전과 현재의 레벨이 같다.
			visited[v[v.size() - 2].first] = false; // 이전 노드를 미방문 처리하고 
			v.erase(v.end()-2, v.end() - 1); // 방문 이력에서 삭제
		}
		// 탐색중에 바로 이전에 더이상 갈 수 없는 위치에 도달해서 현재 전혀 다른 노드를 조사중일 때
		if (beforelevel > level) {
			int deleteindex = 0; // 방문 이력에서 삭제해야 하는 첫 인덱스
			for (int i = 0; i < v.size(); i++) {
				if (v[i].second >= level) { // 방문 이력에서 현재보다 레벨이 같거나 큰 경우는 모두 미방문처리
					if (v[i].second == level && v[i].first != start)
						deleteindex = i;
					visited[v[i].first] = false;
				}
			}
			v.erase(v.begin() + deleteindex, v.end() - 1); // 위에서 미방문 처리한 만큼 모두 방문 이력에서 삭제
		}

		beforelevel = level;
		level++;
		for (int i = 0; i < snum; i++) { // 현재 노드에서 미방문했고 또 연결점이 있는 노드를 스택에 추가
			if (graph[start][i] && !visited[i]) {
				stack.push({ i, level });
			}
		}
	}
}
void Hamiltonian(vector<string>s) {
	// vertex 개수에 맞춰서 그래프와 배열 동적 할당
	int snum = s.size();
	int slen = s[0].size(); // 한 조각의 길이
	graph = new bool*[snum];
	for (int i = 0; i < snum; i++)
		graph[i] = new bool[snum];
	MakeGraph(s, snum, slen); // 그래프 생성

	visited = new bool [snum]; // 방문 여부 저장할 배열
	for (int i = 0; i < snum; i++) {
		for (int j = 0; j < snum; j++)
			visited[j] = false;
		DFS(s, i, snum, slen); // 각 vertex에 대해서 조사
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
	for (int i = 0; i <= stringlen - slen; i++) { // 순서대로 slen개의 조각으로 끊어서
		tmp = "";
		for (int j = i; j < i + slen; j++) {
			tmp += s[j];
		}
		res.push_back(tmp); // res 벡터에 삽입
	}
	int resSize = res.size();

	bool* tmpTable; // 중복을 검사할 테이블
	tmpTable = new bool[resSize];
	for (int i = 0; i < resSize; i++)
		tmpTable[i] = false;
	srand((unsigned int)time(NULL));
	int cnt;
	int mod = cnt = resSize;
	while (cnt > 0) {
		int index = rand() % mod;
		if (!tmpTable[index]) { // 사용한 숫자가 아니면
			tmpTable[index] = true; // 사용된 숫자 표시
			res2.push_back(res[index]); // res2에 랜덤한 순서로 집어 넣음
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
	s = MakeSpectrum(mstring, slen); // string 입력받고 스펙트럼 만듬
	cout << "My Spectrum : ";
	for (int i = 0; i < s.size(); i++)
		cout << s[i] << " ";
	cout << endl;
	Hamiltonian(s); // hamiltonian 알고리즘 수행
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