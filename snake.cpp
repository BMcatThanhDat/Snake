#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include<bits/stdc++.h>

using namespace std;

int speedd;
bool chuachon=true;
string n;
int chieudai,chieurong;
bool gameover = false;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail;


enum eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirecton dir;


void gotoxy(int x,int y)
{    
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};    SetConsoleCursorPosition(h, a);
}

void TextColor(int x)
{
    HANDLE h= GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, x);
}

/// ////////////
void setup()
{
    chieudai=22;
    chieurong=22;
    x=chieurong/2;
    y=chieudai/2;
    fruitX=5;
    fruitY=5;
}

void vekhung()
{
     

    for(int i=0;i<=chieudai;i++) // ke khung tren cung
    {
        gotoxy(i,0);
        TextColor(70);
        if(i==0 ) cout<<(char) 201;
        else 
            {
            if(i==chieudai) cout<< (char) 187;
            else cout<<(char) 205;
            }
    }
    TextColor(15);
    for(int i=0;i<chieurong;i++) // ke 2 cot 2 ben
    {
        for(int j=0;j<=chieudai;j++)
        {
            if(j==0 || j==chieudai) {gotoxy(j,i);TextColor(70);cout<<(char) 199;}
        }
    }
    // ke khung duoi cung
    for(int i=0;i<=chieudai;i++) 
    {
        gotoxy(i,chieurong);
        TextColor(70);
        if(i==0 ) cout<<(char) 200;
        else 
            {
            if(i==chieudai) cout<< (char) 188;
            else cout<<(char) 205;
            }
    }
}

void clearsnake()
{
    for(int i=1;i<chieurong;i++)
    {
        for(int j=1;j<chieudai;j++)
        {
            gotoxy(i,j);
            TextColor(15);
            cout<<" ";
        }
    }
}

void draw()
{
    clearsnake();
    for (int k = 0; k < nTail; k++)
                {
                    

                    gotoxy(tailX[k], tailY[k]);
                    cout<<(char)1;
                }
    gotoxy(x,y);
    cout<<(char)2;
    gotoxy(fruitX,fruitY);
    cout<<(char)3;
    gotoxy(0,0);
    TextColor(70);
    cout<<(char) 201;
    TextColor(15);
    
}

void Input() // nhap vao tu ban phim
{
    if (_kbhit())
    {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameover = true;
            break;
        }
    }
}

void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }
    
    if (x >= chieudai-1) x = 1; else if (x <= 0) x = chieudai - 1;
    if (y >= chieurong) y = 1; else if (y <= 0) y = chieurong - 1;
 
    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            gameover = true;
 
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        fruitX = rand() % (chieudai-2) +1;
        fruitY = rand() % (chieurong-2) +1;
        nTail++;
    }
}


void menu()
{
    // system("cls");
    TextColor(202);
            gotoxy(33, 10); printf("%c  PLAY GAME  ", 175);
            TextColor(14);
            gotoxy(33, 11); printf("  1.HARD         ");
            gotoxy(33, 12); printf("  2.NORMAL        ");
            gotoxy(33, 13); printf("  3.EASY   ");
            // gotoxy(33, 14); printf("  EXIT         ");
            gotoxy(33,14) ; printf("  Nhap do kho:");
            while(chuachon==true)
            {
                cin>>n;
                if(n=="1"){speedd=100;chuachon=false;}
                if(n=="2"){speedd=200;chuachon=false;}
                if(n=="3"){speedd=300;chuachon=false;}
            }
         system("cls");
}

int main()
{
    menu();
    setup();
    vekhung();
    while(gameover==false)
    {
        draw();
        Input();
        Logic();
        this_thread::sleep_for(chrono::milliseconds(speedd));
    }
    gotoxy(chieudai+1,chieurong+1);
    cout<<endl;
    cout<<"score="<<score;
    this_thread::sleep_for(chrono::milliseconds(150000));
}