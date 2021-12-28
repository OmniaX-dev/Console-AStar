#ifndef __UTILITIES__H__
#define __UTILITIES__H__

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef WIN32
#include <Windows.h>
#endif

#ifndef NULL
#define NULL 0
#endif

using namespace std;

template<class ITEM_TYPE>
static ITEM_TYPE** alloc_2d_array(int x, int y)
{
	ITEM_TYPE **arr = new ITEM_TYPE*[x];
	for (int i = 0; i < x; i++)
		arr[i] = new ITEM_TYPE[y];
	return arr;
}

template<class ITEM_TYPE>
static void delete_2d_array(ITEM_TYPE **arr, int x)
{
	for (int i = 0; i < x; i++)
		delete arr[i];
	delete[] arr;
}

static string str_to_lower_case(string str)
{
	for (unsigned int i = 0; i < str.length(); i++)
		if (str[i] >= 0x41 && str[i] <= 0x5A)
			str[i] = str[i] + 0x20;
	return str;
}

static bool str_equals(string s1, string s2)
{
	if (s1.length() != s2.length())
		return false;
	for (unsigned int i = 0; i < s1.length(); i++)
		if (s1[i] != s2[i])
			return false;
	return true;
}

static std::string str_trim(std::string str)
{
	int i,j,start,end;
    for (i=0; (str[i]!=0 && str[i]<=32); )
        i++;
    start=i;
    for(i=0,j=0; str[i]!=0; i++)
        j = ((str[i]<=32)? j+1 : 0);
    end=i-j;
    str = str.substr(start,end-start);
    return str;
}

static bool str_starts_with(std::string str, std::string with)
{
	if (with.length() > str.length())
		return false;
	for (unsigned int i = 0; i < with.length(); i++)
		if (str[i] != with[i])
			return false;
	return true;
}

static bool str_ends_with(std::string str, std::string with)
{
	if (with.length() > str.length())
		return false;
	int d = abs((int)(str.length() - with.length()));
	for (int i = str.length() - 1; i >= d; i--)
		if (str[i] != with[i - d])
			return false;
	return true;
}

static bool str_contains(std::string str, std::string what)
{
	return (str.find(what) != std::string::npos);
}

static bool str_is_numeric(std::string s)
{
	unsigned int cont = 0;
	std::string str = str_trim(s);
	for (unsigned int i = 0; i < str.length(); i++)
	{
		char c = str[i];
		if (cont == 0 && c == '-')
		{
			cont++;
			continue;
		}
		if (c < 48 || c > 57)
			return false;
		cont++;
	}
	return true;
}

static std::string str_substr(std::string str, int start, int end)
{
	std::string s = "";
	for (int i = start; i < end; i++)
		s += str[i];
	return s;
}

static int str_to_int(std::string str)
{
	std::string s(str);
	s = str_trim(s);
	if (!str_is_numeric(s))
		return 0;
	bool neg = false;
	if (str_starts_with(s, "-"))
	{
		neg = true;
		s = str_trim(str_substr(s, 1, s.length()));
	}
	unsigned int len = s.length();
	unsigned int start = (unsigned int)pow(10, len - 1);
	int n = 0;
	for (unsigned int i = 0; i < s.length(); i++)
	{
		char c = s[i];
		if (c >= 48 && c <= 57)
		{
			n += (c - 48) * start;
			start /= 10;
		}
	}
	n *= (neg ? -1 : 1);
	return n;
}

static std::string str_reverse(std::string str)
{
	std::string str2 = "";
	for (int i = str.length() - 1; i >= 0; i--)
		str2 += str[i];
	return str2;
}

static std::string int_to_str(int n)
{
	int nn = n;
	if (nn == 0)
		return "0";
	std::string str = "";
	while (nn > 0)
	{
		int tmp = nn % 10;
		str += (char)(tmp + 48);
		nn /= 10;
	}
	return str_reverse(str);
}

static std::string str_replace(const std::string str, const std::string what, const std::string with)
{
	if (!str_contains(str, what))
		return str;
	int i = str.find(what);
	std::string ret = str_substr(str, 0, i);
	ret = ret.append(with);
	ret = ret.append(str_substr(str, i + what.length(), str.length()));
	return ret;
}

static std::string str_replace_all(const std::string str, const std::string what, const std::string with)
{
	std::string ret = str;
	while (str_contains(ret, what))
		ret = str_replace(ret, what, with);
	return ret;
}

static std::string get_file_content(std::string fname)
{
	FILE *f = NULL;
#ifdef _MSC_VER
	fopen_s(&f, fname.c_str(), "r");
#else
	f = fopen(fname.c_str(), "r");
#endif
	std::string str = "";
	if (f != NULL)
	{
		char c = ' ';
		while ((c = fgetc(f)) != EOF)
			str += c;
	}
	fclose(f);
	return str;
}

static int util_distance(float x1, float y1, float x2, float y2)
{
	float xx = x2 - x1;
	float yy = y2 - y1;
	return (int)(sqrt((xx * xx) + (yy * yy)) + .5f);
}
#ifdef WIN32
static void MsgBox(std::string str)
{
	MessageBox(NULL, str.c_str(), "INFO", 0);
}

static void MsgBox(int i)
{
	MsgBox(int_to_str(i));
}

static void MsgBox(bool b)
{
	MessageBox(NULL, b ? "true" : "false", "INFO", 0);
}

static void MsgBox(char c)
{
	MessageBox(NULL, &c, "INFO", 0);
}
#endif
template<class ITEM_TYPE>
static void util_array_copy(ITEM_TYPE *src, ITEM_TYPE *dest, int elements)
{
	for (int i = 0; i < elements; i++)
		dest[i] = src[i];
}

#endif
