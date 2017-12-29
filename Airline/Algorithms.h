#ifndef ALGORITHMS_H_INCLUDED
#define ALGORITHMS_H_INCLUDED

#include<iostream>
#include<string>
#include<cctype>
#include<algorithm>
#include<cstring>
#include<sstream>
#include<fstream>
#include<sstream>
#include<ctime>
#include<regex>

using namespace std;

string ToCaps(string a)
{
    for(char& i : a)
    {
        i = toupper(i);
    }
    return a;
}

string ToTitle(string a)
{
    a[0] = toupper(a[0]);
    for(int i=1;i<a.length();i++)
    {
        if(!isalnum(a[i-1])) a[i] = toupper(a[i]);
        else a[i] = tolower(a[i]);
    }
    return a;
}

template<typename T>
inline void iter(int no,T disp,ostream& os)
{
    for(int i=0;i<no;i++)
        os<<disp;
}

template<typename t>
t Convert(string data)
{
    t res;
    stringstream ss(data);
    ss>>res;
    return res;
}

template<typename t>
string Revert(t var)
{
    stringstream ss;
    ss<<var;
    return ss.str();
}

int FindTX(string s,int startx)
{
    int tx=startx;
    for(int i=s.length()-1;i>=0;i--)
    {
        if(s[i]!='\n') tx++;
        else break;
    }
    return tx;
}

string Spc(int no)
{
    string res;
    for(int i=0;i<no;i++) res+=" ";
    return res;
}

bool ValidPNR(string name)
{
    for(int i=0;i<name.length();i++)
    {
        if(!(isalnum(name[i])))
            return false;
    }
    return true;
}

bool Contact(string no)
{
    for(int i=0;i<no.length();i++)
    {
        if(isdigit(no[i])||no[i]=='+'||no[i]==' '||no[i]=='-')
            continue;
        else return false;
    }
    return true;
}

string Revert(float var, int prec)
{
    stringstream ss;
    ss.setf(ios::fixed);
    ss.precision(prec);
    ss<<var;
    return ss.str();
}

string GenPNR()
{
    srand(time(nullptr));
    string res = "";
    string ALPHA = "ABCDEFGHIJKLMOPQRSTUVWXYZ";
    string NUM = "1234567890";
    string ALNUM = "ABCDEFGHIJKLMOPQRSTUVWXYZ1234567890";
    res += ALPHA[rand()%26];
    res += NUM[rand()%10];
    for(int i=0;i<3;i++) res+=ALNUM[rand()%36];
    res += ALPHA[rand()%26];
    if(ValidPNR(res)) return res;
    else return GenPNR();
}

int len(int no)
{
    int ctr=0;
    while(no!=0)
    {
        ctr++;
        no/=10;
    }
    return ctr;
}

bool EMail(string email)
{
   const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
   return regex_match(email, pattern);
}

int Row(string s)
{
    string sub="";
    for(int i=0;i<s.length();i++)
    {
        if(isdigit(s[i])) sub+=s[i];
        else break;
    }
    return Convert<int>(sub);
}

int Col(string s)
{
    char cs = '\0';
    for(int i=s.length()-1;i>=0;i--)
    {
        if(isalpha(s[i])) cs = s[i];
        else break;
    }
    return static_cast<int>(cs-64);
}

void ParseFormat(string cmd,string& o,string& d,string& cbn,string& date,string& td,string& ta,string& jt,string& type)
{
    vector<string> str(9); int k=0;
    for(int i=0;i<cmd.length();i++)
    {
        if(cmd[i]==' '){k++;}
        else {str[k] += cmd[i];}
    }
    if(k<8)
    {
        for(int j=k+1;j<=8;j++)
        {
            str[j]="*";
        }
    }
    o = str[1]; d = str[2]; cbn = str[3]; date = str[4]; td = str[5]; ta = str[6]; jt = str[7]; type = str[8];
}

#endif // KV_AIRLINES_ALGORITHMS_H_INCLUDED
