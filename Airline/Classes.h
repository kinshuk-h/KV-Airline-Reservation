#ifndef KV_AIRLINES_CLASSES_H_INCLUDED
#define KV_AIRLINES_CLASSES_H_INCLUDED

#include"Algorithms.h"
#include"Data.h"
#include"Utility.h"
#include<vector>
#pragma pack(1)

using namespace std;
int totalmoney;

class Coordinate
{
    int X, Y;
public:
    Coordinate():X(0),Y(0){}
    Coordinate(int x, int y):X(x),Y(y){}
    Coordinate(COORD C)
    {
        X = C.X;
        Y = C.Y;
    }
    COORD To_COORD()
    {
        COORD C = {SHORT(X),SHORT(Y)};
        return C;
    }
    Coordinate& operator=(const Coordinate& C)
    {
        if(this==&C) return *this;
        X = C.X; Y = C.Y;
        return *this;
    }
    void Assign(int x, int y)
    {
        X =x; Y=y;
    }
    bool operator==(Coordinate C2)
    {
        return bool(X==C2.X && Y==C2.Y);
    }
    int Absicca()
    {
        return X;
    }
    int Ordinate()
    {
       return Y;
    }
};
struct Date
{
    Date(){D=0;M=0;Y=0;}
    Date(int d,int m,int y):D(d),M(m),Y(y){}
    int D; int M; int Y;
    void Show(){cout<<D<<"/"<<M<<"/"<<Y;}
    void Read(){cin>>D>>M>>Y;}
    string Value()
    {
        return (Revert(D)+"-"+Revert(M)+"-"+Revert(Y));
    }
    Date& operator=(const Date& d)
    {
        if(&d==this)
            return *this;
        else
        {
            this->D = d.D;
            this->M = d.M;
            this->Y = d.Y;
            return *this;
        }
    }
    friend ostream& operator<<(ostream& os, Date D1)
    {
        os<<Revert(D1.D)+"/"+Revert(D1.M)+"/"+Revert(D1.Y);
        return os;
    }
    bool Verify()
    {
        if(Y<0||M<0||D<0) return false;
        if(M>12) return false;

        if(M==2&&D>29) return false;
        else if((M==4||M==6||M==9||M==11)&&(D>30)) return false;
        else if(D>31) return false;

        return true;
    }
    void Assign(string data)
    {
        string d,m,y;
        int i = 0;
        for(i;i<data.length();i++)
            if(data[i]!='/') d+=data[i];
            else if(data[i]=='/') {i++;break;}
        for(i;i<data.length();i++)
            if(data[i]!='/') m+=data[i];
            else if(data[i]=='/') {i++;break;}
        for(i;i<data.length();i++)
            if(data[i]!='/') y+=data[i];
            else if(data[i]=='/') {i++;break;}
        D = Convert<int>(d);
        M = Convert<int>(m);
        Y = Convert<int>(y);
    }
    bool Future()
    {
        Date temp;
        time_t tt; tm* info;
        time(&tt); info=localtime(&tt);
        char* buf=new char[80];
        strftime(buf,80,"%d %m %Y",info);
        std::string a; a.assign(buf);
        istringstream iss(a);
        iss>>temp.D>>temp.M>>temp.Y;
        if(temp.Y>Y) return false;
        if(temp.Y==Y&&temp.M>M) return false;
        if(temp.Y==Y&&temp.M==M&&temp.D>D) return false;
        return Verify();
    }
    bool Check()
    {
        if(Y>Convert<int>(GetTime("%Y"))+1) return false;
        Date temp;
        time_t tt; tm* info;
        time(&tt); info=localtime(&tt);
        char* buf=new char[80];
        strftime(buf,80,"%d %m %Y",info);
        std::string a; a.assign(buf);
        istringstream iss(a);
        iss>>temp.D>>temp.M>>temp.Y;
        if(temp.Y>Y) return false;
        if(temp.Y==Y&&temp.M>M) return false;
        if(temp.Y==Y&&temp.M==M&&temp.D>D) return false;
        return Verify();
    }
    bool Check(Date D2)
    {
        if(Check()&&D2.Check())
        {
            if(M>D2.M&&Y==D2.Y) return false;
            if(Y==D2.Y&&M==D2.M && D>D2.D) return false;
            if(Y>D2.Y) return false;
            return true;
        }
        else return false;
    }
    bool operator<(Date D2)
    {
        if(Y<D2.Y) return true;
        if(Y==D2.Y&&M<D2.M) return true;
        if(Y==D2.Y&&M==D2.M&&D<D2.D) return true;
        return false;
    }
    bool operator>(Date D2)
    {
        if(Y>D2.Y) return true;
        if(Y==D2.Y&&M>D2.M) return true;
        if(Y==D2.Y&&M==D2.M&&D>D2.D) return true;
        return false;
    }
    bool operator==(Date D2)
    {
        return (D==D2.D && M==D2.M && Y==D2.Y);
    }
    bool operator<=(Date D2)
    {
        return (*this<D2 || *this==D2);
    }
    bool operator>=(Date D2)
    {
        return (*this>D2 || *this==D2);
    }
    bool operator!=(Date D2)
    {
        return not(*this==D2);
    }
    bool Check(int nage)
    {
        Date DN;
        DN.Assign(DisplayTime());
        DN.Y -= nage;
        return *this>=DN;
    }
};
struct Location
{
    string DTime;
    string ATime;
    string FlightNo;
    string Dest;
    string Arrival;
    string Dur;
    string FName;
    void Read(fstream& fs)
    {
        char* str; int sz = 0;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; DTime = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; ATime = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; FlightNo = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Dest = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Arrival = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; FName = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Dur = str;
    }
    void Write(fstream& fs)
    {
        int sz = 0;
        sz = DTime.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(DTime.c_str(),sz);
        sz = ATime.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(ATime.c_str(),sz);
        sz = FlightNo.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(FlightNo.c_str(),sz);
        sz = Dest.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Dest.c_str(),sz);
        sz = Arrival.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Arrival.c_str(),sz);
        sz = FName.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(FName.c_str(),sz);
        sz = Dur.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Dur.c_str(),sz);
    }
    string Time()
    {
        string res = "";
        res = res+DTime[0]+""+DTime[1]+""+ATime[0]+""+ATime[1]+"";
        return res;
    }
    void TrPrint(ostream& os = cout)
    {
        os<<ULB;
        for(int i=0;i<8;i++) os<<HT;
        os<<DC;
        for(int i=0;i<11;i++) os<<HT;
        os<<DC;
        for(int i=0;i<14;i++) os<<HT;
        os<<DC;
        for(int i=0;i<14;i++) os<<HT;
        os<<DC;
        for(int i=0;i<16;i++) os<<HT;
        os<<DC;
        for(int i=0;i<16;i++) os<<HT;
        os<<DC;
        for(int i=0;i<13;i++) os<<HT;
        os<<URB;
        os<<left;
        os<<VT<<setw(8)<<" "+FlightNo<<VT<<setw(11)<<"  "+Dur<<VT<<setw(14)<<"  "+DTime<<VT<<setw(14)<<"  "+ATime<<VT<<setw(16)<<"    "+Dest<<VT<<setw(16)<<"    "+Arrival<<VT<<setw(13)<<" "+FName<<VT;
        os<<DLB;
        for(int i=0;i<8;i++) os<<HT;
        os<<UC;
        for(int i=0;i<11;i++) os<<HT;
        os<<UC;
        for(int i=0;i<14;i++) os<<HT;
        os<<UC;
        for(int i=0;i<14;i++) os<<HT;
        os<<UC;
        for(int i=0;i<16;i++) os<<HT;
        os<<UC;
        for(int i=0;i<16;i++) os<<HT;
        os<<UC;
        for(int i=0;i<13;i++) os<<HT;
        os<<DRB;
    }
    void Print(ostream& os = cout)
    {
        os<<left;
        os<<VT<<setw(8)<<" "+FlightNo<<VT<<setw(11)<<"  "+Dur<<VT<<setw(14)<<"  "+DTime<<VT<<setw(14)<<"  "+ATime<<VT<<setw(16)<<"    "+Dest<<VT<<setw(16)<<"    "+Arrival<<VT<<setw(13)<<" "+FName<<VT;
        os<<LC;
        for(int i=0;i<8;i++) os<<HT;
        os<<NC;
        for(int i=0;i<11;i++) os<<HT;
        os<<NC;
        for(int i=0;i<14;i++) os<<HT;
        os<<NC;
        for(int i=0;i<14;i++) os<<HT;
        os<<NC;
        for(int i=0;i<16;i++) os<<HT;
        os<<NC;
        for(int i=0;i<16;i++) os<<HT;
        os<<NC;
        for(int i=0;i<13;i++) os<<HT;
        os<<RC;
    }
    string Route(bool full = false)
    {
        stringstream ss;
        if(full) {for(int i=0;i<96;i++) ss<<"-"; ss<<"\\line ";}
        ss<<left;
        ss<<"|"<<setw(8)<<" "+FlightNo<<"|"<<setw(11)<<"  "+Dur<<"|"<<setw(14)<<"  "+DTime<<"|"<<setw(14)<<"  "+ATime<<"|"
          <<setw(16)<<"    "+Dest<<"|"<<setw(16)<<"    "+Arrival<<"|"<<setw(13)<<" "+FName<<"|\\line ";
        for(int i=0;i<96;i++) ss<<"-";
        return ss.str();
    }
    bool operator == (Location d)
    {
        if(DTime==d.DTime && ATime==d.ATime && FlightNo==d.FlightNo && Dest==d.Dest \
           && Arrival==d.Arrival && Dur==d.Dur && FName==d.FName)
            return true;
        return false;
    }
};

vector<Location> DOM =
{
    {"13:00","15:10","KA-101","DELHI"    ,"MUMBAI"   ,"02h 10m","Boeing 777"},
    {"17:00","19:10","KA-102","DELHI"    ,"MUMBAI"   ,"02h 10m","Boeing 777"},
    {"11:20","12:30","KA-111","DELHI"    ,"JAMMU"    ,"01h 10m","Boeing 777"},
    {"08:45","11:35","KA-121","DELHI"    ,"CHENNAI"  ,"02h 50m","Boeing 787"},
    {"06:50","09:00","KA-131","DELHI"    ,"KOLKATA"  ,"02h 10m","Boeing 777"},
    {"09:30","12:00","KA-141","DELHI"    ,"BANGALORE","02h 30m","Boeing 777"},
    {"16:00","18:10","KA-102","MUMBAI"   ,"DELHI"    ,"02h 10m","Boeing 777"},
    {"20:00","22:10","KA-103","MUMBAI"   ,"DELHI"    ,"02h 10m","Boeing 777"},
    {"15:50","17:00","KA-112","JAMMU"    ,"DELHI"    ,"01h 10m","Boeing 777"},
    {"12:30","15:20","KA-122","CHENNAI"  ,"DELHI"    ,"02h 50m","Boeing 787"},
    {"10:00","12:10","KA-132","KOLKATA"  ,"DELHI"    ,"02h 10m","Boeing 777"},
    {"13:30","16:00","KA-142","BANGALORE","DELHI"    ,"02h 30m","Boeing 777"},
    {"06:15","08:15","KA-171","MUMBAI"   ,"CHENNAI"  ,"02h 00m","Boeing 788"},
    {"15:00","17:00","KA-172","CHENNAI"  ,"MUMBAI"   ,"02h 00m","Boeing 788"}
};
vector<Location> INTL =
{
    {"13:15","18:55"     ,"KA-601","DELHI"    ,"PARIS"    ,"09h 10m","Boeing 787"},
    {"13:15","06:10 (+1)","KA-611","DELHI"    ,"SYDNEY"   ,"12h 25m","Boeing 787"},
    {"23:15","07:30 (+1)","KA-621","DELHI"    ,"SINGAPORE","05h 40m","Boeing 787"},
    {"02:45","07:30"     ,"KA-631","DELHI"    ,"LONDON"   ,"09h 15m","Boeing 787"},
    {"00:10","05:05"     ,"KA-641","DELHI"    ,"TORONTO"  ,"14h 25m","Boeing 787"},
    {"13:35","04:10 (+1)","KA-651","DELHI"    ,"NEW YORK" ,"14h 35m","Boeing 787"},
    {"02:35","05:05"     ,"KA-661","MUMBAI"   ,"CAIRO"    ,"06h 00m","Boeing 787"},
    {"22:00","09:35 (+1)","KA-600","PARIS"    ,"DELHI"    ,"08h 05h","Boeing 787"},
    {"09:45","18:25"     ,"KA-610","SYDNEY"   ,"DELHI"    ,"13h 10m","Boeing 787"},
    {"08:35","11:35"     ,"KA-620","SINGAPORE","DELHI"    ,"05h 30m","Boeing 787"},
    {"09:45","22:50"     ,"KA-630","LONDON"   ,"DELHI"    ,"08h 40m","Boeing 787"},
    {"22:00","21:20 (+1)","KA-640","TORONTO"  ,"DELHI"    ,"13h 50m","Boeing 787"},
    {"21:15","12:45 (+1)","KA-650","NEW YORK" ,"DELHI"    ,"14h 00m","Boeing 787"},
    {"16:20","01:30 (+1)","KA-660","CAIRO"    ,"MUMBAI"   ,"05h 40m","Boeing 787"}
};

class Seat
{
    char*** SEAT;
    string cbn,date,jt1,o,d,times;
    int x, y;
public:
    Seat():cbn("NULL"),date("----------"),jt1("NULL"),x(0),y(0),o("NULL"),d("NULL"),times("----")
    {
        for(int i=0;i<y;i++)
        {
            SEAT[i] = new char*[x];
            for(int j=0;j<x;j++)
            {
                SEAT[i][j] = new char[5];
                strcpy(SEAT[i][j],const_cast<char*>((Revert(i+1)+char(65+j)+".").c_str()));
            }
        }
    }
    Seat(string cb, string dt, string j1, string og, string ds, string tms, int sx, int sy)
        :cbn(cb),date(dt),jt1(j1),x(sx),y(sy),o(og),d(ds),times(tms)
    {
        SEAT = new char**[y];
        for(int i=0;i<y;i++)
        {
            SEAT[i] = new char*[x];
            for(int j=0;j<x;j++)
            {
                SEAT[i][j] = new char[5];
            }
        }
    }
    void Create()
    {
        if(Exist()){ Retrieve(); return;}
        for(int i=0;i<y;i++)
            for(int j=0;j<x;j++)
                strcpy(SEAT[i][j],const_cast<char*>((Revert(i+1)+char(65+j)+".").c_str()));
        fstream file;
        file.open(("Airline\\Seat Records\\Record "+cbn+" "+o+"-"+d+" "+date+" "+jt1+" "+times+".txt").c_str(),ios::out);
        for(int i=0;i<y;i++)
            for(int j=0;j<x;j++)
                file<<SEAT[i][j]<<(j==x-1?"\n":" ");
        file.close();
    }
    bool Exist()
    {
        fstream file;
        file.open(("Airline\\Seat Records\\Record "+cbn+" "+o+"-"+d+" "+date+" "+jt1+" "+times+".txt").c_str(),ios::in);
        return bool(file);
    }
    void Book(int r, char c)
    {
        Retrieve();
        strcpy(SEAT[r-1][c-1],const_cast<char*>((Revert(r)+char(64+c)+"*").c_str()));
        fstream file;
        file.open(("Airline\\Seat Records\\Record "+cbn+" "+o+"-"+d+" "+date+" "+jt1+" "+times+".txt").c_str(),ios::out|ios::trunc);
        file.seekp(0);
        for(int i=0;i<y;i++)
            for(int j=0;j<x;j++)
                file<<SEAT[i][j]<<(j==x-1?"\n":" ");
        file.close();
    }
    bool Booked(int r, int c)
    {
        Retrieve();
        int len = strlen(SEAT[r-1][c-1]);
        return SEAT[r-1][c-1][len-1] == '*';
    }
    void Unbook(int r, int c)
    {
        Retrieve();
        strcpy(SEAT[r-1][c-1],const_cast<char*>((Revert(r)+char(64+c)+".").c_str()));
        fstream file;
        file.open(("Airline\\Seat Records\\Record "+cbn+" "+o+"-"+d+" "+date+" "+jt1+" "+times+".txt").c_str(),ios::out|ios::trunc);
        file.seekp(0);
        for(int i=0;i<y;i++)
            for(int j=0;j<x;j++)
                file<<SEAT[i][j]<<(j==x-1?"\n":" ");
        file.close();
    }
    void Retrieve()
    {
        ifstream fin;
        fin.open(("Airline\\Seat Records\\Record "+cbn+" "+o+"-"+d+" "+date+" "+jt1+" "+times+".txt").c_str(),ios::in);
        for(int i=0;i<y;i++)
            for(int j=0;j<x;j++)
                fin>>SEAT[i][j];
        fin.close();
    }
    void Show()
    {
        for(int i=0;i<y;i++)
            for(int j=0;j<x;j++)
                cout<<SEAT[i][j]<<(j==x-1?"\n":" ");
    }
    vector<Coordinate> Print(int sx=0,int sy=0,int seatw = 3)
    {
        vector<Coordinate> pts(x*y); Retrieve();
        SetConsoleColor(WHITE); GOTO(sx-2,sy-2); cout<<BLK<<BLK;
        SetConsoleColor(YELLOW); GOTO(sx+2,sy-2);
        for(int i=1;i<=x;i++)
        {
            cout<<char(64+i)<<" ";
            if(i%seatw==0) cout<<" "<<" ";
        }
        for(int i=0;i<y;i++)
        {
            GOTO(sx-2,sy+(2*i));
            cout<<((i+1<10)?"0":"")<<i+1;
        }
        for(int i=0;i<y;i++)
        {
            int offset = 0;
            for(int j=0;j<x;j++)
            {
                GOTO(((j+1)*2)+sx+offset,(i*2)+sy);
                int len = strlen(SEAT[i][j]);
                if(SEAT[i][j][len-1] == '.')
                { SetConsoleColor(GREEN); cout<<BLK; }
                else
                { SetConsoleColor(RED); cout<<BLK; }
                pts[(x*i)+j] = {((j+1)*2)+sx+offset,(i*2)+sy};
                offset += ((j+1)%(seatw)==0)?2:0;
            }
        }
        SetConsoleColor(WHITE);
        return pts;
    }
    int Count()
    {
        int ctr = 0; fstream file;
        file.open(("Airline\\Seat Records\\Record "+cbn+" "+o+"-"+d+" "+date+" "+jt1+" "+times+".txt").c_str(),ios::in);
        for(int i=0;i<y;i++)
            for(int j=0;j<x;j++)
            {
                file>>SEAT[i][j];
                int len = strlen(SEAT[i][j]);
                if(SEAT[i][j][len-1] == '.') ctr++;
            }
        file.close();
        return ctr;
    }
    string SeatNo(int r, int c)
    {
        Retrieve();
        return string(Revert(r)+char(64+c));
    }
};
struct Fare
{
    int fare;
    bool HIGHV;
    string cbn,jt,type;
    int HP,LP;
    void Get(string a,string b,Location tr)
    {
        cbn = a; jt = b;
        if(jt=="Domestic") jt="DOM";
        else jt="INTL";
        fstream file;
        HIGH();
        file.open(("Airline\\IATA Fares\\"+jt+"\\"+cbn+" "+type+" "+jt+".txt").c_str(),ios::in);
        for(int i=0;i<14;i++)
        {
            file>>HP;
            if(jt=="DOM")
            {
                if(tr==DOM[i]) break;
            }
            else
            {
                if(tr==INTL[i]) break;
            }
        }
        file.close();
        LOW();
        file.open(("Airline\\IATA Fares\\"+jt+"\\"+cbn+" "+type+" "+jt+".txt").c_str(),ios::in);
        for(int i=0;i<14;i++)
        {
            file>>LP;
            if(jt=="DOM")
            {
                if(tr==DOM[i]) break;
            }
            else
            {
                if(tr==INTL[i]) break;
            }
        }
        file.close();
    }
    void Print(int x,int y)
    {
        string data = cbn+" "+(HIGHV?"HIGH -  INR ":"LOW  -  INR ")+Revert((HIGHV?HP:LP))
                      +(((HP/10)<LP)?"":" ")+"       "
                      + "( "+(HIGHV?"No Date Change & Cancellation Charges Apply.  "
                      : "Date Change & Cancellation Charges Applicable.")+" )";
        Button Temp(91,1,x,y,WHITE,0,YELLOW,0,data);
        Temp.Print();
    }
    void HIGH()
    {
        HIGHV=true;
        type = "HIGH";
    }
    void LOW()
    {
        HIGHV=false;
        type = "LOW";
    }
    int Invoice(int a, int c, int i, int y, string jtr, Location tr, Location trr)
    {
        double total=0,  P = (HIGHV?HP:LP), CP = (0.75*P), IP = (0.1*P);
        SetCursorAt(0,y); cout.setf(ios::fixed); cout.precision(2);
        string d1=tr.Dest+" -> "+tr.Arrival, d2=trr.Dest+" -> "+trr.Arrival;
        if(d1.length()%2==0) d1+=" "; if(d2.length()%2==0) d2+=" ";

        Head(cout,("FARE INVOICE - "+type),100);
        Head(cout,"| S.NO. |            ROUTE            |   TYPE   | PASSENGERS |  BASE FARE  |  GST  |  TOTAL FARE  |",100);
        iter(100,'-',cout);
        cout<<left<<"|   01  |"<<Spc((14-(d1.length()/2)))<<setw(d1.length()+(14-(d1.length()/2)))<<d1
            <<"|  ADULT   |     "<<setw(7)<<Revert(a)<<"|"<<Spc(2)<<setw(11)<<P*a<<"|  20%  |"
            <<Spc(3)<<setw(11)<<float(P*a*1.2)<<"|";
        total += float(1.2*P*a); iter(100,'-',cout);
        cout<<left<<"|   02  |"<<Spc((14-(d1.length()/2)))<<setw(d1.length()+(14-(d1.length()/2)))<<d1
            <<"|  CHILD   |     "<<setw(7)<<Revert(c)<<"|"<<Spc(2)<<setw(11)<<CP*c<<"|  20%  |"
            <<Spc(3)<<setw(11)<<float(CP*c*1.2)<<"|";
        total += float(1.2*CP*c); iter(100,'-',cout);
        cout<<left<<"|   03  |"<<Spc((14-(d1.length()/2)))<<setw(d1.length()+(14-(d1.length()/2)))<<d1
            <<"|  INFANT  |     "<<setw(7)<<Revert(i)<<"|"<<Spc(2)<<setw(11)<<IP*i<<"|  18%  |"
            <<Spc(3)<<setw(11)<<float(IP*i*1.18)<<"|";
        total += float(1.18*IP*i); iter(100,'-',cout);
        if(jtr=="Return")
        {
            cout<<left<<"|   04  |"<<Spc((14-(d2.length()/2)))<<setw(d2.length()+(14-(d2.length()/2)))<<d2
                <<"|  ADULT   |     "<<setw(7)<<Revert(a)<<"|"<<Spc(2)<<setw(11)<<P*a<<"|  20%  |"
                <<Spc(3)<<setw(11)<<float(P*a*1.2)<<"|";
            total += float(1.2*P*a); iter(100,'-',cout);
            cout<<left<<"|   05  |"<<Spc((14-(d2.length()/2)))<<setw(d2.length()+(14-(d2.length()/2)))<<d2
                <<"|  CHILD   |     "<<setw(7)<<Revert(c)<<"|"<<Spc(2)<<setw(11)<<CP*c<<"|  20%  |"
                <<Spc(3)<<setw(11)<<float(CP*c*1.2)<<"|";
            total += float(1.2*CP*c); iter(100,'-',cout);
            cout<<left<<"|   06  |"<<Spc((14-(d2.length()/2)))<<setw(d2.length()+(14-(d2.length()/2)))<<d2
                <<"|  INFANT  |     "<<setw(7)<<Revert(i)<<"|"<<Spc(2)<<setw(11)<<IP*i<<"|  18%  |"
                <<Spc(3)<<setw(11)<<float(IP*i*1.18)<<"|";
            total += float(1.18*IP*i); iter(100,'-',cout);
        }

        Head(cout,"GRAND TOTAL                                                           =   INR "+Revert(total,2),100);
        return total;
    }
    double GetFare(string Type)
    {
        double P = (HIGHV?HP:LP), CP = (0.75*P), IP = (0.1*P);
        if(Type=="Adult") return double(P*1.2);
        if(Type=="Child") return double(CP*1.2);
        if(Type=="Infant") return double(IP*1.18);
    }
};

