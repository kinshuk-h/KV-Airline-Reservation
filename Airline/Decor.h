#ifndef DECOR_H_INCLUDED
#define DECOR_H_INCLUDED

#include<iomanip>
#include<iostream>
#include<vector>
#include"Data.h"

using namespace std;

/// Banners and Headings

void GetDefault()
{
    GetConsoleScreenBufferInfo(out,&csbi);
    GetConsoleCursorInfo(out,&cursorInfo);
    ::ORIGINAL=csbi.wAttributes;
    ::CONSOLE=GetConsoleWindow();
    GetWindowRect(CONSOLE, &R);
    R.left=0;
    R.top=0;
    CONSOLECOORD.X=0;
    CONSOLECOORD.Y=0;
}
void SetConsoleOriginalColor()
{
    SetConsoleTextAttribute(out,ORIGINAL);
}
void SetConsoleColor(WORD COLOR)
{
    SetConsoleTextAttribute(out,COLOR);
}
void SetBufferSize(int w,int h)
{
    COORD buf = {(SHORT)w,(SHORT)h};
    SetConsoleScreenBufferSize(out,buf);
}
void SetConsoleOriginalSize()
{
    R.left=350;
    R.right=R.left+80;
    R.top=0;
    R.bottom=R.top+25;
    MoveWindow(CONSOLE,R.left,R.top,80,25,FALSE);
    COORD BufferCoord = {SHORT(80),SHORT(50)};
    SetConsoleScreenBufferSize(out,BufferCoord);
    SMALL_RECT SIZE = {0,0,79,24};
    SetConsoleWindowInfo(out,TRUE,&SIZE);
}
void SetConsoleSize(int w, int h, int rl=350,bool var = true)
{
    if(var)
    {
        DWORD fm = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
        SetConsoleMode(in,fm);
    }
    R.left=rl;
    R.right=R.left+w;
    R.top=0;
    R.bottom=R.top+h;
    MoveWindow(CONSOLE,R.left,R.top,w,h,FALSE);
    COORD BufferCoord = {SHORT(w),SHORT(h)};
    SetConsoleScreenBufferSize(out,BufferCoord);
    SMALL_RECT SIZE = {0,0,SHORT(w-1),SHORT(h-1)};
    SetConsoleWindowInfo(out,TRUE,&SIZE);
}
void Head(ostream& obj,string name,int mx_width,char sym1='-',char sym2='|')
{
    for(int i=1;i<=mx_width;i++)
        obj<<sym1;
    if(name.length()<mx_width)
    {
        obj<<sym2;
        for(int i=1;i<=(mx_width-2-name.length())/2;i++) obj<<" ";
        if(name.length()%2==0)
            obj<<name;
        else
            obj<<name<<" ";
        for(int i=1;i<=(mx_width-2-name.length())/2;i++) obj<<" ";
        obj<<sym2;
    }
    else
    {
        obj<<name;
    }
    for(int i=1;i<=mx_width;i++)
        obj<<sym1;
}
void SplHead(ostream& obj,string name,int mx_width)
{
    obj<<char(201); for(int i=0;i<mx_width-2;i++) obj<<char(205); obj<<char(187);
    if(name.length()<mx_width-2)
    {
        obj<<char(186);
        for(int i=1;i<=(mx_width-2-name.length())/2;i++) obj<<" ";
        if(name.length()%2==0)
            obj<<name;
        else
            obj<<name<<" ";
        for(int i=1;i<=(mx_width-2-name.length())/2;i++) obj<<" ";
        obj<<char(186);
    }
    else if(name.length()==mx_width-2)
    {
        obj<<char(186)<<name<<char(186);
    }
    else
    {
        obj<<name;
    }
    obj<<char(200); for(int i=0;i<mx_width-2;i++) obj<<char(205); obj<<char(188);
}
void SetCursorAt(int X,int Y)
{
    CONSOLECOORD.X=X;
    CONSOLECOORD.Y=Y;
    SetConsoleCursorPosition(out,CONSOLECOORD);
}
void GOTO(int x,int y)
{
    SetCursorAt(x,y);
}
string GetEXEAddress()
{
    HMODULE hModule = GetModuleHandleA(NULL);
    TCHAR path[MAX_PATH];
    GetModuleFileNameA(hModule, path, MAX_PATH);
    string a;
    a.assign(path);
    int init = a.length()-4;
    a.resize(init);
    for(int i=init;i>=0;i--)
    {
        if(a[i]=='\\') break;
        else a.resize(i);
    }
    return a;
}
string GetEXEDrive()
{
    HMODULE hModule = GetModuleHandleA(NULL);
    TCHAR path[MAX_PATH];
    GetModuleFileNameA(hModule, path, MAX_PATH);
    string a;
    a.assign(path);
    a.resize(2);
    return a;
}
void ClearFormBox(int X,int Y,int Size)
{
    SetCursorAt(X,Y);
    for(int i=0;i<Size;i++) cout<<" ";
    SetCursorAt(X,Y);
}
void GenFormBox(int X,int Y,int Size)
{
    SetCursorAt(X,Y-1); cout<<char(201); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(187);
    SetCursorAt(X,Y);   cout<<char(186); for(int i=0;i<Size;i++) cout<<" ";       cout<<char(186);
    SetCursorAt(X,Y+1); cout<<char(200); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(188);
}
void GenFormBoxSC(int X,int Y,int Size)
{
    SetCursorAt(X,Y-1); cout<<char(201); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(187);
    SetCursorAt(X,Y);   cout<<char(186); for(int i=0;i<Size;i++) cout<<" ";       cout<<char(186);
    SetCursorAt(X,Y+1); cout<<char(0xCC); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(0xB9);
}
void GenFormBoxBC(int X,int Y,int Size)
{
    SetCursorAt(X,Y-1); cout<<char(0xCC); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(0xB9);
    SetCursorAt(X,Y);   cout<<char(186); for(int i=0;i<Size;i++) cout<<" ";       cout<<char(186);
    SetCursorAt(X,Y+1); cout<<char(0xCC); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(0xB9);
}
void GenFormBoxEC(int X,int Y,int Size)
{
    SetCursorAt(X,Y-1); cout<<char(0xCC); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(0xB9);
    SetCursorAt(X,Y);   cout<<char(186); for(int i=0;i<Size;i++) cout<<" ";       cout<<char(186);
    SetCursorAt(X,Y+1); cout<<char(200); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(188);
}
void GenFormBoxSR(int X,int Y,int Size)
{
    SetCursorAt(X,Y-1); cout<<char(201); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(0xCB);
    SetCursorAt(X,Y);   cout<<char(186); for(int i=0;i<Size;i++) cout<<" ";       cout<<char(186);
    SetCursorAt(X,Y+1); cout<<char(200); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(0xCA);
}
void GenFormBoxBR(int X,int Y,int Size)
{
    SetCursorAt(X,Y-1); cout<<char(0xCB); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(0xCB);
    SetCursorAt(X,Y);   cout<<char(186); for(int i=0;i<Size;i++) cout<<" ";       cout<<char(186);
    SetCursorAt(X,Y+1); cout<<char(0xCA); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(0xCA);
}
void GenFormBoxER(int X,int Y,int Size)
{
    SetCursorAt(X,Y-1); cout<<char(0xCB); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(187);
    SetCursorAt(X,Y);   cout<<char(186); for(int i=0;i<Size;i++) cout<<" ";       cout<<char(186);
    SetCursorAt(X,Y+1); cout<<char(0xCA); for(int i=0;i<Size;i++) cout<<char(205); cout<<char(188);
}
void ClearScreen(int w,int h)
{
    for(int i=0;i<w*h;i++)
        cout<<" ";
    SetCursorAt(0,0);
}

