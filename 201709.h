//
// Created by leonardo on 18-3-18.
//

#ifndef CCFANSWER_201709_H
#define CCFANSWER_201709_H
/*
问题描述
　　有一个学校的老师共用N个教室，按照规定，所有的钥匙都必须放在公共钥匙盒里，老师不能带钥匙回家。每次老师上课前，都从公共钥匙盒里找到自己上课的教室的钥匙去开门，上完课后，再将钥匙放回到钥匙盒中。
　　钥匙盒一共有N个挂钩，从左到右排成一排，用来挂N个教室的钥匙。一串钥匙没有固定的悬挂位置，但钥匙上有标识，所以老师们不会弄混钥匙。
　　每次取钥匙的时候，老师们都会找到自己所需要的钥匙将其取走，而不会移动其他钥匙。每次还钥匙的时候，还钥匙的老师会找到最左边的空的挂钩，将钥匙挂在这个挂钩上。如果有多位老师还钥匙，则他们按钥匙编号从小到大的顺序还。如果同一时刻既有老师还钥匙又有老师取钥匙，则老师们会先将钥匙全还回去再取出。
　　今天开始的时候钥匙是按编号从小到大的顺序放在钥匙盒里的。有K位老师要上课，给出每位老师所需要的钥匙、开始上课的时间和上课的时长，假设下课时间就是还钥匙时间，请问最终钥匙盒里面钥匙的顺序是怎样的？
输入格式
　　输入的第一行包含两个整数N, K。
　　接下来K行，每行三个整数w, s, c，分别表示一位老师要使用的钥匙编号、开始上课的时间和上课的时长。可能有多位老师使用同一把钥匙，但是老师使用钥匙的时间不会重叠。
　　保证输入数据满足输入格式，你不用检查数据合法性。
输出格式
　　输出一行，包含N个整数，相邻整数间用一个空格分隔，依次表示每个挂钩上挂的钥匙编号。
样例输入
5 2
4 3 3
2 2 7
样例输出
1 4 3 2 5
样例说明
　　第一位老师从时刻3开始使用4号教室的钥匙，使用3单位时间，所以在时刻6还钥匙。第二位老师从时刻2开始使用钥匙，使用7单位时间，所以在时刻9还钥匙。
　　每个关键时刻后的钥匙状态如下（X表示空）：
　　时刻2后为1X345；
　　时刻3后为1X3X5；
　　时刻6后为143X5；
　　时刻9后为14325。
样例输入
5 7
1 1 14
3 3 12
1 15 12
2 7 20
3 18 12
4 21 19
5 30 9
样例输出
1 2 3 5 4
评测用例规模与约定
　　对于30%的评测用例，1 ≤ N, K ≤ 10, 1 ≤ w ≤ N, 1 ≤ s, c ≤ 30；
　　对于60%的评测用例，1 ≤ N, K ≤ 50，1 ≤ w ≤ N，1 ≤ s ≤ 300，1 ≤ c ≤ 50；
　　对于所有评测用例，1 ≤ N, K ≤ 1000，1 ≤ w ≤ N，1 ≤ s ≤ 10000，1 ≤ c ≤ 100。
*/

#include <iostream>
#include <list>
#include <queue>
#include <vector>
#include <map>
#define picked (-1)

