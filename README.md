//Author zlynn 2020.2.13,sleeping//
#include<iostream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
using namespace std;
int chessb[18][18];//18×18的棋盘为扫雷的方法//
int chessa[18][18];//18x18的模拟棋盘//
int winb(int x,int y,int c);//判断谁赢的函数，x为横坐标，y为纵坐标，c为下黑白棋的指标(flag%2为0还是1)，如果c=1则为白棋，c=0则为黑棋//
int wina(int x,int y,int c);
int fullb();//判断是否下满整个棋盘//
int fulla();
void getbest(int x,int y,int c);
int pcwinchance(int i,int j);//计算胜率//
int pclosechance(int i,int j);
int max(int i,int j);
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
                if(winb(a,b,1)==-1)
                    {
                        cout<<"you win"<<endl;
                        break;
                    }
                if(winb(a,b,0)==1)
                    {
                        cout<<"you lose"<<endl;
                        break;
                    }
            }
        }
        flag--;
    }
}

int winb(int x,int y,int c)//return1为黑棋赢，return-1为白棋赢,不return则继续下棋//
{
    int i,j,k,k1,k2,sum=0;
    int a=x+4;
    int b=y+4;
    for(i=a-4;i<a+1;i++)//判断横向有没有五子连珠//
    {
        for(k=i,sum=0;k<i+5;k++) sum=sum+chessb[k][b];
        if(c==0&&sum==5) return 1;
        if(c==1&&sum==-5) return -1;
    }
    for(j=b-4;j<b+1;j++)// 判断纵向有没有五子连珠//
    {
        for(k=j,sum=0;k<j+5;k++) sum=sum+chessb[a][k];
        if(c==0&&sum==5) return 1;
        if(c==1&&sum==-5) return -1;
    }
    for(i=a+4,j=b-4;i>a-1,j<b+1;i--,j++)//判断斜右上方//
    {
        for(k1=i,k2=j,sum=0;k1>i-5,k2<j+5;k1--,k2++) sum=sum+chessb[k1][k2];
        if(c==0&&sum==5) return 1;
        if(c==1&&sum==-5) return -1;
    }
    for(i=a-4,j=b-4;i<a+1,j<b+1;i++,j++)//判断斜左上方//
    {
        for(k1=i,k2=j,sum=0;k1<i+5,k2<j+5;k1++,k2++) sum=sum+chessb[k1][k2];
        if(c==0&&sum==5) return 1;
        if(c==1&&sum==-5) return -1;
    }
}

int wina(int x,int y,int c)//return1为黑棋赢，return-1为白棋赢,不return则继续下棋//
{
    int i,j,k,k1,k2,sum=0;
    int a=x+4;
    int b=y+4;
    for(i=a-4;i<a+1;i++)//判断横向有没有五子连珠//
    {
        for(k=i,sum=0;k<i+5;k++) sum=sum+chessa[k][b];
        if(c==0&&sum==5) return 1;
        if(c==1&&sum==-5) return -1;
    }
    for(j=b-4;j<b+1;j++)// 判断纵向有没有五子连珠//
    {
        for(k=j,sum=0;k<j+5;k++) sum=sum+chessa[a][k];
        if(c==0&&sum==5) return 1;
        if(c==1&&sum==-5) return -1;
    }
    for(i=a+4,j=b-4;i>a-1,j<b+1;i--,j++)//判断斜右上方//
    {
        for(k1=i,k2=j,sum=0;k1>i-5,k2<j+5;k1--,k2++) sum=sum+chessa[k1][k2];
        if(c==0&&sum==5) return 1;
        if(c==1&&sum==-5) return -1;
    }
    for(i=a-4,j=b-4;i<a+1,j<b+1;i++,j++)//判断斜左上方//
    {
        for(k1=i,k2=j,sum=0;k1<i+5,k2<j+5;k1++,k2++) sum=sum+chessa[k1][k2];
        if(c==0&&sum==5) return 1;
        if(c==1&&sum==-5) return -1;
    }
}

int fullb()//返回值为0则为满的情况，为1则为未下满//
{
    int i,j,flag=0;
    for(i=4;i<14;i++){
        for(j=4;j<14;j++){
            if(chessb[i][j]==0)
                flag=1;
        }
    }
    return flag;
}

int fulla()//返回值为0则为满的情况，为1则为未下满//
{
    int i,j,flag=0;
    for(i=4;i<14;i++){
        for(j=4;j<14;j++){
            if(chessa[i][j]==0)
                flag=1;
        }
    }
    return flag;
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
                lost=pclosechance(i,j);
                i1=i;
                j1=j;
                i2=i;
                j2=j;
                break;
            }
        }
        if(lost!=0)
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
                if(wina(x,y,1)==-1){
                    fp++;
                    break;
                }
                if(fulla()==0)
                    break;
            }
            x=rand()%10;
            y=rand()%10;
            if(chessa[x+4][y+4]==0){
                chessa[x+4][y+4]=1;
                if(wina(i-4,j-4,0)==1){
                    fc++;
                    break;
                }
                if(fulla()==0)
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
                if(wina(x,y,0)==1){
                    fc++;
                    break;
                }
                if(fulla()==0)
                    break;
            }
            x=rand()%10;
            y=rand()%10;
            if(chessa[x+4][y+4]==0){
                chessa[x+4][y+4]=-1;
                if(wina(i-4,j-4,1)==-1){
                    fp++;
                    break;
                }
                if(fulla()==0)
                    break;
            }
        }
    }
        return fp;
}