void Banner()
{
    unsigned char aaa=223,bbb=220,ccc=219,ddd=178,eee=30,fff=238;
    SetConsoleColor(BGWHITE|DARK_BLUE);
    for(int i=1;i<=80;i++)cout<<ddd;
    for(int i=1;i<=80;i++)cout<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    for(int i=0;i<14;i++)cout<<" ";cout<<" "<<" "<<" "<<ccc<<" "<<" "<<" ";for(int i=0;i<12;i++)cout<<" ";cout<<" "<<" "<<" ";for(int j=0;j<44;j++)cout<<" ";
    for(int i=0;i<14;i++)cout<<" ";cout<<" "<<" "<<ccc<<ccc<<ccc<<" "<<" ";for(int i=0;i<12;i++)cout<<" ";cout<<" "<<" "<<" ";for(int j=0;j<44;j++)cout<<" ";
    for(int i=0;i<14;i++)cout<<" ";cout<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" ";for(int i=0;i<12;i++)cout<<" ";cout<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    for(int i=0;i<14;i++)cout<<" ";cout<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" ";for(int i=0;i<12;i++)cout<<" ";cout<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    for(int i=0;i<14;i++)cout<<" ";cout<<bbb<<ccc<<ccc<<ccc<<ccc<<ccc<<bbb;for(int i=0;i<12;i++)cout<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<                                                     " "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<bbb<<bbb<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<bbb<<bbb<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<bbb<<bbb<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<bbb<<bbb<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    cout<<" "<<" "<<" "<<bbb<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<bbb<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    cout<<" "<<" "<<ccc<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<ccc<<ccc<<ccc<<ccc<<ccc<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<aaa<<ccc<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    for(int i=0;i<14;i++)cout<<" ";cout<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" ";for(int i=0;i<12;i++)cout<<" ";cout<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    for(int i=0;i<14;i++)cout<<" ";cout<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" ";for(int i=0;i<12;i++)cout<<" ";cout<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    for(int i=0;i<14;i++)cout<<" ";cout<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" ";for(int i=0;i<12;i++)cout<<" ";cout<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|GRAY);
    for(int i=0;i<14;i++)cout<<" ";cout<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" ";for(int i=0;i<12;i++)cout<<" ";cout<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|BROWN);
    cout<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" ";
    for(int i=1;i<=80;i++)cout<<" ";
    SetConsoleColor(BGWHITE|DARK_BLUE);
    for(int i=0;i<11;i++)cout<<" ";
    SetConsoleColor(BGYELLOW|BLUE);
    for(int i=1;i<=58;i++)cout<<" ";
    SetConsoleColor(BGWHITE|DARK_BLUE);
    for(int i=0;i<11;i++)cout<<" ";
    for(int i=0;i<11;i++)cout<<" ";
    SetConsoleColor(BGYELLOW|BLUE);
    cout<<" "<<ccc<<" "<<" "<<ccc<<ccc<<" "<<ccc<<" "<<" "<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<ccc<<" "<<" "<<" "<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" ";
    SetConsoleColor(BGWHITE|DARK_BLUE);
    for(int i=0;i<11;i++)cout<<" ";
    for(int i=0;i<11;i++)cout<<" ";
    SetConsoleColor(BGYELLOW|BLUE);
    cout<<" "<<ccc<<" "<<ccc<<ccc<<" "<<" "<<ccc<<" "<<" "<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<" "<<" "<<ccc<<" "<<ccc<<" "<<ccc<<" "<<" "<<" "<<ccc<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<ccc<<ccc<<" "<<" "<<ccc<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<" "<<" "<<" "<<" ";
    SetConsoleColor(BGWHITE|DARK_BLUE);
    for(int i=0;i<11;i++)cout<<" ";
    for(int i=0;i<11;i++)cout<<" ";
    SetConsoleColor(BGYELLOW|BLUE);
    cout<<" "<<ccc<<ccc<<ccc<<" "<<" "<<" "<<ccc<<ccc<<" "<<ccc<<ccc<<" "<<" "<<ccc<<ccc<<" "<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<ccc<<" "<<ccc<<" "<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" ";
    SetConsoleColor(BGWHITE|DARK_BLUE);
    for(int i=0;i<11;i++)cout<<" ";
    for(int i=0;i<11;i++)cout<<" ";
    SetConsoleColor(BGYELLOW|BLUE);
    cout<<" "<<ccc<<" "<<ccc<<ccc<<" "<<" "<<" "<<ccc<<ccc<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<" "<<" "<<ccc<<" "<<ccc<<" "<<ccc<<" "<<ccc<<ccc<<" "<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<ccc<<" "<<" "<<ccc<<ccc<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<" ";
    SetConsoleColor(BGWHITE|DARK_BLUE);
    for(int i=0;i<11;i++)cout<<" ";
    for(int i=0;i<11;i++)cout<<" ";
    SetConsoleColor(BGYELLOW|BLUE);
    cout<<" "<<ccc<<" "<<" "<<ccc<<ccc<<" "<<" "<<" "<<ccc<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<" "<<ccc<<" "<<" "<<" "<<ccc<<" "<<ccc<<" "<<ccc<<" "<<" "<<ccc<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<ccc<<" "<<ccc<<" "<<" "<<" "<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" "<<ccc<<ccc<<ccc<<ccc<<ccc<<" ";
    SetConsoleColor(BGWHITE|DARK_BLUE);
    for(int i=0;i<11;i++)cout<<" ";
    for(int i=0;i<11;i++)cout<<" ";
    SetConsoleColor(BGYELLOW|BLUE);
    for(int i=1;i<=58;i++)cout<<" ";
    SetConsoleColor(BGWHITE|DARK_BLUE);
    for(int i=0;i<11;i++)cout<<" ";
    for(int i=1;i<=80;i++)cout<<" ";
    for(int i=1;i<=80;i++)cout<<ddd;
    SetConsoleOriginalColor();
}

