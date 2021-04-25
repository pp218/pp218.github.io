#include<cstdio>
#include<windows.h>
#include<ctime>
int a[4][4],i,j,xc,yc,mouse=0,ok=0,record[2][9],foot=9,winner,first=0,who=0;
void Place(const int x, const int y) 
{ COORD PlaceCursorHere;PlaceCursorHere.X = y;PlaceCursorHere.Y = x;
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), PlaceCursorHere);
return;
}
void color(int x)
{SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);}
int search(int x0,int y0,int x,int y)
{
mouse=GetAsyncKeyState(VK_LBUTTON);
POINT pt; HWND h=GetForegroundWindow(); GetCursorPos(&pt); ScreenToClient(h,&pt);
if(pt.x>=x0&&pt.y>=y0&&pt.x<=x&&pt.y<=y)
{
if(mouse!=0) {Sleep(100); return 2;} else return 1;
}
else return 0;
}
bool check(int x)
{
int b=0,c=0,d=0,e=0;
for(i=1;i<=3;i++)
{
for(j=1;j<=3;j++) {b+=a[i][j]; c+=a[j][i];} d+=a[i][i]; e+=a[i][4-i];
if(b==x||c==x||d==x||e==x) return true; b=0; c=0;
}
return false;
}
void pcmove()
{
int x=10,b=0,c=0,d=0,e=0; xc=0; yc=0;
while(x>0)
{
for(i=1;i<=3;i++)
{
b=0; c=0; for(j=1;j<=3;j++) {b+=a[i][j]; c+=a[j][i];} d+=a[i][i]; e+=a[i][4-i];
if(b==x) {for(j=1;j<=3;j++) if(a[i][j]==0) {xc=i; yc=j; return;}} if(c==x) {for(j=1;j<=3;j++) if(a[j][i]==0) {xc=j; yc=i; return;}}
if(d==x) {for(j=1;j<=3;j++) if(a[j][j]==0) {xc=yc=j; return;}} if(e==x) {for(j=1;j<=3;j++) if(a[j][4-j]==0) {xc=j; yc=4-j; return;}}
} x-=8;
}
if(a[2][2]==0) {xc=yc=2; return;} x=2;
while(x>0) {for(i=1;i<=3;i+=x) for(j=1;j<=3;j+=x) if(a[i][j]==0) {xc=i; yc=j; return;} x--;}
}
void show()
{
int x=foot;
for(i=1;i<=3;i++) for(j=1;j<=3;j++) if(a[i][j]!=0) {if(a[i][j]==1) color(15); else color(11); Place(2*i-1,4*j-2); printf("●");}
color(15); Place(7,0);
if(who==0) {if(foot%2==1) printf("1号"); else printf("2号");} else printf("电脑");
if(who==0||first==1) x--;
printf("下子:(%d,%d)",record[0][8-x],record[1][8-x]);
}
void button(int x)
{
if(x<3)
{
Place(x*3,15); printf("┌┄┄┐");
Place(x*3+1,17); if(x==0){if(ok==0) printf("开始"); else printf("悔棋");} if(x==1) printf("重来"); if(x==2) printf("退出");
Place(x*3+2,15); printf("└┄┄┘");
}
if(x>2&&x<6)
{
Place(10,(x-4)*7); printf("┌┄┐");
Place(11,(x-4)*7+2); if(x==4) printf("是"); else printf("否");
Place(12,(x-4)*7); printf("└┄┘");
}
if(x>5&&x<8)
{
Place(10,(x-6)*12); printf("┌┄┄┄┄┐");
Place(11,(x-6)*12+2); if(x==6) printf("人机对战"); else printf("人人对战");
Place(12,(x-6)*12); printf("└┄┄┄┄┘");
}
if(x>7)
{
Place(10,(x-8)*12); printf("┌┄┄┄┄┐");
Place(11,(x-8)*12+2); if(x==8) printf(" 我先手 "); else printf("电脑先手");
Place(12,(x-8)*12); printf("└┄┄┄┄┘");
}
}
void menu(int x)
{
int k,l;
if(x==0)
{
if(ok==0) {ok=1; return;}
else if(9-foot>1)
{
foot+=2; for(i=9-foot;i<=11-foot;i++) {a[record[0][i]][record[1][i]]=0; record[0][i]=record[1][i]=0;}
for(i=1;i<=3;i++) for(j=1;j<=3;j++) {Place(2*i-1,4*j-2); printf(" ");} show();
}
}
if(x>0&&x<3)
{
for(l=10;l<=12;l++) for(j=1;j<=22;j++) {Place(l,j); printf(" ");}
Place(9,1); printf("你想"); if(x==1) printf("重来吗？"); if(x==2) printf("退出吗？");
button(4); button(5);
while(1)
{
mouse=GetAsyncKeyState(VK_LBUTTON);
for(i=0;i<=1;i++)
{
k=search(7+i*55,165,40+i*55,200);
if(k!=2) {if(k==1) color(15); else color(7); button(i+4);}
else 
{for(l=9;l<=12;l++) for(j=1;j<=12;j++) {Place(l,j); printf(" ");}
if(i==0) {if(x==1) ok=2; else exit(0);} return;
} 
}
Sleep(50);
}
}
if(x>2&&x<5) {if(x==3) {who=1; return;} else {who=0; return;}}
if(x>4) {if(x==5) {first=0; return;} else {first=1; return;}}
}
void click()
{
for(i=0;i<=2;i++) 
{ mouse=GetAsyncKeyState(VK_LBUTTON);
int k=search(125,i*50+5,175,i*50+40);
if(k!=2) {if(k==1) color(15); else color(7); button(i); color(7);}
else{menu(i); return;} 
}
Sleep(50);
}
void humove()
{
while(1)
{
for(i=1;i<=3;i++) for(j=1;j<=3;j++) if(search(7+(i-1)*32,7+(j-1)*32,7+i*32,7+j*32)==2&&a[j][i]==0)
{if(who==0&&foot%2!=1) a[j][i]=5; else a[j][i]=1; record[0][9-foot]=j; record[1][9-foot]=i; return;} click(); if(ok==2) return;
}
}
void replace()
{
int k,l,p,q;
Place(7,0); for(i=1;i<=15;i++) printf(" "); for(i=1;i<=3;i++) for(j=1;j<=3;j++) {Place(2*i-1,4*j-2); printf(" "); a[i][j]=0;}
for(i=0;i<2;i++) for(j=0;j<9;j++) record[i][j]=0; foot=9; winner=0; first=0; who=0; ok=1; button(6); button(7);
while(1)
{
for(i=0;i<=1;i++)
{
mouse=GetAsyncKeyState(VK_LBUTTON); k=search(i*80+7,165,i*80+103,200); q=search(125,105,175,140);
if(k!=2) {if(k==1) color(15); else color(7); button(i+6); color(7);} 
else 
{
menu(i+3); for(l=10;l<=12;l++) for(j=1;j<=22;j++) {Place(l,j); printf(" ");}
if(who==1)
{
button(7); button(8);
while(1)
{
for(j=0;j<=1;j++)
{
mouse=GetAsyncKeyState(VK_LBUTTON); k=search(j*80+7,165,j*80+103,200); q=search(125,105,175,140);
if(k!=2) {if(k==1) color(15); else color(7); button(j+8); color(7);}
else{menu(j+5); for(l=10;l<=12;l++) for(p=1;p<=22;p++) {Place(l,p); printf(" ");} return;}
if(q!=2) {if(q==1) color(15); else color(7); button(2); color(7);} else menu(2);
} Sleep(50);
}
}
return;
}
if(q!=2) {if(q==1) color(15); else color(7); button(2); color(7);} else menu(2);
}
Sleep(50);
}
}
int main()
{
printf("┌─┬─┬─┐\n\n├─┼─┼─┤\n\n├─┼─┼─┤\n\n└─┴─┴─┘\n\n");
for(i=0;i<3;i++) button(i);
while(ok==0) click();
while(1)
{
replace();
while(foot>0&&ok!=0)
{
if(first!=1) {humove(); show(); if(check(3)) {winner=1; ok=0; break;} foot--; if(foot<=0||ok==0||ok==2) break;}
if(who==0&&check(15)) {winner=2;ok=0;break;}
if(who!=0) {pcmove(); record[0][9-foot]=xc; record[1][9-foot]=yc; a[xc][yc]=5; show(); if(check(15)) {winner=2;ok=0;} foot--; first=0;}
}
if(ok==2) {ok=1; continue;} Place(7,0); for(i=1;i<=15;i++) printf(" ");
Place(7,4); color(15); if(winner==0) printf("平局!");
if(who!=0) {if(winner==1) printf("你赢了!"); if(winner==2) printf("你输了!"); Sleep(50);}
else {if(winner==1) printf("1号赢了!"); if(winner==2) printf("2号赢了!"); Sleep(50);}
ok=0; while(ok==0) click();
}
}
