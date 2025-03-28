#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>	
using namespace std;

class CMyString
{
public:
	CMyString(const char* p = nullptr)
	{
		if (p != nullptr)
		{
			mptr = new char[strlen(p) + 1];
			strcpy(mptr, p);
		}
		else
		{
			mptr = new char[1];
			*mptr = '\0';
		}
		cout << "CMyString()" << *mptr << endl;
	}
	~CMyString()
	{
		delete[] mptr;
		mptr = nullptr;
		cout << "~CMyString()" << endl;
	}

	CMyString(const CMyString& str)
	{
		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);
		cout << "CMyString(const CMyString&)" << endl;
	}

	CMyString(CMyString&& str)
	{
		mptr = str.mptr;
		str.mptr = nullptr;
		cout << "CMyString(CMyString&&)" << endl;
	}

	CMyString& operator=(CMyString& str)
	{
		cout << "CMyString& operator=(String&)" << endl;
		if (this == &str)
			return *this;

		delete[] mptr;

		mptr = new char[strlen(str.mptr) + 1];
		strcpy(mptr, str.mptr);

		return *this;
	}

	CMyString& operator=(CMyString&& str)
	{
		cout << "CMyString& operator=(String&&)" << endl;
		if (this == &str)
			return *this;

		delete[] mptr;

		mptr = str.mptr;
		str.mptr = nullptr;
		
		return *this;
	}
	const char* c_str() const { return mptr; }

private:
	char* mptr;
	friend CMyString operator+(const CMyString& lhs,
		const CMyString& rhs);
	friend ostream& operator<<(ostream& out, const CMyString& str);
};

CMyString GetString(CMyString& str)
{
	const char* pstr = str.c_str();
	CMyString tmpStr(pstr);
	cout << "--------------------" << endl;
	return tmpStr;
}

CMyString operator+(const CMyString& lhs,
	const CMyString& rhs)
{
	cout << "--------------------" << endl;
	// char* ptmp = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
	CMyString tmpStr;
	tmpStr.mptr = new char[strlen(lhs.mptr) + strlen(rhs.mptr) + 1];
	strcpy(tmpStr.mptr, lhs.mptr);
	strcat(tmpStr.mptr, rhs.mptr);
	cout << "--------------------" << endl;
	return tmpStr;//最终拷贝构造
}

ostream& operator<<(ostream& out, const CMyString& str)
{
	out << str.mptr;
	return out;
}

int main()
{
	CMyString str1 = "aaaaaaaaaaaaaaaaa";
	CMyString str2 = "bbbbbbbbbb";
	// CMyString str3;
	// str3 = str1 + str2;
	// CMyString str4;
	// str4 = str2;
	// cout << str3 << endl;
	cout << "--------------------" << endl;
	CMyString  str3 = str1 + str2;  
	cout << "--------------------" << endl;
	cout << str3<< endl;




	return 0;
}