class Passenger
{
protected:
    string FirstName, MidName, SurName, Email, Contact, Gender, TicketNumber, nt, n1, n2, n3, n4;
    string MealPref, Requirements, Doc, DocNo, VisaNo, VisaLoc, JType1, JType2, Cabin, RLOC, SeatD, SeatR, Nationality;
    Date DOB, Exp, VisaExp, DOD, DOR; Location Depart, Return;
public:
    string Type; bool State; double PFare;
    Passenger(){}
    ~Passenger(){}
    bool cmp(string o, string d, string cbn, Date dd, string td, string ta, string jt, string type)
    {
        o = ToCaps(o); d = ToCaps(d); cbn = ToCaps(cbn); jt = ToTitle(jt); type = ToTitle(type);
        string t; t+=td[0]; t+=td[1]; t+=ta[0]; t+=ta[1];
        bool bd = ((Depart.Dest==o)&&(Depart.Arrival==d)&&(dd!=Date(0,0,0)?dd==DOD:true));
        bool ba = ((Return.Dest==o)&&(Return.Arrival==d)&&(dd!=Date(0,0,0)?dd==DOR:true));
        if(o=="*") { bd = (Depart.Arrival==d)&&(dd!=Date(0,0,0)?dd==DOD:true);
                     ba = (Return.Arrival==d)&&(dd!=Date(0,0,0)?dd==DOR:true);  }
        if(d=="*") { bd = (Depart.Dest==d)&&(dd!=Date(0,0,0)?dd==DOD:true);
                     ba = (Return.Dest==d)&&(dd!=Date(0,0,0)?dd==DOR:true);  }
        if(o=="*"||d=="*") { bd = (dd!=Date(0,0,0)?dd==DOD:true);
                             ba = (dd!=Date(0,0,0)?dd==DOR:true); }
        bool b1 = bd||ba;
        bool b2 = ((td!="*"&&ta!="*")?(t==Depart.Time()||t==Return.Time()):true);
        bool b3 = cbn !="*"?Cabin==cbn  :true;
        bool b4 = type!="*"?Type==type  :true;
        bool b5 = jt!="*"  ?(jt==JType1):true;
        bool b6 = not Type.empty();
        //cout<<boolalpha<<b1<<" "<<b2<<" "<<b3<<" "<<b4<<" "<<b5<<" "<<b6<<"\n";
        return b1&&b2&&b3&&b4&&b5&&b6;
    }
    void Disp(Date d)
    {
        if(d==Date(0,0,0))
        {
            cout<<left<<"|  "<<setw(8)<<RLOC<<"|       "<<setw(27)<<ToCaps(SurName)+" / "+ToCaps(FirstName)<<"|  "<<setw(8)<<Type;
            cout<<left<<"|  "<<setw(6)<<SeatD<<"|    "<<setw(16)<<TicketNumber<<"| "<<setw(10)<<Cabin<<"|";
            for(int i=0;i<100;i++) cout<<"-";
            if(JType2=="Return")
            {
                cout<<left<<"|  "<<setw(8)<<RLOC<<"|       "<<setw(27)<<ToCaps(SurName)+" / "+ToCaps(FirstName)<<"|  "<<setw(8)<<Type;
                cout<<left<<"|  "<<setw(6)<<SeatR<<"|    "<<setw(16)<<TicketNumber<<"| "<<setw(10)<<Cabin<<"|";
                for(int i=0;i<100;i++) cout<<"-";
            }
        }
        else if(d==DOD)
        {
            cout<<left<<"|  "<<setw(8)<<RLOC<<"|       "<<setw(27)<<ToCaps(SurName)+" / "+ToCaps(FirstName)<<"|  "<<setw(8)<<Type;
            cout<<left<<"|  "<<setw(6)<<SeatD<<"|    "<<setw(16)<<TicketNumber<<"| "<<setw(10)<<Cabin<<"|";
            for(int i=0;i<100;i++) cout<<"-";
        }
        else if(d==DOR)
        {
            cout<<left<<"|  "<<setw(8)<<RLOC<<"|       "<<setw(27)<<ToCaps(SurName)+" / "+ToCaps(FirstName)<<"|  "<<setw(8)<<Type;
            cout<<left<<"|  "<<setw(6)<<SeatR<<"|    "<<setw(16)<<TicketNumber<<"| "<<setw(10)<<Cabin<<"|";
            for(int i=0;i<100;i++) cout<<"-";
        }
    }
    bool operator==(const Passenger& p2)
    {
        bool b1 = TicketNumber==p2.TicketNumber&&RLOC==p2.RLOC&&FirstName==p2.FirstName&&MidName==p2.MidName
                  &&SurName==p2.SurName&&Email==p2.Email&&Contact==p2.Contact;
        if(b1)
        {
            bool b2 = Gender==p2.Gender&&nt==p2.nt&&n1==p2.n1&&n2==p2.n2&&n3==p2.n3&&n4==p2.n4&&DOB==p2.DOB
                      &&Cabin==p2.Cabin&&SeatD==p2.SeatD&&SeatR==p2.SeatR&&Nationality==p2.Nationality;
            if(b2)
            {
                bool b3 = Exp==p2.Exp&&Depart==p2.Depart&&Return==p2.Return&&DOD==p2.DOD&&DOR==p2.DOR&&VisaExp==p2.VisaExp;
                if(b3)
                {
                    bool b4 = MealPref==p2.MealPref&&Requirements==p2.Requirements&&Doc==p2.Doc&&DocNo==p2.DocNo;
                    if(b4)
                    {
                        bool b5 = VisaNo==p2.VisaNo&&VisaLoc==p2.VisaLoc&&JType1==p2.JType1&&JType2==p2.JType2;
                        return b5&&Type==p2.Type&&State==p2.State&&PFare==p2.PFare;
                    }
                    return false;
                }
                return false;
            }
            return false;
        }
        return false;
    }
    pair<string,string> BkSeat()
    {
        return make_pair(SeatD.substr(1),JType2=="Return"?SeatR.substr(1):"");
    }
    string Info()
    {
        return ToCaps(SurName)+"/"+ToCaps(FirstName)+" - "+TicketNumber+" - "+Type+" - "+DOB.Value()+" - "+Gender;
    }
    Location Rt(bool ret = false)
    {
        if(ret) return Return;
        else    return Depart;
    }
    Date DEP()
    {
        return DOD;
    }
    Date ARR()
    {
        return DOR;
    }
    string Class()
    {
        return Cabin;
    }
    pair<string,string> JT()
    {
        return make_pair(JType1,JType2);
    }
    string PayMode()
    {
        return nt+" - "+n1;
    }
    string Ref()
    {
        return TicketNumber;
    }
    void Read(fstream& fs)
    {
        char* str; int sz = 0;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; RLOC = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; TicketNumber = str;
        fs.read(reinterpret_cast<char*>(&DOB),    sizeof(Date));
        fs.read(reinterpret_cast<char*>(&DOD),    sizeof(Date));
        fs.read(reinterpret_cast<char*>(&DOR),    sizeof(Date));
        fs.read(reinterpret_cast<char*>(&Exp),    sizeof(Date));
        fs.read(reinterpret_cast<char*>(&VisaExp),sizeof(Date));
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; FirstName = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; MidName = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; SurName = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Email = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Contact = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Gender = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; nt = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; n1 = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; n2 = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; n3 = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; n4 = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; JType1 = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; JType2 = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Cabin = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Type = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Nationality = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; SeatD = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; SeatR = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; MealPref = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Requirements = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; Doc = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; DocNo = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; VisaNo = str;
        fs.read(reinterpret_cast<char*>(&sz),sizeof(sz));
        str = new char[sz+1]; fs.read(str,sz); str[sz] = '\0'; VisaLoc = str;
        Depart.Read(fs); Return.Read(fs);
        fs.read(reinterpret_cast<char*>(&State),sizeof(State));
        fs.read(reinterpret_cast<char*>(&PFare),sizeof(PFare));
    }
    void Write(fstream& fs)
    {
        int sz = 0;
        sz = RLOC.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(RLOC.c_str(),sz);
        sz = TicketNumber.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(TicketNumber.c_str(),sz);
        fs.write(reinterpret_cast<char*>(&DOB),    sizeof(Date));
        fs.write(reinterpret_cast<char*>(&DOD),    sizeof(Date));
        fs.write(reinterpret_cast<char*>(&DOR),    sizeof(Date));
        fs.write(reinterpret_cast<char*>(&Exp),    sizeof(Date));
        fs.write(reinterpret_cast<char*>(&VisaExp),sizeof(Date));
        sz = FirstName.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(FirstName.c_str(),sz);
        sz = MidName.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(MidName.c_str(),sz);
        sz = SurName.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(SurName.c_str(),sz);
        sz = Email.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Email.c_str(),sz);
        sz = Contact.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Contact.c_str(),sz);
        sz = Gender.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Gender.c_str(),sz);
        sz = nt.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(nt.c_str(),sz);
        sz = n1.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(n1.c_str(),sz);
        sz = n2.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(n2.c_str(),sz);
        sz = n3.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(n3.c_str(),sz);
        sz = n4.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(n4.c_str(),sz);
        sz = JType1.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(JType1.c_str(),sz);
        sz = JType2.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(JType2.c_str(),sz);
        sz = Cabin.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Cabin.c_str(),sz);
        sz = Type.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Type.c_str(),sz);
        sz = Nationality.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Nationality.c_str(),sz);
        sz = SeatD.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(SeatD.c_str(),sz);
        sz = SeatR.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(SeatR.c_str(),sz);
        sz = MealPref.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(MealPref.c_str(),sz);
        sz = Requirements.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Requirements.c_str(),sz);
        sz = Doc.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(Doc.c_str(),sz);
        sz = DocNo.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(DocNo.c_str(),sz);
        sz = VisaNo.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(VisaNo.c_str(),sz);
        sz = VisaLoc.size(); fs.write(reinterpret_cast<char*>(&sz),sizeof(sz));
        fs.write(VisaLoc.c_str(),sz);
        Depart.Write(fs); Return.Write(fs);
        fs.write(reinterpret_cast<char*>(&State),sizeof(State));
        fs.write(reinterpret_cast<char*>(&PFare),sizeof(PFare));
    }
    friend ostream& operator<<(ostream& os, Passenger p)
    {
        SetConsoleColor(YELLOW); os<<"GENERAL DETAILS"<<endl;iter(100,"-",os);os<<endl; SetConsoleColor(WHITE);
        os<<" Name        - "<<p.FirstName+(p.MidName.empty()?"":" ")+p.MidName+" "+p.SurName<<endl;
        os<<" Type        - "<<p.Type<<"\t\t\t"<<" DOB         - "<<p.DOB<<endl;
        os<<" Nationality - "<<(p.JType1=="International"?p.Nationality:"Indian")<<"\t\t\t";
        os<<" Gender      - "<<p.Gender<<endl;
        os<<" Contact No. - "<<p.Contact<<"\t\t"<<" E-Mail      - "<<p.Email<<endl<<endl;
        os<<" Special Requirements - "<<p.Requirements<<endl;
        os<<" Meal Preference      - "<<p.MealPref<<endl;
        if(p.JType1=="International")
        {
            SetConsoleColor(YELLOW);os<<"\n\nDOCUMENT DETAILS"<<endl;iter(100,"-",os);os<<endl;SetConsoleColor(WHITE);
            os<<left<<setw(12)<<" Visa - "<<"<  "<<setw(15)<<p.VisaNo
                <<">  , Expiry - "<<p.VisaExp<<", For "<<setw(p.VisaLoc.length()+2)<<p.VisaLoc<<endl;
            os<<left<<" "<<setw(11)<<p.Doc+" - "<<"<  "<<setw(15)<<p.DocNo<<">  , Expiry - "<<p.Exp<<endl;
        }
        SetConsoleColor(YELLOW);os<<"\n\nJOURNEY DETAILS"<<endl;iter(100,"-",os);os<<endl;SetConsoleColor(WHITE);
        os<<" Ticket Reference Number (13 Digits)                   - "<<p.TicketNumber<<endl;
        os<<" Resource Locator (RLOC) / Passenger Name Record (PNR) - "<<p.RLOC<<endl<<endl;
        os<<" Journey Type - "<<p.JType1<<", "<<p.JType2<<endl;
        os<<" Chosen Cabin - "<<p.Cabin<<endl;
        SetConsoleColor(GREEN); os<<"\n Current Departure Route - For ";p.DOD.Show();os<<" in "<<p.Cabin<<" class."<<endl;
        SetConsoleColor(WHITE); p.Depart.TrPrint();
        if(p.JType2=="Return")
        {
            SetConsoleColor(GREEN); os<<"\n Current Return Route    - For ";p.DOR.Show();os<<" in "<<p.Cabin<<" class."<<endl;
            SetConsoleColor(WHITE); p.Return.TrPrint();
        }
        os<<"\n Seat During Outbound Journey - "<<p.SeatD<<endl;
        if(p.JType2=="Return") os<<" Seat During Inbound Journey  - "<<p.SeatR<<endl;
        SetConsoleColor(YELLOW);os<<"\n\nFARE DETAILS"<<endl;iter(100,"-",os);os<<endl;SetConsoleColor(WHITE);
        os<<" Type of Fare                   - "<<(p.State?
        "HIGH (No Date Change and Cancellation Charges)":"LOW (Date Change and Cancellation Charges Applicable)")<<endl;
        os<<" Total Fare of Outbound Journey - "<<p.PFare<<endl;
        if(p.JType2=="Return") os<<" Total Fare of Inbound Journey  - "<<p.PFare<<endl;
        os<<" Mode of Payment                - "<<p.nt<<endl<<endl;
        //os<<left<<" "<<setw(18)<<p.nt<<"  |  "<<p.n1<<"  |  "<<p.n2<<"  |  "<<p.n3<<"  |  "<<p.n4<<"  |"<<endl<<endl;
    }
    void DownloadTicket()
    {
        Location Title = {"DEPARTURE"," ARRIVAL","F. NO."," ORIGIN"    ,"TERMINUS"   ,"DURATION","FLIGHT NAME"};
        fstream word; word.open("Passenger Tickets\\Downloads\\Ticket "+TicketNumber+".doc",ios::out|ios::trunc);
        string data = "", Head = "  KV Airlines "+Spc(26)+" E - Ticket ";
        data += Word.Print(Head,White,Turquoise,Harlow,22,'l',0,0,1);
        data += Word.Print("\\line",White,White,Consolas,10,'l',0,0,0);
        string info = "", td = Revert(1+rand()%3), ta = Revert(1+rand()%3);
        info = " Ticket Number    -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = Revert(TicketNumber)+" \\line "; data+=Word.Print(info,Black,White,Consolas,12,'l',0,0,0,0);
        info = " Booking Timings  -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = DisplayFullTime()+" \\line "      ; data+=Word.Print(info,Black,White,Consolas,12,'l',0,0,0,0);
        info = " PNR / RLOC       -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = RLOC+" \\line \\line "; data+=Word.Print(info,Black,White,Consolas,12,'l',0,0,0,0);
        info = " Itinerary        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        data+=Word.Print(" \\line ",Blue,White,Aharoni,12,'l',1,0,0);
        data += Word.Print(Title.Route(1),Brown,Yellow,Consolas,10,'c');
        info = " Outbound       - "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " Departure from Terminal-"+td+", Arrival to Terminal-"+ta+"           ";
        data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        info = " Baggage - 25K  "                ; data+=Word.Print(info,DarkGreen,White,Arial,12,'l',0,0,0,0);
        data+=Word.Print(" ",Blue,White,Aharoni,12,'l',1,0,0);
        data += Word.Print(Depart.Route(1),Brown,White,Consolas,10,'c');
        if(JType2 == "Return")
        {
            info = " Inbound        - "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
            info = " Departure from Terminal-"+ta+", Arrival to Terminal-"+td+"           ";
            data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
            info = " Baggage - 25K  "                ; data+=Word.Print(info,DarkGreen,White,Arial,12,'l',0,0,0,0);
            data+=Word.Print(" ",Blue,White,Aharoni,12,'l',1,0,0);
            data += Word.Print(Return.Route(1),Brown,White,Consolas,10,'c');
        }
        data += Word.Print(" \\line ",Black,White,Consolas,12);
        info = " Passenger Details    -   \\line "      ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0);
        stringstream ss; for(int i=0;i<95;i++) ss<<"-"; ss<<"\\line ";
        ss<<"|        Passenger Name        |   Type   |         Route          | Seat |   Journey Date   |\\line";
        for(int i=0;i<96;i++) ss<<"-"; data += Word.Print(ss.str(),DarkBlue,Green,Consolas,10,'c',0,0,0);
        data += Word.Print(Print(1,1),DarkBlue,White,Consolas,10,'c',0,0,0);
        if(JType2=="Return") data += Word.Print(Print(1,0),DarkBlue,White,Consolas,10,'c',0,0,0);
        data+=Word.Print("\\line",Black,White,Consolas,12);
        info = " Fare Type        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = State?" HIGH (No Date Change and Cancellation Charges). \\line":" LOW (Date Change and Cancellation Charges Apply). \\line";
        data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        int mult = JType2=="Return"?2:1; PFare*=mult;
        double Base = Type!="Infant"?(PFare-(PFare/1.2)):(PFare-(PFare/1.18));
        info = " Base Fare        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " INR "+Revert(double((Type=="Infant")?PFare/1.18:PFare/1.2))+" \\line";data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        info = " Net Taxes        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " INR "+Revert(Base)+" \\line";data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        info = " Total Fare        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " INR "+Revert(PFare)+" \\line\\line ";data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        info = " Status           -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " Confirmed \\line";data+=Word.Print(info,DarkGreen,White,Arial,12,'l',1,0,0);
        string dummy; for(int i=0;i<201;i++) dummy += "-"; data += Word.Print(dummy,Black,White,Harlow,14);
        string inst = ""; inst = "\\line  Instructions -: "; data += Word.Print(inst,Blue,White,Aharoni,12,'l',0,0,1);
        data += Word.Print("",Black,White,Consolas,12);
        inst = "*) Please carry this Itinerary Receipt and Valid photo ID Card to the Airport.";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) Kindly Report for Check-In atleast 2-3 hours before scheduled departure for all Flights.";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) The Carry On Baggage includes a single piece of not more than 8 kgs, plus a Laptop or Purse.";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) Passengers are advised not to carry fragile and valuable items in baggage to prevent loss.";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) KV Airlines Toll - Free Numbers - :\\line         24X7-18002345678, India-011234562345";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) For More Details onTravel and Baggage, visit www.kvair.com.\\line";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "KV Airlines wishes you a Prosperous Journey.";
        data += Word.Print(inst,DarkGreen,White,Arial,12,'c');
        word<<Word.File(data);
        word.close();
    }
    void GenTicket(bool fnew = true)
    {
        if(fnew)
        {
            string res = "";
            string NUM = "1234567890";
            while(true)
            {
                res += "696";
                for(int i=0;i<10;i++) {res += NUM[rand()%10];}
                if(ValidPNR(res)) { TicketNumber = res; break; }
                else res.clear();
            }
        }
        CreateDirectory((GetEXEDrive()+"\\All C++ Files\\KV Airlines\\Passenger Tickets\\"+RLOC+"\\").c_str(),nullptr);
        Location Title = {"DEPARTURE"," ARRIVAL","F. NO."," ORIGIN"    ,"TERMINUS"   ,"DURATION","FLIGHT NAME"};
        fstream word; word.open("Passenger Tickets\\"+RLOC+"\\Ticket "+TicketNumber+".doc",ios::out|ios::trunc);
        string data = "", Head = "  KV Airlines "+Spc(26)+" E - Ticket ";
        data += Word.Print(Head,White,Turquoise,Harlow,22,'l',0,0,1);
        data += Word.Print("\\line",White,White,Consolas,10,'l',0,0,0);
        string info = "", td = Revert(1+rand()%3), ta = Revert(1+rand()%3);
        info = " Ticket Number    -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = Revert(TicketNumber)+" \\line "; data+=Word.Print(info,Black,White,Consolas,12,'l',0,0,0,0);
        info = " Booking Timings  -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = DisplayFullTime()+" \\line "      ; data+=Word.Print(info,Black,White,Consolas,12,'l',0,0,0,0);
        info = " PNR / RLOC       -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = RLOC+" \\line \\line "; data+=Word.Print(info,Black,White,Consolas,12,'l',0,0,0,0);
        info = " Itinerary        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        data+=Word.Print(" \\line ",Blue,White,Aharoni,12,'l',1,0,0);
        data += Word.Print(Title.Route(1),Brown,Yellow,Consolas,10,'c');
        info = " Outbound       - "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " Departure from Terminal-"+td+", Arrival to Terminal-"+ta+"           ";
        data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        info = " Baggage - 25K  "                ; data+=Word.Print(info,DarkGreen,White,Arial,12,'l',0,0,0,0);
        data+=Word.Print(" ",Blue,White,Aharoni,12,'l',1,0,0);
        data += Word.Print(Depart.Route(1),Brown,White,Consolas,10,'c');
        if(JType2 == "Return")
        {
            info = " Inbound        - "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
            info = " Departure from Terminal-"+ta+", Arrival to Terminal-"+td+"           ";
            data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
            info = " Baggage - 25K  "                ; data+=Word.Print(info,DarkGreen,White,Arial,12,'l',0,0,0,0);
            data+=Word.Print(" ",Blue,White,Aharoni,12,'l',1,0,0);
            data += Word.Print(Return.Route(1),Brown,White,Consolas,10,'c');
        }
        data += Word.Print(" \\line ",Black,White,Consolas,12);
        info = " Passenger Details    -   \\line "      ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0);
        stringstream ss; for(int i=0;i<95;i++) ss<<"-"; ss<<"\\line ";
        ss<<"|        Passenger Name        |   Type   |         Route          | Seat |   Journey Date   |\\line";
        for(int i=0;i<96;i++) ss<<"-"; data += Word.Print(ss.str(),DarkBlue,Green,Consolas,10,'c',0,0,0);
        data += Word.Print(Print(1,1),DarkBlue,White,Consolas,10,'c',0,0,0);
        if(JType2=="Return") data += Word.Print(Print(1,0),DarkBlue,White,Consolas,10,'c',0,0,0);
        data+=Word.Print("\\line",Black,White,Consolas,12);
        info = " Fare Type        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = State?" HIGH (No Date Change and Cancellation Charges). \\line":" LOW (Date Change and Cancellation Charges Apply). \\line";
        data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        int mult = JType2=="Return"?2:1; PFare*=mult;
        double Base = Type!="Infant"?(PFare-(PFare/1.2)):(PFare-(PFare/1.18));
        info = " Base Fare        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " INR "+Revert(double((Type=="Infant")?PFare/1.18:PFare/1.2))+" \\line";data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        info = " Net Taxes        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " INR "+Revert(Base)+" \\line";data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        info = " Total Fare        -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " INR "+Revert(PFare)+" \\line\\line ";data+=Word.Print(info,Black,White,Arial,12,'l',0,0,0,0);
        info = " Status           -   "          ; data+=Word.Print(info,Blue,White,Aharoni,12,'l',1,0,0,0);
        info = " Confirmed \\line";data+=Word.Print(info,DarkGreen,White,Arial,12,'l',1,0,0);
        string dummy; for(int i=0;i<201;i++) dummy += "-"; data += Word.Print(dummy,Black,White,Harlow,14);
        string inst = ""; inst = "\\line  Instructions -: "; data += Word.Print(inst,Blue,White,Aharoni,12,'l',0,0,1);
        data += Word.Print("",Black,White,Consolas,12);
        inst = "*) Please carry this Itinerary Receipt and Valid photo ID Card to the Airport.";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) Kindly Report for Check-In atleast 2-3 hours before scheduled departure for all Flights.";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) The Carry On Baggage includes a single piece of not more than 8 kgs, plus a Laptop or Purse.";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) Passengers are advised not to carry fragile and valuable items in baggage to prevent loss.";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) KV Airlines Toll - Free Numbers - :\\line         24X7-18002345678, India-011234562345";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "*) For More Details onTravel and Baggage, visit www.kvair.com.\\line";
        data += Word.Print(inst,Black,White,Arial,12);
        inst = "KV Airlines wishes you a Prosperous Journey.";
        data += Word.Print(inst,DarkGreen,White,Arial,12,'c');
        word<<Word.File(data);
        word.close();
    }
    void Print(bool dep = true)
    {
        if(dep)
        {
            cout<<left<<"|       "<<setw(23)<<ToCaps(SurName)+" / "+ToCaps(FirstName)<<"|  "<<setw(8)<<Type<<"|     ";
            cout<<left<<setw(18)<<Depart.Dest+"->"+Depart.Arrival<<"| "<<setw(5)<<SeatD<<"|   "<<setw(15)<<TicketNumber<<"|";
            for(int i=0;i<100;i++) cout<<"-";
        }
        else
        {
            cout<<left<<"|       "<<setw(23)<<ToCaps(SurName)+" / "+ToCaps(FirstName)<<"|  "<<setw(8)<<Type<<"|     ";
            cout<<left<<setw(18)<<Return.Dest+"->"+Return.Arrival<<"| "<<setw(5)<<SeatR<<"|   "<<setw(15)<<TicketNumber<<"|";
            for(int i=0;i<100;i++) cout<<"-";
        }
    }
    string Print(int d,bool dep)
    {
        stringstream ss;
        if(dep)
        {
            ss<<left<<"|       "<<setw(23)<<ToCaps(SurName)+" / "+ToCaps(FirstName)<<"|  "<<setw(8)<<Type<<"|     ";
            ss<<left<<setw(18)<<Depart.Dest+"->"+Depart.Arrival<<"| "<<setw(5)<<SeatD<<"|     "<<setw(13)<<DOD<<"|\\line ";
            for(int i=0;i<96;i++) ss<<"-";
        }
        else
        {
            ss<<left<<"|       "<<setw(23)<<ToCaps(SurName)+" / "+ToCaps(FirstName)<<"|  "<<setw(8)<<Type<<"|     ";
            ss<<left<<setw(18)<<Return.Dest+"->"+Return.Arrival<<"| "<<setw(5)<<SeatR<<"|     "<<setw(13)<<DOR<<"|\\line ";
            for(int i=0;i<96;i++) ss<<"-";
        }
        return ss.str();
    }
    void Register(string FN, string MN, string LN, string G, string EM, string No, Date DB, string M, string S)
    {
        FirstName = FN; MidName = MN; SurName = LN;
        DOB = DB; MealPref = M; Requirements = S;
        Email = EM; Contact = No; Gender = G;
    }
    void Documents(string DN, string DT, Date DE, string VL, string VN, Date VE, string N)
    {
        VisaLoc = VL; VisaNo = VN; VisaExp = VE;
        Doc = DT, DocNo = DN, Exp = DE; Nationality = N;
    }
    void Assign(string JT1,string JT2,string cbn,string PNR,Date dd,Date dr,Location o, Location d)
    {
        RLOC = PNR;
        Cabin = cbn;
        JType1 = JT1;
        JType2 = JT2;
        DOD = dd;
        DOR = dr;
        Depart = o;
        Return = d;
    }
    void AllocSeat(string S1)
    {
        SeatD = Cabin[0]+S1;
    }
    void AllocReturnSeat(string S2)
    {
        SeatR = Cabin[0]+S2;
    }
    void Payment(string s1,string s2,string s3, string s4, string s5)
    {
        nt = s1; n1 = s2; n2 = s3; n3 = s4; n4 = s5;
    }
}* netp;

