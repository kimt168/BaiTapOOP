#include<bits/stdc++.h>

using namespace std;

class so
{
	int a;
	int b;
	public:
		void nhap();
		int tong();
};
void so::nhap()
{
	cin >> a >> b;
	
}

int so::tong()
{
	return a + b;
}
int main()
{
	so a;
	a.nhap();
	int kq = a.tong();
	cout << kq;
	
}