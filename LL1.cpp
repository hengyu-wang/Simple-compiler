#include<iostream>
#include<stdio.h>
#include<string.h>
using namespace std;
#define SIZE 1000
//һ���ķ���Ӧһ����������
char A[20];      /*����ջ*/
char B[20];      /*ʣ�മ*/
char v1[20]={'i','+','*','(',')','#'};/*�ս��  */
char v2[20]={'E','G','T','S','F'};/*���ս��   */
int j=0,b=0,top=0,l;       /*LΪ���봮���� */

typedef struct type   /*����ʽ���Ͷ���*/
 {
	char origin;   /*��д�ַ�  */
	char array[5];   /*����ʽ�ұ��ַ� */
	int length;/*�ַ�����      */
 }type;

type e,t,g,g1,s,s1,f,f1;/*�ṹ�������������Ŀ�������ķ�����ʾ  */
type C[10][10];/*Ԥ�������ջ������������ǰ�����ַ���ʱִ��ĳ������Ķ������뵱ǰջ�����ŵ�first���Ϻ�follow�������   */
void print()/*�������ջ  */
{
	int a;/*ָ��*/
	for(a=0;a<=top+1;a++)   //�����һ���ո�
		printf("%c",A[a]);
	printf("\t\t");
 }
void print1()/*���ʣ�മ*/
{
	int j;
	for(j=0;j<b;j++)/*��������*/
		printf(" ");
	for(j=b;j<=l;j++)
		printf("%c",B[j]);
	printf("\t\t\t");
}

//����������
void work()
{
	char ch,x;
	bool flag;
	int i=0,j=0,k=0,finish,m,n;
	type cha;
	j=0,b=0,top=0,l;/*LΪ���봮���� */

	do   /*���������*/
	{
	   scanf("%c",&ch);     //ÿ��ֻ����һ���ַ���
	   if ((ch!='i') &&(ch!='+') &&(ch!='*')&&(ch!='(')&&(ch!=')')&&(ch!='#'))
	   {
		   printf("���봮���зǷ��ַ�\n");
		   return;
	   }
	   B[j]=ch;     //B = [i,+,i,*,i,#]
	   j++;
	}while(ch!='#');

   l=j; /*����������*/
   ch=B[0]; /*��ǰ�����ַ�*/
   A[top]='#';  //��ʼ��ʱtopΪ0
   A[++top]='E';  /*'#','E'��ջ*/
   printf("����\t\t����ջ \t\tʣ���ַ� \t\t���ò���ʽ \n");
   printf("start\t\t");

   //��ӡ��ǰ����ջ��ʣ���ַ�
   print();
   print1();
   printf("\n");

    do
    {
        //��ջ������һ���ַ���
        x=A[top--];/*xΪ��ǰջ���ַ�*/
        printf("%d",k++);       //��ʾ��k��
        printf("\t\t");
        flag=0;
        for(j=0;j<=5;j++)  /*�ж��Ƿ�Ϊ�ս��*/
            if(x==v1[j])
            {
                flag=1;
                break;
            }

		  if(flag==1)/*������ս��*/
		  {
              if(x=='#')
			  {
                  finish=1;/*�������*/
				  printf("acc!\n");/*���� */
				  getchar();    //�ٰ������س���������
				  getchar();
				  return;
              }
			  if(x==ch)
			  {
                  print();
				  print1();
				  printf("%cƥ��\n",ch);
				  ch=B[++b];/*��һ�������ַ�*/
				  flag=0;/*�ָ����*/
              }
			  else/*������*/
			  {
                  print();
				  print1();
				  printf("%c����\n",ch);/*��������ս��*/
				  return;
              }
          }

        else       /*���ս������*/
        {
            //x�ǵ�ǰջ���ַ���ch�ǵ�ǰ�����ַ�
            //��xΪ�У�chΪ��Ѱ�ҷ������ж�Ӧ�ı��ʽ
            for(j=0;j<=4;j++)
                if(x==v2[j])
				{
				    m=j;/*��m��¼���к�*/
				    break;
                }
            for(j=0;j<=5;j++)
                if(ch==v1[j])
                {
                    n=j;/*�к�*/
                    break;
                }
            cha=C[m][n];
            if(cha.origin!='N')/*�ж��Ƿ�Ϊ��*/
            {
                print();
                print1();
				printf("%c->",cha.origin);/*�������ʽ*/

                printf("%s",cha.array);
				printf("\n");
		        for(j=(cha.length-1);j>=0;j--)/*����ʽ������ջ*/
			    A[++top]=cha.array[j];
		         if(A[top]=='^')/*Ϊ���򲻽�ջ*/
			        top--;
			}
            else {
                //����ǿ�˵����������
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
	  /*���ķ�����ʽ��ֵ�ṹ��*/
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

	for(m=0;m<=4;m++)/*��ʼ�������� E��G��T��S��F*/
		for(n=0;n<=5;n++)   //�����ս��
			C[m][n].origin='N';/*ȫ����Ϊ��*/


    /*����������������ͨ�����㽫�������������Ȼ����Ӧ�ı��ʽ��䵽��������*/
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