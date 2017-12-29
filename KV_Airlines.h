#ifndef KV_AIRLINES_H_INCLUDED
#define KV_AIRLINES_H_INCLUDED

#include"Airline/Classes.h"
#include"Airline/Decor.h"

using namespace std;

void CustomerHelpline()
{
    DWORD ev = 0; GetDefault(); INPUT_RECORD Buf;
    SetConsoleSize(80,30); SetBufferSize(80,30); SetConsoleColor(BGTURQUOISE); ClearScreen(80,30);
    Button IMG(28,28,0,0,WHITE,0,0,BGGRAY,"");
    IMG.Paste("AIRPORT",26,26,2,2,1);
    SetConsoleColor(WHITE|BGDARK_TURQUOISE);
    GOTO(30,0);for(int i=0;i<50;i++)cout<<"-"; int diff = 38;
    GOTO(30,1);cout<<"|"<<Spc((diff/2)-1)<<"KV_AIRLINES"<<Spc(diff/2);cout<<"|";
    GOTO(30,2);for(int i=0;i<50;i++)cout<<"-";
    Button Ret(10,1,50,26,BROWN,BGTURQUOISE,DARK_BLUE,BGTURQUOISE,"RETURN"); Ret.Print();
    vector<SHORT> CA = Ret.Area();
    SetConsoleColor(BGTURQUOISE|RED);
    GOTO(35, 5);cout<<"# Call Centers ";
    GOTO(35, 6);cout<<"  ------------ ";
    SetConsoleColor(BGTURQUOISE|BLUE);
    GOTO(35, 7);cout<<"    INDIA          - 011-2435X85X";
    GOTO(35, 8);cout<<"    SINGAPORE      - 065-85754X7X";
    GOTO(35, 9);cout<<"    CANADA         - 001-74565XX6";
    GOTO(35,10);cout<<"    AUSTRALIA      - 002-84X77X43";
    SetConsoleColor(BGTURQUOISE|RED);
    GOTO(35,12);cout<<"# General Customer Support";
    GOTO(35,13);cout<<"  ------------------------";
    SetConsoleColor(BGTURQUOISE|DARK_GREEN);
    GOTO(35,14);cout<<"    E-Mail         - info@kv_air.com";
    GOTO(35,15);cout<<"    24x7 Help Desk - 1800-23X-93X7";
    SetConsoleColor(BGTURQUOISE|RED);
    GOTO(35,17);cout<<"# Bookings Helpline (India) - ";
    GOTO(35,18);cout<<"  ------------------------";
    SetConsoleColor(BGTURQUOISE|DARK_GRAY);
    GOTO(35,19);cout<<"    E-Mail         - ecommerce@kv_air.com";
    GOTO(35,20);cout<<"    Landline No.   - 011-2342X76X";
    SetConsoleColor(BGTURQUOISE|PURPLE);
    GOTO(40,23);cout<<"Copyright @ 2017 KV Airlines Ltd.";
    GOTO(40,24);cout<<"      All Rights Reserved.";
    GOTO(0,0);
    while(true)
    {
        ReadConsoleInput(in,&Buf,1,&ev);
        switch(Buf.EventType)
        {
        case KEY_EVENT:
            {
                if(Buf.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                    exit(0);
                break;
            }
        case MOUSE_EVENT:
            {
                int x = Buf.Event.MouseEvent.dwMousePosition.X;
                int y = Buf.Event.MouseEvent.dwMousePosition.Y;
                switch(Buf.Event.MouseEvent.dwButtonState)
                {
                case FROM_LEFT_1ST_BUTTON_PRESSED:
                    {
                        if((x>=CA[0]&&x<=CA[2])&&(y>=CA[1]&&y<=CA[3]))
                        {
                            system("cls");
                            return;
                        }
                        break;
                    }
                }
                break;
            }
        }
    }
}
void TimeTable()
{
    DWORD ev=0;
    INPUT_RECORD Buf;
    ClearScreen(80,30);
    up:
    SetConsoleSize(80,30);
    SetBufferSize(80,30);
    SetConsoleColor(TURQUOISE);
    ClearScreen(80,30);
    SplHead(cout,"TIME-TABLE MENU",80);
    SetConsoleColor(WHITE);
    Head(cout,"Which Time Table is to be Displayed ?",80);
    Button BD(37,21,0,6,WHITE,0,YELLOW,BGDARK_GRAY,"DOMESTIC TIME-TABLE");
    Button BI(37,21,41,6,WHITE,0,YELLOW,BGDARK_GRAY,"INTERNATIONAL TIME-TABLE");
    Button Back(20,1,18,35,PINK,BGDARK_BLUE,WHITE,BGDARK_BLUE,"RETURN");
    Button Ok(20,1,60,35,GREEN,BGDARK_BLUE,WHITE,BGDARK_BLUE,"Main Menu");
    vector<SHORT> CA1 = BD.Area();
    vector<SHORT> CA2 = BI.Area();
    vector<SHORT> CA3 = Back.Area();
    vector<SHORT> CA4 = Ok.Area();
    BD.Print("DOM",-1);
    BI.Print("INTL");
    SetCursorAt(0,0);
    bool inDom = false;
    bool inIntl = false;
    Sleep(1000);
    while(true)
    {
        ReadConsoleInput(in,&Buf,1,&ev);
        switch(Buf.EventType)
        {
        case KEY_EVENT:
            {
                if(Buf.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                    exit(0);
                break;
            }
        case MOUSE_EVENT:
            {
                int x = Buf.Event.MouseEvent.dwMousePosition.X;
                int y = Buf.Event.MouseEvent.dwMousePosition.Y;
                switch(Buf.Event.MouseEvent.dwButtonState)
                {
                case FROM_LEFT_1ST_BUTTON_PRESSED:
                    {
                        if(((x>=CA1[0]&&x<=CA1[2])&&(y>=CA1[1]&&y<=CA1[3]))&&(inDom!=true)&&(inIntl!=true))
                        {
                            system("cls");
                            SetConsoleSize(100,40,289);
                            SetConsoleColor(BGDARK_BLUE|TURQUOISE);
                            ClearScreen(100,40);
                            SetBufferSize(100,40);
                            SplHead(cout,"TIME - TABLE",100);
                            SetCursorAt(0,4);
                            SetConsoleColor(BGDARK_BLUE|YELLOW);
                            Location Table = {"DEPARTURE"," ARRIVAL","F. NO."," ORIGIN"    ,"DESTINATION"   ,"DURATION","FLIGHT NAME"};
                            Table.TrPrint();
                            SetConsoleColor(BGDARK_BLUE|WHITE);
                            cout<<ULB;
                            for(int i=0;i<8;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<11;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<14;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<14;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<16;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<16;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<13;i++) cout<<HT;
                            cout<<URB;
                            for(int i=0;i<12;i++)
                                DOM[i].Print();
                            POINT newp;
                            GetConsoleScreenBufferInfo(out,&csbi);
                            SetCursorAt(0,csbi.dwCursorPosition.Y-1);
                            SetConsoleColor(BGDARK_BLUE|WHITE);
                            cout<<DLB;
                            for(int i=0;i<8;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<11;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<14;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<14;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<16;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<16;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<13;i++) cout<<HT;
                            cout<<DRB;
                            inDom = true;
                            Back.Print();
                            Ok.Print();
                            DWORD fm = ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT;
                            SetConsoleMode(in,fm);
                        }
                        else if((x>=CA2[0]&&x<=CA2[2])&&(y>=CA2[1]&&y<=CA2[3])&&(inIntl!=true)&&(inDom!=true))
                        {
                            system("cls");
                            SetConsoleSize(100,40,289);
                            SetConsoleColor(BGDARK_BLUE|TURQUOISE);
                            ClearScreen(100,40);
                            SplHead(cout,"TIME - TABLE",100);
                            SetCursorAt(0,4);
                            SetConsoleColor(BGDARK_BLUE|YELLOW);
                            Location Table = {"DEPARTURE"," ARRIVAL","F. NO."," ORIGIN"    ,"DESTINATION"   ,"DURATION","FLIGHT NAME"};
                            Table.TrPrint();
                            SetConsoleColor(BGDARK_BLUE|WHITE);
                            cout<<ULB;
                            for(int i=0;i<8;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<11;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<14;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<14;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<16;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<16;i++) cout<<HT;
                            cout<<DC;
                            for(int i=0;i<13;i++) cout<<HT;
                            cout<<URB;
                            for(int i=0;i<12;i++)
                                INTL[i].Print();
                            POINT newp;
                            GetConsoleScreenBufferInfo(out,&csbi);
                            SetCursorAt(0,csbi.dwCursorPosition.Y-1);
                            SetConsoleColor(BGDARK_BLUE|WHITE);
                            cout<<DLB;
                            for(int i=0;i<8;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<11;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<14;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<14;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<16;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<16;i++) cout<<HT;
                            cout<<UC;
                            for(int i=0;i<13;i++) cout<<HT;
                            cout<<DRB;
                            inIntl = true;
                            Back.Print();
                            Ok.Print();
                            DWORD fm = ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT;
                            SetConsoleMode(in,fm);
                        }
                        else if((x>=CA3[0]&&x<=CA3[2])&&(y==CA3[1])&&(inDom==true))
                        {
                            system("cls");
                            goto up;
                        }
                        else if((x>=CA4[0]&&x<=CA4[2])&&(y==CA4[1])&&(inDom==true))
                        {
                            system("cls");
                            return;
                        }
                        else if((x>=CA3[0]&&x<=CA3[2])&&(y==CA3[1])&&(inIntl==true))
                        {
                            system("cls");
                            goto up;
                        }
                        else if((x>=CA4[0]&&x<=CA4[2])&&(y==CA4[1])&&(inIntl==true))
                        {
                            system("cls");
                            return;
                        }
                    }
                }
            }
        }
    }
}
void FeedBack()
{
    GetDefault(); SetCursor(false); DWORD ev = 0; INPUT_RECORD Buf;
    int ctr=0,startx=5,finish=75,starty=9,finisy=42,myx=(startx+34);
    int posx = startx,posy = starty,ox=startx,oy=starty,tx=startx,ty=starty;
    string file_data="", name="";
    SetConsoleSize(80,50); ClearScreen(80,50); SetBufferSize(80,50);
    SetConsoleColor(BGDARK_TURQUOISE|WHITE); SplHead(cout," - FEEDBACK SERVICE - ",80);
    SetConsoleColor(GREEN|BGDARK_GREEN);     Boundary(startx,starty,finish,finisy);
    SetConsoleColor(BGWHITE);                ClearWriteArea(startx,starty,finish,finisy);
    Button SUB(10,1,39,45,RED,0,WHITE,0,"SUBMIT");
    Button CLS(10,1,52,45,BLUE,0,WHITE,0,"CLEAR");
    Button RET(10,1,65,45,GREEN,0,WHITE,0,"BACK");
    RET.Print(); CLS.Print(); SUB.Print();
    vector<SHORT> CA1 = SUB.Area();
    vector<SHORT> CA2 = CLS.Area();
    vector<SHORT> CA3 = RET.Area();
    bool writer = false; SetConsoleColor(PINK);
    rename:
    GOTO(startx,5);cout<<"Enter Your Name / PNR of Flight - ";GOTO(startx+34,5);SetCursor(true);
    while(true)
    {
        ReadConsoleInput(in,&Buf,1,&ev);
        switch(Buf.EventType)
        {
        case KEY_EVENT:
            {
                char ch = Buf.Event.KeyEvent.uChar.AsciiChar;
                if(Buf.Event.KeyEvent.wVirtualKeyCode==VK_ESCAPE)
                {
                    return;
                }
                if(writer == true)
                {
                    SetConsoleColor(WHITE);
                    GOTO(6,45);cout<<((2310-ctr)<1000?" ":"")<<((2310-ctr)<100?" ":"")\
                               <<((2310-ctr)<10?" ":"")<<2310-ctr<<" Characters Remaining..."<<endl;
                    SetConsoleColor(BGWHITE);
                }
                if(ctr<(finish-startx)*(finisy-starty) && writer == true)
                {
                    char ch = Buf.Event.KeyEvent.uChar.AsciiChar;
                    if((Buf.Event.KeyEvent.wVirtualKeyCode==VK_RETURN)&&(Buf.Event.KeyEvent.bKeyDown)&&writer==true)
                    {
                        tx = posx;
                        ty = posy;
                        ox = posx;
                        oy = posy;
                        file_data+='\n';
                        ctr+=(finish-startx)-(posx-startx);
                        SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<" ";SetConsoleColor(BGWHITE);
                        posx=startx;
                        posy++;
                        SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<"_";SetConsoleColor(BGWHITE);
                        SetCursorAt(posx,posy);
                    }
                    else if(((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch>='0'&&ch<='9')||(ch=='.'||ch=='!'\
                        ||ch=='?'||ch==','||ch=='"'||ch=='\''||ch==' '||ch==':'))&&(Buf.Event.KeyEvent.bKeyDown))
                    {
                        if(posx<finish-1)
                        {
                            ox = posx;
                            oy = posy;
                            SetCursorAt(posx,posy);cout<<ch;
                            posx++;
                            file_data+=ch;
                            ctr++;
                            SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<"_";SetConsoleColor(BGWHITE);
                            SetCursorAt(posx,posy);
                        }
                        else if(posx==finish-1)
                        {
                            ox = posx;
                            oy = posy;
                            SetCursorAt(posx,posy);cout<<ch;
                            posx++;
                            file_data+=ch;
                            ctr++;
                            SetCursorAt(startx,posy+1);SetConsoleColor(GRAY|BGWHITE);cout<<"_";SetConsoleColor(BGWHITE);
                            SetCursorAt(posx,posy);
                        }
                        else
                        {
                            ox = posx;
                            oy = posy;
                            tx = posx;
                            ty = posy;
                            SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<" ";SetConsoleColor(BGWHITE);
                            posx=startx;
                            ctr++;
                            posy++;
                            file_data+='\n';
                            SetCursorAt(posx,posy);cout<<ch;
                            file_data+=ch;
                            posx++;
                            SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<"_";SetConsoleColor(BGWHITE);
                            SetCursorAt(posx,posy);
                        }
                    }
                }
                if((Buf.Event.KeyEvent.wVirtualKeyCode==VK_BACK)&&(Buf.Event.KeyEvent.bKeyDown)&&writer==true)
                {
                    if(posx==startx&&posy==starty)
                    {
                        ox = posx;
                        oy = posy;
                        SetCursorAt(startx,starty);cout<<" ";
                        file_data="";
                        SetCursorAt(startx,starty);
                        ctr=0;
                        SetCursorAt(startx,starty);SetConsoleColor(GRAY|BGWHITE);cout<<"_";SetConsoleColor(BGWHITE);
                        SetCursorAt(startx+1,starty);SetConsoleColor(GRAY|BGWHITE);cout<<" ";SetConsoleColor(BGWHITE);
                    }
                    else if(posx==startx+1&&posy==starty)
                    {
                        ox = posx;
                        oy = posy;
                        file_data="";
                        SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<" ";SetConsoleColor(BGWHITE);
                        posx--;
                        SetCursorAt(posx,posy);cout<<" ";
                        SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<"_";SetConsoleColor(BGWHITE);
                        SetCursorAt(posx,posy);
                        ctr=0;
                    }
                    else if(posx==startx&&posy>starty&&(file_data.at(file_data.length()-1)=='\n'))
                    {
                        ox=posx;
                        oy=posy;
                        file_data.resize(file_data.length()-1);
                        SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<" ";SetConsoleColor(BGWHITE);
                        posy--;
                        posx=FindTX(file_data,startx);
                        ctr-=(finish-startx)-(posx-startx);
                        SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<"_";SetConsoleColor(BGWHITE);
                        GOTO(posx,posy);
                    }
                    else if(posx>startx)
                    {
                        ox = posx;
                        oy = posy;
                        SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<" ";SetConsoleColor(BGWHITE);
                        posx--;
                        ctr--;
                        SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<"_";SetConsoleColor(BGWHITE);
                        SetCursorAt(posx,posy);
                        file_data.resize(file_data.length()-1);
                    }
                    else
                    {
                        ox = posx;
                        oy = posy;
                        SetCursorAt(posx,posy);cout<<' ';
                        SetCursorAt(posx,posy);SetConsoleColor(GRAY|BGWHITE);cout<<"_";SetConsoleColor(BGWHITE);
                        posx=finish;
                        posy--;
                        ctr--;
                        SetCursorAt(posx,posy);
                        file_data.resize(file_data.length()-1);
                    }
                }
                if(((ch>='A'&&ch<='Z')||(ch>='a'&&ch<='z')||(ch>='0'&&ch<='9'))&&(Buf.Event.KeyEvent.bKeyDown)&&writer==false)
                {
                    name+=ch;
                    GOTO(myx,5); cout<<ch;
                    myx++;
                }
                else if((Buf.Event.KeyEvent.wVirtualKeyCode==VK_RETURN||Buf.Event.KeyEvent.wVirtualKeyCode==VK_SPACE)&&(Buf.Event.KeyEvent.bKeyDown)&&writer==false)
                {
                    if(ValidPNR(name)&&writer==false)
                    {
                        GOTO(59,5); SetConsoleColor(GREEN); cout<<"  VALID";
                        writer = true;
                        SetConsoleColor(BGWHITE);
                        posx = startx;
                        posy = starty;
                    }
                    else
                    {
                        writer = false;
                        GOTO(59,5); SetConsoleColor(RED); cout<<"INVALID";
                        GOTO(startx,5); for(int i=0;i<5;i++)cout<<"          ";
                        SetConsoleColor(PINK);
                        myx = startx+34;
                        name = "";
                        goto rename;
                    }
                }
                break;
            }
        case MOUSE_EVENT:
            {
                int x = Buf.Event.MouseEvent.dwMousePosition.X;
                int y = Buf.Event.MouseEvent.dwMousePosition.Y;
                if(writer == true && Buf.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    if((x>=CA1[0]&&x<=CA1[2])&&(y>=CA1[1]&&y<=CA1[3]))
                    {
                        int msg = MessageBox(NULL,"You are Submitting your Feedback.\nAre you Sure?","Confirmation",MB_YESNO);
                        if(msg==IDYES)
                        {
                            fstream file;
                            file.open("Airline\\Feedbacks\\F "+name+" "+DisplayTime()+".txt",ios::out);
                            file<<file_data;
                            file.close();
                            return ;
                        }
                    }
                    if((x>=CA2[0]&&x<=CA2[2])&&(y>=CA2[1]&&y<=CA2[3]))
                    {
                        SetConsoleColor(BGWHITE);
                        ClearWriteArea(startx,starty,finish,finisy);
                        ctr = 0;
                        file_data="";
                        posx=startx;
                        posy=starty;
                        SetConsoleColor(WHITE);
                        GOTO(6,45);cout<<((2310-ctr)<1000?" ":"")<<((2310-ctr)<100?" ":"")\
                                       <<((2310-ctr)<10?" ":"")<<2310-ctr<<" Characters Remaining..."<<endl;
                        SetConsoleColor(BGWHITE);
                    }
                }
                if(((x>=CA3[0]&&x<=CA3[2])&&(y>=CA3[1]&&y<=CA3[3]))&&\
                   Buf.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED)
                {
                    return;
                }
                break;
            }
        }
    }
}
void Admin()
{
    SetConsoleColor(WHITE); GetDefault(); system("cls");
    SetConsoleSize(50,10,450); SetBufferSize(50,10);
    GOTO(1,4); cout<<"Enter The Password - "; cin.clear();
    string pass = getpass();
    if(pass=="h1a2p3p4y5")
    {
        SetConsoleColor(WHITE); system("cls"); SetConsoleSize(100,56,289); SetBufferSize(100,10000);
        SetConsoleColor(BGDARK_TURQUOISE|WHITE); SplHead(cout,"STAFF MANIFEST SERVICE",100);
        SetConsoleColor(WHITE);
        GOTO(0,5); cout<<" Welcome to the KV Airlines Manifest Monitor. The Following Commands are Available : ";
        GOTO(0,6); cout<<" >> SELECT ORIGIN DESTINATION CABIN DATE TIMED TIMEA JTYPE TYPE";
        GOTO(0,7); cout<<" >> EXIT "; SetConsoleColor(GRAY); cout<<endl; int i = 0;
        while(true)
        {
            cout<<endl<<">> "; string o,d,cbn,date,td,ta,jt,type,cmd; Date dd;
            SetConsoleMode(in,ConsoleMode); getline(cin,cmd); cmd = ToCaps(cmd); if(ToCaps(cmd) == "EXIT") return;
            else if(ToCaps(cmd).substr(0,6)=="SELECT") ParseFormat(cmd,o,d,cbn,date,td,ta,jt,type);
            else {cout<<"\nInvalid Command\n"; continue;} dd.Assign(date);
            //cout<<o<<"-"<<d<<"-"<<cbn<<"-"<<dd<<"-"<<td<<"-"<<ta<<"-"<<jt<<"-"<<type<<endl;
            fstream file; file.open("Airline\\Passenger Data\\Airline Data.dat",ios::in|ios::binary);
            Head(cout,"|   RLOC   |           PASSENGER NAME         |   TYPE   |  SEAT  |     TICKET NO.     |   CABIN   |",100);
            while(not file.eof())
            {
                Passenger tmp; tmp.Read(file);
                if(tmp.cmp(o,d,cbn,dd,td,ta,jt,type))
                    tmp.Disp(dd);
            }
            file.close();
        }
    }
    return;
}

class AppState
{
public:
    AppState(string openmode)
    {
        atexit(GoodBye);
        GetConsoleMode(in,&ConsoleMode);
        this->Init();
    }
    void Run()
    {
        this->InitMenu();
    }
    ~AppState()
    {
        exit(0);
    }
private:
    void Init()
    {
        SetCursor(false); SetConsoleTitleW(L"Welcome to KV Airlines !"); GetDefault();
        SetConsoleColor(WHITE); SetConsoleSize(80,30); SetBufferSize(80,30);
        cout.flush(); Banner(); cout.flush(); SetConsoleColor(WHITE);
        cout<<"\n\t\t        *** PRESS ENTER TO CONTINUE ***                 \n\t\t\t\t\t";
        SetCursorAt(0,59); SetCursorAt(0,0); SetCursorAt(40,28); char key=getch();
        if(key=='\n'||key=='\r') system("cls"); else this->Destroy();
    }
    void Destroy()
    {
        exit(0);
    }
    void InitMenu()
    {
        _main:
        Sleep(200); SetCursor(false); system("cls"); SetConsoleSize(80,24); SetBufferSize(80,24); SetConsoleColor(YELLOW);
        ClearScreen(80,30); SplHead(cout,"Welcome to KV Airlines !!",80); SetConsoleColor(TURQUOISE);
        SplHead(std::cout,"Menu Loaded At - "+DisplayFullTime(),80);
        SetConsoleColor(GRAY); SetCursorAt(2,8); cout<<"Where Would You like to Proceed ? - ";
        SetCursorAt(2,9); cout<<"( Click on an Option | Press ESC to Exit )";
        SetConsoleColor(WHITE); SetCursorAt(0,11);
        cout<<"           1)   Book A Ticket                                    ... "<<endl;
        cout<<"           ----------------------------------------------------------"<<endl;
        cout<<"         2)   Manage Existing Bookings                         ... "<<endl;
        cout<<"         ----------------------------------------------------------"<<endl;
        cout<<"       3)   View Time-Table of Flights                       ... "<<endl;
        cout<<"       ----------------------------------------------------------"<<endl;
        cout<<"         4)   Leave Feedback                                   ... "<<endl;
        cout<<"         ----------------------------------------------------------"<<endl;
        cout<<"           5)   View Customer Helpline Details                   ... "<<endl;
        cout<<"           ----------------------------------------------------------"<<endl;
        cout<<"             6)   Exit                                             ... "<<endl;
        DWORD ev=0; INPUT_RECORD Buf;
        start:
        while(true)
        {
            ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE),&Buf,1,&ev);
            switch(Buf.EventType)
            {
            case KEY_EVENT:
                {
                    if(Buf.Event.KeyEvent.wVirtualKeyCode==VK_ESCAPE)
                        exit(0);
                    if(Buf.Event.KeyEvent.uChar.AsciiChar == '0')
                    {
                        system("cls");
                        Admin();
                        goto _main;
                    }
                    break;
                }
            case MOUSE_EVENT:
                {
                    if(Buf.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
                    {
                        COORD Final = Buf.Event.MouseEvent.dwMousePosition;
                        if(Final.Y == 11 && (Final.X>10&&Final.X<67))
                        {
                            SetConsoleColor(WHITE);
                            SetCursorAt(0,11);
                            cout<<"           1)   Book A Ticket                                    ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"         2)   Manage Existing Bookings                         ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"       3)   View Time-Table of Flights                       ... "<<endl;
                            cout<<"       ----------------------------------------------------------"<<endl;
                            cout<<"         4)   Leave Feedback                                   ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"           5)   View Customer Helpline Details                   ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"             6)   Exit                                             ... "<<endl;
                            SetCursorAt(11,11);
                            SetConsoleColor(BGWHITE|BLACK);
                            cout<<"1)   Book A Ticket                                    ... ";
                            SetConsoleColor(WHITE);
                        }
                        else if(Final.Y == 13 && (Final.X>8&&Final.X<65))
                        {
                            SetConsoleColor(WHITE);
                            SetCursorAt(0,11);
                            cout<<"           1)   Book A Ticket                                    ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"         2)   Manage Existing Bookings                         ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"       3)   View Time-Table of Flights                       ... "<<endl;
                            cout<<"       ----------------------------------------------------------"<<endl;
                            cout<<"         4)   Leave Feedback                                   ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"           5)   View Customer Helpline Details                   ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"             6)   Exit                                             ... "<<endl;
                            SetCursorAt(9,13);
                            SetConsoleColor(BGWHITE|BLACK);
                            cout<<"2)   Manage Existing Bookings                         ... ";
                            SetConsoleColor(WHITE);
                        }
                        else if(Final.Y == 15 && (Final.X>6&&Final.X<63))
                        {
                            SetConsoleColor(WHITE);
                            SetCursorAt(0,11);
                            cout<<"           1)   Book A Ticket                                    ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"         2)   Manage Existing Bookings                         ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"       3)   View Time-Table of Flights                       ... "<<endl;
                            cout<<"       ----------------------------------------------------------"<<endl;
                            cout<<"         4)   Leave Feedback                                   ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"           5)   View Customer Helpline Details                   ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"             6)   Exit                                             ... "<<endl;
                            SetCursorAt(7,15);
                            SetConsoleColor(BGWHITE|BLACK);
                            cout<<"3)   View Time-Table of Flights                       ... ";
                            SetConsoleColor(WHITE);
                        }
                        else if(Final.Y == 17 && (Final.X>8&&Final.X<65))
                        {
                            SetConsoleColor(WHITE);
                            SetCursorAt(0,11);
                            cout<<"           1)   Book A Ticket                                    ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"         2)   Manage Existing Bookings                         ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"       3)   View Time-Table of Flights                       ... "<<endl;
                            cout<<"       ----------------------------------------------------------"<<endl;
                            cout<<"         4)   Leave Feedback                                   ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"           5)   View Customer Helpline Details                   ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"             6)   Exit                                             ... "<<endl;
                            SetCursorAt(9,17);
                            SetConsoleColor(BGWHITE|BLACK);
                            cout<<"4)   Leave Feedback                                   ... ";
                            SetConsoleColor(WHITE);
                        }
                        else if(Final.Y == 19 && (Final.X>10&&Final.X<67))
                        {
                            SetConsoleColor(WHITE);
                            SetCursorAt(0,11);
                            cout<<"           1)   Book A Ticket                                    ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"         2)   Manage Existing Bookings                         ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"       3)   View Time-Table of Flights                       ... "<<endl;
                            cout<<"       ----------------------------------------------------------"<<endl;
                            cout<<"         4)   Leave Feedback                                   ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"           5)   View Customer Helpline Details                   ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"             6)   Exit                                             ... "<<endl;
                            SetCursorAt(11,19);
                            SetConsoleColor(BGWHITE|BLACK);
                            cout<<"5)   View Customer Helpline Details                   ... ";
                            SetConsoleColor(WHITE);
                        }
                        else if(Final.Y == 21 && (Final.X>12&&Final.X<69))
                        {
                            SetConsoleColor(WHITE);
                            SetCursorAt(0,11);
                            cout<<"           1)   Book A Ticket                                    ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"         2)   Manage Existing Bookings                         ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"       3)   View Time-Table of Flights                       ... "<<endl;
                            cout<<"       ----------------------------------------------------------"<<endl;
                            cout<<"         4)   Leave Feedback                                   ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"           5)   View Customer Helpline Details                   ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"             6)   Exit                                             ... "<<endl;
                            SetCursorAt(13,21);
                            SetConsoleColor(BGWHITE|BLACK);
                            cout<<"6)   Exit                                             ... ";
                            SetConsoleColor(WHITE);
                        }
                        else
                        {
                            SetConsoleColor(WHITE);
                            SetCursorAt(0,11);
                            cout<<"           1)   Book A Ticket                                    ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"         2)   Manage Existing Bookings                         ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"       3)   View Time-Table of Flights                       ... "<<endl;
                            cout<<"       ----------------------------------------------------------"<<endl;
                            cout<<"         4)   Leave Feedback                                   ... "<<endl;
                            cout<<"         ----------------------------------------------------------"<<endl;
                            cout<<"           5)   View Customer Helpline Details                   ... "<<endl;
                            cout<<"           ----------------------------------------------------------"<<endl;
                            cout<<"             6)   Exit                                             ... "<<endl;
                        }
                    }
                    switch(Buf.Event.MouseEvent.dwButtonState)
                    {
                    case FROM_LEFT_1ST_BUTTON_PRESSED:
                        {
                            COORD Final = Buf.Event.MouseEvent.dwMousePosition;
                            if(Final.Y == 11 && (Final.X>10&&Final.X<67))
                            {
                                system("cls");
                                Book(netp);
                                goto _main;
                            }
                            if(Final.Y == 13 && (Final.X>8&&Final.X<65))
                            {
                                system("cls");
                                Manage();
                                goto _main;
                            }
                            if(Final.Y == 15 && (Final.X>6&&Final.X<63))
                            {
                                TimeTable();
                                system("cls");
                                goto _main;
                            }
                            if(Final.Y == 17 && (Final.X>8&&Final.X<65))
                            {
                                system("cls");
                                FeedBack();
                                goto _main;
                            }
                            if(Final.Y == 19 && (Final.X>10&&Final.X<67))
                            {
                                system("cls");
                                CustomerHelpline();
                                goto _main;
                            }
                            if(Final.Y == 21 && (Final.X>12&&Final.X<69))
                            {
                                exit(0);
                            }
                            break;
                        }
                    }
                    break;
                }
            }
        }
    }
};

#endif // KV_AIRLINES_H_INCLUDED
