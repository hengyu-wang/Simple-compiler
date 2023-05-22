#include<iostream>
#include<string>
#include<cstring>
using namespace std;

template <class T>  //作为模板类，可以给T传递int,char类型等
class Stack
{
public:
    T sta[20];
    int num;
    Stack(){num=0;}
    void push_back(T t){
        sta[num++]=t;
    }
    T top(){
        if(num>0)return sta[num-1];
    }
    void pop(){
        if(num>0)num--;
    }
    bool empty(){
        return !num;
    }
};

struct Op{
    int type;   //1--移进；2--规约；3--acc；S1中的S
    int idx;   //横坐标--状态：当前项目集规范组的标号
    int go;   //goto，对应一个状态，如S1中的1
};

Stack<int> stu;     //状态栈
Stack<char> sym;    //符号栈
Stack<char> ipt;    //输入串
Op table_action[10][3];     //action表
Op table_goto[10][2];       //goto表

Op findop(char cch,int cnum)   //根据当前的字符和数字查找相应的操作并返回
{
    int line;
    if(cch=='a')line=0;
    if(cch=='b')line=1;
    if(cch=='#')line=2;     //三个终结符
    return table_action[cnum][line];
}

int findgoto(char ch,int idx)
{
    int line;
    if(ch=='S')line=0;
    if(ch=='B')line=1;    //两个非终结符
    return table_goto[idx][line].idx;       //idx是项目集规范组的索引(某个状态)
}

bool cut(int idx)
{
    if(idx==0)
    {
        if(sym.top()=='S')
        {
            sym.pop();
            sym.push_back('E');
            stu.pop();//
            return 1;
        }
    }
    else if(idx==1)
    {
        if(sym.num>=2 && sym.sta[sym.num-1]=='B' && sym.sta[sym.num-1]=='B')
        {
            sym.pop();
            sym.pop();
            sym.push_back('S');
            stu.pop();//
            stu.pop();//
            return 1;
        }
    }
    else if(idx==2)
    {
        if(sym.num>=2 && sym.sta[sym.num-1]=='B' && sym.sta[sym.num-1]=='a')
        {
            sym.pop();
            sym.pop();
            sym.push_back('B');
            stu.pop();
            stu.pop();
            return 1;
        }
    }
    else if(idx==3)
    {
        if(sym.top()=='b')
        {
            sym.pop();
            sym.push_back('B');
            stu.pop();//
            return 1;
        }
    }
    return 0;
}


int time=1;
void show(Op op)
{
    printf("%d\t",time++);
    for(int i=0;i<stu.num;i++)
        cout<<stu.sta[i];   //状态栈
    printf("\t");
    for(int i=0;i<sym.num;i++)
        cout<<sym.sta[i];   //符号栈
    printf("\t");
    for(int i=ipt.num-1;i>=0;i--)
        cout<<ipt.sta[i];   //输入串
    printf("\t");
    if(op.type==1)  //1表示移进
        printf("S%d",op.idx);
    if(op.type==2)  //2表示规约
        printf("r%d",op.idx);
    if(op.type==3)  //3表示接收
        printf("acc");
    printf("\t");

}

void work()
{
    char cch;
    int cnum;
    bool complete=0;
    while(complete!=1)
    {
        cch=ipt.top();      //cch 当前输入字符串(终结符)
        cnum=stu.top();     //cnum 当前状态
        Op op=findop(cch,cnum);   //通过当前输入串和状态去action表中找到相应op（）
        show(op);           //打印一行

        if(op.type==1)      //移进
        {
            sym.push_back(ipt.top());
            ipt.pop();
            stu.push_back(op.idx);
        }
        else if(op.type==3)//终止
        {
            return ;
        }
        else
        {
            cut(op.idx);   //规约
            op.go=findgoto(sym.top(),stu.top());
            stu.push_back(op.go);
            cout<<op.go;
        }
        cout<<endl;
    }
}

void init()     //给出LR1分析表
{
    table_action[0][0].type=1;	table_action[0][0].idx=3;
    table_action[0][1].type=1;	table_action[0][1].idx=4;
    table_action[1][2].type=3;	table_action[1][2].idx=0;
    table_action[2][0].type=1;	table_action[2][0].idx=6;
    table_action[2][1].type=1;	table_action[2][1].idx=7;
    table_action[3][0].type=1;	table_action[3][0].idx=3;
    table_action[3][1].type=1;	table_action[3][1].idx=4;
    table_action[4][0].type=2;	table_action[4][0].idx=3;
    table_action[4][1].type=2;	table_action[4][1].idx=3;
    table_action[5][2].type=2;	table_action[5][2].idx=1;
    table_action[6][0].type=1;	table_action[6][0].idx=6;
    table_action[6][1].type=1;	table_action[6][1].idx=7;
    table_action[7][2].type=2;	table_action[7][2].idx=3;
    table_action[8][0].type=2;	table_action[8][0].idx=2;
    table_action[8][1].type=2;	table_action[8][1].idx=2;
    table_action[9][2].type=2;	table_action[9][2].idx=2;

    table_goto[0][0].type=0;		table_goto[0][0].idx=1;
    table_goto[0][1].type=0;		table_goto[0][1].idx=2;
    table_goto[2][1].type=0;		table_goto[2][1].idx=5;
    table_goto[3][1].type=0;		table_goto[3][1].idx=8;
    table_goto[6][1].type=0;		table_goto[6][1].idx=9;
}
int main()
{
    init();
    string str;
    getline(cin,str,'#');

    ipt.push_back('#');
    for(int i=0;i<str.size();i++)
    {
        ipt.push_back(str[i]);
    }
    sym.push_back('#');
    stu.push_back(0);
    work();
    return 0;
}