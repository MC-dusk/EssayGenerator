#include "pch.h"
#include "EssayGenerator.h"

int EssayGenerator::get_random_num(unsigned long total)
{
    // srand((unsigned int)clock());
    // int num = rand() % (total);
    // return num; // 经典C风格随机数取法
    random_device rd;  // 随机设备，用于生成种子
    mt19937 gen(rd()); // Mersenne Twister随机数生成器，用于生成随机数
    uniform_int_distribution<> dis(0, total - 1); // 分布器，用于将随机数映射到指定范围内
    return dis(gen); // C++11新型随机数取法
}

string EssayGenerator::get_noun()
{
    unsigned long total = data["noun"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["noun"][random_num];
    return str;
}

string EssayGenerator::get_verb()
{
    unsigned long total = data["verb"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["verb"][random_num];
    return str;
}

string EssayGenerator::get_adverb(int type)
{
    string str;
    if (type == 1)
    {
        unsigned long total = data["adverb_1"].size();
        unsigned long random_num = get_random_num(total);
        str = data["adverb_1"][random_num];
    }
    else if (type == 2)
    {
        unsigned long total = data["adverb_2"].size();
        unsigned long random_num = get_random_num(total);
        str = data["adverb_2"][random_num];
    }
    return str;
}

string EssayGenerator::get_phrase() // 获取成语
{
    unsigned long total = data["phrase"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["phrase"][random_num];
    return str;
}

string EssayGenerator::get_sentence() // 获取名言
{
    unsigned long total = data["sentence"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["sentence"][random_num];
    return str;
}

string EssayGenerator::get_parallel_sentence(const string& theme) // 获取一句排比句
{
    unsigned long total = data["parallel_sentence"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["parallel_sentence"][random_num];
    // alert(str);
    while (replace_theme(str, theme));
    // alert(str);
    return str;
}

string EssayGenerator::get_title(const string& theme) // 生成标题
{
    unsigned long total = data["title"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["title"][random_num];
    replace_all(str, theme);
    return str;
}

string EssayGenerator::get_beginning(const string& theme) // 生成一句开头，循环调用可生成一段开头，下同
{
    unsigned long total = data["beginning"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["beginning"][random_num];
    replace_all(str, theme);
    return str;
}

string EssayGenerator::get_body(const string& theme)
{
    unsigned long total = data["body"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["body"][random_num];
    replace_all(str, theme);
    return str;
}

string EssayGenerator::get_ending(const string& theme)
{
    unsigned long total = data["ending"].size();
    unsigned long random_num = get_random_num(total);
    string str = data["ending"][random_num];
    replace_all(str, theme);
    return str;
}

bool EssayGenerator::replace_theme(string& str, const string& theme) // 把标识符xx替换为实际主题theme，下同
{
    unsigned long step = str.find("xx");
    if (step < str.length())
    {
        str.replace(step, 2, theme);
        return true;
    }
    return false;
}

bool EssayGenerator::replace_verb_noun(string& str)
{
    unsigned long step = str.find("vn");
    if (step >= str.length()) // 没找到vn就返回
    {
        return false;
    }
    unsigned long random_num = get_random_num(4) + 1;
    string vn = "";
    for (size_t i = 0; i < random_num; i++)
    {
        vn += get_verb() + get_noun();
        if (i != random_num - 1) vn += u8"、"; // 如果不是最后一个，就加逗号分隔；u8显式指定utf8编码，便于后续统一处理
    }
    str.replace(step, 2, vn);
    return true;
}

bool EssayGenerator::replace_verb(string& str)
{
    unsigned long step = str.find("v");
    if (step < str.length())
    {
        str.replace(step, 1, get_verb());
        return true;
    }
    return false;
}

bool EssayGenerator::replace_noun(string& str)
{
    unsigned long step = str.find("n");
    if (step < str.length())
    {
        str.replace(step, 1, get_noun());
        return true;
    }
    return false;
}

bool EssayGenerator::replace_sentence(string& str)
{
    unsigned long step = str.find("ss");
    if (step < str.length())
    {
        str.replace(step, 2, get_sentence());
        return true;
    }
    return false;
}

bool EssayGenerator::replace_parallel_sentence(string& str, const string& theme)
{
    unsigned long step = str.find("sp");
    if (step < str.length())
    {
        str.replace(step, 2, get_parallel_sentence(theme));
        return true;
    }
    return false;
}

bool EssayGenerator::replace_phrase(string& str)
{
    unsigned long step = str.find("p");
    if (step < str.length())
    {
        str.replace(step, 1, get_phrase());
        return true;
    }
    return false;
}

bool EssayGenerator::replace_adverb(string& str)
{
    unsigned long step = str.find("ad");
    if (step < str.length())
    {
        str.replace(step, 2, get_adverb(get_random_num(2) + 1));
        return true;
    }
    return false;
}

void EssayGenerator::replace_all(string& str, const string& theme) // 替换所有需要替换的标识符为实际内容
{
    while (replace_theme(str, theme));
    while (replace_verb_noun(str));
    while (replace_verb(str));
    while (replace_noun(str));
    while (replace_sentence(str));
    while (replace_parallel_sentence(str, theme));
    while (replace_phrase(str));
    while (replace_adverb(str));
}

string EssayGenerator::error(int n) // 报错处理函数
{
    string temp;
    if (n == 1)
    {
        temp = "请正确输入";
    }
    else if (n == 2)
    {
        temp = "字数太小";
    }
    else if (n == 3)
    {
        temp = "字数太大";
    }
    return temp;
}
