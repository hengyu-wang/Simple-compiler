#include <iostream>
#include <fstream>
#include <string>
#include<map>

#define SIZE(a)(sizeof(a)/sizeof(a[0])) //求元素个数
using namespace std;
char op[] = {'+','-','*','/'};      //运算符

void set_mp(map<int,string>&mp) {
    mp[1] = "标识符";
    mp[2] = "关键字";
    mp[3] = "运算符";
    mp[4] = "分隔符";
    mp[5] = "整数";
    mp[6] = "小数";
}

int find_k(string s){//查找s是否在保留字表keyword中（关键字）
    string keyword[] = {"void","main","short","long","int","double","float","while","if","else","for","break","return","char" };//keyword表
    for (int i = 0; i < SIZE(keyword); i++) {
        if (s.compare(keyword[i]) == 0)return 1;//是保留字，返回1
    }
    return 0;//不是保留字，返回0
}

int isLimit(char c){
    if (c == ',' || c == ';' || c == '(' || c == ')' || c == '{' || c == '}') {//识别分界符 4
        return 1;
    }
    return 0;
}

int isOp(char c) {
    int p = -1;
    for(int i = 0; i < 4; i++) {
        if(c == op[i]) p = i;
    }
    return p;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("D:\\CSP\\Simple-compiler\\output.txt");
    string s;
    char word;
    int op_pos = -1;
    map<int,string>mp;
    set_mp(mp);
    word = in.get();

    while (!in.eof()) {
        cout << word << endl;   //word为每次读入的一个字符
        if (isLimit(word)) {//识别分界符
            out << "<" << word << ",4,"<<mp[4]<<">\n";      //输出分隔符
            word = in.get();      //获取下一个字符
        }else if (isdigit(word)) {//识别整数/实数
            s = "";
            while (isdigit(word)) {
                s += word;
                word = in.get();
                if (word == '.') {//如果出现小数点，有可能是常实数
                    s += word;
                    word = in.get();
                    if (isdigit(word)) {
                        while (isdigit(word)) {
                            s += word;
                            word = in.get();
                        }
                        out << "<" << s << ",6,"<<mp[6]<<">\n";//常实数
                        break;
                    }
                    else out << s + " is error!\n";//如果小数点后没有数字，则报错
                }
                if (!isdigit(word)) {
                    out << "<" << s << ",5,"<<mp[5]<<">\n";//常整数
                    break;
                }
            }
        }
        //标识符只能以字母或_开头，不能以字母开头
        else if (isalpha(word) || word == '_') {//识别标识符/保留字  isalpha(word)如果是大写字母就返回1，小写字母返回2，非字母返回0
            s = "";
            while (isalpha(word) || isdigit(word) || word =='_') {
                s += word;
                word = in.get();
            }
            if (find_k(s)) {//在keyword表中查找s是否是保留字
                out << "<" << s << ",2,"<<mp[2]<<">\n";//保留字
            }
            else out << "<" << s << ",1,"<<mp[1]<<">\n";//标识符
        }else if (word == '>') {//后面都是运算符
            s = "";
            s += word;
            word = in.get();
            if (word == '=') {//">="，也可能没有=，直接打印>
                s += word;
                word = in.get();
            }
            out << "<" << s << ",3,"<<mp[3]<<">\n";
        }
        else if (word == '<') {
            s = "";
            s += word;
            word = in.get();
            if (word == '=') {//"<="
                s += word;
                word = in.get();
            }
            out << "<" << s << ",3,"<<mp[3]<<">\n";
        }else if (word == '=') {
            s = "";
            s += word;
            word = in.get();
            if (word == '=') {//"=="
                s += word;
                word = in.get();
            }
            out << "<" << s << ",3,"<<mp[3]<<">\n";
        }else if((op_pos = isOp(word)) != -1) {     //加减乘除的运算符
            out << "<" << word << ",3,"<<mp[3]<<">\n";
            word = in.get();
        }else {//跳过当前单词
            word = in.get();
        }
    }
    return 0;
}