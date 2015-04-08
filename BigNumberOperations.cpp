#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <cstring>

using namespace std;
const int MAX_LENGTH = 200;

class BigInteger {
	private:
		int number[MAX_LENGTH];
		bool positive;
		int length;
	public:
		BigInteger();
		BigInteger(int);
		BigInteger(string);
		static int compare(BigInteger, BigInteger);
		BigInteger operator+(BigInteger);
		BigInteger operator-(BigInteger);
		BigInteger operator*(BigInteger);
		BigInteger operator/(BigInteger);
		friend ostream& operator<<(ostream&, BigInteger&);
};

BigInteger::BigInteger() {
	memset(number, 0, 100);
	positive = true;
	length = 0;
}

BigInteger::BigInteger(int a) {
	char cstr[12];
	sprintf(cstr, "%d", a);
	string str = cstr;
	memset(number, 0, MAX_LENGTH);
	positive = true;
	int index = 0;
	for (int i=str.length()-1; i>=0; --i) {
		if (str[i]=='(' || str[i]==')' || str[i]=='+')
			continue;
		if (str[i] == '-') {
			positive = false;
			continue;
		}
		number[index++] = str[i] - '0';
	}
	length = index;
	int i;
	for (i=length-1; i>=0; --i) {
		if (number[i]) {
			length = i + 1;
			break;
		}
	}
	if (i == -1)
		length = 0;
}

BigInteger::BigInteger(string a) {
	memset(number, 0, MAX_LENGTH);
	positive = true;
	int index = 0;
	for (int i=a.length()-1; i>=0; --i) {
		if (a[i]=='(' || a[i]==')' || a[i]=='+')
			continue;
		if (a[i] == '-') {
			positive = false;
			continue;
		}
		number[index++] = a[i] - '0';
	}
	length = index;
	int i;
	for (i=length-1; i>=0; --i) {
		if (number[i]) {
			length = i + 1;
			break;
		}
	}
	if (i == -1)
		length = 0;
}

int BigInteger::compare(BigInteger a, BigInteger b) {
	int len = (a.length > b.length) ? a.length : b.length;
	for (int i=len-1; i>=0; --i) {
		if (a.number[i] > b.number[i])
			return 1;
		else if (a.number[i] < b.number[i])
			return -1;
	}
	return 0;
}

BigInteger BigInteger::operator+(BigInteger a) {
	BigInteger c;
	if (positive == a.positive) {
		int len = (a.length > length) ? a.length : length;
		for (int i=0; i<len; ++i) {
			c.number[i] += number[i] + a.number[i];
			if (c.number[i] > 9) {
				c.number[i] -= 10;
				c.number[i+1]++;
			}
		}
		c.length = (c.number[len] == 0) ? len : len+1;
		if (!positive)
			c.positive = false;
	}
	else if (positive && !a.positive) {
		a.positive = true;
		c = *this - a;
	}
	else {
		BigInteger b = *this;
		b.positive = true;
		c = a - b;
	}
	return c;
}

BigInteger BigInteger::operator-(BigInteger a) {
	BigInteger c;
	if (positive && a.positive) {
		int result = BigInteger::compare(*this, a);
		if (result == 1) {
			for (int i=0; i<length; ++i) {
				c.number[i] += number[i] - a.number[i];
				if (c.number[i] < 0) {
					c.number[i] += 10;
					c.number[i+1]--;
				}
			}
			for (int i=length-1; i>=0; --i) {
				if (c.number[i]) {
					c.length = i + 1;
					break;
				}
			}
		}
		else if (result == -1) {
			BigInteger b = *this;
			c = a - b;
			c.positive = false;
		}
	}
	else if (positive && !a.positive) {
		a.positive = true;
		c = *this + a;
	}
	else if (!positive && a.positive) {
		BigInteger b = *this;
		b.positive = true;
		c = a + b;
		c.positive = false;
	}
	else {
		a.positive = true;
		BigInteger b = *this;
		b.positive = true;
		c = a - b;
	}
	return c;
}

BigInteger BigInteger::operator*(BigInteger a) {
	BigInteger c;
	if (length==0 || a.length==0)
		return c;
	c.length = length + a.length;
	for (int i=0; i<length; ++i)
		for (int j=0; j<a.length; ++j)
			c.number[i+j] += number[i] * a.number[j];
	for (int i=0; i<c.length; i++) {
		c.number[i+1] += c.number[i] / 10;
		c.number[i] %= 10;
	}
	if (c.length!=0 && c.number[c.length]!=0)
		c.length++;
	else if (c.length!=0 && c.number[c.length-1]==0)
		c.length--;
	if (positive != a.positive)
		c.positive = false;
	return c;
}

BigInteger BigInteger::operator/(BigInteger a) {
	BigInteger c;
	if (a.length==0 || BigInteger::compare(*this, a)<=0)
		return c;
	BigInteger dividend = *this;
	dividend.positive = true;
	int diff = dividend.length - a.length;
	c.length = diff + 1;
	while (diff >= 0) {
		BigInteger divisor = a;
		divisor.positive = true;
		for (int i=divisor.length-1; i>=0; --i)
			divisor.number[i+diff] = divisor.number[i];
		for (int i=diff-1; i>=0; --i)
			divisor.number[i] = 0;
		divisor.length += diff;
		int i;
		BigInteger multiple;
		for (i=0; i<=10; ++i) {
			BigInteger bigI = i;
			multiple = divisor * bigI;
			if (BigInteger::compare(multiple, dividend) == 1) {
				i--;
				bigI = i;
				multiple = divisor * bigI;
				break;
			}
		}
		dividend = dividend - multiple;
		c.number[diff] = i;
		diff--;
	}
	c.length = (c.number[c.length-1] == 0) ? c.length-1 : c.length;
	if (positive != a.positive)
		c.positive = false;
	return c;
}

ostream& operator<<(ostream& os, BigInteger& a) {
	if (a.length == 0) {
		os << "0";
		return os;
	}
	if (!a.positive)
		os << "-";
	for (int i=a.length-1; i>=0; --i)
		os << a.number[i];
	return os;
}

int main() {
	fstream input;
	string filename;
	cout << "Please input the filename: ";
	cin >> filename;
	input.open(filename.c_str(), ios::in);
	if (input.is_open()) {
		while (!input.eof()) {
			string strA, strB;
			char oper;
			input >> strA >> oper >> strB;
			BigInteger a = strA;
			BigInteger b = strB;
			BigInteger c;
			switch (oper) {
				case '+':
					c = a + b;
					cout << a << " " << oper << " " << b << " = " << c << endl;
					break;
				case '-':
					c = a - b;
					cout << a << " " << oper << " " << b << " = " << c << endl;
					break;
				case '*':
					c = a * b;
					cout << a << " " << oper << " " << b << " = " << c << endl;
					break;
				case '/':
					c = a / b;
					cout << a << " " << oper << " " << b << " = " << c << endl;
					break;
				default:
					cout << "Invalid input." << endl;
					break;
			}
		}
	}
	else {
		cout << "Invalid filename." << endl;
	}
	input.close();
	return 0;
}
