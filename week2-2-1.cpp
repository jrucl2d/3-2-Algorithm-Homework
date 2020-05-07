#include <iostream> // 2015112083 유성근
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// 비순환방식 사용
int func(vector<int>v, int size) {
	int res = 1; // 결과 저장할 변수
	int minNum = 9999; // v에 저장된 수 중 가장 작은 수 저장
	int count = 0;

	for (int i = 0; i < size; i++)
		minNum = min(v[i], minNum); // v에 저장된 수 중에서 가장 작은 수 찾음

	for (int i = 2; i <= minNum; i++) { // 벡터 내의 수를 i로 나누어볼 것이다. 
		count = 0;
		for (int j = 0; j < size; j++) { // j로 벡터를 순회하며 모두 i로 나눠본다.
			if (v[j] % i == 0) // 나눌 수 있으면 count 증가
				count++;
		}
		if (count == size) // 벡터내 모든 수가 i로 나눠질 수 있으면 최대공약수를 i로 갱신
			res = i; // i는 minNum까지 계속 증가할 것이므로 최종적으로 최대공약수가 저장된다.
	}
	return res;
}

int main() {
	vector<int>v;

	v.push_back(24);
	v.push_back(16);
	v.push_back(32);
	v.push_back(56);
	for (int i = 0; i < v.size(); i++)
		cout << v[i] << " ";
	cout << "\n최대 공약수는 : " << func(v, v.size());
}
