#include <iostream> // 2015112083 유성근
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 순환방식 사용
// 매우 유명한 gcd 알고리즘을 사용.
// a와 b의 최대 공약수는 큰 값 a와 작은 값 b가 있을 때 a를 b로 나눈 나머지를 r이라고 하면
// a와 b의 최대 공약수가 b와 r의 최대공약수와 같다는 점을 이용해서 구할 수 있다.
int gcd(int a, int b) {
	if (b == 0) // 이전의 a%b가 0이면 현재의 a는 최대공약수이다.
		return a;
	else return gcd(b, a % b); // b와 r(a%b)의 최대공약수가 같다는 점을 이용
}

// 배열을 내림차순으로 정렬하기 위해 버블 정렬 사용
void sort(vector<int>v, int size) {
	bool sorted = false; // 시간 단축을 위한 flag
	for (int i = size - 1; i > 0; i--) {
		while (!sorted) { // 이전 반복에서 바뀐 것이 없으면 sorted가 true이므로 정렬 완료라서 알고리즘 중단
			sorted = true;
			for (int j = 0; j < i; j++) { // i이전의 모든 인덱스 j에 대해서
				if (v[j] < v[j + 1]) { // 작은 수가 왼쪽에 있으면 교환(내림차순)
					int tmp = v[j];
					v[j] = v[j + 1];
					v[j + 1] = tmp;
					sorted = false; // 교환이 있었다면 sorted가 false
				}
			}
		}
	}
}

int main() {
	vector<int>v;

	v.push_back(24);
	v.push_back(16);
	v.push_back(32);
	v.push_back(56);

	// gcd(a,b,c)가 gcd(gcd(a,b),c)라는 특성 이용할 것인데, 큰 수가 제일 왼 쪽에 와야 하므로 내림차순 정렬을 진행해 주어야 한다.
	sort(v, v.size());

	int res = gcd(v[0], v[1]); // 처음 두 수를 이용해 구한 최대 공약수를 res에 저장
	for (int i = 2; i < v.size(); i++) {
		res = gcd(res, v[i]); // 이후부터 gcd(gcd(a,b),c)의 방식으로 res에 gcd 값을 갱신
	}
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << "\n최대 공약수는 : " << res;
}