bool CheckDomRoute(string dest, string arr)
{
    for(int i=0;i<12;i++)
    {
        if(DOM[i].Dest == dest && DOM[i].Arrival == arr)
            return true;
    }
    return false;
}
bool CheckIntlRoute(string dest, string arr)
{
    for(int i=0;i<14;i++)
    {
        if(INTL[i].Dest == dest && INTL[i].Arrival == arr)
            return true;
    }
    return false;
}
string RouteMsg(string jt)
{
    if(jt=="One-Way")
    {
        string Msg = string("There are Multiple Routes Available for DELHI->MUMBAI.\n")+
                     string("1) Route 1 - Departure at ")+DOM[0].DTime+", Arrival at "+DOM[0].ATime+"\n"+
                     "2) Route 2 - Departure at "+DOM[1].DTime+", Arrival at "+DOM[1].ATime+"\n"+
                     "\nWould you like to use Route 2?";
        return Msg;
    }
    else
    {
        string Msg = string("There are Multiple Routes Available for DELHI->MUMBAI.\n")+
                     string("1) Route 1 - Departure at ")+DOM[0].DTime+", Arrival at "+DOM[0].ATime+"\n"+
                     "     Return  - Departure at "+DOM[6].DTime+", Arrival at "+DOM[6].ATime+"\n"+
                     "2) Route 2 - Departure at "+DOM[1].DTime+", Arrival at "+DOM[1].ATime+"\n"+
                     "     Return  - Departure at "+DOM[7].DTime+", Arrival at "+DOM[7].ATime+"\n"+
                     "\nWould you like to use Route 2?";
        return Msg;
    }
}

