#include <iostream> // 2015112083 유성근
#include <vector>
#include <string>
using namespace std;

vector<pair<int, string>> FillTheRest(string t) {
	vector<pair<int,string>> res; // index와 해당 번째 string을 pair로 넣어줌
	int endIndex = t.size() - 1;
	string tmp = "";
	for (int i = endIndex; i >= 0; i--) { // $부터 첫 글자까지를 첫 글자로 해서
		tmp = "";
		for (int j = i; j <= endIndex; j++)  // 해당 첫 글자부터 끝까지 문자열에 추가하고
			tmp += t[j];
		for (int j = 0; j < i; j++) // 처음부터 해당 첫 글자 전까지 문자열에 추가
			tmp += t[j];
		res.push_back({ i, tmp }); // 완성된 문자열을 index와 함께 벡터에 넣어줌
	}
	return res;
}

void Sort(vector<pair<int, string>> &t) {
	bool sorted = false; // 시간 단축을 위한 flag
	int size = t.size();
	int stringSize = t.size() - 1; // $를 제외한 벡터의 수가 문자열 길이
	for (int i = size - 1; i > 2; i--) {
		while (!sorted) { // 이전 반복에서 바뀐 것이 없으면 sorted가 true가 되고 알고리즘 중단
			sorted = true;
			for (int j = 1; j < i; j++) { // i 이전 모든 인덱스 j에 대해서, 첫 문자열은 무조건 $이므로 생략
				bool change = false;
				for (int k = 0; k < stringSize; k++) { // 문자열 비교
					if (t[j].second[k] > t[j + 1].second[k]) { // 이전이 더 크면 change를 true로
						change = true;
						break;
					}
					else if (t[j].second[k] == t[j + 1].second[k]) // 같으면 다음 문자 비교
						continue;
					else { // 순서에 맞으면 교환이 필요 없으므로 change를 false로
						change = false;
						break;
					}
				}
				if (change) { // 이전 것이 더 크면(change가 true이면) 교환
					pair<int, string> tmp = t[j];
					t[j] = t[j + 1];
					t[j + 1] = tmp;
					sorted = false;
				}
			}
		}
	}
}

string Restore(vector<pair<int, string>>& t) {
	int stringSize;
	int back = stringSize = t.size() - 1; // 문자열 길이는 벡터 개수에서 $를 하나 뺀 것과 같음
	int front = 0;
	string res = "";
	
	for (int i = stringSize; i > 0; i--) { // 마지막 $을 제외하고 끝부터 인덱스에 해당하는 문자를 추가
		for (int j = 0; j <= stringSize; j++) {
			if (t[j].first == i) { // 해당 인덱스의 끝에 있는 문자를 추가
				res += t[j].second[back];
				break;
			}
		}	
	}
	string res2 = "";
	for (int i = stringSize - 1; i >= 0; i--)
		res2 += res[i]; // res의 내용을 거꾸로 res2에 넣음
	return res2;
}
int main() {
	string T = "missisippi";
	string T$ = T + "$";
	vector<pair<int, string>>ftr;
	ftr = FillTheRest(T$);
	cout << "[Fill the rest]" << endl;
	for (int i = 0; i < ftr.size(); i++) // Fill the rest 결과를 출력
		cout << ftr[i].first << " " << ftr[i].second << endl;
	Sort(ftr);
	cout << endl;
	cout << "[Sort result]" << endl;
	for (int i = 0; i < ftr.size(); i++) // Sort 결과를 출력
		cout << ftr[i].first << " " << ftr[i].second << endl;

	// 복원 과정
	string res = "";
	res = Restore(ftr);
	cout << endl;
	cout << "[Resotred string]" << endl;
	cout << res << endl;
}