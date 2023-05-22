#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stack>
#include<cstring>

using namespace std;

struct Item{
    int type;
    double value;
    char ch;
    Item(int t,double v){type=t;value=v;}
    Item(int t,int v){type=t;value=v;}
    Item(int t,char c){type=t;ch=c;}
};
vector<Item> polan;

int cmpch(char ch1,char ch2)
{
    int n1,n2;
    if(ch1=='(')n1=1;
    if(ch1=='+'||ch1=='-')n1=2;
    if(ch1=='*'||ch1=='/')n1=3;
    if(ch2=='(')n2=1;
    if(ch2=='+'||ch2=='-')n2=2;
    if(ch2=='*'||ch2=='/')n2=3;
    return n1-n2;
}

void printPolan()
{
    for(int i=0;i<polan.size();i++)
    {
        if(polan[i].type==1)
            cout<<polan[i].value<<"_";
        else if(polan[i].type==2)
            cout<<polan[i].ch<<"_";
    }
    cout<<endl;
}

void work()
{
    char str[100],strtmp[100];
    cin.getline(str,50,'#');
    int i,j,len=strlen(str);
    double tmp;
    char ch;
    vector<Item>ready;

    for(i=0;i<len;i++)
    {
        ch=str[i];
        if(ch==10)continue;

        if(ch>='0' && ch<='9')
        {
            sscanf(str+i,"%lf",&tmp);   //从str+i字符串开始读入一个数字型字符串（200-1-1则读到的是200）
            ready.push_back(Item(1,tmp));   //将1，tmp压栈
            while(str[i]>='0' && str[i]<='9')i++;   //指针后移，一直移到下一个非数字字符（可能是小数点）
            if(str[i]=='.')
            {
                i++;
                while(str[i]>='0' && str[i]<='9')i++;
            }
            i--;  //将指针后移到读取完的double类型数据的最后一位（该循环结束后i会++，移到下一个非数字字符）
        }
        else if(ch=='+' ||ch=='-' ||ch=='*' ||ch=='/' )
        {
            ready.push_back(Item(2,ch));  //将符号压栈，类型type=2
        }
        else if(ch=='(' )
        {
            ready.push_back(Item(3,ch));
        }
        else if(ch==')' )
        {
            ready.push_back(Item(4,ch));
        }
        else if(ch==' '){
            continue;
        }
        else
        {
            cout<<"illegel char error!"<<endl;
            return ;
        }
    }


    polan.clear();  //vactor.clear只会把vector的size清0，但是不会回收这一段内存，即将当前vector中的值视为垃圾数据
    stack<Item> sta;  //栈:用于存放运算符
    for(i=0;i<ready.size();i++)     //所有数字+运算符
    {
        if(ready[i].type==1)
        {
            polan.push_back(ready[i]);      //遇到数字直接放入
        }
        else if(ready[i].type==2)
        {
            if(sta.empty()==1)
                sta.push(ready[i]);
            else
            {
                while(sta.empty()!=1 && cmpch(ready[i].ch,sta.top().ch)<0)	//比栈顶的符号优先级要小
                {
                    polan.push_back(sta.top());  //如果遇到的是符号：需要将当前栈顶所有优先级大于等于当前符号的运算符弹栈、压入polan;
                    sta.pop();
                }
                sta.push(ready[i]);  //将所有优先级不小于当前运算符的运算符弹栈后，将当前运算符压栈
            }
        }
        else if(ready[i].type==3)
        {
            sta.push(ready[i]);     //如果是左括号，直接压栈
        }
        else if(ready[i].type==4)       //如果是右括号，则将运算符栈中的运算符依次弹栈，直到弹出左括号 (
        {
            while(sta.empty()!=1 && sta.top().ch!='(')
            {
                polan.push_back(sta.top());
                sta.pop();
            }
            if(sta.top().ch=='(')
                sta.pop();
            else if(sta.empty()==1)
            {   //如果弹不出左括号，一直到栈空，就报错；
                cout<<"error!"<<endl;
                return;
            }
        }
        else
        {
            cout<<"type error!"<<endl;
            return;
        }
    }
    while(sta.empty()!=1)
    {   //最后可能还剩下了运算符，将其压到逆波兰栈中
        polan.push_back(sta.top());
        sta.pop();
    }
    printPolan();
}

double process(double a,double b,char ch)
{
    switch(ch)
    {
        case '+':return a+b;break;
        case '-':return a-b;break;
        case '*':return a*b;break;
        case '/':return a/b;break;
    }
}

void count() {
    stack<double> commuteStack;     //用于存放数字（不存运算符）
    int i, j;
    double cur, ex;
    for (i = 0; i < polan.size(); i++) {    //后缀表达式的特点是从前往后分析，只要遇到运算符就将前面两个数字通过该运算符进行运算
        if (polan[i].type == 1)
            commuteStack.push(polan[i].value);
        else {
            cur = commuteStack.top();
            commuteStack.pop();
            if (commuteStack.empty() == 1) {
                cout << "stack error!" << endl;
                return ;
            }
            ex = commuteStack.top();
            commuteStack.pop();
            //进行运算
            commuteStack.push(process(ex, cur, polan[i].ch));
        }

    }
    //输出运算结果
    cout << commuteStack.top() << endl;

}
int main()
{
    freopen("D:\\CSP\\Simple-compiler\\in.txt","r",stdin);
    work();
    count();
    return 0;
}