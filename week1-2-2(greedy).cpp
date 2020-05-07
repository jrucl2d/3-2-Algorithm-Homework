#include<iostream> //2015112083 유성근
#include <vector>
using namespace std;

int main() {
	int m; // 돈의 총 합계
	int d; // coin의 개수
	vector<int>c; // coin의 종류
	vector<int>k; // 정답을 출력할 벡터
	int tmp; // 다용도 임시 변수

	cout << "돈의 총 합계 입력 :";
	cin >> m;
	cout << "동전의 개수 입력 :";
	cin >> d;
	cout << "동전의 종류 입력 :";
	
	for (int i = 0; i < d; i++) {
		cin >> tmp; // 임시변수를 이용해서 동전 종류 입력 받음
		c.push_back(tmp); // 입력받은 동전의 종류를 저장
	}

	for (int i = 0; i < d; i++) {
		tmp = m / c[i]; // 전체 돈을 현재 동전으로 나눈다. 그 몫이 해당 동전을 최대로 몇 개 쓸 수 있는지(k값)
		m -= tmp * c[i]; // 해당 동전을 최대로 쓴 만큼의 값을 전체 돈에서 빼준다.
		k.push_back(tmp);
	}
	
	cout << "결과 : ";
	for (int i = 0; i < k.size(); i++)
		cout << k[i] << " ";
}