template<typename fx>
void InfoBox(string data,string title,fx f)
{
    UINT buttons = MB_OK;
    int res = MessageBox(NULL,data.c_str(),title.c_str(),MB_ICONINFORMATION|buttons);
    switch(res)
    {
    case IDOK:
        {
            f();
        }
    default:
        {
            break;
            return;
        }
    }
}
template<typename fx>
void QuestionBox(string data,string title,fx f1, fx f2)
{
    UINT buttons = MB_YESNO;
    int res = MessageBox(NULL,data.c_str(),title.c_str(),MB_ICONQUESTION|buttons);
    switch(res)
    {
    case IDYES:
        {
            f1();
            break;
        }
    case IDNO:
        {
            f2();
            break;
        }
    default:
        {
            break;
            return;
        }
    }
}

class Button
{
private:
    WORD FCol,BCol,FCCol,BCCol;
    COORD Pos,Size;
    string Text;
public:
    Button(int w=1,int h=1,int x=0,int y=0,WORD fCol=0,WORD bCol=0,WORD fcc=0,WORD bcc=0,string data=""):
        Text(data),FCol(fCol),BCol(bCol),FCCol(fcc),BCCol(bcc)
    {
        Pos.X = x;
        Pos.Y = y;
        Size.X = w;
        if((data.length()+2)>Size.X) Size.X = data.length()+2;
        Size.Y = h;
    }
    void Print()
    {
        if(Text.length()%2!=0) Text+=" ";
        int ws = Text.length();
        SetConsoleColor(FCol|BCol);

        SetCursorAt(Pos.X,Pos.Y);
        cout<<ULB;
        for(int i=0;i<Size.X;i++) cout<<HT;
        cout<<URB<<endl;

        if(Size.Y%2==0) Size.Y++;
        int diff = Size.X - ws;
        string data,d2;
        for(int i=0;i<(diff/2);i++) data+=" ";
        for(int i=0;i<ws;i++) d2+=" ";
        if(Size.X%2!=0)
        {
            d2 = " "+d2;
            Text = " "+Text;
        }
        Text = data+Text+data;
        d2+=(data+data);

        int i=1;
        for(i;i<=((Size.Y-1)/2);i++)
        {
            SetCursorAt(Pos.X,Pos.Y+i);
            SetConsoleColor(FCol|BCol);
            cout<<VT;
            SetConsoleColor(FCCol|BCCol);
            cout<<d2;
            SetConsoleColor(FCol|BCol);
            cout<<VT;
        }
        SetCursorAt(Pos.X,Pos.Y+i);
        SetConsoleColor(FCol|BCol);
        cout<<VT;
        SetConsoleColor(FCCol|BCCol);
        cout<<Text;
        SetConsoleColor(FCol|BCol);
        cout<<VT;
        for(int j = i+1;j<=Size.Y;j++)
        {
            SetCursorAt(Pos.X,Pos.Y+j);
            SetConsoleColor(FCol|BCol);
            cout<<VT;
            SetConsoleColor(FCCol|BCCol);
            cout<<d2;
            SetConsoleColor(FCol|BCol);
            cout<<VT;
        }
        SetCursorAt(Pos.X,Pos.Y+Size.Y+1);
        cout<<DLB;
        for(int i=0;i<Size.X;i++) cout<<HT;
        cout<<DRB;
    }
    void Print(string icon,int offset = 0)
    {
        CHAR_INFO ico[24*15];
        fstream file;
        file.open(("Images\\"+icon+".afi").c_str(),ios::in|ios::binary);
        for(int i=0;i<15;i++)
        {
            for(int j=0;j<24;j++)
            {
                file.read((char*)&ico[(24*i)+j],sizeof(CHAR_INFO));
            }
        }
        file.close();

        Text+=" ";
        int ws = Text.length();
        SetConsoleColor(FCol|BCol);

        SetCursorAt(Pos.X,Pos.Y);
        cout<<ULB;
        for(int i=0;i<Size.X;i++) cout<<HT;
        cout<<URB<<endl;

        string tm = "";
        if(ws%2==0) tm+=" ";
        if(Size.Y%2==0) Size.Y++;
        int diff = Size.X - ws;
        string data,d2;
        for(int i=0;i<(diff/2);i++) data+=" ";
        for(int i=0;i<ws;i++) d2+=" ";
        Text = data+Text+data+tm;
        d2+=(data+data+tm);

        int i=1;
        for(i;i<=((Size.Y-1)/2);i++)
        {
            SetCursorAt(Pos.X,Pos.Y+i);
            SetConsoleColor(FCol|BCol);
            cout<<VT;
            SetConsoleColor(FCCol|BCCol);
            cout<<d2;
            SetConsoleColor(FCol|BCol);
            cout<<VT;
        }
        SetCursorAt(Pos.X,Pos.Y+i);
        SetConsoleColor(FCol|BCol);
        cout<<VT;
        SetConsoleColor(FCCol|BCCol);
        cout<<d2;
        SetConsoleColor(FCol|BCol);
        cout<<VT;
        for(int j = i+1;j<=Size.Y;j++)
        {
            SetCursorAt(Pos.X,Pos.Y+j);
            SetConsoleColor(FCol|BCol);
            cout<<VT;
            SetConsoleColor(FCCol|BCCol);
            cout<<d2;
            SetConsoleColor(FCol|BCol);
            cout<<VT;
        }
        SetCursorAt(Pos.X,Pos.Y+Size.Y+1);
        cout<<DLB;
        for(int i=0;i<Size.X;i++) cout<<HT;
        cout<<DRB;

        COORD charBufSize = {24,15};
        COORD characterPos = {0,0};
        SMALL_RECT writeArea = {SHORT(Pos.X+data.length()+1+offset),SHORT(Pos.Y+3),SHORT(Pos.X+24+data.length()+offset),SHORT(Pos.Y+17)};
        WriteConsoleOutput(out,ico,charBufSize,characterPos,&writeArea);
        SetCursorAt(Pos.X,Pos.Y+19);
        SetConsoleColor(FCol|BCol);
        cout<<VT;
        SetConsoleColor(FCCol|BCCol);
        cout<<Text;
        SetConsoleColor(FCol|BCol);
        cout<<VT;
    }
    void Paste(string icon,int w,int h,int x,int y,int strpos)
    {
        CHAR_INFO ico[w*h];
        fstream file;
        file.open(("Images\\"+icon+".afi").c_str(),ios::in|ios::binary);
        if(file.is_open())
        {
            for(int i=0;i<h;i++)
            {
                for(int j=0;j<w;j++)
                {
                    file.read((char*)&ico[(w*i)+j],sizeof(CHAR_INFO));
                }
            }
        }
        else
        {
            for(int i=0;i<h;i++)
            {
                for(int j=0;j<w;j++)
                {
                    ico[(w*i)+j].Char.AsciiChar = ' ';
                    ico[(w*i)+j].Attributes = BGWHITE;
                }
            }
        }
        file.close();

        if(Text.length()%2!=0) Text+=" ";
        int ws = Text.length();
        SetConsoleColor(FCol|BCol);

        SetCursorAt(Pos.X,Pos.Y);
        cout<<ULB;
        for(int i=0;i<Size.X;i++) cout<<HT;
        cout<<URB<<endl;

        int diff = Size.X - ws;
        string data,d2;
        for(int i=0;i<(diff/2);i++) data+=" ";
        for(int i=0;i<ws;i++) d2+=" ";
        Text = data+Text+data;
        d2+=(data+data);

        int i=1;
        for(i;i<=Size.Y;i++)
        {
            SetCursorAt(Pos.X,Pos.Y+i);
            SetConsoleColor(FCol|BCol);
            cout<<VT;
            SetConsoleColor(FCCol|BCCol);
            cout<<d2;
            SetConsoleColor(FCol|BCol);
            cout<<VT;
        }

        SetCursorAt(Pos.X,Pos.Y+Size.Y+1);
        cout<<DLB;for(int i=0;i<Size.X;i++) cout<<HT; cout<<DRB;

        SetCursorAt(Pos.X,Pos.Y+strpos);
        SetConsoleColor(FCol|BCol);
        cout<<VT;
        SetConsoleColor(FCCol|BCCol);
        cout<<Text;
        SetConsoleColor(FCol|BCol);
        cout<<VT;

        COORD charBufSize = {SHORT(w),SHORT(h)};
        COORD characterPos = {0,0};
        SMALL_RECT writeArea = {SHORT(Pos.X+x),SHORT(Pos.Y+y),SHORT(Pos.X+x+w),SHORT(Pos.Y+h+y)};
        WriteConsoleOutput(out,ico,charBufSize,characterPos,&writeArea);
    }
    void Click(WORD NF=BLACK, WORD NB=BGWHITE)
    {
        WORD tF = FCCol, tB = BCCol; FCCol = NF; BCCol = NB;
        Print(); BCCol = tB; FCCol = tF;
    }
    void Move(int x, int y)
    {
        Pos.X += x;
        Pos.Y += y;
    }
    void Recolor(WORD Fc,WORD Bc, WORD FCC, WORD BCC)
    {
        BCCol = BCC; FCCol = FCC;
        FCol = Fc; BCol = Bc;
    }
    vector<SHORT> Area()
    {
        vector<SHORT> res(4);
        res[0] = Pos.X+1;
        res[1] = Pos.Y+1;
        res[2] = Pos.X+Size.X;
        res[3] = Pos.Y+Size.Y;
        return res;
    }
    ~Button(){}
    Button& operator=(const Button& b)
    {
        if(this==&b) return *this;
        else
        {
            Text = b.Text.data();
            this->Pos = b.Pos;
            this->Size = b.Size;
            this->FCol = b.FCol;
            this->BCol = b.BCol;
            this->FCCol = b.FCCol;
            this->BCCol = b.BCCol;
            return *this;
        }
    }
};