void Book(Passenger* p)
{
    p = new Passenger[30]; SetCursor(true); GetDefault();
    int ctr = 0; int noa=0,noc=0,noi=0;
    Button NEXT(10,1,84,52,RED ,0,WHITE,0,"->");
    Button MENU(14,1,44,52,BLUE,0,WHITE,0,"MENU");
    Button RST (20,1,3,52,PINK,0,WHITE,0,"RESET DETAILS");
    vector<SHORT> C1 = RST.Area(); vector<SHORT> C2 = MENU.Area(); vector<SHORT> C3 = NEXT.Area();
    string jt1,jt2,o,d,cabin,a,c,i,ddp,dar,PNR; vector<Coordinate> SeatsBookedToday(30);
    Location tr,trr; Date dep, arr; INPUT_RECORD Rec; DWORD ev;
    bool j1=1,j2=0,dp=0,ar=0,cbn=0,dd=0,da=0,na=0,nc=0,ni=0,complete=0,*rf = &j1,printonce=false,done=0;
    while(true)
    {
        if(ctr==0) //OxFFFFFF
        {
            SetCursor(false); system("cls");SetConsoleSize(80,50); SetBufferSize(80,50);
            SetConsoleColor(BGDARK_TURQUOISE|WHITE); SplHead(cout,"BOOK A FLIGHT",80);
            MENU.Move(-35,-8); NEXT.Move(-25,-8); MENU.Print(); NEXT.Print(); C2 = MENU.Area(); C3 = NEXT.Area();
            SetConsoleColor(GRAY); GOTO(0, 5); cout<<"Instructions - :"; GOTO(0,6); cout<<"------------"; SetConsoleColor(WHITE);
            GOTO(0, 8); cout<<" >> All timings are local to the respective cities.";
            GOTO(0,10); cout<<" >> Please click on the time table to view flight information.";
            GOTO(0,12); cout<<" >> Check-in counters open 3 hours prior to departure of flights, and close 1";
            GOTO(0,13); cout<<"    hour prior to departure of flights. You may be denied boarding if you do ";
            GOTO(0,14); cout<<"    not report in time.";
            GOTO(0,16); cout<<" >> Online bookings can be made upto 2 hours before flight departure.";
            GOTO(0,18); cout<<" >> The fare is not guaranteed until payment is made and is valid for bookings";
            GOTO(0,19); cout<<"    made through the KV Airlines Service Program only.";
            GOTO(0,21); cout<<" >> All known taxes/surcharges/fees at the time of reservation are included.";
            GOTO(0,23); cout<<" >> In case of International travel, please check your requirements for travel ";
            GOTO(0,24); cout<<"    documentation like visa/health/insurance with the relevant Embassy or";
            GOTO(0,25); cout<<"    Consulate before commencing your journey.";
            GOTO(0,27); cout<<" >> KV Airlines will not be liable for incomplete documentation.";
            GOTO(0,29); cout<<" >> In case of International travel, the name should be entered exactly as it ";
            GOTO(0,30); cout<<"    appears on the passport to avoid inconvenience or delay at the airport and";
            GOTO(0,31); cout<<"    avoid denied boarding.";
            GOTO(0,33); cout<<" >> Please note that the Advance Passenger Information Passport Details must";
            GOTO(0,34); cout<<"    be provided before commencement of travel.";
            GOTO(0,36); cout<<" >> Please note that the name and title of all the passengers for whom this ";
            GOTO(0,37); cout<<"    booking is being made should match the identification shown at the time ";
            GOTO(0,38); cout<<"    of check-in. ";
            GOTO(0,40); cout<<" >> Kindly provide all contact numbers (including your mobile ";
            GOTO(0,41); cout<<"    number) as this will help us contact you in case of any changes in timing.";
            while(true)
            {
                ReadConsoleInput(in,&Rec,1,&ev);
                switch(Rec.EventType)
                {
                case KEY_EVENT:
                    {
                        if(Rec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                        {
                            system("cls"); return;
                        }
                    }
                case MOUSE_EVENT:
                    {
                        int x = Rec.Event.MouseEvent.dwMousePosition.X;
                        int y = Rec.Event.MouseEvent.dwMousePosition.Y;
                        switch(Rec.Event.MouseEvent.dwButtonState)
                        {
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            {
                                if(x>=C2[0]&&x<=C2[2] && y>=C2[1]&&y<=C2[3])
                                {
                                    system("cls");
                                    return;
                                }
                                if(x>=C3[0]&&x<=C3[2] && y>=C3[1]&&y<=C3[3])
                                {
                                    goto edit;
                                }
                            }
                        }
                    }
                }
            }
            edit:
            {
                ctr++; system("cls");
                MENU.Move(35,8); NEXT.Move(25,8);
                C2 = MENU.Area();
                C3 = NEXT.Area();
            }
        }
        if(ctr==1) //0xFFFFFF
        {
            jt1.clear(); jt2.clear(); cabin.clear(); o.clear(); d.clear(); SetCursor(true);
            a.clear(); c.clear(); i.clear(); ddp.clear(); dar.clear(); PNR.clear();
            SetConsoleSize(100,56,289); system("cls"); SetConsoleColor(GREEN); SplHead(cout,"JOURNEY DETAILS",100);
            NEXT.Print(); MENU.Print(); RST.Print(); SetConsoleColor(YELLOW);
            SetCursorAt(0,5); cout<<" Domestic      Destinations - ";
            SetCursorAt(0,6); cout<<" International Destinations - ";
            SetConsoleColor(WHITE);
            GOTO(31,5); for(int i=1;i<6;i++) cout<<DOM[i].Arrival<<", "; cout<<DOM[0].Dest;
            GOTO(31,6); for(int i=0;i<6;i++) cout<<INTL[i].Arrival<<",";
            cout<<INTL[6].Dest<<","<<INTL[6].Arrival<<","<<INTL[0].Dest;
            SetConsoleColor(GRAY);
            SetCursorAt(0,9); cout<<" Type of Journey (Domestic/International) \t\t\t";GenFormBoxSC(80, 9,15);
            SetCursorAt(0,11);cout<<" Type of Journey (One-Way /Return       ) \t\t\t";GenFormBoxBC(80,11,15);
            SetCursorAt(0,13);cout<<" Origin                                   \t\t\t";GenFormBoxBC(80,13,15);
            SetCursorAt(0,15);cout<<" Destination                              \t\t\t";GenFormBoxEC(80,15,15);
            SetConsoleColor(YELLOW);
            GOTO(0,18);cout<<" Flight Availability                     -:  ";
            SetConsoleColor(GRAY);
            SetCursorAt(0,21);cout<<" Date of Departure                        \t\t\t(DD/MM/YYYY)";GenFormBoxSC(80,21,15);
            SetCursorAt(0,23);cout<<" Date of Return                           \t\t\t(DD/MM/YYYY)";GenFormBoxEC(80,23,15);
            SetConsoleColor(YELLOW);
            GOTO(0,26);cout<<" Seat   Availability                     -:  ";
            SetConsoleColor(GRAY);
            SetCursorAt(0,29);cout<<" Number of Passengers (Type:Adult )       \t\t\t(  Numeric )";GenFormBoxSC(80,29,15);
            SetCursorAt(0,31);cout<<" Number of Passengers (Type:Child ) (Age : From 2 to 12 years)\t(  Numeric )";GenFormBoxBC(80,31,15);
            SetCursorAt(0,33);cout<<" Number of Passengers (Type:Infant) (Age : Less than 2 years )\t(  Numeric )";GenFormBoxEC(80,33,15);
            SetCursorAt(0,37);cout<<" Flight Cabin (ECONOMY/BUSINESS/FIRST)    \t\t\t";GenFormBox  (80,37,15);
            SetConsoleColor(YELLOW);
            GOTO(0,40);cout<<" Unique PNR/RLOC Number of Registration   -: ";
            GOTO(0,42);cout<<" Special Instructions                     -: ";
            GOTO(0,44);cout<<" Current Route                            -: ";
            SetConsoleColor(GRAY);
            SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);GOTO(82,9);
            while(true)
            {
                if(complete&&printonce)
                {
                    PNR = GenPNR();
                    GOTO(50,40); cout<<PNR;
                    GOTO(50,42); cout<<"Registration Complete. Press -> to Continue.";
                    printonce = 0;
                }
                SetConsoleColor(WHITE);
                ReadConsoleInput(in,&Rec,1,&ev);
                switch(Rec.EventType)
                {
                case KEY_EVENT:
                    {
                        char ch = Rec.Event.KeyEvent.uChar.AsciiChar;
                        GetConsoleScreenBufferInfo(out,&csbi);GetDefault();
                        int cx = csbi.dwCursorPosition.X;
                        if(Rec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                        {
                            system("cls");
                            return;
                        }
                        if((isalnum(ch)||ch=='-'||ch==' '||ch=='_'||ch=='/')&&Rec.Event.KeyEvent.bKeyDown && cx<95 && not complete)
                        {
                            if(j1)
                            {
                                jt1+=ch;
                                GOTO(81+jt1.length(),9);cout<<ch;
                            }
                            if(j2)
                            {
                                jt2+=ch;
                                GOTO(81+jt2.length(),11);cout<<ch;
                            }
                            if(dp)
                            {
                                o+=ch;
                                GOTO(81+o.length(),13);cout<<ch;
                            }
                            if(ar)
                            {
                                d+=ch;
                                GOTO(81+d.length(),15);cout<<ch;
                            }
                            if(dd)
                            {
                                ddp+=ch;
                                GOTO(81+ddp.length(),21);cout<<ch;
                            }
                            if(da)
                            {
                                dar+=ch;
                                GOTO(81+dar.length(),23);cout<<ch;
                            }
                            if(na)
                            {
                                a+=ch;
                                GOTO(81+a.length(),29);cout<<ch;
                            }
                            if(nc)
                            {
                                c+=ch;
                                GOTO(81+c.length(),31);cout<<ch;
                            }
                            if(ni)
                            {
                                i+=ch;
                                GOTO(81+i.length(),33);cout<<ch;
                            }
                            if(cbn)
                            {
                                cabin+=ch;
                                GOTO(81+cabin.length(),37);cout<<ch;
                            }
                        }
                        else if(Rec.Event.KeyEvent.wVirtualKeyCode==VK_RETURN&&Rec.Event.KeyEvent.bKeyDown && not complete)
                        {
                            jt1 = ToTitle(jt1); jt2 = ToTitle(jt2); o = ToCaps(o); d = ToCaps(d); cabin = ToCaps(cabin);
                            *rf = false;
                            if     (rf==&j1 )
                            {
                                if(jt1=="Domestic"||jt1=="International")
                                {
                                    rf = &j2;
                                    GOTO(82,11);
                                }
                                else
                                {
                                    jt1 = "";
                                    GOTO(82,9); cout<<"              ";
                                    GOTO(50,42); cout<<"Incorrect Journey Type!";
                                    Sleep(1500);
                                    GOTO(50,42); cout<<"                        ";
                                    GOTO(82,9);
                                }
                            }
                            else if(rf==&j2 )
                            {
                                if(jt2=="One-Way"||jt2=="Return")
                                {
                                    rf = &dp;
                                    GOTO(82,13);
                                }
                                else
                                {
                                    jt2 = "";
                                    GOTO(82,11); cout<<"              ";
                                    GOTO(50,42); cout<<"Incorrect Journey Type!";
                                    Sleep(1500);
                                    GOTO(50,42); cout<<"                        ";
                                    GOTO(82,11);
                                }
                            }
                            else if(rf==&dp )
                            {
                                rf = &ar; GOTO(82,15);
                            }
                            else if(rf==&ar )
                            {
                                if(jt1 == "Domestic")
                                {
                                    if(CheckDomRoute(o,d)&&CheckDomRoute(d,o))
                                    {
                                        rf = &dd;
                                        for(int i=0;i<14;i++)
                                        {
                                            if(DOM[i].Dest == o && DOM[i].Arrival == d)
                                                tr = DOM[i];
                                        }
                                        for(int i=0;i<14;i++)
                                        {
                                            if(DOM[i].Dest == d && DOM[i].Arrival == o)
                                                trr = DOM[i];
                                        }
                                        if(o=="DELHI"&&d=="MUMBAI")
                                        {
                                            tr = DOM[0];
                                            trr = DOM[6];
                                        }
                                        GOTO(50,18);SetConsoleColor(GREEN);cout<<"Route Available.";SetConsoleColor(TURQUOISE);
                                        if(tr == DOM[0])
                                        {
                                            int q = MessageBox(NULL,(RouteMsg(jt2)).c_str(),"Route Conformation",MB_YESNO);
                                            switch(q)
                                            {
                                            case IDYES:
                                                tr  = DOM[1]; trr = DOM[7]; break;
                                            case IDNO:
                                                tr  = DOM[0]; trr = DOM[6]; break;
                                            }
                                        }
                                        GOTO(0,46); tr.TrPrint();
                                        if(jt2 == "Return")
                                        {
                                            trr.Print(); GOTO(0,48);
                                            cout<<LC; for(int i=0;i<8;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<11;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<14;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<14;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<16;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<16;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<13;i++) cout<<HT; cout<<RC;
                                            GOTO(0,50); cout<<DLB;
                                            for(int i=0;i<8;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<11;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<14;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<14;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<16;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<16;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<13;i++) cout<<HT; cout<<DRB;
                                        }
                                        SetConsoleColor(WHITE); GOTO(82,21);
                                    }
                                    else
                                    {
                                        o = ""; d = "";
                                        GOTO(82,13); cout<<"              ";
                                        GOTO(82,15); cout<<"              ";
                                        GOTO(50,18); SetConsoleColor(RED); cout<<"No Such Route Available!";
                                        SetConsoleColor(WHITE);
                                        GOTO(50,42); cout<<"Incorrect Route!";
                                        Sleep(1500);
                                        GOTO(50,42); cout<<"                        ";
                                        GOTO(50,18); cout<<"                          ";
                                        GOTO(82,13);
                                        *rf = false;rf = &dp;*rf = true;
                                    }
                                }
                                if(jt1 == "International")
                                {
                                    if(CheckIntlRoute(o,d)&&CheckIntlRoute(d,o))
                                    {
                                        rf = &dd;
                                        for(int i=0;i<14;i++)
                                        {
                                            if(INTL[i].Dest == o && INTL[i].Arrival == d)
                                                tr = INTL[i];
                                        }
                                        for(int i=0;i<14;i++)
                                        {
                                            if(INTL[i].Dest == d && INTL[i].Arrival == o)
                                                trr = INTL[i];
                                        }
                                        GOTO(50,18);SetConsoleColor(GREEN);cout<<"Route Available.";SetConsoleColor(TURQUOISE);
                                        GOTO(0,46); tr.TrPrint();
                                        if(jt2 == "Return")
                                        {
                                            trr.Print(); GOTO(0,48);
                                            cout<<LC; for(int i=0;i<8;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<11;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<14;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<14;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<16;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<16;i++) cout<<HT; cout<<NC;
                                            for(int i=0;i<13;i++) cout<<HT; cout<<RC;
                                            GOTO(0,50); cout<<DLB;
                                            for(int i=0;i<8;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<11;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<14;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<14;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<16;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<16;i++) cout<<HT; cout<<UC;
                                            for(int i=0;i<13;i++) cout<<HT; cout<<DRB;
                                        }
                                        SetConsoleColor(WHITE); GOTO(82,21);
                                    }
                                    else
                                    {
                                        o = ""; d = "";
                                        GOTO(82,13); cout<<"              ";
                                        GOTO(82,15); cout<<"              ";
                                        GOTO(50,18); SetConsoleColor(RED); cout<<"No Such Route Available!";
                                        SetConsoleColor(WHITE);
                                        GOTO(50,42); cout<<"Incorrect Route!";
                                        Sleep(1500);
                                        GOTO(50,42); cout<<"                        ";
                                        GOTO(50,18); cout<<"                          ";
                                        GOTO(82,13);
                                        *rf = false;rf = &dp;*rf = true;
                                    }
                                }
                            }
                            else if(rf==&dd )
                            {
                                dep.Assign(ddp);
                                if(dep.Check()&&not ddp.empty())
                                {
                                    if(jt2 == "Return")
                                    {
                                        rf = &da; GOTO(82,23);
                                    }
                                    else
                                    {
                                        GOTO(82,23);cout<<"--/--/----";
                                        rf = &na;
                                        GOTO(82,29);
                                    }
                                }
                                else
                                {
                                    ddp = "";
                                    GOTO(82,21); cout<<"              ";
                                    GOTO(50,42); cout<<"Incorrect Departure Date!";
                                    Sleep(1500);
                                    GOTO(50,42); cout<<"                          ";
                                    GOTO(82,21);
                                }
                            }
                            else if(rf==&da )
                            {
                                arr.Assign(dar);
                                if(dep.Check(arr)&& not dar.empty())
                                {
                                    rf = &na; GOTO(82,29);
                                }
                                else
                                {
                                    dar = "";
                                    GOTO(82,23); cout<<"              ";
                                    GOTO(50,42); cout<<"Incorrect Return Date!";
                                    Sleep(1500);
                                    GOTO(50,42); cout<<"                        ";
                                    GOTO(82,23);
                                }
                            }
                            else if(rf==&na )
                            {
                                noa = Convert<int>(a);
                                if(a.empty()) noa = 0;
                                if(noa<10&&noa>0)
                                {
                                    rf = &nc; GOTO(82,31);
                                }
                                else
                                {
                                    a="";
                                    GOTO(82,29); cout<<"              ";
                                    GOTO(50,42); cout<<"Too many/less Adult Passengers!";
                                    Sleep(1500);
                                    GOTO(50,42); cout<<"                                ";
                                    GOTO(82,29);
                                }
                            }
                            else if(rf==&nc )
                            {
                                noc = Convert<int>(c);
                                if(c.empty()) noc = 0;
                                if(noc<10&&noc>=0)
                                {
                                    rf = &ni; GOTO(82,33);
                                }
                                else
                                {
                                    c="";
                                    GOTO(82,31); cout<<"              ";
                                    GOTO(50,42); cout<<"Too many/less Child Passengers!";
                                    Sleep(1500);
                                    GOTO(50,42); cout<<"                                ";
                                    GOTO(82,31);
                                }
                            }
                            else if(rf==&ni )
                            {
                                noi = Convert<int>(i);
                                if(i.empty()) noi = 0;
                                if(noi<10&&noi>=0)
                                {
                                    rf = &cbn; GOTO(82,37);
                                }
                                else
                                {
                                    i="";
                                    GOTO(82,33); cout<<"              ";
                                    GOTO(50,42); cout<<"Too many/less Infant Passengers!";
                                    Sleep(1500);
                                    GOTO(50,42); cout<<"                                  ";
                                    GOTO(82,33);
                                }
                            }
                            else if(rf==&cbn)
                            {
                                if(jt1 == "International")
                                {
                                    if(cabin=="ECONOMY"||cabin=="BUSINESS"||cabin=="FIRST")
                                    {
                                        int sx,sy;
                                        if(jt1=="Domestic")
                                        {
                                            if(cabin=="ECONOMY"){ sx = 9 , sy = 16; }
                                            else{ sx = 6 , sy = 6 ; }
                                        }
                                        else
                                        {
                                            if(cabin=="ECONOMY"){ sx = 12, sy = 18;}
                                            else if(cabin=="BUSINESS"){ sx = 6 , sy = 6 ;}
                                            else{ sx = 4 , sy = 2 ; }
                                        }
                                        Seat SR(cabin,dep.Value(),jt1,o,d,tr.Time(),sx,sy);
                                        Seat S1(cabin,arr.Value(),jt1,d,o,trr.Time(),sx,sy);
                                        SR.Create(); int ctr = SR.Count();
                                        S1.Create(); int ct1 = S1.Count();
                                        if(ctr>=noc+noi+noa&&(jt2=="Return"?(ct1>=noc+noi+noa):1))
                                        {
                                            rf = &complete;
                                            printonce = true;
                                            GOTO(50,26); SetConsoleColor(GREEN); cout<<"Seats Available.";
                                        }
                                        else
                                        {
                                            GOTO(50,26); SetConsoleColor(RED); cout<<"Seats Unavailable.";
                                            Sleep(1500);
                                            GOTO(50,26); SetConsoleColor(GRAY); cout<<"                  ";
                                            a="";c="";i="";ddp="";dar="";cabin="";
                                            GOTO(82,21); cout<<"              ";
                                            GOTO(82,23); cout<<"              ";
                                            GOTO(82,29); cout<<"              ";
                                            GOTO(82,31); cout<<"              ";
                                            GOTO(82,33); cout<<"              ";
                                            GOTO(82,37); cout<<"              ";
                                            rf = &dd;
                                        }
                                    }
                                    else
                                    {
                                        cabin="";
                                        GOTO(82,37); cout<<"              ";
                                        GOTO(50,42); cout<<"Incorrect Flight Cabin!";
                                        Sleep(1500);
                                        GOTO(50,42); cout<<"                         ";
                                        GOTO(82,37);
                                    }
                                }
                                else
                                {
                                    if(cabin=="ECONOMY"||cabin=="BUSINESS")
                                    {
                                        int sx,sy;
                                        if(jt1=="Domestic")
                                        {
                                            if(cabin=="ECONOMY"){ sx = 9 , sy = 16; }
                                            else{ sx = 6 , sy = 6 ; }
                                        }
                                        else
                                        {
                                            if(cabin=="ECONOMY"){ sx = 12, sy = 18;}
                                            else if(cabin=="BUSINESS"){ sx = 6 , sy = 6 ;}
                                            else{ sx = 4 , sy = 2 ; }
                                        }
                                        Seat SR(cabin,dep.Value(),jt1,o,d,tr.Time(),sx,sy);
                                        Seat S1(cabin,arr.Value(),jt1,d,o,trr.Time(),sx,sy);
                                        SR.Create(); int ctr = SR.Count();
                                        S1.Create(); int ct1 = S1.Count();
                                        if(ctr>=noc+noi+noa&&(jt2=="Return"?(ct1>=noc+noi+noa):true))
                                        {
                                            rf = &complete;
                                            printonce = true;
                                            GOTO(50,26); SetConsoleColor(GREEN); cout<<"Seats Available.";
                                        }
                                        else
                                        {
                                            GOTO(50,26); SetConsoleColor(RED); cout<<"Seats Unavailable.";
                                            Sleep(1500);
                                            GOTO(50,26); SetConsoleColor(GRAY); cout<<"                  ";
                                            a="";c="";i="";ddp="";dar="";cabin="";
                                            GOTO(82,21); cout<<"              ";
                                            GOTO(82,23); cout<<"              ";
                                            GOTO(82,29); cout<<"              ";
                                            GOTO(82,31); cout<<"              ";
                                            GOTO(82,33); cout<<"              ";
                                            GOTO(82,37); cout<<"              ";
                                            rf = &dd;
                                        }
                                    }
                                    else
                                    {
                                        cabin="";
                                        GOTO(82,37); cout<<"              ";
                                        GOTO(50,42); cout<<"Incorrect Flight Cabin!";
                                        Sleep(1500);
                                        GOTO(50,42); cout<<"                          ";
                                        GOTO(82,37);
                                    }
                                }
                            }
                            *rf = true;
                        }
                        else if(Rec.Event.KeyEvent.wVirtualKeyCode==VK_BACK&&Rec.Event.KeyEvent.bKeyDown&&cx>82 && not complete)
                        {
                            GOTO(csbi.dwCursorPosition.X-1,csbi.dwCursorPosition.Y);
                            cout<<" ";
                            GOTO(csbi.dwCursorPosition.X-1,csbi.dwCursorPosition.Y);
                            if(j1)
                            {
                                if(jt1.length()>1)
                                {
                                    jt1.resize(jt1.length()-1);
                                }
                                else
                                    jt1 = "";
                            }
                            if(j2)
                            {
                                if(jt2.length()>1)
                                {
                                    jt2.resize(jt2.length()-1);
                                }
                                else
                                    jt2 = "";
                            }
                            if(dp)
                            {
                                if(o.length()>1)
                                {
                                    o.resize(o.length()-1);
                                }
                                else
                                    o = "";
                            }
                            if(ar)
                            {
                                if(d.length()>1)
                                {
                                    d.resize(d.length()-1);
                                }
                                else
                                    d = "";
                            }
                            if(dd)
                            {
                                if(ddp.length()>1)
                                {
                                    ddp.resize(ddp.length()-1);
                                }
                                else
                                    ddp = "";
                            }
                            if(da)
                            {
                                if(dar.length()>1)
                                {
                                    dar.resize(dar.length()-1);
                                }
                                else
                                    dar = "";
                            }
                            if(na)
                            {
                                if(a.length()>1)
                                {
                                    a.resize(a.length()-1);
                                }
                                else
                                    a = "";
                            }
                            if(nc)
                            {
                                if(c.length()>1)
                                {
                                    c.resize(c.length()-1);
                                }
                                else
                                    c = "";
                            }
                            if(ni)
                            {
                                if(i.length()>1)
                                {
                                    i.resize(i.length()-1);
                                }
                                else
                                    i = "";
                            }
                            if(cbn)
                            {
                                if(cabin.length()>1)
                                {
                                    cabin.resize(cabin.length()-1);
                                }
                                else
                                    cabin = "";
                            }
                        }
                        break;
                    }
                case MOUSE_EVENT:
                    {
                        int x = Rec.Event.MouseEvent.dwMousePosition.X;
                        int y = Rec.Event.MouseEvent.dwMousePosition.Y;
                        switch(Rec.Event.MouseEvent.dwButtonState)
                        {
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            {
                                if((x>=C1[0]&&x<=C1[2])&&(y>=C1[1]&&y<=C1[3]) && not complete)
                                {
                                    GOTO(82, 9); cout<<"              ";
                                    GOTO(82,11); cout<<"              ";
                                    GOTO(82,13); cout<<"              ";
                                    GOTO(82,15); cout<<"              ";
                                    GOTO(82,21); cout<<"              ";
                                    GOTO(82,23); cout<<"              ";
                                    GOTO(82,29); cout<<"              ";
                                    GOTO(82,31); cout<<"              ";
                                    GOTO(82,33); cout<<"              ";
                                    GOTO(82,37); cout<<"              ";
                                    GOTO(50,18); cout<<"                                         ";
                                    GOTO(50,42); cout<<"                                         ";
                                    GOTO(50,26); cout<<"                                         ";
                                    GOTO(50,40); cout<<"                                         ";
                                    GOTO(0,46); for(int i=0;i<5;i++) { for(int i=0;i<100;i++) cout<<" "; }
                                    *rf = false; rf = &j1; GOTO(82,9); *rf = true;
                                    jt1 = ""; jt2 = ""; o = ""; d = ""; i = "";
                                    ddp = ""; dar = ""; cabin = ""; a = ""; c = "";
                                }
                                if((x>=C2[0]&&x<=C2[2])&&(y>=C2[1]&&y<=C2[3]))
                                {
                                    return;
                                }
                                if((x>=C3[0]&&x<=C3[2])&&(y>=C3[1]&&y<=C3[3]))
                                {
                                    if(complete)
                                    {
                                        int n = noa+noc+noi;
                                        p = new Passenger[noa+noc+noi];
                                        for(int i=0;i<n;i++)
                                        {
                                            p[i].Assign(jt1,jt2,cabin,PNR,dep,arr,tr,trr);
                                        }
                                        for(int i=0;i<noa;i++)
                                        {
                                            p[i].Type = "Adult";
                                        }
                                        for(int i=noa;i<noa+noc;i++)
                                        {
                                            p[i].Type = "Child";
                                        }
                                        for(int i=noa+noc;i<noa+noc+noi;i++)
                                        {
                                            p[i].Type = "Infant";
                                        }
                                        goto endit;
                                    }
                                    else
                                    {
                                        GOTO(50,42); cout<<"Incomplete Form. Resetting...";
                                        Sleep(1500); GOTO(50,42); cout<<"                               ";
                                        GOTO(82, 9); cout<<"              ";
                                        GOTO(82,11); cout<<"              ";
                                        GOTO(82,13); cout<<"              ";
                                        GOTO(82,15); cout<<"              ";
                                        GOTO(82,21); cout<<"              ";
                                        GOTO(82,23); cout<<"              ";
                                        GOTO(82,29); cout<<"              ";
                                        GOTO(82,31); cout<<"              ";
                                        GOTO(82,33); cout<<"              ";
                                        GOTO(82,37); cout<<"              ";
                                        GOTO(50,18); cout<<"                                         ";
                                        GOTO(50,42); cout<<"                                         ";
                                        GOTO(50,26); cout<<"                                         ";
                                        GOTO(50,40); cout<<"                                         ";
                                        GOTO(0,46); for(int i=0;i<5;i++) { for(int i=0;i<80;i++) cout<<""; }
                                        *rf = false; rf = &j1; GOTO(82,9); *rf = true;
                                        jt1 = ""; jt2 = ""; o = ""; d = ""; i = "";
                                        ddp = ""; dar = ""; cabin = ""; a = ""; c = "";
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
            endit:
                ctr++;
        }
        if(ctr==2) //0xFFFFFF
        {
            Button R1(2,1,1,17,WHITE,0,WHITE,0,""); Button R2(2,1,1,20,WHITE,0,WHITE,0,"");
            Fare data; data.Get(cabin,jt1,tr);
            fare:
            SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
            SetConsoleSize(100,56,289); system("cls"); SetBufferSize(100,56);
            SetConsoleColor(PINK);SplHead(cout,"FARE DETAILS",100);
            NEXT.Print(); RST.Print(); MENU.Print();
            SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
            SetConsoleColor(GREEN); GOTO(0,5); cout<<" Current Departure Route - For ";dep.Show();cout<<" in "<<cabin<<" class.";
            SetConsoleColor(WHITE); GOTO(0,6); tr.TrPrint();
            if(jt2=="Return")
            {
                SetConsoleColor(GREEN); GOTO(0,10); cout<<" Current Return Route    - For ";arr.Show();cout<<" in "<<cabin<<" class.";
                SetConsoleColor(WHITE); GOTO(0,11); trr.TrPrint();
            }
            SetConsoleColor(GREEN); GOTO(0,49);cout<<"   Special Instructions                     -: "; SetConsoleColor(WHITE);
            GOTO(0,15); SetConsoleColor(GREEN); cout<<"Fares Available for "<<o<<" -> "<<d<<"  -: "; SetConsoleColor(WHITE);
            R1.Print(); data.HIGH(); data.Print(6,17);
            R2.Print(); data.LOW (); data.Print(6,20);
            vector<SHORT> A1 = R1.Area(); vector<SHORT> A2 = R2.Area();
            SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
            while(true)
            {
                ReadConsoleInput(in,&Rec,1,&ev);
                switch(Rec.EventType)
                {
                case KEY_EVENT:
                    {
                        char ch = Rec.Event.KeyEvent.uChar.AsciiChar;
                        if(Rec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                        {
                            return;
                        }
                        break;
                    }
                case MOUSE_EVENT:
                    {
                        int x = Rec.Event.MouseEvent.dwMousePosition.X;
                        int y = Rec.Event.MouseEvent.dwMousePosition.Y;
                        switch(Rec.Event.MouseEvent.dwButtonState)
                        {
                        case FROM_LEFT_1ST_BUTTON_PRESSED:
                            {
                                if((x>=A1[0]&&x<=A1[2])&&(y>=A1[1]&&y<=A1[3]))
                                {
                                    done=true; data.HIGH(); R1.Click(); R2.Print();
                                    ::totalmoney = data.Invoice(noa,noc,noi,25,jt2,tr,trr);
                                    GOTO(50,49);cout<<"Fare Details Acquired. Press '->' to Continue";
                                    for(int i=0;i<noc+noa+noi;i++) p[i].State = HIGH;
                                    for(int i=0;i<noc+noi+noa;i++) p[i].PFare = data.GetFare(p[i].Type);
                                }
                                if((x>=A2[0]&&x<=A2[2])&&(y>=A2[1]&&y<=A2[3]))
                                {
                                    done=true; data.LOW (); R2.Click(); R1.Print();
                                    ::totalmoney = data.Invoice(noa,noc,noi,25,jt2,tr,trr);
                                    GOTO(50,49);cout<<"Fare Details Acquired. Press '->' to Continue";
                                    for(int i=0;i<noc+noa+noi;i++) p[i].State = LOW;
                                    for(int i=0;i<noc+noi+noa;i++) p[i].PFare = data.GetFare(p[i].Type);
                                }
                                if((x>=C1[0]&&x<=C1[2])&&(y>=C1[1]&&y<=C1[3]))
                                {
                                    system("cls");
                                    goto fare;
                                }
                                if((x>=C2[0]&&x<=C2[2])&&(y>=C2[1]&&y<=C2[3]))
                                {
                                    system("cls");
                                    return;
                                }
                                if((x>=C3[0]&&x<=C3[2])&&(y>=C3[1]&&y<=C3[3]))
                                {
                                    if( done )
                                    {
                                        done = false;
                                        goto endit2;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
            endit2:
                ctr++;
        }
        if(ctr==3) //0xFFFFFF
        {
            Date DOB; Date Expiry; Date Issue; bool sel[18]; int chs = 0, ct = 0;
            for(int i=0;i<18;i++) sel[i]=false; sel[chs] = true;
            SetConsoleSize(100,56,289); SetConsoleColor(BGWHITE); ClearScreen(100,56); SetBufferSize(100,56);
            while(ct<noc+noi+noa)
            {
                SetConsoleMode(in,ENABLE_WINDOW_INPUT|ENABLE_MOUSE_INPUT);
                system("cls");SetConsoleColor(BGGREEN|BROWN);SplHead(cout,"PASSENGER INFORMATION",100);
                string fname="",mname="",lname="",dob="",gender="",tvltype="",tvlno="",
                       nation="",exp="",meal="",reqmt="",email="",no="",vno="",vd="",vis="";
                SetConsoleColor(BGWHITE); GOTO(0, 4); SetConsoleColor(BLUE|BGWHITE);
                cout<<"   -> Please ensure that the details filled below are of the travelling passengers only. \n";
                cout<<"   -> Fields marked * are mandatory."; RST.Recolor(PINK,BGWHITE,BLACK,BGWHITE);
                NEXT.Recolor(RED,BGWHITE,BLACK,BGWHITE); MENU.Recolor(BLUE,BGWHITE,BLACK,BGWHITE);
                NEXT.Print(); MENU.Print(); RST.Print(); SetConsoleColor(BGWHITE|RED); done = false;
                C1 = RST.Area(); C2 = MENU.Area(); C3 = NEXT.Area();
                RST.Recolor(PINK,0,WHITE,0); NEXT.Recolor(RED,0,WHITE,0); MENU.Recolor(BLUE,0,WHITE,0);
                GOTO(0, 7); cout<<"  \t\t\t\t\tPassenger "<<ct+1<<", "<<p[ct].Type;SetConsoleColor(BGWHITE);
                GOTO(0, 9); cout<<"* First Name                            \t\t\t";GenFormBoxSC(80, 9,15);
                GOTO(0,11); cout<<"  Middle Name                           \t\t\t";GenFormBoxBC(80,11,15);
                GOTO(0,13); cout<<"* Last Name                             \t\t\t";GenFormBoxEC(80,13,15);
                GOTO(0,17); cout<<"* Date of Birth                         \t\t\t(DD/MM/YYYY)";GenFormBoxSC(80,17,15);
                GOTO(0,19); cout<<"* Gender (Male/Female)                  \t\t\t";GenFormBoxEC(80,19,15);
                GOTO(0,33); cout<<"  Meal Preference                       \t\t\t";GOTO(0,34); cout<<"->";
                GOTO(0,36); cout<<"  Special Requirement (Disabled, etc)   \t\t\t";GOTO(0,37); cout<<"->";
                GOTO(0,39); cout<<"* Contact Number                        \t\t\t(Number,+,-)";GenFormBox  (80,39,15);
                GOTO(0,41); cout<<"* Email                                 \t\t\t(Email Type)";GOTO(0,42); cout<<"->";
                if(jt1 == "International")
                {
                    GOTO(0,23); cout<<"* Travel Document (Passport/National ID)\t\t\t";GenFormBoxSC(80,23,15);
                    GOTO(0,25); cout<<"* Document (Passport/National ID) Number\t\t\t(AlNum Type)";GenFormBoxBC(80,25,15);
                    GOTO(0,27); cout<<"* Document Expiry                       \t\t\t(DD/MM/YYYY)";GenFormBoxEC(80,27,15);
                    GOTO(0,31); cout<<"* Nationality                           \t\t\t";GenFormBox  (80,31,15);
                    GOTO(0,44); cout<<"* Visa Number                             \t\t\t(Number,-,/)";GenFormBoxSC(80,44,15);
                    GOTO(0,46); cout<<"* Visa Expiry Date                        \t\t\t(DD/MM/YYYY)";GenFormBoxBC(80,46,15);
                    GOTO(0,48); cout<<"* Location Issued in Visa                 \t\t\t";GenFormBoxEC(80,48,15);
                } GOTO(82,9);
                while(true)
                {
                    GetDefault();SetConsoleColor(BGWHITE|BROWN); SetConsoleMode(in,ENABLE_WINDOW_INPUT|ENABLE_MOUSE_INPUT);
                    SetCursor(true); ReadConsoleInput(in,&Rec,1,&ev);
                    switch(Rec.EventType)
                    {
                    case KEY_EVENT:
                        {
                            char ch = Rec.Event.KeyEvent.uChar.AsciiChar; GetDefault();
                            int cx = csbi.dwCursorPosition.X;
                            bool appl = (sel[9]||sel[10]||sel[12])?(cx>3):(cx>82);
                            if(Rec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                            {
                                system("cls"); return;
                            }
                            if(Rec.Event.KeyEvent.wVirtualKeyCode==VK_RETURN&&Rec.Event.KeyEvent.bKeyDown&&not done)
                            {
                                vis = ToCaps(vis); nation = ToTitle(nation); tvltype = ToTitle(tvltype); gender = ToTitle(gender);
                                sel[chs] = false;
                                if(chs == 0)
                                {
                                    if(!fname.empty()) {chs++; GOTO(82,11);}
                                    else {MessageBox(NULL,"Empty Field - First Name !!!","Error",MB_OK); fname = "";
                                          GOTO(82,9); cout<<"              ";GOTO(82,9);}
                                }
                                else if(chs == 1)
                                {
                                    chs++; GOTO(82,13);
                                }
                                else if(chs == 2)
                                {
                                    if(!lname.empty()) {chs++; GOTO(82,17);}
                                    else {MessageBox(NULL,"Empty Field - Last Name !!!","Error",MB_OK); lname = "";
                                          GOTO(82,13); cout<<"              "; GOTO(82,13);}
                                }
                                else if(chs == 3)
                                {
                                    DOB.Assign(dob);
                                    bool redo = false;
                                    if(not DOB.Future())
                                    {
                                        if(p[ct].Type=="Infant")
                                        {
                                            if(DOB.Check(2)) {chs++; GOTO(82,19);}
                                            else redo = true;
                                        }
                                        else if(p[ct].Type=="Child")
                                        {
                                            if(DOB.Check(12)) {chs++; GOTO(82,19);}
                                            else redo = true;
                                        }
                                        else
                                        {
                                            chs++; GOTO(82,19);
                                        }
                                    }
                                    else redo = true;
                                    if(redo) {MessageBox(NULL,("Incorrect Date Given for DOB of "+p[ct].Type+" Passenger !!!")
                                              .c_str(),"Error",MB_OK); dob=""; GOTO(82,17); cout<<"              "; GOTO(82,17);}
                                }
                                else if(chs == 4)
                                {
                                    if(!gender.empty()||gender=="Male"||gender=="Female"||gender=="Other")
                                    {
                                        if(jt1=="International")
                                        {
                                            chs++; GOTO(82,23);
                                        }
                                        else
                                        {
                                            chs = 9; GOTO(3,34);
                                        }
                                    }
                                    else {MessageBox(NULL,"Empty Field - Gender !!!","Error",MB_OK);
                                          gender = ""; GOTO(82,19); cout<<"              "; GOTO(82,19);}
                                }
                                else if(chs == 5)
                                {
                                    if(tvltype=="Passport"||tvltype =="National ID"){chs++; GOTO(82,25);}
                                    else {MessageBox(NULL,"Incorrect Document Type !!!\nUse only Passport or National ID.",
                                          "Error",MB_OK); tvltype = ""; GOTO(82,23); cout<<"              "; GOTO(82,23);}
                                }
                                else if(chs == 6)
                                {
                                    if(!tvlno.empty() && tvlno.length()>9 && ValidPNR(tvlno)){chs++; GOTO(82,27);}
                                    else {MessageBox(NULL,"Incorrect/Empty Document Number !!!","Error",MB_OK);
                                          tvlno = ""; GOTO(82,25); cout<<"              "; GOTO(82,25);}
                                }
                                else if(chs == 7)
                                {
                                    Date Today; Today.Assign(DisplayTime()); Expiry.Assign(exp);
                                    if(Expiry>Today){chs++; GOTO(82,31);}
                                    else {MessageBox(NULL,"Incorrect Expiry Date !!!","Error",MB_OK);
                                          exp = ""; GOTO(82,27); cout<<"              "; GOTO(82,27);}
                                }
                                else if(chs == 8)
                                {
                                    if(!nation.empty()){chs++; GOTO(3,34);}
                                    else {MessageBox(NULL,"Empty Field - Nationality !!!","Error",MB_OK);
                                          nation = ""; GOTO(82,31); cout<<"              "; GOTO(82,31);}
                                }
                                else if(chs == 9)
                                {
                                    if(meal.empty()) meal = "None";
                                    chs++; GOTO(3,37);
                                }
                                else if(chs == 10)
                                {
                                    if(reqmt.empty()) reqmt = "None";
                                    chs++; GOTO(82,39);
                                }
                                else if(chs == 11)
                                {
                                    bool var = (nation=="Indian")?(no.length()==10):true;
                                    if(Contact(no)&& not no.empty()){chs++; GOTO(3,42);}
                                    else {MessageBox(NULL,"Incorrect Contact Number !!!","Error",MB_OK);
                                          no = ""; GOTO(82,39); cout<<"              "; GOTO(82,39);}
                                }
                                else if(chs == 12)
                                {
                                    if(EMail(email))
                                    {
                                        if(jt1=="International") { chs++; GOTO(82,44); }
                                        else { chs = 0; SetCursor(false); done = true;
                                               MessageBox(NULL,"Data Recording Complete. \nPress '->' To Continue",
                                               "Completion",MB_OK); }
                                    }
                                    else {MessageBox(NULL,"Incorrect EMail ID !!!","Error",MB_OK);
                                           email = ""; GOTO(3,42);
                                          cout<<"                                                                "; GOTO(3,42);}
                                }
                                else if(chs == 13)
                                {
                                    if(ValidPNR(vno)) { chs++; GOTO(82,46) ; }
                                    else {MessageBox(NULL,"Incorrect Visa Number !!!","Error",MB_OK);
                                          vno = ""; GOTO(82,44); cout<<"              "; GOTO(82,44);}
                                }
                                else if(chs == 14)
                                {
                                    Issue.Assign(vd);
                                    if(Issue>=dep) { chs++; GOTO(82,48) ; }
                                    else {MessageBox(NULL,"Incorrect Visa Expiry !!!","Error",MB_OK);
                                          vd = ""; GOTO(82,46); cout<<"              "; GOTO(82,46);}
                                }
                                else if(chs == 15)
                                {
                                    if(vis == tr.Arrival)
                                    { chs = 0; SetCursor(false); done = true;
                                      MessageBox(NULL,"Data Recording Complete. \nPress '->' To Continue",
                                      "Completion",MB_OK);}
                                    else {MessageBox(NULL,"Incorrect Visa Location !!!","Error",MB_OK);
                                          vis = ""; GOTO(82,48); cout<<"              "; GOTO(82,48);}
                                }
                                sel[chs] = true;
                            }
                            if(isprint(ch)&&Rec.Event.KeyEvent.bKeyDown&&cx<95&&not done)
                            {
                                if(sel[0]){fname+=ch; GOTO(81+fname.length(),9);cout<<ch;}
                                if(sel[1]){mname+=ch; GOTO(81+mname.length(),11);cout<<ch;}
                                if(sel[2]){lname+=ch; GOTO(81+lname.length(),13);cout<<ch;}
                                if(sel[3]){dob+=ch; GOTO(81+dob.length(),17);cout<<ch;}
                                if(sel[4]){gender+=ch; GOTO(81+gender.length(),19);cout<<ch;}
                                if(sel[6]){tvlno+=ch; GOTO(81+tvlno.length(),25);cout<<ch;}
                                if(sel[5]){tvltype+=ch; GOTO(81+tvltype.length(),23);cout<<ch;}
                                if(sel[7]){exp+=ch; GOTO(81+exp.length(),27);cout<<ch;}
                                if(sel[8]){nation+=ch; GOTO(81+nation.length(),31);cout<<ch;}
                                if(sel[9]){meal+=ch; GOTO(2+meal.length(),34);cout<<ch;}
                                if(sel[10]){reqmt+=ch; GOTO(2+reqmt.length(),37);cout<<ch;}
                                if(sel[11]){no+=ch; GOTO(81+no.length(),39);cout<<ch;}
                                if(sel[12]){email+=ch; GOTO(2+email.length(),42);cout<<ch;}
                                if(sel[13]){vno+=ch; GOTO(81+vno.length(),44);cout<<ch;}
                                if(sel[14]){vd+=ch; GOTO(81+vd.length(),46);cout<<ch;}
                                if(sel[15]){vis+=ch; GOTO(81+vis.length(),48);cout<<ch;}
                            }
                            if(Rec.Event.KeyEvent.wVirtualKeyCode==VK_BACK&&Rec.Event.KeyEvent.bKeyDown&&not done&&(appl))
                            {
                                GOTO(csbi.dwCursorPosition.X-1,csbi.dwCursorPosition.Y);
                                cout<<" "; GOTO(csbi.dwCursorPosition.X-1,csbi.dwCursorPosition.Y);
                                if(chs==0)
                                {
                                    if(fname.length()>1) { fname.resize(fname.length()-1); }
                                    else fname = "";
                                }
                                if(chs==1)
                                {
                                    if(mname.length()>1) { mname.resize(mname.length()-1); }
                                    else mname = "";
                                }
                                if(chs==2)
                                {
                                    if(lname.length()>1) { lname.resize(lname.length()-1); }
                                    else lname = "";
                                }
                                if(chs==3)
                                {
                                    if(dob.length()>1) { dob.resize(dob.length()-1); }
                                    else dob = "";
                                }
                                if(chs==4)
                                {
                                    if(gender.length()>1) { gender.resize(gender.length()-1); }
                                    else gender = "";
                                }
                                if(chs==6)
                                {
                                    if(tvlno.length()>1) { tvlno.resize(tvlno.length()-1); }
                                    else tvlno = "";
                                }
                                if(chs==5)
                                {
                                    if(tvltype.length()>1) { tvltype.resize(tvltype.length()-1); }
                                    else tvltype = "";
                                }
                                if(chs==7)
                                {
                                    if(exp.length()>1) { exp.resize(exp.length()-1); }
                                    else exp = "";
                                }
                                if(chs==8)
                                {
                                    if(nation.length()>1) { nation.resize(nation.length()-1); }
                                    else nation = "";
                                }
                                if(chs==9)
                                {
                                    if(meal.length()>1) { meal.resize(meal.length()-1); }
                                    else meal = "";
                                }
                                if(chs==10)
                                {
                                    if(reqmt.length()>1) { reqmt.resize(reqmt.length()-1); }
                                    else reqmt = "";
                                }
                                if(chs==11)
                                {
                                    if(no.length()>1) { no.resize(no.length()-1); }
                                    else no = "";
                                }
                                if(chs==12)
                                {
                                    if(email.length()>1) { email.resize(email.length()-1); }
                                    else email = "";
                                }
                                if(chs==15)
                                {
                                    if(vis.length()>1) { vis.resize(vis.length()-1); }
                                    else vis = "";
                                }
                                if(chs==14)
                                {
                                    if(vd.length()>1) { vd.resize(vd.length()-1); }
                                    else vd = "";
                                }
                                if(chs==13)
                                {
                                    if(vno.length()>1) { vno.resize(vno.length()-1); }
                                    else vno = "";
                                }
                            }
                        }
                    case MOUSE_EVENT:
                        {
                            int x = Rec.Event.MouseEvent.dwMousePosition.X;
                            int y = Rec.Event.MouseEvent.dwMousePosition.Y;
                            switch(Rec.Event.MouseEvent.dwButtonState)
                            {
                            case FROM_LEFT_1ST_BUTTON_PRESSED:
                                {
                                    if((x>=C1[0]&&x<=C1[2])&&(y>=C1[1]&&y<=C1[3])&&not done)
                                    {
                                        GOTO(82, 9); cout<<"              ";
                                        GOTO(82,11); cout<<"              ";
                                        GOTO(82,13); cout<<"              ";
                                        GOTO(82,17); cout<<"              ";
                                        GOTO(82,19); cout<<"              ";
                                        GOTO(82,23); cout<<"              ";
                                        GOTO(82,25); cout<<"              ";
                                        GOTO(82,27); cout<<"              ";
                                        GOTO(82,31); cout<<"              ";
                                        GOTO(3,34); cout<<"                                                                     ";
                                        GOTO(3,37); cout<<"                                                                     ";
                                        GOTO(82,39); cout<<"              ";
                                        GOTO(3,42); cout<<"                                                                     ";
                                        GOTO(82,44); cout<<"              ";
                                        GOTO(82,46); cout<<"              ";
                                        GOTO(82,48); cout<<"              ";
                                        GOTO(82,9);
                                        fname="",mname="",lname="",dob="",gender="",tvltype="",tvlno="",
                                        nation="",exp="",meal="",reqmt="",email="",no="",vno="",vd="",vis="";
                                        sel[chs] = false; chs = 0; sel[chs] = true;
                                    }
                                    if((x>=C2[0]&&x<=C2[2])&&(y>=C2[1]&&y<=C2[3]))
                                    {
                                        return;
                                    }
                                    if((x>=C3[0]&&x<=C3[2])&&(y>=C3[1]&&y<=C3[3]))
                                    {
                                        if(done)
                                        {
                                            done = false; a[chs] = true;
                                            p[ct].Register(fname,mname,lname,gender,email,no,DOB,meal,reqmt);
                                            p[ct].Documents(tvlno,tvltype,Expiry,vis,vno,Issue,nation);
                                            goto edit2;
                                        }
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                edit2:
                    ct++;
            }
            ctr++;
        }
        if(ctr==4) //OxFFFFFF
        {
            SetConsoleColor(BLACK); ClearScreen(100,56);
            Button A(46,45,0,3,WHITE,0,WHITE,0,""), HD(46,1,0,47,WHITE,0,PINK,0,cabin+" CLASS SEATS - "+jt1+" Flight");
            int sx, sy, cx=0, cy=0, sctr = noc+noa, sw=3; SetCursor(false); int pctr = 0; int mctr=0;
            if(jt1=="Domestic")
            {
                if(cabin=="ECONOMY")
                { sx = 9 , sy = 16; cx = 12; cy = 10 ;}
                else
                { sx = 6 , sy = 6 ; cx = 15; cy = 18;}
            }
            else
            {
                if(cabin=="ECONOMY")
                { sx = 12, sy = 18; cx = 8 ; cy = 9 ;}
                else if(cabin=="BUSINESS")
                { sx = 6 , sy = 6 ; cx = 15; cy = 18;}
                else
                { sx = 4 , sy = 2 ; cx = 16; cy = 24; sw = 1;}
            }
            system("cls"); SetConsoleSize(100,50,289); SetBufferSize(100,50);
            SetConsoleColor(TURQUOISE); SplHead(cout,"SEAT ALLOCATION",100);
            A.Print(); HD.Print(); NEXT.Move(0,-6); NEXT.Print();
            MENU.Move(10,-6); MENU.Print(); C3 = NEXT.Area(); C2 = MENU.Area();
            Seat SRD(cabin,dep.Value(),jt1,o,d,tr.Time(),sx,sy); SRD.Create();
            vector<Coordinate> Pos = SRD.Print(cx,cy,sw);
            SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
            SetConsoleColor(GRAY);GOTO(60,7 );cout<<"Outbound - "<<dep.Value()<<" - ";
            SetConsoleColor(GRAY);GOTO(60,17);cout<<"Instructions - ";
            SetConsoleColor(WHITE);
            GOTO(63,19); cout<<"Double Click the Seat : ";
            GOTO(63,20); cout<<"Confirm the Booking.";
            GOTO(63,22); cout<<"Single Click the Seat : ";
            GOTO(63,23); cout<<"View the Seat Number.";
            GOTO(63,25); cout<<"Hover the Mouse on the Seat : ";
            GOTO(63,26); cout<<"View the Seat Number.";
            while(true)
            {
                SetConsoleColor(WHITE);
                GOTO(63, 9);cout<<"Total Seats Left   - "<<SRD.Count();
                GOTO(63,11);cout<<"Seats to be Booked - "<<right<<setw(len(SRD.Count()))<<sctr;
                if(sctr!=0) { GOTO(63,13);cout<<"Booking Seat for Passenger "<<pctr+1<<endl; }
                if(sctr == 0)
                {
                    GOTO(63,14);cout<<"                                 "<<endl;
                    SetConsoleColor(GRAY); GOTO(58,33); if(noi>0) cout<<noi<<" Bassinet Seat(s) will be installed.";
                    SetConsoleColor(YELLOW); GOTO(65,37); cout<<"Seat Booking Complete.";
                    GOTO(66,39); cout<<"Press -> to Continue.";
                }
                ReadConsoleInput(in,&Rec,1,&ev);
                switch(Rec.EventType)
                {
                case KEY_EVENT:
                    {
                        if(Rec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                        {
                            system("cls"); return;
                        }
                    }
                case MOUSE_EVENT:
                    {
                       int x = Rec.Event.MouseEvent.dwMousePosition.X;
                       int y = Rec.Event.MouseEvent.dwMousePosition.Y;
                       Coordinate CP = {x,y};
                       switch(Rec.Event.MouseEvent.dwEventFlags)
                       {
                       case MOUSE_MOVED:
                       {
                            if(find(Pos.begin(),Pos.end(),CP)!=Pos.end())
                            {
                                vector<Coordinate>::iterator it = find(Pos.begin(),Pos.end(),CP);
                                SRD.Print(cx,cy,sw);
                                SetConsoleColor(BLUE); GOTO(x,y); cout<<BLK;
                                for(int i=0;i<sy;i++)
                                {
                                    for(int j=0;j<sx;j++)
                                    {
                                        if(*it == Pos[(sx*i)+j])
                                        {
                                            SetConsoleColor(WHITE); GOTO(68,42); cout<<"Seat Number - "<<SRD.SeatNo(i+1,j+1);
                                        }
                                    }
                                }
                            }
                            else
                            {
                                SRD.Print(cx,cy,sw);
                                SetConsoleColor(WHITE); GOTO(65,42); cout<<"                              ";
                            }
                            break;
                       }
                       case 0:
                            {
                                if(Rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                                {
                                     if(x>=C3[0]&&x<=C3[2] && y>=C3[1]&&y<=C3[3])
                                     {
                                         if(sctr==0) goto endit3;
                                     }
                                     if(x>=C2[0]&&x<=C2[2] && y>=C2[1]&&y<=C2[3])
                                     {
                                         system("cls");
                                         return;
                                     }
                                }
                                break;
                            }
                       case DOUBLE_CLICK:
                            {
                                if(find(Pos.begin(),Pos.end(),CP)!=Pos.end() && sctr>0)
                                {
                                    SRD.Print(cx,cy,sw);
                                    SetConsoleColor(GRAY); GOTO(x,y); cout<<BLK;
                                    vector<Coordinate>::iterator it = find(Pos.begin(),Pos.end(),CP);
                                    for(int i=0;i<sy;i++)
                                    {
                                        for(int j=0;j<sx;j++)
                                        {
                                            if(*it == Pos[(sx*i)+j])
                                            {
                                                if(not SRD.Booked(i+1,j+1))
                                                {
                                                    SRD.Book(i+1,j+1);
                                                    p[pctr].AllocSeat(SRD.SeatNo(i+1,j+1));
                                                    Coordinate T(i+1,j+1);
                                                    SeatsBookedToday[mctr] = T;
                                                    pctr++; sctr--; mctr++; break;
                                                }
                                                else
                                                {
                                                    Coordinate T(i+1,j+1);
                                                    if(find(SeatsBookedToday.begin(),SeatsBookedToday.end(),T)!=SeatsBookedToday.end())
                                                    {
                                                        SRD.Unbook(i+1,j+1);
                                                        SeatsBookedToday.erase(remove(SeatsBookedToday.begin(),
                                                                               SeatsBookedToday.end(),T),SeatsBookedToday.end());
                                                        mctr--; pctr--; sctr++;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
            }
            endit3:
            if(jt2!="Return") goto btl;
            if(jt2=="Return")
            {
                system("cls"); SetConsoleSize(100,50,289); SetBufferSize(100,50);
                SetConsoleColor(TURQUOISE); SplHead(cout,"SEAT ALLOCATION",100);
                A.Print(); HD.Print(); NEXT.Print(); MENU.Print();
                Seat SRR(cabin,arr.Value(),jt1,d,o,trr.Time(),sx,sy); SRR.Create();
                Pos = SRR.Print(cx,cy,sw); pctr = 0; sctr = noc+noa;
                SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
                SetConsoleColor(GRAY);GOTO(60,7 );cout<<"Inbound - "<<arr.Value()<<" - ";
                SetConsoleColor(GRAY);GOTO(60,17);cout<<"Instructions - ";
                SetConsoleColor(WHITE);
                GOTO(63,19); cout<<"Double Click the Seat : ";
                GOTO(63,20); cout<<"Confirm the Booking.";
                GOTO(63,22); cout<<"Single Click the Seat : ";
                GOTO(63,23); cout<<"View the Seat Number.";
                GOTO(63,25); cout<<"Hover the Mouse on the Seat : ";
                GOTO(63,26); cout<<"View the Seat Number.";
                while(true)
                {
                    SetConsoleColor(WHITE);
                    GOTO(63, 9);cout<<"Total Seats Left   - "<<SRR.Count();
                    GOTO(63,11);cout<<"Seats to be Booked - "<<right<<setw(len(SRR.Count()))<<sctr;
                    if(sctr!=0) { GOTO(63,13);cout<<"Booking Seat for Passenger "<<pctr+1<<endl; }
                    if(sctr == 0)
                    {
                        GOTO(63,14);cout<<"                                 "<<endl;
                        SetConsoleColor(GRAY); GOTO(58,33); if(noi>0) cout<<noi<<" Bassinet Seat(s) will be installed.";
                        SetConsoleColor(YELLOW); GOTO(65,37); cout<<"Seat Booking Complete.";
                        GOTO(66,39); cout<<"Press -> to Continue.";
                    }
                    ReadConsoleInput(in,&Rec,1,&ev);
                    switch(Rec.EventType)
                    {
                    case KEY_EVENT:
                        {
                            if(Rec.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
                            {
                                system("cls"); return;
                            }
                        }
                    case MOUSE_EVENT:
                        {
                           int x = Rec.Event.MouseEvent.dwMousePosition.X;
                           int y = Rec.Event.MouseEvent.dwMousePosition.Y;
                           Coordinate CP = {x,y};
                           switch(Rec.Event.MouseEvent.dwEventFlags)
                           {
                           case MOUSE_MOVED:
                           {
                                if(find(Pos.begin(),Pos.end(),CP)!=Pos.end())
                                {
                                    vector<Coordinate>::iterator it = find(Pos.begin(),Pos.end(),CP);
                                    SRR.Print(cx,cy,sw);
                                    SetConsoleColor(BLUE); GOTO(x,y); cout<<BLK;
                                    for(int i=0;i<sy;i++)
                                    {
                                        for(int j=0;j<sx;j++)
                                        {
                                            if(*it == Pos[(sx*i)+j])
                                            {
                                                SetConsoleColor(WHITE); GOTO(68,42); cout<<"Seat Number - "<<SRR.SeatNo(i+1,j+1);
                                            }
                                        }
                                    }
                                }
                                else
                                {
                                    SRR.Print(cx,cy,sw);
                                    SetConsoleColor(WHITE); GOTO(65,42); cout<<"                              ";
                                }
                                break;
                           }
                           case 0:
                                {
                                    if(Rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                                    {
                                         if(x>=C3[0]&&x<=C3[2] && y>=C3[1]&&y<=C3[3])
                                         {
                                             if(sctr==0) goto btl;
                                         }
                                         if(x>=C2[0]&&x<=C2[2] && y>=C2[1]&&y<=C2[3])
                                         {
                                             system("cls");
                                             return;
                                         }
                                    }
                                    break;
                                }
                           case DOUBLE_CLICK:
                                {
                                    if(find(Pos.begin(),Pos.end(),CP)!=Pos.end() && sctr>0)
                                    {
                                        SRR.Print(cx,cy,sw);
                                        SetConsoleColor(GRAY); GOTO(x,y); cout<<BLK;
                                        vector<Coordinate>::iterator it = find(Pos.begin(),Pos.end(),CP);
                                        for(int i=0;i<sy;i++)
                                        {
                                            for(int j=0;j<sx;j++)
                                            {
                                                if(*it == Pos[(sx*i)+j])
                                                {
                                                    if(not SRR.Booked(i+1,j+1))
                                                    {
                                                        SRR.Book(i+1,j+1);
                                                        p[pctr].AllocReturnSeat(SRR.SeatNo(i+1,j+1));
                                                        Coordinate T(i+1,j+1);
                                                        SeatsBookedToday[mctr] = T;
                                                        pctr++; sctr--; mctr++; break;

                                                    }
                                                    else
                                                    {
                                                        Coordinate T(i+1,j+1);
                                                        if(find(SeatsBookedToday.begin(),SeatsBookedToday.end(),T)!=SeatsBookedToday.end())
                                                        {
                                                            SRR.Unbook(i+1,j+1);
                                                            SeatsBookedToday.erase(remove(SeatsBookedToday.begin(),
                                                                                   SeatsBookedToday.end(),T),SeatsBookedToday.end());
                                                            mctr--; pctr--; sctr++;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            ctr++;
            btl : ctr++;
        }
        if(ctr==5) //0xFFFFFF
        {
            system("cls"); SetConsoleSize(100,56,289,false); SetBufferSize(100,150); SetConsoleColor(BGDARK_TURQUOISE|WHITE);
            SplHead(cout,"BOOKING SUMMARY",100);SetConsoleColor(BLACK);
            SetConsoleColor(GREEN); GOTO(0,5); cout<<" Current Departure Route - For ";dep.Show();cout<<" in "<<cabin<<" class.";
            SetConsoleColor(WHITE); GOTO(0,6); tr.TrPrint();
            if(jt2=="Return")
            {
                SetConsoleColor(GREEN); GOTO(0,10); cout<<" Current Return Route    - For ";arr.Show();cout<<" in "<<cabin<<" class.";
                SetConsoleColor(WHITE); GOTO(0,11); trr.TrPrint();
            }
            SetConsoleColor(YELLOW); GetDefault(); int y = csbi.dwCursorPosition.Y;
            Fare data; data.Get(cabin,jt1,tr); if(p[0].State) data.HIGH(); else data.LOW(); data.Invoice(noa,noc,noi,y+1,jt2,tr,trr);
            SetConsoleColor(TURQUOISE); cout<<"\n List of Passengers Travelling -: \n"; SetConsoleColor(WHITE); GetDefault();
            GOTO(0,csbi.dwCursorPosition.Y+1); Head(cout," SNo. |        Passenger Name        |   Type   |         Route         | Seat |   Ticket Number  ",100);
            GOTO(0,csbi.dwCursorPosition.Y+4); for(int i=0;i<100;i++) cout<<"-";
            srand(time(nullptr)); for(int i=0;i<noc+noa+noi;i++) { p[i].GenTicket(); }
            for(int i=0;i<noc+noi+noa;i++)
            {
                cout<<right<<"| "<<setw(3)<<i+1<<"  ";p[i].Print();
            }
            if(jt2=="Return")
            {
                for(int i=0;i<noc+noi+noa;i++)
                {
                    cout<<right<<"| "<<setw(3)<<i+1<<"  ";p[i].Print(0);
                }
            }
            SetConsoleColor(TURQUOISE); cout<<"\n CURRENT OFFERED MODES OF PAYMENT - ";
            SetConsoleColor(WHITE); cout<<"Online Banking, Credit Card, Debit Card\n\n";
            GetDefault(); int Ref = csbi.dwCursorPosition.Y;
            string mode,name,no1,pw,no2; SetConsoleMode(in,ConsoleMode);
            while(true)
            {
                SetCursor(true);
                GOTO(0,Ref); cout<<" Mode of Payment    -   "; getline(cin,mode,'\n');
                mode = ToTitle(mode);
                if(mode=="Online Banking"||mode=="Credit Card"||mode=="Debit Card")
                {
                    if(mode=="Credit Card")
                    {
                        GOTO(0,Ref+2); cout<<" Name of Holder         -- "; GenFormBoxSC(75,Ref+2,20);
                        GOTO(0,Ref+4); cout<<" Credit Card Number     -- "; GenFormBoxBC(75,Ref+4,20);
                        GOTO(0,Ref+6); cout<<" Credit Card Expiry     -- "; GenFormBoxBC(75,Ref+6,20);
                        GOTO(0,Ref+8); cout<<" 3-Digit CVV            -- "; GenFormBoxEC(75,Ref+8,20);
                        SetConsoleColor(GRAY);
                        while(true)
                        {
                            GOTO(77,Ref+2); getline(cin,name);
                            if(not name.empty()) break;
                            else {GOTO(77,Ref+2); cout<<"                  "; GOTO(77,Ref+2);}
                        }
                        while(true)
                        {
                            GOTO(77,Ref+4);getline(cin,no1);
                            if(not no1.empty() && ValidPNR(no1) && no1.length()==16) break;
                            else {GOTO(77,Ref+4); cout<<"                  "; GOTO(77,Ref+4);}
                        }
                        while(true)
                        {
                            GOTO(77,Ref+6);getline(cin,no2);
                            Date d ; d.Assign(no2);
                            if(not no2.empty() && d.Future()) break;
                            else {GOTO(77,Ref+6); cout<<"                  "; GOTO(77,Ref+6);}
                        }
                        while(true)
                        {
                            GOTO(77,Ref+8);pw = getpass();
                            if(not pw.empty()&&ValidPNR(pw)&&pw.length()==3) break;
                            else {GOTO(77,Ref+8); cout<<"                  "; GOTO(77,Ref+8);}
                        }
                        SetConsoleColor(WHITE);
                    }
                    else if(mode=="Debit Card")
                    {
                        GOTO(0,Ref+2); cout<<" Debit Card Number      -- "; GenFormBoxSC(75,Ref+2,20);
                        GOTO(0,Ref+4); cout<<" Debit Card PIN         -- "; GenFormBoxBC(75,Ref+4,20);
                        GOTO(0,Ref+6); cout<<" Account Number         -- "; GenFormBoxEC(75,Ref+6,20);
                        SetConsoleColor(GRAY);
                        while(true)
                        {
                            GOTO(77,Ref+2); getline(cin,name);
                            if(not name.empty() && name.length()==16 && ValidPNR(name)) break;
                            else {GOTO(77,Ref+2); cout<<"                  "; GOTO(77,Ref+2);}
                        }
                        while(true)
                        {
                            GOTO(77,Ref+4);no1=getpass();
                            if(not no1.empty() && ValidPNR(no1) && no1.length()==4) break;
                            else {GOTO(77,Ref+4); cout<<"                  "; GOTO(77,Ref+4);}
                        }
                        while(true)
                        {
                            GOTO(77,Ref+6);getline(cin,no2);
                            if(not no2.empty() && ValidPNR(no2) && no2.length()==15) break;
                            else {GOTO(77,Ref+6); cout<<"                  "; GOTO(77,Ref+6);}
                        }
                        SetConsoleColor(GREEN);
                        GOTO(0,Ref+8); cout<<" Account Detected. Proceed to Transaction.";
                        SetConsoleColor(WHITE);
                        GOTO(0,Ref+10); cout<<" Transaction Password   -- "; GenFormBox  (75,Ref+10,20);
                        SetConsoleColor(GRAY);
                        while(true)
                        {
                            GOTO(77,Ref+10);pw=getpass();
                            if(not pw.empty() && pw.length()>=6) break;
                            else {GOTO(77,Ref+10); cout<<"                  "; GOTO(77,Ref+10);}
                        }
                        SetConsoleColor(WHITE);
                    }
                    else
                    {
                        GOTO(0,Ref+2); cout<<" Bank Name              -- "; GenFormBoxSC(75,Ref+2,20);
                        GOTO(0,Ref+4); cout<<" Account Number         -- "; GenFormBoxBC(75,Ref+4,20);
                        GOTO(0,Ref+6); cout<<" Password               -- "; GenFormBoxEC(75,Ref+6,20);
                        SetConsoleColor(GRAY);
                        while(true)
                        {
                            GOTO(77,Ref+2); getline(cin,name);
                            const regex pattern ("((\\w*)( |_)?)*(Bank|bank)(( |_)?(\\w*))*");
                            if(not name.empty() && regex_match(name,pattern)) break;
                            else {GOTO(77,Ref+2); cout<<"                  "; GOTO(77,Ref+2);}
                        }
                        while(true)
                        {
                            GOTO(77,Ref+4);getline(cin,no1);
                            if(not no1.empty() && ValidPNR(no1) && no1.length()==15) break;
                            else {GOTO(77,Ref+4); cout<<"                  "; GOTO(77,Ref+4);}
                        }
                        while(true)
                        {
                            GOTO(77,Ref+6);no2=getpass();
                            if(not no2.empty() && no2.length()>=6) break;
                            else {GOTO(77,Ref+6); cout<<"                  "; GOTO(77,Ref+6);}
                        }
                        SetConsoleColor(GREEN);
                        GOTO(0,Ref+8); cout<<" Account Detected. Proceed to Transaction.";
                        SetConsoleColor(WHITE);
                        GOTO(0,Ref+10); cout<<" Transaction Password   -- "; GenFormBox  (75,Ref+10,20);
                        SetConsoleColor(GRAY);
                        while(true)
                        {
                            GOTO(77,Ref+10);pw=getpass();
                            if(not pw.empty() && pw.length()>=6) break;
                            else {GOTO(77,Ref+10); cout<<"                  "; GOTO(77,Ref+10);}
                        }
                        SetConsoleColor(WHITE);
                    }
                    SetCursor(false); SetConsoleColor(TURQUOISE);
                    cout<<"\n\n\n INR "<<totalmoney<<" is Deducted from your Account."<<endl<<endl<<endl;
                    SetConsoleColor(GREEN);
                    Head(cout,"Booking Complete. Press ANY KEY to Continue.",100);
                    for(int i=0;i<noc+noi+noa;i++)
                    {
                        p[i].Payment(mode,name,no1,no2,pw);
                    }
                    fstream file; file.open("Airline\\Passenger Data\\Payment "+PNR+".txt",ios::out);
                    file<<mode<<endl<<name<<endl<<no1<<endl<<no2<<endl<<pw<<endl<<totalmoney<<endl; file.close();
                    getch(); break;
                }
                else {GOTO(24,Ref); cout<<"                    "; GOTO(24,Ref);}
            }
            fstream fout; fout.open(("Airline\\Passenger Data\\"+PNR+".dat").c_str(),ios::out|ios::binary);
            for(int i=0;i<noa+noc+noi;i++)
            {
                p[i].Write(fout);
            }
            fout.close();
            fout.open("Airline\\Passenger Data\\Airline Data.dat",ios::out|ios::binary|ios::app);
            for(int i=0;i<noa+noc+noi;i++)
            {
                p[i].Write(fout);
            }
            fout.close();
            system(("explorer \""+GetEXEDrive()+"\\All C++ Files\\KV Airlines\\Passenger Tickets\\"+PNR+"\"").c_str());
            return;
        }
    }

}

void Manage()
{
    INPUT_RECORD Rec; DWORD ev; int opt=1; GetDefault();GetConsoleMode(in,&ConsoleMode);
    _esc:
    Sleep(200); SetConsoleSize(80,22); SetBufferSize(80,22); system("cls");SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
    SetConsoleColor(BGYELLOW|DARK_BLUE); SplHead(cout,"Manage Your Bookings",80);
    SetConsoleColor(GRAY); GOTO(0,5); cout<<"  Click on an Option : (Press ESC to Return)"; GOTO(0,9);
    SetConsoleColor(WHITE);SetCursor(false);
    cout<<"         1)   View Flight Summary                              ... "<<endl;
    cout<<"         ----------------------------------------------------------"<<endl;
    cout<<"           2)   Change Date of Travel                            ... "<<endl;
    cout<<"           ----------------------------------------------------------"<<endl;
    cout<<"             3)   Cancel Booking(s)                                ... "<<endl;
    cout<<"             ----------------------------------------------------------"<<endl;
    cout<<"           4)   Show Passenger Data / Download E-Ticket          ... "<<endl;
    cout<<"           ----------------------------------------------------------"<<endl;
    cout<<"         5)   Return to Main Menu                              ... "<<endl;
    while(true)
    {
        ReadConsoleInput(in,&Rec,1,&ev);
        switch(Rec.EventType)
        {
        case KEY_EVENT:
            {
                if(Rec.Event.KeyEvent.wVirtualKeyCode==VK_ESCAPE) return;
                break;
            }
        case MOUSE_EVENT:
            {
                if(Rec.Event.MouseEvent.dwEventFlags == MOUSE_MOVED)
                {
                    COORD Final = Rec.Event.MouseEvent.dwMousePosition;
                    if(Final.Y == 9 && (Final.X> 9&&Final.X<66))
                    {
                        GOTO(0,9); SetConsoleColor(WHITE);SetCursor(false);
                        cout<<"         1)   View Flight Summary                              ... "<<endl;
                        cout<<"         ----------------------------------------------------------"<<endl;
                        cout<<"           2)   Change Date of Travel                            ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"             3)   Cancel Booking(s)                                ... "<<endl;
                        cout<<"             ----------------------------------------------------------"<<endl;
                        cout<<"           4)   Show Passenger Data / Download E-Ticket          ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"         5)   Return to Main Menu                              ... "<<endl;
                        SetCursorAt(9,9);
                        SetConsoleColor(BGWHITE|BLACK);
                        cout<<"1)   View Flight Summary                              ... ";
                        SetConsoleColor(WHITE);
                    }
                    else if(Final.Y == 11 && (Final.X>11&&Final.X<68))
                    {
                        GOTO(0,9); SetConsoleColor(WHITE);SetCursor(false);
                        cout<<"         1)   View Flight Summary                              ... "<<endl;
                        cout<<"         ----------------------------------------------------------"<<endl;
                        cout<<"           2)   Change Date of Travel                            ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"             3)   Cancel Booking(s)                                ... "<<endl;
                        cout<<"             ----------------------------------------------------------"<<endl;
                        cout<<"           4)   Show Passenger Data / Download E-Ticket          ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"         5)   Return to Main Menu                              ... "<<endl;
                        SetCursorAt(11,11);
                        SetConsoleColor(BGWHITE|BLACK);
                        cout<<"2)   Change Date of Travel                            ... ";
                        SetConsoleColor(WHITE);
                    }
                    else if(Final.Y == 13 && (Final.X>13&&Final.X<70))
                    {
                        GOTO(0,9); SetConsoleColor(WHITE);SetCursor(false);
                        cout<<"         1)   View Flight Summary                              ... "<<endl;
                        cout<<"         ----------------------------------------------------------"<<endl;
                        cout<<"           2)   Change Date of Travel                            ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"             3)   Cancel Booking(s)                                ... "<<endl;
                        cout<<"             ----------------------------------------------------------"<<endl;
                        cout<<"           4)   Show Passenger Data / Download E-Ticket          ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"         5)   Return to Main Menu                              ... "<<endl;
                        SetCursorAt(13,13);
                        SetConsoleColor(BGWHITE|BLACK);
                        cout<<"3)   Cancel Booking(s)                                ... ";
                        SetConsoleColor(WHITE);
                    }
                    else if(Final.Y == 15 && (Final.X>11&&Final.X<68))
                    {
                        GOTO(0,9); SetConsoleColor(WHITE);SetCursor(false);
                        cout<<"         1)   View Flight Summary                              ... "<<endl;
                        cout<<"         ----------------------------------------------------------"<<endl;
                        cout<<"           2)   Change Date of Travel                            ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"             3)   Cancel Booking(s)                                ... "<<endl;
                        cout<<"             ----------------------------------------------------------"<<endl;
                        cout<<"           4)   Show Passenger Data / Download E-Ticket          ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"         5)   Return to Main Menu                              ... "<<endl;
                        SetCursorAt(11,15);
                        SetConsoleColor(BGWHITE|BLACK);
                        cout<<"4)   Show Passenger Data / Download E-Ticket          ... ";
                        SetConsoleColor(WHITE);
                    }
                    else if(Final.Y == 17 && (Final.X> 9&&Final.X<66))
                    {
                        GOTO(0,9); SetConsoleColor(WHITE);SetCursor(false);
                        cout<<"         1)   View Flight Summary                              ... "<<endl;
                        cout<<"         ----------------------------------------------------------"<<endl;
                        cout<<"           2)   Change Date of Travel                            ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"             3)   Cancel Booking(s)                                ... "<<endl;
                        cout<<"             ----------------------------------------------------------"<<endl;
                        cout<<"           4)   Show Passenger Data / Download E-Ticket          ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"         5)   Return to Main Menu                              ... "<<endl;
                        SetCursorAt(9,17);
                        SetConsoleColor(BGWHITE|BLACK);
                        cout<<"5)   Return to Main Menu                              ... ";
                        SetConsoleColor(WHITE);
                    }
                    else
                    {
                        GOTO(0,9); SetConsoleColor(WHITE);SetCursor(false);
                        cout<<"         1)   View Flight Summary                              ... "<<endl;
                        cout<<"         ----------------------------------------------------------"<<endl;
                        cout<<"           2)   Change Date of Travel                            ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"             3)   Cancel Booking(s)                                ... "<<endl;
                        cout<<"             ----------------------------------------------------------"<<endl;
                        cout<<"           4)   Show Passenger Data / Download E-Ticket          ... "<<endl;
                        cout<<"           ----------------------------------------------------------"<<endl;
                        cout<<"         5)   Return to Main Menu                              ... "<<endl;
                    }
                }
                switch(Rec.Event.MouseEvent.dwButtonState)
                {
                    case FROM_LEFT_1ST_BUTTON_PRESSED:
                        {
                            COORD Final = Rec.Event.MouseEvent.dwMousePosition;
                            if     (Final.Y ==  9 && (Final.X> 9&&Final.X<66)) { opt = 1; goto endol; }
                            else if(Final.Y == 11 && (Final.X>11&&Final.X<68)) { opt = 2; goto endol; }
                            else if(Final.Y == 13 && (Final.X>13&&Final.X<70)) { opt = 3; goto endol; }
                            else if(Final.Y == 15 && (Final.X>11&&Final.X<68)) { opt = 4; goto endol; }
                            else if(Final.Y == 17 && (Final.X> 9&&Final.X<66)) { return; }
                            break;
                        }
                }
                break;
            }
        }
    }
    endol:
    switch(opt)
    {
    case 1:
        {
            Passenger* p = new Passenger[30];
            system("cls"); SetConsoleSize(100,56,289,false); SetBufferSize(100,100); SetConsoleColor(BGDARK_TURQUOISE|WHITE);
            SplHead(cout,"BOOKING SUMMARY",100);SetConsoleColor(WHITE);
            int i = 0, noc = 0, noa = 0, noi = 0;
            string PNR; GOTO(0,5); cout<<" PNR/ RLOC                            - \t\t\t"; GenFormBox (80,5,15);
            SetConsoleMode(in,ConsoleMode);GOTO(82,5); SetConsoleColor(GRAY); cin>>PNR; cout<<endl;
            fstream fin; fin.open(("Airline\\Passenger Data\\"+PNR+".dat").c_str(),ios::in|ios::binary);
            if(not fin.is_open()) goto exitmode;
            else
            {
                while(!fin.eof())
                {
                    p[i].Read(fin); i++;
                    if(p[i-1].Type == "Child") noc++;
                    else if(p[i-1].Type == "Infant") noi++;
                    else if(p[i-1].Type == "Adult") noa++;
                }
                fin.close();
                string jt = p[0].JT().first, jt2 = p[0].JT().second, cabin = p[0].Class();
                SetConsoleColor(GREEN); cout<<" Journey Type - "<<jt<<","<<jt2<<endl<<endl;
                GetDefault(); int CY = csbi.dwCursorPosition.Y;
                SetConsoleColor(GREEN); GOTO(0,CY); cout<<" Current Departure Route - For ";
                p[0].DEP().Show();cout<<" in "<<cabin<<" class.";
                SetConsoleColor(WHITE); GOTO(0,CY+1); p[0].Rt().TrPrint();
                if(jt2=="Return")
                {
                    SetConsoleColor(GREEN); GOTO(0,CY+5); cout<<" Current Return Route    - For ";
                    p[0].ARR().Show();cout<<" in "<<cabin<<" class.";
                    SetConsoleColor(WHITE); GOTO(0,CY+6); p[0].Rt(1).TrPrint();
                }
                SetConsoleColor(YELLOW); GetDefault(); int y = csbi.dwCursorPosition.Y;
                Fare data; data.Get(cabin,jt,p[0].Rt()); if(p[0].State) data.HIGH(); else data.LOW(); data.Invoice(noa,noc,noi,y+1,jt2,p[0].Rt(),p[0].Rt(1));
                SetConsoleColor(TURQUOISE); cout<<"\n List of Passengers Travelling -: \n"; SetConsoleColor(WHITE); GetDefault();
                GOTO(0,csbi.dwCursorPosition.Y+1); Head(cout," SNo. |        Passenger Name        |   Type   |         Route         | Seat |   Ticket Number  ",100);
                GOTO(0,csbi.dwCursorPosition.Y+4); for(int i=0;i<100;i++) cout<<"-";
                for(int i=0;i<noc+noi+noa;i++)
                {
                    if(p[i].Type!=""){cout<<right<<"| "<<setw(3)<<i+1<<"  ";p[i].Print();}
                }
                if(jt2=="Return")
                {
                    for(int i=0;i<noc+noi+noa;i++)
                    {
                        if(p[i].Type!=""){cout<<right<<"| "<<setw(3)<<i+1<<"  ";p[i].Print(0);}
                    }
                }
                SetConsoleColor(TURQUOISE); cout<<"\n SELECTED MODE OF PAYMENT - ";
                SetConsoleColor(WHITE); cout<<p[0].PayMode(); cout<<"\n\n Data Retrieval Complete. Press Any Key to Exit.";
                getch(); goto _esc;
            }
            exitmode:
                SetConsoleColor(RED); cout<<"\n\n\n\n No PNR Found. Press Any Key to Exit."; getch(); goto _esc;
        }
    case 2:
        {
            Passenger* p = new Passenger[30]; string PNR; bool done = false;
            Date Dep,Arr,OD,OR; int noc = 0, noa = 0, noi = 0, i = 0; double oldtot=0, lowf = 0;
            system("cls"); SetConsoleSize(80,26); SetBufferSize(80,26); SetConsoleColor(BGDARK_TURQUOISE|WHITE);
            SplHead(cout,"ALTER BOOKING",80); SetConsoleColor(WHITE);
            GOTO(0,5); cout<<" PNR / RLOC                            - \t\t\t"; GenFormBox (60,5,15);
            SetConsoleMode(in,ConsoleMode);GOTO(62,5); SetConsoleColor(GRAY); getline(cin,PNR); cout<<endl;
            SetConsoleColor(GRAY); cout<<"\n Press Enter to Keep Original Dates. Kindly Enter in DD/MM/YYYY Format only.\n\n";
            fstream fin; fin.open(("Airline\\Passenger Data\\"+PNR+".dat").c_str(),ios::in|ios::binary);
            if(not fin.is_open()) goto exitc;
            else
            {
                while(!fin.eof())
                {
                    p[i].Read(fin); i++;
                    if(p[i-1].Type == "Child") noc++;
                    else if(p[i-1].Type == "Infant") noi++;
                    else if(p[i-1].Type == "Adult") noa++;
                    if(not p[i-1].Type.empty()) oldtot += p[i-1].PFare;
                }
                fin.close();
                if(p[0].State==LOW) lowf = 0.5*(oldtot/(noc+noa+noi));
                Passenger tmp;
                fstream fout,f2;
                fout.open("Airline\\Passenger Data\\Airline Data.dat",ios::in|ios::binary);
                f2.open("Airline\\Passenger Data\\T.dat",ios::out|ios::binary);
                while(not fout.eof())
                {
                    tmp.Read(fout);
                    if(find(p,p+noc+noa+noi,tmp)==p+noc+noa+noi && tmp.Type!="")
                    tmp.Write(f2);
                }
                f2.close(); fout.close();
                remove("Airline\\Passenger Data\\Airline Data.dat");
                rename("Airline\\Passenger Data\\T.dat","Airline\\Passenger Data\\Airline Data.dat");
                string jt = p[0].JT().first, jt2 = p[0].JT().second, cabin = p[0].Class();
                SetConsoleColor(GREEN); cout<<" Journey Type - "<<jt<<","<<jt2<<endl<<endl;
                OD = p[0].DEP(); OR = p[0].ARR(); GetDefault(); int Y = csbi.dwCursorPosition.Y;
                SetConsoleColor(WHITE);
                cout<<" Original Date of Departure            -   "; GOTO(62,Y); cout<<OD<<endl<<endl;
                cout<<" New      Date of Departure            -   "; GenFormBox(60,Y+2,12);
                string dp, ar;
                while(true)
                {
                    SetConsoleColor(YELLOW);
                    GOTO(62,Y+2); getline(cin,dp); Dep.Assign(dp); if(dp.empty()) Dep = OD;
                    if(Dep.Check()) break;
                    else { GOTO(62,Y+2); cout<<"          "; GOTO(62,Y+2); }
                }
                if(jt2=="Return")
                {
                    GOTO(0,Y+4); SetConsoleColor(WHITE);
                    cout<<" Original Date of Arrival              -   "; GOTO(62,Y+4); cout<<OR<<endl<<endl;
                    cout<<" New      Date of Arrival              -   "; GenFormBox(60,Y+6,12);
                    while(true)
                    {
                        SetConsoleColor(YELLOW);
                        GOTO(62,Y+6); getline(cin,ar); Arr.Assign(ar); if(ar.empty()) Arr = OR;
                        if(Dep.Check(Arr)) break;
                        else { GOTO(62,Y+6); cout<<"          "; GOTO(62,Y+6); }
                    }
                }
                if(OD!=Dep||(jt2=="Return"?false:OR!=Arr))
                {
                    int sx, sy, cx=0, cy=0, sw=3,sctr=noc+noa,mctr=0,pctr=0; Location tr=p[0].Rt(), trr = p[0].Rt(1);
                    if(jt=="Domestic")
                    {
                        if(cabin=="ECONOMY")
                        { sx = 9 , sy = 16; cx = 12; cy = 10 ;}
                        else
                        { sx = 6 , sy = 6 ; cx = 15; cy = 18;}
                    }
                    else
                    {
                        if(cabin=="ECONOMY")
                        { sx = 12, sy = 18; cx = 8 ; cy = 9 ;}
                        else if(cabin=="BUSINESS")
                        { sx = 6 , sy = 6 ; cx = 15; cy = 18;}
                        else
                        { sx = 4 , sy = 2 ; cx = 16; cy = 24; sw = 1;}
                    }
                    Seat SOD(cabin,OD.Value(),jt,p[0].Rt().Dest,p[0].Rt().Arrival,p[0].Rt().Time(),sx,sy),
                         SOR(cabin,OR.Value(),jt,p[0].Rt(1).Dest,p[0].Rt(1).Arrival,p[0].Rt(1).Time(),sx,sy);
                    SOD.Create(); SOR.Create();
                    for(int i=0;i<noa+noc;i++)
                    {
                        SOD.Unbook(Row(p[i].BkSeat().first),Col(p[i].BkSeat().first));
                        if(jt2=="Return") SOR.Unbook(Row(p[i].BkSeat().second),Col(p[i].BkSeat().second));
                    }
                    for(int i=0;i<noa+noc+noi;i++)
                    {
                        p[i].Assign(jt,jt2,cabin,PNR,Dep,Arr,p[i].Rt(),p[i].Rt(1));
                    }
                    Button A(46,45,0,3,WHITE,0,WHITE,0,""), HD(46,1,0,47,WHITE,0,PINK,0,cabin+" CLASS SEATS - "+jt+" Flight");
                    system("cls"); SetConsoleSize(100,50,289); SetBufferSize(100,50);
                    SetConsoleColor(TURQUOISE); SplHead(cout,"SEAT ALLOCATION",100);
                    A.Print(); HD.Print(); Button NEXT(10,1,84,52-6,RED ,0,WHITE,0,"->"); NEXT.Print();
                    vector<SHORT> C3 = NEXT.Area(); vector<Coordinate> SeatsBookedToday(30);
                    Seat SRD(cabin,Dep.Value(),jt,tr.Dest,tr.Arrival,tr.Time(),sx,sy); SRD.Create();
                    vector<Coordinate> Pos = SRD.Print(cx,cy,sw);
                    SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
                    SetConsoleColor(GRAY);GOTO(60,7 );cout<<"Outbound - "<<Dep.Value()<<" - ";
                    SetConsoleColor(GRAY);GOTO(60,17);cout<<"Instructions - ";
                    SetConsoleColor(WHITE);
                    GOTO(63,19); cout<<"Double Click the Seat : ";
                    GOTO(63,20); cout<<"Confirm the Booking.";
                    GOTO(63,22); cout<<"Single Click the Seat : ";
                    GOTO(63,23); cout<<"View the Seat Number.";
                    GOTO(63,25); cout<<"Hover the Mouse on the Seat : ";
                    GOTO(63,26); cout<<"View the Seat Number.";
                    while(true)
                    {
                        SetConsoleColor(WHITE);
                        GOTO(63, 9);cout<<"Total Seats Left   - "<<SRD.Count();
                        GOTO(63,11);cout<<"Seats to be Booked - "<<right<<setw(len(SRD.Count()))<<sctr;
                        if(sctr!=0) { GOTO(63,13);cout<<"Booking Seat for Passenger "<<pctr+1<<endl; }
                        if(sctr == 0)
                        {
                            GOTO(63,14);cout<<"                                 "<<endl;
                            SetConsoleColor(GRAY); GOTO(58,33); if(noi>0) cout<<noi<<" Bassinet Seat(s) will be installed.";
                            SetConsoleColor(YELLOW); GOTO(65,37); cout<<"Seat Booking Complete.";
                            GOTO(66,39); cout<<"Press -> to Continue.";
                        }
                        ReadConsoleInput(in,&Rec,1,&ev);
                        switch(Rec.EventType)
                        {
                        case MOUSE_EVENT:
                            {
                               int x = Rec.Event.MouseEvent.dwMousePosition.X;
                               int y = Rec.Event.MouseEvent.dwMousePosition.Y;
                               Coordinate CP = {x,y};
                               switch(Rec.Event.MouseEvent.dwEventFlags)
                               {
                               case MOUSE_MOVED:
                               {
                                    if(find(Pos.begin(),Pos.end(),CP)!=Pos.end())
                                    {
                                        vector<Coordinate>::iterator it = find(Pos.begin(),Pos.end(),CP);
                                        SRD.Print(cx,cy,sw);
                                        SetConsoleColor(BLUE); GOTO(x,y); cout<<BLK;
                                        for(int i=0;i<sy;i++)
                                        {
                                            for(int j=0;j<sx;j++)
                                            {
                                                if(*it == Pos[(sx*i)+j])
                                                {
                                                    SetConsoleColor(WHITE); GOTO(68,42);
                                                    cout<<"Seat Number - "<<SRD.SeatNo(i+1,j+1);
                                                }
                                            }
                                        }
                                    }
                                    else
                                    {
                                        SRD.Print(cx,cy,sw);
                                        SetConsoleColor(WHITE); GOTO(65,42); cout<<"                              ";
                                    }
                                    break;
                               }
                               case 0:
                                    {
                                        if(Rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                                        {
                                             if(x>=C3[0]&&x<=C3[2] && y>=C3[1]&&y<=C3[3])
                                             {
                                                 if(sctr==0) goto endit3;
                                             }
                                        }
                                        break;
                                    }
                               case DOUBLE_CLICK:
                                    {
                                        if(find(Pos.begin(),Pos.end(),CP)!=Pos.end() && sctr>0)
                                        {
                                            SRD.Print(cx,cy,sw);
                                            SetConsoleColor(GRAY); GOTO(x,y); cout<<BLK;
                                            vector<Coordinate>::iterator it = find(Pos.begin(),Pos.end(),CP);
                                            for(int i=0;i<sy;i++)
                                            {
                                                for(int j=0;j<sx;j++)
                                                {
                                                    if(*it == Pos[(sx*i)+j])
                                                    {
                                                        if(not SRD.Booked(i+1,j+1))
                                                        {
                                                            SRD.Book(i+1,j+1);
                                                            p[pctr].AllocSeat(SRD.SeatNo(i+1,j+1));
                                                            Coordinate T(i+1,j+1);
                                                            SeatsBookedToday[mctr] = T;
                                                            pctr++; sctr--; mctr++; break;
                                                        }
                                                        else
                                                        {
                                                            Coordinate T(i+1,j+1);
                                                            if(find(SeatsBookedToday.begin(),
                                                                    SeatsBookedToday.end(),T)!=SeatsBookedToday.end())
                                                            {
                                                                SRD.Unbook(i+1,j+1);
                                                                SeatsBookedToday.erase(remove(SeatsBookedToday.begin(),
                                                                                       SeatsBookedToday.end(),T),
                                                                                       SeatsBookedToday.end());
                                                                mctr--; pctr--; sctr++;
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    endit3:
                    if(jt2=="Return")
                    {
                        system("cls"); SetConsoleSize(100,50,289); SetBufferSize(100,50);
                        SetConsoleColor(TURQUOISE); SplHead(cout,"SEAT ALLOCATION",100);
                        A.Print(); HD.Print(); NEXT.Print();
                        Seat SRR(cabin,Arr.Value(),jt,trr.Dest,trr.Arrival,trr.Time(),sx,sy); SRR.Create();
                        Pos = SRR.Print(cx,cy,sw); pctr = 0; sctr = noc+noa;
                        SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
                        SetConsoleColor(GRAY);GOTO(60,7 );cout<<"Inbound - "<<Arr.Value()<<" - ";
                        SetConsoleColor(GRAY);GOTO(60,17);cout<<"Instructions - ";
                        SetConsoleColor(WHITE);
                        GOTO(63,19); cout<<"Double Click the Seat : ";
                        GOTO(63,20); cout<<"Confirm the Booking.";
                        GOTO(63,22); cout<<"Single Click the Seat : ";
                        GOTO(63,23); cout<<"View the Seat Number.";
                        GOTO(63,25); cout<<"Hover the Mouse on the Seat : ";
                        GOTO(63,26); cout<<"View the Seat Number.";
                        while(true)
                        {
                            SetConsoleColor(WHITE);
                            GOTO(63, 9);cout<<"Total Seats Left   - "<<SRR.Count();
                            GOTO(63,11);cout<<"Seats to be Booked - "<<right<<setw(len(SRR.Count()))<<sctr;
                            if(sctr!=0) { GOTO(63,13);cout<<"Booking Seat for Passenger "<<pctr+1<<endl; }
                            if(sctr == 0)
                            {
                                GOTO(63,14);cout<<"                                 "<<endl;
                                SetConsoleColor(GRAY); GOTO(58,33); if(noi>0) cout<<noi<<" Bassinet Seat(s) will be installed.";
                                SetConsoleColor(YELLOW); GOTO(65,37); cout<<"Seat Booking Complete.";
                                GOTO(66,39); cout<<"Press -> to Continue.";
                            }
                            ReadConsoleInput(in,&Rec,1,&ev);
                            switch(Rec.EventType)
                            {
                            case MOUSE_EVENT:
                                {
                                   int x = Rec.Event.MouseEvent.dwMousePosition.X;
                                   int y = Rec.Event.MouseEvent.dwMousePosition.Y;
                                   Coordinate CP = {x,y};
                                   switch(Rec.Event.MouseEvent.dwEventFlags)
                                   {
                                   case MOUSE_MOVED:
                                   {
                                        if(find(Pos.begin(),Pos.end(),CP)!=Pos.end())
                                        {
                                            vector<Coordinate>::iterator it = find(Pos.begin(),Pos.end(),CP);
                                            SRR.Print(cx,cy,sw);
                                            SetConsoleColor(BLUE); GOTO(x,y); cout<<BLK;
                                            for(int i=0;i<sy;i++)
                                            {
                                                for(int j=0;j<sx;j++)
                                                {
                                                    if(*it == Pos[(sx*i)+j])
                                                    {
                                                        SetConsoleColor(WHITE); GOTO(68,42); cout<<"Seat Number - "
                                                                                                 <<SRR.SeatNo(i+1,j+1);
                                                    }
                                                }
                                            }
                                        }
                                        else
                                        {
                                            SRR.Print(cx,cy,sw);
                                            SetConsoleColor(WHITE); GOTO(65,42); cout<<"                              ";
                                        }
                                        break;
                                   }
                                   case 0:
                                        {
                                            if(Rec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
                                            {
                                                 if(x>=C3[0]&&x<=C3[2] && y>=C3[1]&&y<=C3[3])
                                                 {
                                                     if(sctr==0) goto btl;
                                                 }
                                            }
                                            break;
                                        }
                                   case DOUBLE_CLICK:
                                        {
                                            if(find(Pos.begin(),Pos.end(),CP)!=Pos.end() && sctr>0)
                                            {
                                                SRR.Print(cx,cy,sw);
                                                SetConsoleColor(GRAY); GOTO(x,y); cout<<BLK;
                                                vector<Coordinate>::iterator it = find(Pos.begin(),Pos.end(),CP);
                                                for(int i=0;i<sy;i++)
                                                {
                                                    for(int j=0;j<sx;j++)
                                                    {
                                                        if(*it == Pos[(sx*i)+j])
                                                        {
                                                            if(not SRR.Booked(i+1,j+1))
                                                            {
                                                                SRR.Book(i+1,j+1);
                                                                p[pctr].AllocReturnSeat(SRR.SeatNo(i+1,j+1));
                                                                Coordinate T(i+1,j+1);
                                                                SeatsBookedToday[mctr] = T;
                                                                pctr++; sctr--; mctr++; break;

                                                            }
                                                            else
                                                            {
                                                                Coordinate T(i+1,j+1);
                                                                if(find(SeatsBookedToday.begin(),SeatsBookedToday.end(),T)
                                                                       !=SeatsBookedToday.end())
                                                                {
                                                                    SRR.Unbook(i+1,j+1);
                                                                    SeatsBookedToday.erase(remove(SeatsBookedToday.begin(),
                                                                                           SeatsBookedToday.end(),T),
                                                                                           SeatsBookedToday.end());
                                                                    mctr--; pctr--; sctr++;
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    btl:
                    MessageBox(nullptr,("INR "+Revert(lowf)+" will be Deducted \nFrom the type "+p[0].PayMode()).c_str(),
                               "Fare Details",MB_OK|MB_ICONINFORMATION);
                    fstream file;
                    file.open("Airline\\Passenger Data\\"+PNR+".dat",ios::out|ios::binary|ios::trunc);
                    for(int i=0;i<noc+noa+noi;i++)
                    {
                        p[i].GenTicket(LOW);
                        p[i].Write(file);
                    }
                    file.close();
                    fout.open("Airline\\Passenger Data\\Airline Data.dat",ios::out|ios::binary|ios::app);
                    for(int i=0;i<noa+noc+noi;i++)
                    {
                        p[i].Write(fout);
                    }
                    fout.close();
                    goto _esc;
                }
                else
                {
                    SetCursor(false);
                    fout.open("Airline\\Passenger Data\\Airline Data.dat",ios::out|ios::binary|ios::app);
                    for(int i=0;i<noa+noc+noi;i++)
                    {
                        p[i].Write(fout);
                    }
                    fout.close();
                    cout<<endl<<endl<<" Date Change Complete. Press any key to continue.";getch();break;
                }
            }
            exitc:
                SetConsoleColor(RED); cout<<"\n\n\n\n No PNR Found. Press Any Key to Exit."; getch(); break;
        }
    case 3:
        {
            Passenger* p = new Passenger[30]; string PNR; bool done = false; int no = 0; bool po = false;
            bool mark[30]; for(int i=0;i<30;i++) mark[i]=false; int i = 0, noc = 0, noa = 0, noi = 0;
            system("cls"); SetConsoleSize(100,56,289,false); SetBufferSize(100,56); SetConsoleColor(BGDARK_TURQUOISE|WHITE);
            SplHead(cout,"CANCEL BOOKING(S)",100);SetConsoleColor(WHITE);
            GOTO(0,5); cout<<" PNR/ RLOC                            - \t\t\t"; GenFormBox (80,5,15);
            SetConsoleMode(in,ConsoleMode);GOTO(82,5); SetConsoleColor(GRAY); cin>>PNR; cout<<endl;
            fstream fin; fin.open(("Airline\\Passenger Data\\"+PNR+".dat").c_str(),ios::in|ios::binary);
            if(not fin.is_open()) goto exitm;
            else
            {
                double oldtot = 0,lowf = 0;
                while(!fin.eof())
                {
                    p[i].Read(fin); i++;
                    if(p[i-1].Type == "Child") noc++;
                    else if(p[i-1].Type == "Infant") noi++;
                    else if(p[i-1].Type == "Adult") noa++;
                    if(not p[i-1].Type.empty()) oldtot += p[i-1].PFare;
                }
                fin.close();
                if(p[0].State==HIGH) lowf = 0.05*oldtot;
                string jt = p[0].JT().first, jt2 = p[0].JT().second, cabin = p[0].Class();
                SetConsoleColor(GREEN); cout<<" Journey Type - "<<jt<<","<<jt2<<endl<<endl;
                GetDefault(); int CY = csbi.dwCursorPosition.Y;
                SetConsoleColor(GREEN); GOTO(0,CY); cout<<" Current Departure Route - For ";
                p[0].DEP().Show();cout<<" in "<<cabin<<" class.";
                SetConsoleColor(WHITE); GOTO(0,CY+1); p[0].Rt().TrPrint();
                if(jt2=="Return")
                {
                    SetConsoleColor(GREEN); GOTO(0,CY+5); cout<<" Current Return Route    - For ";
                    p[0].ARR().Show();cout<<" in "<<cabin<<" class.";
                    SetConsoleColor(WHITE); GOTO(0,CY+6); p[0].Rt(1).TrPrint();
                }
                SetConsoleColor(TURQUOISE); cout<<"\n List of Passengers Travelling -: \n"; SetConsoleColor(WHITE);
                GetDefault(); int Y = csbi.dwCursorPosition.Y;
                if(noc+noa+noi > 12) SetBufferSize(100,100);
                Button* Radio = new Button[30],* PButton = new Button[30]; vector<SHORT>* CA = new vector<SHORT>[30];
                for(int i=0;i<noc+noa+noi;i++)
                {
                    if(not p[i].Type.empty())
                    {
                        Radio[i] = Button(2,1,0,Y+(3*i),WHITE,0,WHITE,0,"");
                        PButton[i] = Button(92,1,5,Y+(3*i),YELLOW,0,WHITE,0,p[i].Info());
                        CA[i] = Radio[i].Area(); Radio[i].Print(); PButton[i].Print();
                    }
                }
                GetDefault(); Y = csbi.dwCursorPosition.Y;
                if(Y<40); SetConsoleSize(100,Y+10,289);
                Button MENU(10,1,60,Y+3,BLUE,0,WHITE,0,"RETURN");
                Button NEXT(10,1,80,Y+3,RED ,0,WHITE,0," -> ");
                vector<SHORT> C1 = MENU.Area(), C2 = NEXT.Area();
                MENU.Print(); NEXT.Print();
                SetConsoleMode(in,ENABLE_MOUSE_INPUT|ENABLE_WINDOW_INPUT);
                while(true)
                {
                    if(not done&&po)
                    {
                        GOTO(0,Y+3); SetConsoleColor(BLUE); cout<<"                                                     ";
                        po = false;
                    }
                    if(done&&not po)
                    {
                        GOTO(0,Y+3); SetConsoleColor(BLUE); cout<<"To confirm cancellation of your selection, Press ->.";
                        po = true;
                    }
                    ReadConsoleInput(in,&Rec,1,&ev);
                    switch(Rec.EventType)
                    {
                    case KEY_EVENT:
                        {
                            if(Rec.Event.KeyEvent.wVirtualKeyCode==VK_MENU) goto _esc;
                            break;
                        }
                    case MOUSE_EVENT:
                        {
                            int x = Rec.Event.MouseEvent.dwMousePosition.X;
                            int y = Rec.Event.MouseEvent.dwMousePosition.Y;
                            switch(Rec.Event.MouseEvent.dwButtonState)
                            {
                            case FROM_LEFT_1ST_BUTTON_PRESSED:
                                {
                                    if((x>=C1[0]&&x<=C1[2])&&(y>=C1[1]&&y<=C1[3])) { goto _esc;}
                                    else if((x>=C2[0]&&x<=C2[2])&&(y>=C2[1]&&y<=C2[3])&&done)
                                    {
                                        int ct = 0; for(int i=0;i<noa+noc+noi;i++) { if(mark[i]) ct++; }
                                        int sx, sy, cx=0, cy=0, sw=3;
                                        if(jt=="Domestic")
                                        {
                                            if(cabin=="ECONOMY")
                                            { sx = 9 , sy = 16; cx = 12; cy = 10 ;}
                                            else
                                            { sx = 6 , sy = 6 ; cx = 15; cy = 18;}
                                        }
                                        else
                                        {
                                            if(cabin=="ECONOMY")
                                            { sx = 12, sy = 18; cx = 8 ; cy = 9 ;}
                                            else if(cabin=="BUSINESS")
                                            { sx = 6 , sy = 6 ; cx = 15; cy = 18;}
                                            else
                                            { sx = 4 , sy = 2 ; cx = 16; cy = 24; sw = 1;}
                                        }
                                        Seat SRD(cabin,p[0].DEP().Value(),jt,p[0].Rt().Dest,p[0].Rt().Arrival,p[0].Rt().Time(),sx,sy);
                                        Seat SRR(cabin,p[0].ARR().Value(),jt,p[0].Rt(1).Dest,p[0].Rt(1).Arrival,p[0].Rt(1).Time(),sx,sy);
                                        if(ct==noc+noa+noi)
                                        {
                                            MessageBox(nullptr,"Y","",MB_OK);
                                            for(int i=0;i<noa+noc+noi;i++)
                                            {
                                                if(p[i].Type=="Adult"||p[i].Type=="Child")
                                                {
                                                    remove(("Passenger Tickets\\"+PNR+"\\Ticket "+p[i].Ref()+".doc").c_str());
                                                    SRD.Unbook(Row(p[i].BkSeat().first),Col(p[i].BkSeat().first));
                                                    if(jt2=="Return") SRR.Unbook(Row(p[i].BkSeat().second),Col(p[i].BkSeat().second));
                                                }
                                                else
                                                {
                                                    remove(("Passenger Tickets\\"+PNR+"\\Ticket "+p[i].Ref()+".doc").c_str());
                                                }
                                            }
                                            remove(("Airline\\Passenger Data\\"+PNR+".dat").c_str());
                                            remove(("Airline\\Passenger Data\\Payment "+PNR+".txt").c_str());
                                            MessageBox(nullptr,("INR "+Revert(oldtot-lowf)+
                                                                " will be Refunded\nto the Type "+p[0].PayMode()).c_str()
                                                       ,"Fare Refund",MB_OK|MB_ICONINFORMATION);
                                            RemoveDirectory((GetEXEDrive()+
                                                             "All C++ Files\\KV Airlines\\Passenger Tickets\\"+PNR+"\\").c_str());
                                        }
                                        else if(ct!=noc+noi+noa)
                                        {
                                            fstream temp; ::totalmoney=0; int ac = 0;
                                            temp.open("Airline\\Passenger Data\\temp.dat",ios::out|ios::binary|ios::trunc);
                                            for(int i=0;i<noc+noa+noi;i++)
                                            {
                                                if(mark[i]==true&&p[i].Type=="Adult")
                                                    ac++;
                                            }
                                            if(noa-ac==0)
                                            {
                                                MessageBox(nullptr,("Invalid Action on "+PNR+
                                                                    "!\nThere must remain atleast one Adult Passenger!\n").c_str(),
                                                           "Error",MB_ICONERROR|MB_OK);
                                                goto _esc;
                                            }
                                            for(int i=0;i<noa+noc+noi;i++)
                                            {
                                                if(mark[i]==false&&not p[i].Type.empty())
                                                {
                                                    p[i].Write(temp);
                                                    ::totalmoney+=p[i].PFare;
                                                }
                                                else if(mark[i]==true)
                                                {
                                                    if(p[i].Type=="Adult"||p[i].Type=="Child")
                                                    {
                                                        remove(("Passenger Tickets\\"+PNR+"\\Ticket "+p[i].Ref()+".doc").c_str());
                                                        SRD.Unbook(Row(p[i].BkSeat().first),Col(p[i].BkSeat().first));
                                                        if(jt2=="Return") SRR.Unbook(Row(p[i].BkSeat().second),Col(p[i].BkSeat().second));
                                                    }
                                                    else
                                                    {
                                                        remove(("Passenger Tickets\\"+PNR+"\\Ticket "+p[i].Ref()+".doc").c_str());
                                                    }
                                                }
                                            }
                                            temp.close();
                                            remove(("Airline\\Passenger Data\\"+PNR+".dat").c_str());
                                            rename(("Airline\\Passenger Data\\temp.dat"),
                                                   ("Airline\\Passenger Data\\"+PNR+".dat").c_str());
                                            fstream tm; tm.open("Airline\\Passenger Data\\Payment "+PNR+".txt",ios::in);
                                            temp.open("Airline\\Passenger Data\\tmp.txt",ios::out|ios::trunc);
                                            for(int i=0;i<4;i++)
                                            {
                                                string s; getline(tm,s);
                                                temp<<s<<endl;
                                            }
                                            temp<<::totalmoney;
                                            tm.close(); temp.close();
                                            remove(("Airline\\Passenger Data\\Payment "+PNR+".txt").c_str());
                                            rename(("Airline\\Passenger Data\\tmp.txt"),
                                                ("Airline\\Passenger Data\\Payment "+PNR+".txt").c_str());
                                            MessageBox(nullptr,("INR "+Revert(oldtot - ::totalmoney - lowf)+
                                                                " will be Refunded\nto the Type "+p[0].PayMode()).c_str()
                                                       ,"Fare Refund",MB_OK|MB_ICONINFORMATION);
                                        }
                                        Passenger tmp;
                                        fstream fout,f2;
                                        fout.open("Airline\\Passenger Data\\Airline Data.dat",ios::in|ios::binary);
                                        f2.open("Airline\\Passenger Data\\T.dat",ios::out|ios::binary);
                                        while(not fout.eof())
                                        {
                                            tmp.Read(fout);
                                            if((find(p,p+noc+noa+noi,tmp)==(p+noa+noc+noi)) && tmp.Type!="")
                                                tmp.Write(f2);
                                        }
                                        for(int i=0;i<noc+noa+noi;i++)
                                        {
                                            if(mark[i]==false&&p[i].Type!="") p[i].Write(f2);
                                        }
                                        f2.close(); fout.close();
                                        remove("Airline\\Passenger Data\\Airline Data.dat");
                                        rename("Airline\\Passenger Data\\T.dat","Airline\\Passenger Data\\Airline Data.dat");
                                        goto _esc;
                                    }
                                    else
                                    {
                                        for(int i=0;i<noa+noc+noi;i++)
                                        {
                                            if(not p[i].Type.empty())
                                            {
                                                if((x==CA[i][0]||x==CA[i][2])&&(y==CA[i][1]||y==CA[i][3])&&mark[i]==false)
                                                {
                                                    mark[i] = true;
                                                    Radio[i].Click();
                                                    no++;
                                                    break;
                                                }
                                                else if((x==CA[i][0]||x==CA[i][2])&&(y==CA[i][1]||y==CA[i][3])&&mark[i]==true&&no>0)
                                                {
                                                    mark[i] = false;
                                                    Radio[i].Click(WHITE,0);
                                                    no--;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                    if(no>0) done = true;
                                    else done = false;
                                }
                            }
                            break;
                        }
                    }
                }
            }
            exitm:
                SetConsoleColor(RED); cout<<"\n\n\n\n No PNR Found. Press Any Key to Exit."; getch(); goto _esc;
        }
    case 4:
        {
            re:
            string PNR,ticket; bool done = false, pnr=true, tn=false, *rf=&pnr;
            int i=0; system("cls"); SetConsoleSize(60,20,472,true); SetBufferSize(60,20); Passenger *p = new Passenger[30];
            SetConsoleColor(BGOLIVE|WHITE); Head(cout,"RESOURCE LOCATOR",60);SetConsoleColor(WHITE);
            GOTO(0,11); cout<<"    PNR/RLOC of Journey - "; GenFormBox(30,11,20);
            GOTO(0,15); cout<<"    Ticket Reference    - "; GenFormBox(30,15,20);
            SetConsoleColor(GRAY); GOTO(0, 5); cout<<"  Enter Details to find a Passenger. Press ALT to GO Back.";
            while(true)
            {
                if(done)
                {
                    done=false;
                    goto exec;
                }
                ReadConsoleInput(in,&Rec,1,&ev);
                switch(Rec.EventType)
                {
                case KEY_EVENT:
                    {
                        GetDefault(); int x = csbi.dwCursorPosition.X;
                        char ch = Rec.Event.KeyEvent.uChar.AsciiChar;
                        if(Rec.Event.KeyEvent.wVirtualKeyCode==VK_MENU) goto _esc;
                        else if(isprint(ch)&&Rec.Event.KeyEvent.bKeyDown&&not done)
                        {
                            if(pnr){PNR+=ch;GOTO(31+PNR.length(),11); cout<<ch;}
                            if(tn){ticket+=ch;GOTO(31+ticket.length(),15); cout<<ch;}
                        }
                        else if(Rec.Event.KeyEvent.wVirtualKeyCode==VK_RETURN&&Rec.Event.KeyEvent.bKeyDown&&not done&&x<49)
                        {
                            *rf = false;
                            if(rf==&pnr)
                            {
                                if(ValidPNR(PNR)) rf=&tn;
                                else {GOTO(31,11); cout<<"                  "; GOTO(31,11);PNR="";}
                            }
                            else if(rf==&tn)
                            {
                                if(ValidPNR(ticket)&&ticket.length()==13&&not ticket.empty()) {done=true; rf=&pnr;}
                                else {GOTO(31,15); cout<<"                  "; GOTO(31,15);ticket="";}
                            }
                            *rf = true;
                        }
                        else if(Rec.Event.KeyEvent.wVirtualKeyCode==VK_BACK&&Rec.Event.KeyEvent.bKeyDown&&not done&&x>32)
                        {
                            GOTO(csbi.dwCursorPosition.X-1,csbi.dwCursorPosition.Y);
                            cout<<" ";
                            GOTO(csbi.dwCursorPosition.X-1,csbi.dwCursorPosition.Y);
                            if(pnr)
                            {
                                if(PNR.length()>1) PNR.resize(PNR.length()-1);
                                else PNR="";
                            }
                            if(tn)
                            {
                                if(ticket.length()>1) ticket.resize(ticket.length()-1);
                                else ticket="";
                            }
                        }
                    }
                }
            }
            exec:
            fstream fin; fin.open("Airline//Passenger Data//"+PNR+".dat",ios::in|ios::binary);
            string message = "";
            while(not fin.eof()&&fin.is_open())
            {
                p[i].Read(fin);
                i++;
            }
            if(not fin.is_open()) message = "Unallocated PNR/RLOC. No Booking Exist.";
            fin.close(); bool f = false;
            for(int j=0;j<i;j++)
            {
                if(p[j].Ref()==ticket)
                {
                    SetConsoleSize(100,56,289); system("cls"); f = true; cout<<endl<<endl<<p[j];
                    SetConsoleColor(GREEN); GOTO(0,55); cout<<"Retrieval Complete. Press Any Key to return.";
                    int msg = MessageBox(0,("Do you wish to Download the E-Ticket Again for Passenger - "+ticket+"?").c_str()
                                          ,"Prompt",MB_YESNO);
                    if(msg==IDYES)
                    {
                        p[j].DownloadTicket();
                        system(("explorer \""+GetEXEDrive()+"\\All C++ Files\\KV "
                                +"Airlines\\Passenger Tickets\\Downloads\\\"").c_str());
                    }
                }
            }
            if(not f)
            {
                if(message.empty()) message = "Invalid Ticket Reference. No such record in "+PNR+".";
                MessageBox(0,("Resource Locator was unable to find a match for your query.\n ERROR - "+message).c_str(),
                           "Resource Locator",MB_OK|MB_ICONERROR);
                goto re;
            }
            getch();
        }
    }
    goto _esc;
}

#endif // KV_AIRLINES_CLASSES_H_INCLUDED
