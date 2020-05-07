#include<iostream> //2015112083 유성근
#include<vector>
using namespace std;

void DP(int m, int d, int* c, int* k) {

	for (int i = 0; i < d; i++) 
		k[i] = 0; // 결과값 넣을 배열 초기화
	
	int dp[200]; // 해당 index의 돈을 만드는 데 드는 최소의 동전 개수가 저장됨
	int changedCoins[200]; // 바뀐 동전을 저장

	for (int i = 1; i <= m; i++) // dp에는 최소값이 저장되어야 하므로 적당히 높은 수로 모두 초기화해준다.
		dp[i] = 10000;
	dp[0] = 0; // 0원을 만드는 경우는 동전을 사용하지 않는 경우이므로 0으로 초기화해준다.

	// O(Md)의 시간 복잡도로 구하기. 
	for (int i = 0; i < d; i++) // 현재 동전 종류를 인덱스로 접근
	{
		// j의 값은 내가 현재 가진 동전들을 이용해서 만들고 싶은 돈의 총액이다.
		// 현재 동전의 값(c[i])보다 작은 돈은 현재의 동전을 가지고 아무것도 할 수 없으므로 생략한다.
		// 따라서 j(내가 만들고 싶은 돈)는 c[i]부터 시작한다.
		for (int j = c[i]; j <= m; j++)
		{
			// 원래 j의 돈을 만드는 데 드는 최소 동전 개수와 'j - i동전(c[i])의 값'을 만들 때 드는
			// 최소 동전 개수(dp[j-c[i]])에 c[i]동전 하나를 추가(+1)했을 때의 개수를 비교했을 때
			// 후자가 더 개수가 적다면 dp 값을 갱신해준다. 
			// 이 때 dp를 이용해 구할 때는 다음 dp의 값이 이전 dp의 값에 영향을 받기 때문에 새로 사용한
			// 동전이 있을 때는 해당 돈을 만들 때 변화된 사용 동전을 changedCoins 배열에 저장해준다.
			if (dp[j] > dp[j - c[i]] + 1)
			{
				dp[j] = dp[j - c[i]] + 1;
				changedCoins[j] = c[i];
			} // 반복을 모두 돌고 나면 dp[m]에는 m 동전을 만드는 데 드는 최소 동전 개수가 저장된다.
		}
	}
	cout << "m의 값이 " << m << "일 때의 결과(1,4,7) : ";
	cout << "총 " << dp[m] << "개 동전 사용, ";
	// 출력
	while (m > 0) {
		for (int i = 0; i < d; i++) {
			if (c[i] == changedCoins[m]) // m원을 만드는데 해당 동전이 사용되었으면 해당 인덱스의 결과값을 증가시킨다.
				k[i]++;
		}
		m -= changedCoins[m]; // m은 그 동전을 사용하기 전의 값으로 만들어서 그 전의 값에는 어떤 동전을 사용했는지 또 파악한다.
	}

	for (int i = 0; i < d; i++)
		cout << k[i] << " ";
	cout << endl;
}

int main()
{
	int m; // 돈의 총 합계
	int d; // coin의 개수
	int* c; // coin의 종류
	int* k; // 각 coin의 개수(출력할 답)

	cout << "돈의 총 합계 입력 :";
	cin >> m;
	cout << "동전의 개수 입력 :";
	cin >> d;
	cout << "동전의 종류 입력 :";

	c = new int[d]; // 동전의 종류와 개수를 저장할 배열을 동전 개수 만큼 동적 할당
	k = new int[d];
	for (int i = 0; i < d; i++) {
		cin >> c[i];  // 입력받은 동전의 종류를 저장
	}
	for(int i = 1; i <= 11; i++) // m의 값을 1~11까지 넣으며 결과 출력
		DP(i, d, c, k);
}