typedef int Key;
typedef int TimePoint;
void SchoolRun();
class Teacher {
public:
    Key key;
    TimePoint OpTime;
    bool isReturn;
    Teacher() {
    }
    Teacher(Key mykey,TimePoint time,bool isreturn) {
        key=mykey;
        OpTime=time;
        isReturn=isreturn;
    }
};
bool cmp_time(Teacher t1,Teacher t2);
bool cmp_key(Teacher t1,Teacher t2);
void  SchoolRun() {
    int n,k;
    int tmp=0;
    int startTime,lastTime,keyTmp;
    cin>>n>>k;
    list<Key> empty_space;
    map<Key,int> key_map;
    for(int i=1; i<=n; i++) {
        key_map.insert(pair<Key,int>(i,i));
    }
    list<Teacher> teacher_list;
    for(int i=0; i<k; i++) {
        cin>>keyTmp>>startTime>>lastTime;
        Teacher teacher(keyTmp,startTime,false);
        Teacher teacher_return(keyTmp,startTime+lastTime,true);
        teacher_list.push_back(teacher);
        teacher_list.push_back(teacher_return);
    }
    Teacher teachertmp;
    list<Teacher> pick_list,return_list;
    teacher_list.sort(cmp_time);
    while(!teacher_list.empty()) {
        teachertmp=teacher_list.front();
        teacher_list.pop_front();
        if(teachertmp.isReturn)
            return_list.push_back(teachertmp);
        else
            pick_list.push_back(teachertmp);
        while(!teacher_list.empty()&&teacher_list.front().OpTime==teachertmp.OpTime) {
            teachertmp=teacher_list.front();
            teacher_list.pop_front();
            if(teachertmp.isReturn)
                return_list.push_back(teachertmp);
            else
                pick_list.push_back(teachertmp);
        }
        //pick_list.sort(cmp_key);
        return_list.sort(cmp_key);
        while(!return_list.empty()) {
            key_map[return_list.front().key]=empty_space.front();
            return_list.pop_front();
            empty_space.pop_front();
        }
        while(!pick_list.empty()) {
            empty_space.push_back(key_map[pick_list.front().key]);
            key_map[pick_list.front().key]=picked;
            pick_list.pop_front();

        }
        empty_space.sort();
    }
    vector<Key> key_vec(n+1);
    for(int i=1; i<=n; i++) {
        key_vec[key_map[i]]=i;
    }
    for(int i=1; i<=n; i++) {
        cout<<key_vec[i];
        if(i!=n)
            cout<<" ";
    }
}

bool cmp_time(Teacher t1,Teacher t2) {
    if(t1.OpTime<t2.OpTime)
        return true;
    else
        return false;
}
bool cmp_key(Teacher t1,Teacher t2) {
    if(t1.key<t2.key)
        return true;
    else
        return false;
}
/*
问题描述
　　JSON (JavaScript Object Notation) 是一种轻量级的数据交换格式，可以用来描述半结构化的数据。JSON 格式中的基本单元是值 (value)，出于简化的目的本题只涉及 2 种类型的值：
　　* 字符串 (string)：字符串是由双引号 " 括起来的一组字符（可以为空）。如果字符串的内容中出现双引号 "，在双引号前面加反斜杠，也就是用 \" 表示；如果出现反斜杠 \，则用两个反斜杠 \\ 表示。反斜杠后面不能出现 " 和 \ 以外的字符。例如：""、"hello"、"\"\\"。
　　* 对象 (object)：对象是一组键值对的无序集合（可以为空）。键值对表示对象的属性，键是属性名，值是属性的内容。对象以左花括号 { 开始，右花括号 } 结束，键值对之间以逗号 , 分隔。一个键值对的键和值之间以冒号 : 分隔。键必须是字符串，同一个对象所有键值对的键必须两两都不相同；值可以是字符串，也可以是另一个对象。例如：{}、{"foo": "bar"}、{"Mon": "weekday", "Tue": "weekday", "Sun": "weekend"}。
　　除了字符串内部的位置，其他位置都可以插入一个或多个空格使得 JSON 的呈现更加美观，也可以在一些地方换行，不会影响所表示的数据内容。例如，上面举例的最后一个 JSON 数据也可以写成如下形式。
　　{
　　"Mon": "weekday",
　　"Tue": "weekday",
　　"Sun": "weekend"
　　}
　　给出一个 JSON 格式描述的数据，以及若干查询，编程返回这些查询的结果。
输入格式
　　第一行是两个正整数 n 和 m，分别表示 JSON 数据的行数和查询的个数。
　　接下来 n 行，描述一个 JSON 数据，保证输入是一个合法的 JSON 对象。
　　接下来 m 行，每行描述一个查询。给出要查询的属性名，要求返回对应属性的内容。需要支持多层查询，各层的属性名之间用小数点 . 连接。保证查询的格式都是合法的。
输出格式
　　对于输入的每一个查询，按顺序输出查询结果，每个结果占一行。
　　如果查询结果是一个字符串，则输出 STRING <string>，其中 <string> 是字符串的值，中间用一个空格分隔。
　　如果查询结果是一个对象，则输出 OBJECT，不需要输出对象的内容。
　　如果查询结果不存在，则输出 NOTEXIST。
样例输入
10 5
{
"firstName": "John",
"lastName": "Smith",
"address": {
"streetAddress": "2ndStreet",
"city": "NewYork",
"state": "NY"
},
"esc\\aped": "\"hello\""
}
firstName
address
address.city
address.postal
esc\aped
样例输出
STRING John
OBJECT
STRING NewYork
NOTEXIST
STRING "hello"
评测用例规模与约定
　　n ≤ 100，每行不超过 80 个字符。
　　m ≤ 100，每个查询的长度不超过 80 个字符。
　　字符串中的字符均为 ASCII 码 33-126 的可打印字符，不会出现空格。所有字符串都不是空串。
　　所有作为键的字符串不会包含小数点 .。查询时键的大小写敏感。
　　50%的评测用例输入的对象只有 1 层结构，80%的评测用例输入的对象结构层数不超过 2 层。举例来说，{"a": "b"} 是一层结构的对象，{"a": {"b": "c"}} 是二层结构的对象，以此类推。
*/
#include <map>
#include <string>
#include <list>
#include <iostream>
#include <vector>
using namespace std;

