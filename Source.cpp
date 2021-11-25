#include <iostream>
using namespace std;

class InhaString {
private:
	char* m_msg;
	int m_len;
public:
	InhaString();
	InhaString(const char*);
	InhaString(const InhaString&);
	~InhaString();
	InhaString& operator=(const InhaString&);
	InhaString& operator+=(const InhaString&);
	friend InhaString operator+(const InhaString&, const InhaString&);
	friend bool operator==(const InhaString&, const InhaString&);
	friend std::ostream& operator<<(std::ostream&, const InhaString&);
	friend std::istream& operator>>(std::istream&, InhaString&);
	int getLen() {
		return m_len;
	}
};

InhaString::InhaString() : m_msg{ nullptr }, m_len{0} {}

InhaString::InhaString(const char* msg){
	m_len = strlen(msg) + 1;
	m_msg = new char[m_len];
	strcpy_s(m_msg, m_len, msg);
}

InhaString::InhaString(const InhaString& str) {
	m_len = str.m_len;
	m_msg = new char[str.m_len];
	strcpy_s(m_msg, m_len, str.m_msg);
}

InhaString::~InhaString() {
	delete[] m_msg;
}

InhaString& InhaString::operator=(const InhaString& str){
	if (this == &str)
		return *this;
	
	if (m_msg)
		delete[] m_msg;
	m_len = str.m_len;
	m_msg = new char[str.m_len];
	strcpy_s(m_msg, str.m_len, str.m_msg);
	return *this;
}

InhaString& InhaString::operator+=(const InhaString& str) {
	InhaString data;
	m_len = m_len + str.m_len - 1;
	data.m_msg = new char[m_len];
	strcpy_s(data.m_msg, m_len, m_msg);
	strcat_s(data.m_msg, m_len, str.m_msg);
	delete[] m_msg;
	m_msg = new char[m_len];
	strcpy_s(m_msg, m_len, data.m_msg);
	return *this;
}

InhaString operator+(const InhaString& str1, const InhaString& str2) {
	InhaString str{str1.m_msg};
	str.m_len = str1.m_len + str2.m_len - 1;
	str.m_msg = new char[str.m_len];
	strcpy_s(str.m_msg, str.m_len, str1.m_msg);
	strcat_s(str.m_msg, str.m_len, str2.m_msg);
	return str;
}

bool operator==(const InhaString& str1, const InhaString& str2) {
	return strcmp(str1.m_msg, str2.m_msg);
}

std::ostream& operator<<(std::ostream& out, const InhaString& str) {
	cout << str.m_msg;
	return out;
}

std::istream& operator>>(std::istream& in, InhaString& str) {
	char* data = new char[100];
	in >> data;
	str = InhaString{ data };
	delete[] data;
	return in;
}

int main() {
	InhaString str1 = "I like ";
	InhaString str2 = "string class";
	InhaString str3 = str1 + str2;
	
	cout << str1 << endl;
	cout << str2 << endl;
	cout << str3 << endl;

	InhaString st{ str3 };
	str1 += str2;
	if (str1 == str3)
		cout << "The two strings are identical." << endl;
	else
		cout << "The two strings are different." << endl;

	

	InhaString str4;
	cout << "Enter a string: ";
	cin >> str4;
	cout << "You entered: " << str4 << endl;

	return 0;
}