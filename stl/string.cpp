#include <string>
#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

char rot13(char c) {
	if((c >= 'a' && c <='m') || (c >= 'A' && c <= 'M'))
		return c + 13;
	if((c > 'm' && c <='z') || (c > 'M' && c <= 'Z'))
		return c - 13;
}

int main() {
	string s("abcdefghijklmnopqrstuvwxyz");
	string s2 = s;

	transform(s.begin(), s.end(), s2.begin(), rot13);

	cout << s + '\n' << s2 << endl;

	printf("%02X%02X%02X\n", 255, 0, 128);
	return 0;
}
