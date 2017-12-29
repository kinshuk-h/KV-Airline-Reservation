#include"KV_Airlines.h"
void Man()
{
    GetDefault(); GetConsoleMode(in,&ConsoleMode); system("cls");
    SetConsoleSize(50,10,450); SetBufferSize(50,10);
    GOTO(1,4); cout<<"Enter The Password - ";
    string pass = getpass();
    if(pass=="h1a2p3p4y5")
    {
        system("cls"); SetConsoleSize(100,56,289); SetBufferSize(100,10000);
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
/** Airline Data Rewriter - PNR Input.

    fstream f1,f2; string PNR; getline(cin,PNR);
    f1.open("Airline\\Passenger Data\\"+PNR+".dat",ios::in|ios::binary);
    f2.open("Airline\\Passenger Data\\Airline Data.dat",ios::out|ios::binary|ios::app);
    while(not f1.eof()&&f1.is_open())
    {
        Passenger t;
        t.Read(f1);
        if(t.Type!="") t.Write(f2);
    }
    f1.close();
    f2.close();
    cout<<"Done!"<<endl;

*/
int main()
{
    Man();
}
