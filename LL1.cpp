#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
#define SIZE 1000
//一个文法对应一个分析程序
char A[20];      /*分析栈*/
char B[20];      /*剩余串*/
char v1[20]={'i','+','*','(',')','#'};/*终结符  */
char v2[20]={'E','G','T','S','F'};/*非终结符   */
int j=0,b=0,top=0,l;       /*L为输入串长度 */

typedef struct type   /*产生式类型定义*/
 {
	char origin;   /*大写字符  */
	char array[5];   /*产生式右边字符 */
	int length;/*字符个数      */
 }type;

type e,t,g,g1,s,s1,f,f1;/*结构体变量；根据题目给出的文法来显示  */
type C[10][10];/*预测分析表：栈顶符号遇到当前输入字符串时执行某个具体的动作：与当前栈顶符号的first集合和follow集合相关   */
void print()/*输出分析栈  */
{
	int a;/*指针*/
	for(a=0;a<=top+1;a++)   //多打了一个空格
		printf("%c",A[a]);
	printf("\t\t");
 }
void print1()/*输出剩余串*/
{
	int j;
	for(j=0;j<b;j++)/*输出对齐符*/
		printf(" ");
	for(j=b;j<=l;j++)
		printf("%c",B[j]);
	printf("\t\t\t");
}

//主分析过程
void work()
{
	char ch,x;
	bool flag;
	int i=0,j=0,k=0,finish,m,n;
	type cha;
	j=0,b=0,top=0,l;/*L为输入串长度 */

	do   /*读入分析串*/
	{
	   scanf("%c",&ch);     //每次只读入一个字符串
	   if ((ch!='i') &&(ch!='+') &&(ch!='*')&&(ch!='(')&&(ch!=')')&&(ch!='#'))
	   {
		   printf("输入串中有非法字符\n");
		   return;
	   }
	   B[j]=ch;     //B = [i,+,i,*,i,#]
	   j++;
	}while(ch!='#');

   l=j; /*分析串长度*/
   ch=B[0]; /*当前分析字符*/
   A[top]='#';  //初始化时top为0
   A[++top]='E';  /*'#','E'进栈*/
   printf("步骤\t\t分析栈 \t\t剩余字符 \t\t所用产生式 \n");
   printf("start\t\t");

   //打印当前分析栈和剩余字符
   print();
   print1();
   printf("\n");

    do
    {
        //从栈顶弹出一个字符串
        x=A[top--];/*x为当前栈顶字符*/
        printf("%d",k++);       //表示第k轮
        printf("\t\t");
        flag=0;
        for(j=0;j<=5;j++)  /*判断是否为终结符*/
            if(x==v1[j])
            {
                flag=1;
                break;
            }

		  if(flag==1)/*如果是终结符*/
		  {
              if(x=='#')
			  {
                  finish=1;/*结束标记*/
				  printf("acc!\n");/*接受 */
				  getchar();    //再按两个回车结束程序
				  getchar();
				  return;
              }
			  if(x==ch)
			  {
                  print();
				  print1();
				  printf("%c匹配\n",ch);
				  ch=B[++b];/*下一个输入字符*/
				  flag=0;/*恢复标记*/
              }
			  else/*出错处理*/
			  {
                  print();
				  print1();
				  printf("%c出错\n",ch);/*输出出错终结符*/
				  return;
              }
          }

        else       /*非终结符处理*/
        {
            //x是当前栈顶字符、ch是当前输入字符
            //以x为行，ch为列寻找分析表中对应的表达式
            for(j=0;j<=4;j++)
                if(x==v2[j])
				{
				    m=j;/*用m记录下行号*/
				    break;
                }
            for(j=0;j<=5;j++)
                if(ch==v1[j])
                {
                    n=j;/*列号*/
                    break;
                }
            cha=C[m][n];
            if(cha.origin!='N')/*判断是否为空*/
            {
                print();
                print1();
				printf("%c->",cha.origin);/*输出产生式*/

                printf("%s",cha.array);
				printf("\n");
		        for(j=(cha.length-1);j>=0;j--)/*产生式逆序入栈*/
			    A[++top]=cha.array[j];
		         if(A[top]=='^')/*为空则不进栈*/
			        top--;
			}
            else {
                //如果是空说明分析出错
				printf("sorry the input have error!\n");
				return;
			}
}


    }
    while(B[l]!='#');


}
void inital()
{
	int m,n;
	  /*把文法产生式赋值结构体*/
	e.origin='E';           //E->TG
	strcpy(e.array,"TG");
	e.length=strlen(e.array);

    t.origin='T';
	strcpy(t.array,"FS");
	t.length=strlen(t.array);

	g.origin='G';
	strcpy(g.array,"+TG");
	g.length=strlen(g.array);

	g1.origin='G';
	g1.array[0]='^';
	g1.length=strlen(g1.array);

	s.origin='S';
	strcpy(s.array,"*FS");
	s.length=strlen(s.array);

	s1.origin='S';
	s1.array[0]='^';
    s1.length=strlen(s1.array);

	f.origin='F';
	strcpy(f.array,"(E)");
    f.length=strlen(f.array);

	f1.origin='F';
	f1.array[0]='i';
    f1.length=strlen(f1.array);

	for(m=0;m<=4;m++)/*初始化分析表 E、G、T、S、F*/
		for(n=0;n<=5;n++)   //六个终结符
			C[m][n].origin='N';/*全部赋为空*/


    /*填充分析表：这里是先通过手算将分析表求出来，然后将相应的表达式填充到分析表中*/
    C[0][0]=e;C[0][3]=e;
    C[1][1]=g;C[1][4]=g1;C[1][5]=g1;
    C[2][0]=t;C[2][3]=t;
    C[3][1]=s1;C[3][2]=s;C[3][4]=C[3][5]=s1;
    C[4][0]=f1;C[4][3]=f;

}

int main()
{
	inital();

	work();

	return 0;
}