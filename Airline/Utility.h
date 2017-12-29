#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED

#include "Decor.h"
#include "Algorithms.h"

int Red       = Word.Color(255,  0,  0);
int Green     = Word.Color(  0,255,  0);
int Blue      = Word.Color(  0,  0,255);
int Black     = Word.Color(  0,  0,  0);
int White     = Word.Color(255,255,255);
int Yellow    = Word.Color(255,255,  0);
int Orange    = Word.Color(255,140,  0);
int Pink      = Word.Color(255, 20,147);
int Gold      = Word.Color(255,215,  0);
int Lime      = Word.Color(153,204, 50);
int Skin      = Word.Color(255,231,186);
int Purple    = Word.Color(135, 31,120);
int Violet    = Word.Color( 79, 47, 79);
int Maroon    = Word.Color(128,  0,  0);
int DarkGreen = Word.Color(  0,128,  0);
int DarkBlue  = Word.Color(  0,  0,139);
int Lilac     = Word.Color(154, 50,205);
int Brown     = Word.Color(139, 37,  0);
int Chocolate = Word.Color(139, 69, 19);
int RoseWood  = Word.Color(166, 42, 42);
int SkyBlue   = Word.Color( 56,176,222);
int NavyBlue  = Word.Color( 35, 35,142);
int Turquoise = Word.Color(  0,229,238);
int DarkTrqse = Word.Color(  0,197,205);
int BlueBlack = Word.Color( 25, 25,112);

int Consolas = Word.Font("Consolas");
int Berlin_Sans_FB = Word.Font("Berlin Sans FB");
int Calibri = Word.Font("Calibri");
int Times_New_Roman = Word.Font("Times New Roman");
int Arial = Word.Font("Arial");
int Aharoni = Word.Font("Aharoni");
int Harlow = Word.Font("Harlow Solid Italic");

std::string DisplayFullTime(int width = 80)
{
    time_t tt; tm* info;
    time(&tt); info=localtime(&tt);
    char* buf=new char[width];
    strftime(buf,width,"%d/%m/%Y - %X - %Z",info);
    std::string a; a.assign(buf);
    return a;
}

std::string DisplayTime()
{
    time_t tt; tm* info;
    time(&tt); info=localtime(&tt);
    char* buf=new char[80];
    strftime(buf,80,"%d/%m/%Y",info);
    std::string a; a.assign(buf);
    return a;
}

string GetTime(string Format)
{
    time_t tt; tm* info;
    time(&tt); info=localtime(&tt);
    char* buf=new char[80];
    strftime(buf,80,Format.c_str(),info);
    std::string a; a.assign(buf);
    return a;
}

string getpass()
{
    char BACKSPACE='\b', RETURN='\r';
    string pw=""; unsigned char ch = 0;
    DWORD mode = ::ConsoleMode, ev;
    HANDLE in=GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(in, mode & ~(ENABLE_ECHO_INPUT|ENABLE_LINE_INPUT));
    while(ReadConsoleA(in,&ch,1,&ev,NULL) && ch != RETURN)
    {
       if(ch==BACKSPACE)
       {
          if(pw.length()!=0)
          {
              cout <<"\b \b";
              pw.resize(pw.length()-1);
          }
       }
       else
       {
          pw += ch; cout <<'*';
       }
    }
    SetConsoleMode(in, mode);
    return pw;
}

void Leave(){system("cls");SetConsoleColor(YELLOW);}
void Stay(){system("cls");system(("\""+GetEXEAddress()+"KV Airlines\"").c_str());}

void GoodBye()
{
    QuestionBox("Thank You for using KV Airlines Service!\nYou are about to Exit from the Program.\n\nAre you sure about this?","Exit Prompt",Leave,Stay);
}

char getch()
/// Utility Function for satisfying the purpose of getch(), win32api style.
{
    INPUT_RECORD IR; DWORD evs; CHAR ch;
    while(true)
    {
        WINBOOL a = ReadConsoleInput(in, &IR, 1, &evs);
        if(not a) break;
        if (IR.EventType == KEY_EVENT && IR.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT && IR.Event.KeyEvent.bKeyDown
            && IR.Event.KeyEvent.wVirtualKeyCode != VK_MENU && IR.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
        {
            ch = IR.Event.KeyEvent.uChar.AsciiChar;
            return ch;
        }
        else if(IR.EventType == MOUSE_EVENT)
        {
            continue;
        }
    }
    return EOF;
}

#endif // KV_AIRLINES_UTILITY_H_INCLUDED
