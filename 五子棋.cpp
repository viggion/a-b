//Author zlynn 2020.2.13,sleeping//
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;
int chessb[18][18];//18×18的棋盘为扫雷的方法//
int chessa[18][18];//18x18的模拟棋盘//
int win(int x,int y,int c);//判断谁赢的函数，x为横坐标，y为纵坐标，c为下黑白棋的指标(flag%2为0还是1)，如果c=1则为白棋，c=0则为黑棋//
int full(int z);//判断是否下满整个棋盘//
void getbest(int x,int y,int c);
int pcwinchance(int i,int j);//计算胜率//
int pclosechance(int i,int j);
int main()
{
    int i,j,x,y,a,b,flag=1;
    srand(int(time(0)));
    while(1)
    {
        cin>>i>>j;
        x=i-1;
        y=j-1;
        if(i>0&&i<11&&j>0&&j<11){
            if(chessb[i+3][j+3]==0){
                if(flag%2==0) {
                    chessb[i+3][j+3]=1;//输入坐标在棋盘中央，故横纵坐标各加4//       
                    chessa[i+3][j+3]=1;//模拟棋盘下子//
                }
                else 
                {
                    chessb[i+3][j+3]=-1;
                    chessa[i+3][j+3]=-1;
                }
            }
            else{
                    cout<<"There isn't available"<<endl;
                }
        }
        else{
            cout<<"Input error!Please input again"<<endl;
            }
        flag++;//该电脑下//
        getbest(x,y,flag%2);
        for(i=4;i<14;i++){
            for(j=4;j<14;j++) 
            {
                if(chessb[i][j]==1)
                    cout<<setw(3)<<"+";
                if(chessb[i][j]==-1)
                    cout<<setw(3)<<"-";
                if(chessb[i][j]==0)
                    cout<<setw(3)<<"o";
            }
            cout<<endl;
        }
        for(a=0;a<10;a++)
        {
            for(b=0;b<10;b++)
            {
                if(win(a,b,1)==-1)
                    {
                        cout<<"you win"<<endl;
                        break;
                    }
                if(win(a,b,0)==1)
                    {
                        cout<<"you lose"<<endl;
                        break;
                    }
            }
        }
        flag--;
    }
}

int win(int x,int y,int c)//return1为黑棋赢，return-1为白棋赢,不return则继续下棋//
{
    int i,j,k,k1,k2,suma=0,sumb=0;
    int a=x+4;
    int b=y+4;
    for(i=a-4;i<a+1;i++)//判断横向有没有五子连珠//
    {
        for(k=i,sumb=0,suma=0;k<i+5;k++) {
            sumb=sumb+chessb[k][b];
            suma=suma+chessa[k][b];
        }
        if(c==0&&sumb==5) return 1;
        if(c==1&&sumb==-5) return -1;
        if(c==0&&suma==5) return 2;
        if(c==1&&suma==-5) return -2;
    }
    for(j=b-4;j<b+1;j++)// 判断纵向有没有五子连珠//
    {
        for(k=j,suma=0,sumb=0;k<j+5;k++) {
            sumb=sumb+chessb[a][k];
            suma=suma+chessa[a][k];
        }
        if(c==0&&sumb==5) return 1;
        if(c==1&&sumb==-5) return -1;
        if(c==0&&suma==5) return 2;
        if(c==1&&suma==-5) return -2;
    }
    for(i=a+4,j=b-4;i>a-1,j<b+1;i--,j++)//判断斜右上方//
    {
        for(k1=i,k2=j,suma=0,sumb=0;k1>i-5,k2<j+5;k1--,k2++) {
            sumb=sumb+chessb[k1][k2];
            suma=suma+chessa[k1][k2];
        }
        if(c==0&&sumb==5) return 1;
        if(c==1&&sumb==-5) return -1;
        if(c==0&&suma==5) return 2;
        if(c==1&&suma==-5) return -2;
    }
    for(i=a-4,j=b-4;i<a+1,j<b+1;i++,j++)//判断斜左上方//
    {
        for(k1=i,k2=j,sumb=0,suma=0;k1<i+5,k2<j+5;k1++,k2++) {
            sumb=sumb+chessb[k1][k2];
            suma=suma+chessa[k1][k2];
        }
        if(c==0&&sumb==5) return 1;
        if(c==1&&sumb==-5) return -1;
        if(c==0&&suma==5) return 2;
        if(c==1&&suma==-5) return -2;
    }
}