class JsonOpreater {

public:
    void Run();

    void JsonOprate();

    void UpdateObject();

    void AddToLast(char ch);

private:
    int n, m;

    char itor;
    string strtmp, keytmp, valuetmp, objecttmp;
    bool readflag, keyflag;
    list<char> punct_stack;
    list <string> object_stack;
    map<string, string> json_map;
};

void JsonOpreater::JsonOprate() {
    int i = 0;
    int counter = 0;

    cin >> n >> m;
    //cin.get();
    while (counter++ < n) {
        strtmp.clear();
        keytmp.clear();
        valuetmp.clear();
        readflag = false;
        keyflag = true;
        cin >> strtmp;
        for (i = 0; i < strtmp.length(); i++) {
            if (strtmp[i] == '\"') {
                if (i > 0 && strtmp[i - 1] == '\\') {
                    if (keyflag)
                        keytmp.pop_back();
                    else
                        valuetmp.pop_back();
                    AddToLast('\"');
                } else {//露脕脠毛脣芦脪媒潞脜
                    if (punct_stack.back() == '\"') {
                        punct_stack.pop_back();
                        readflag = false;
                        if (keyflag) {
                            keyflag = false;
                        } else {
                            json_map.insert(pair<string, string>(objecttmp + keytmp, "STRING " + valuetmp));
                        }
                    } else {
                        punct_stack.push_back('\"');
                        readflag = true;
                    }
                }
            } else if (strtmp[i] == '}') {
                if (punct_stack.back() == '{' && !readflag) {
                    punct_stack.pop_back();
                    if(!objecttmp.empty()) {
                        object_stack.pop_back();
                        UpdateObject();
                    }
                } else {
                    AddToLast('}');
                }
            } else if (strtmp[i] == ':') {
                if (readflag) {
                    AddToLast(':');
                } else
                    continue;
            } else if (strtmp[i] == '{') {
                if (!keytmp.empty()) {
                    object_stack.push_back(keytmp);
                    json_map.insert(pair<string, string>(objecttmp+keytmp, "OBJECT"));
                }

                punct_stack.push_back('{');
                UpdateObject();
            } else if(strtmp[i]=='\\') {
                if(!(i>0&&strtmp[i-1]=='\\')) {
                    AddToLast(strtmp[i]);
                } else {
                    continue;
                }
            } else {
                AddToLast(strtmp[i]);
            }
        }
    }
}

void JsonOpreater::UpdateObject() {
    objecttmp.clear();
    for (list<string>::iterator itor = object_stack.begin(); itor != object_stack.end(); itor++) {
        objecttmp += (*itor) + '.';
    }
}

void JsonOpreater::AddToLast(char ch) {
    if(readflag) {
        if (keyflag)
            keytmp.push_back(ch);
        else
            valuetmp.push_back(ch);
    }
}

void JsonOpreater::Run() {
    int counter = 0;
    JsonOprate();

    vector<string> requesttmp(m);
    for(int i=0; i<m; i++) {
        cin>>requesttmp[i];
    }
    while (counter++ < m) {
        if (json_map.count(requesttmp[counter-1])) {
            cout << json_map[requesttmp[counter-1]]<<endl;
        } else {
            cout << "NOTEXIST" << endl;
        }
    }
}
#endif //CCFANSWER_201709_H
