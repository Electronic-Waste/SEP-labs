#include <iostream>
#include "lexicon.h"
#include "string"
#include "string.h"
#include <cctype>

using namespace std;

class Map
{
private:
    char letterMap[20][20];
    int mark[20][20];
    int score;
    int masterScore;
    int mapSize;
    int length;
    int masterLength;
    string letterFound[1000];
    string masterFound[1000];

public:
    Map(int N) {
        score = 0;
        masterScore = 0;
        length = 0;
        masterLength = 0;
        mapSize = N;
        //输入地图
        for (int i = 1; i <= mapSize; ++i) {
            for (int j = 1; j <= mapSize; ++j) {
                char letter;
                cin.get(letter);
                letterMap[i][j] = letter;
                mark[i][j] = 0;
            }
            cin.ignore();  //get '\n'
        }

        //mark的外一圈设置成-1
        for (int i = 0; i <= mapSize + 1; ++i) {
            mark[i][0] = -1;
            mark[i][mapSize + 1] = -1;
        }
        for (int j = 1; j <= mapSize; ++j) {
            mark[0][j] = -1;
            mark[mapSize + 1][j] = -1;
        }

    }

    //展示交互界面
    void show() const {
        //show letterMap
        for (int i = 1; i <= mapSize; ++i) {
            for (int j = 1; j <= mapSize; ++j)
                cout << letterMap[i][j];
            cout << endl;
        }

        //show score
        cout << "Your Score: " << score <<endl;

        //show words found
        cout << "Your Words:";
        for (int i = 0; i < 1000; ++i) {
            if (letterFound[i] != "")
                cout << " " << letterFound[i];
            else break;
        }
        cout << endl;
    }

    void masterShow() const {
        //show score
        cout << "Computer Score: " << masterScore <<endl;

        //show words found
        cout << "Computer Words:";
        for (int i = 0; i < 1000; ++i) {
            if (masterFound[i] != "")
                cout << " " << masterFound[i];
            else break;
        }
        cout << endl;
    }

    //加入到已经找到的单词中(以小写存储)
    void addInLetterFound(string str) {
        //小写转换
        for (size_t i = 0; i < str.length(); ++i)
            str[i] = tolower(str[i]);
        letterFound[length++] = str;
    }

    //加入到电脑找到的单词中(以大写存储)
    void addInMasterFound(string str) {
        //大写转换
        for (size_t i = 0; i < str.length(); ++i)
            str[i] = toupper(str[i]);
        masterFound[masterLength++] = str;
    }

    //执行电脑查找所有单词的操作
    void master(const Lexicon &lex) {
        for (int i = 1; i <= mapSize; ++i)
            for (int j = 1; j <= mapSize; ++j) {
                string str = "";
                masterLinked(lex, str, i, j);
                eraseMark();
            }
        sortMaster();
    }

    //电脑查找单词的递归函数
    void masterLinked(const Lexicon &lex, string str, int x, int y) {
        mark[x][y] = 1;
        str += letterMap[x][y];

        //剪枝操作：若不含该前缀，则返回
        if(!lex.containsPrefix(str)) {
            mark[x][y] = 0;
            return;
        }

        //如果含有该单词，且长度达标，先前没有加入到两个数组中，则将其加入到电脑找到的单词中
        if (str.length() >= 4 && lex.contains(str)
                && !isMasterAlreadyFound(str) && !isWordExist(str)) {
            addInMasterFound(str);
            addMasterScore(str);
        }

        //向四周搜寻
        if (mark[x - 1][y - 1] == 0 && lex.containsPrefix(str + letterMap[x - 1][y - 1])) {
            masterLinked(lex, str, x - 1, y - 1);
        }
        if (mark[x - 1][y] == 0 && lex.containsPrefix(str + letterMap[x - 1][y])) {
            masterLinked(lex, str, x - 1, y);
        }
        if (mark[x - 1][y + 1] == 0 && lex.containsPrefix(str + letterMap[x - 1][y + 1])) {
            masterLinked(lex, str, x - 1, y + 1);
        }
        if (mark[x][y + 1] == 0 && lex.containsPrefix(str + letterMap[x][y + 1])) {
            masterLinked(lex, str, x, y + 1);
        }
        if (mark[x + 1][y + 1] == 0 && lex.containsPrefix(str + letterMap[x + 1][y + 1])) {
            masterLinked(lex, str, x + 1, y + 1);
        }
        if (mark[x + 1][y] == 0 && lex.containsPrefix(str + letterMap[x + 1][y])) {
            masterLinked(lex, str, x + 1, y);
        }
        if (mark[x + 1][y - 1] == 0 && lex.containsPrefix(str + letterMap[x + 1][y - 1])) {
            masterLinked(lex, str, x + 1, y - 1);
        }
        if (mark[x][y - 1] == 0 && lex.containsPrefix(str + letterMap[x][y - 1])) {
            masterLinked(lex, str, x, y - 1);
        }

        mark[x][y] = 0;
        return;

    }