void ClearWriteArea(int x,int y,int w,int h)
{
    for(int i=y-1;i<=h;i++)
    {
        for(int j=x-1;j<=w;j++)
        {
            GOTO(j,i);
            cout<<" ";
        }
    }
    SetCursorAt(x,y);
}
void Boundary(int x,int y,int w,int h)
{
    SetCursorAt(x-2,y-2);
    cout<<ULB; for(int i=x-1;i<=w;i++) cout<<HT; cout<<URB;
    SetCursorAt(x-2,h+1);
    cout<<DLB; for(int i=x-1;i<=w;i++) cout<<HT; cout<<DRB;
    for(int i=y-1;i<=h;i++) {GOTO(x-2,i);cout<<VT;}
    for(int i=y-1;i<=h;i++) {GOTO(w-x+6,i);cout<<VT;}
}
void SetCursor(bool value)
{
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = value;
    SetConsoleCursorInfo(out, &cursorInfo);
}

struct RTF
{
    static int fctr;
    static int cctr;
    string ct, ft;
    string fins;
    RTF()
    {
        ct = "{\\colortbl }";
        ft = "{\\fonttbl }";
    }
    string Init()
    {
        return "{\\rtf1\\ansi\\margl720\\margr720\\margt720\\margb720";
    }
    int Font(string F="Consolas")
    {
        string res = "{\\f"+Revert(fctr)+" "+F+";}";
        ft.resize(ft.length()-1); ft+=(res+"}");
        fctr++; return fctr-1;
    }
    string Print(string text,int fc,int bc,int f,int size=14,char align='l',int bold=0,int italic=0,int underline=0,bool p=true)
    {
        string res;
        if(p)
        {
            res = "{\\pard"+(string("\\q")+align)+"\\f"+Revert(f)+"\\fs"+Revert(size*2)+"\\chshdng0\\chcbpat"+Revert(bc)+
                    +"\\cb"+Revert(bc)+"\\cf"+Revert(fc)+(bold?string("\\b1"):string("\\b0"))+(italic?string("\\i1"):
                    string("\\i0"))+(underline?string("\\ul1"):string("\\ul0"))+" "+text+"\\par}";
        }
        else
        {
            res = "{"+(string("\\q")+align)+"\\f"+Revert(f)+"\\fs"+Revert(size*2)+"\\chshdng0\\chcbpat"+Revert(bc)+
                    +"\\cb"+Revert(bc)+"\\cf"+Revert(fc)+(bold?string("\\b1"):string("\\b0"))+(italic?string("\\i1"):
                    string("\\i0"))+(underline?string("\\ul1"):string("\\ul0"))+" "+text+"}";
        }
        return res;
    }
    string File(string d)
    {
        fins = Init() + ft + ct + d + Close();
        return fins;
    }
    int Color(int r=0, int g=0, int b=0)
    {
        ct.resize(ct.length()-1);
        string res = "\\red"+Revert(r)+"\\green"+Revert(g)+"\\blue"+Revert(b)+";";
        cctr++; ct+=(res+"}"); return cctr-1;
    }
    string Close()
    {
        return "}";
    }
} Word;
int RTF::fctr = 0;
int RTF::cctr = 0;

#endif // KV_AIRLINES_DECOR_H_INCLUDED