int full(int z)
{
    int i,j,flagb=0,flaga=0;
    for(i=4;i<14;i++){
        for(j=4;j<14;j++){
            if(chessb[i][j]==0)
                flagb=1;
            if(chessa[i][j]==0)
                flaga=-1;
        }
    }
    if(z==1)
        return flagb;
    if(z==-1)
        return flaga;
}

void getbest(int x,int y,int c)//下在胜率最高的点上//
{
    int i,j,z,i1,j1,i2,j2;
    int takeone,taketwo,best=0,lost=0,m1,m2;
    for(i=4;i<14;i++)
    {
        for(j=4;j<14;j++)
        {
            if(chessb[i][j]==0)
            {
                best=pcwinchance(i,j);
                lost=best;
                i1=i;
                j1=j;
                i2=i;
                j2=j;
                break;
            }
        }
        if(best!=0)
            break;
    }

    if(c==0)
    {
        for(i=4;i<14;i++)
        {
            for(j=4;j<14;j++)
            {
                if((i!=x+4||j!=y+4)&&chessb[i][j]==0)
                {
                    takeone=pcwinchance(i,j);
                    if(takeone>best)
                    {
                        best=takeone;
                        i1=i;
                        j1=j;
                    }
                }
            }
        }
    }
    
    if(c==0)
    {
        for(i=4;i<14;i++)
        {
            for(j=4;j<14;j++)
            {
                if((i!=x+4||j!=y+4)&&chessb[i][j]==0)
                {
                    taketwo=pclosechance(i,j);
                    if(taketwo>lost)
                    {
                        lost=taketwo;
                        i2=i;
                        j2=j;
                    }
                }
            }
        }
    }
    if(best>lost)
        chessb[i1][j1]=1;
    else
        chessb[i2][j2]=1;
}

int pcwinchance(int i,int j){//计算胜率//
    int fc=0,fp=0,z,x,y,i1=i,i2=i,j1=j,j2=j,k,t,n=0;
    for(z=1;z<=10000;z++){
        for(k=4;k<14;k++)
            for(t=4;t<14;t++) 
                chessa[k][t]=chessb[k][t];//虚拟棋盘初始化到真实棋盘状态//

        chessa[i][j]=1;  //added by zcf
        n=0;
        while(1){
            n++;
            x=rand()%10;
            y=rand()%10;
            if(chessa[x+4][y+4]==0){
                chessa[x+4][y+4]=-1;
                if(win(x,y,1)==-2){
                    fp++;
                    break;
                }
                if(full(-1)==0)
                    break;
            }
            x=rand()%10;
            y=rand()%10;
            if(chessa[x+4][y+4]==0){
                chessa[x+4][y+4]=1;
                if(win(i-4,j-4,0)==2){
                    fc++;
                    break;
                }
                if(full(-1)==0)
                    break;
            }
        }
    }
        return fc;
} 

int pclosechance(int i,int j){//计算胜率//
    int fc=0,fp=0,z,x,y,i1=i,i2=i,j1=j,j2=j,k,t,n=0;
    for(z=1;z<=10000;z++){
        for(k=4;k<14;k++)
            for(t=4;t<14;t++) 
                chessa[k][t]=chessb[k][t];//虚拟棋盘初始化到真实棋盘状态//

        chessa[i][j]=-1;  //added by zcf
        n=0;
        while(1){
            n++;
            x=rand()%10;
            y=rand()%10;
            if(chessa[x+4][y+4]==0){
                chessa[x+4][y+4]=1;
                if(win(x,y,0)==2){
                    fc++;
                    break;
                }
                if(full(-1)==0)
                    break;
            }
            x=rand()%10;
            y=rand()%10;
            if(chessa[x+4][y+4]==0){
                chessa[x+4][y+4]=-1;
                if(win(i-4,j-4,1)==-2){
                    fp++;
                    break;
                }
                if(full(-1)==0)
                    break;
            }
        }
    }
        return fp;
}