    //找到单词时加分
    void addScore(string str) {
        score += str.length() - 3;
    }

    //电脑找到单词加分
    void addMasterScore(string str) {
        masterScore += str.length() - 3;
    }

    //清除所有标记
    void eraseMark() {
        for (int i = 1; i <= mapSize; ++i)
            for (int j = 1; j  <= mapSize; ++j)
                mark[i][j] = 0;
    }

    //判断在单词表中是否存在一条路径可以组成该单词
    bool isLetterLinked(string str) {
        for (int i = 1; i <= mapSize; ++i)
            for (int j = 1; j <= mapSize; ++j) {
                //若找到相应开头字母，则进一步判断是否符合(需要设置标记）
                if (letterMap[i][j] == toupper(str[0])) {
                    if (isLinked(str.substr(1), i, j)) {
                        eraseMark();   //清除标记
                        return true;
                    }
                    else eraseMark();   //清除标记
                }
                //否则不进行任何操作
            }
        return false;
    }

    //isLetterLinked的具体实现函数
    bool isLinked(string str, int x, int y) {
        //标记地图
        mark[x][y] = 1;

        //如果字符串为空，则返回true
        if (str == "") return true;

        //向四周搜索
        char ch = toupper(str[0]);
        if (letterMap[x - 1][y - 1] == ch
                && mark[x - 1][y - 1] == 0 && isLinked(str.substr(1), x - 1, y - 1)) return true;

        if (letterMap[x - 1][y] == ch
                && mark[x - 1][y] == 0 && isLinked(str.substr(1), x - 1, y)) return true;

        if (letterMap[x - 1][y + 1] == ch
                && mark[x - 1][y + 1] == 0 && isLinked(str.substr(1), x - 1, y + 1)) return true;

        if (letterMap[x][y + 1] == ch
                && mark[x][y + 1] == 0 && isLinked(str.substr(1), x, y + 1)) return true;

        if (letterMap[x + 1][y + 1] == ch
                && mark[x + 1][y + 1] == 0 && isLinked(str.substr(1), x + 1, y + 1)) return true;

        if (letterMap[x + 1][y] == ch
                && mark[x + 1][y] == 0 && isLinked(str.substr(1), x + 1, y)) return true;

        if (letterMap[x + 1][y - 1] == ch
                && mark[x + 1][y - 1] == 0 && isLinked(str.substr(1), x + 1, y - 1)) return true;

        if (letterMap[x][y - 1] == ch
                && mark[x][y - 1] == 0 && isLinked(str.substr(1), x, y - 1)) return true;

        mark[x][y] = 0;
        return false;
    }

    //判断该单词是否已经在找出的单词之中
    bool isWordExist(string str) {
        //小写转换
        for (size_t i = 0; i < str.length(); ++i)
            str[i] = tolower(str[i]);
        for (int i = 0; i < length; ++i)
            if (str == letterFound[i])
                return true;
        return false;
    }

    //判断该单词是否已经出现在电脑找到的单词之中
    bool isMasterAlreadyFound(string str) {
        //大写转换
        for (size_t i = 0; i < str.length(); ++i)
            str[i] = toupper(str[i]);
        for (int i = 0; i < masterLength; ++i)
            if (str == masterFound[i])
                return true;
        return false;
    }

    //整理电脑找到的单词
    void sortMaster() {
        for (int i = 0; i < masterLength; ++i)
            for (int j = 0; j < masterLength - i - 1; ++j)
                if (masterFound[j] > masterFound[j + 1]) {
                    string tmp = masterFound[j];
                    masterFound[j] = masterFound[j + 1];
                    masterFound[j + 1] = tmp;
                }
    }
};


int main()
{
    int N;
    cin >> N;
    cin.ignore();
    Map map(N);

    Lexicon lex("./EnglishWords.txt");

    while(true) {
        map.show();
        string str;
        cin >> str;
        //若输入"???"则进入电脑回合
        if (str == "???") {
            map.master(lex);
            map.masterShow();
            break;
        }
        //长度<=3首先排除
        else if (str.length() <= 3) {
            cout << str << " is too short." << endl;
        }
        //剪枝操作：若无以前两个单词开头的前缀，则继续循环
        else if (!lex.containsPrefix(str.substr(0,2))) {
            cout << str << " is not a word." << endl;
        }
        //剪枝操作：若无以前三个单词开头的前缀，则继续循环
        else if (!lex.containsPrefix(str.substr(0,3))) {
            cout << str << " is not a word." << endl;
        }
        //若单词不存在，则继续循环
        else if (!lex.contains(str)) {
            cout << str << " is not a word." << endl;
        }
        //若词典中有该单词但是棋盘中没有
        else if (!map.isLetterLinked(str)){
            cout << str << " is not on board." << endl;
        }
        //若词典中有该单词但是已经被找到
        else if (map.isWordExist(str)){
            cout << str << " is already found." << endl;
        }
        else {
            //加入到已找到的数组中
            map.addInLetterFound(str);
            //加分
            map.addScore(str);
        }
    }

}
