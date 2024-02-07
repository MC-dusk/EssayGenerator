#pragma once

// 文章生成器，根据指定主题和字数随机拼凑文章
#ifndef GENER
#define GENER

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
// #include <cstdlib>
// #include <ctime>
#include <random>
#include <nlohmann/json.hpp> // 使用make编译

using namespace std;
using json = nlohmann::json;

#pragma once
class EssayGenerator
{
private:
    json data; // json类型，引用了外部库
    int get_random_num(unsigned long total);
    bool replace_theme(string& str, const string& theme);
    bool replace_verb_noun(string& str);
    bool replace_verb(string& str);
    bool replace_noun(string& str);
    bool replace_sentence(string& str);
    bool replace_parallel_sentence(string& str, const string& theme);
    bool replace_phrase(string& str);
    bool replace_adverb(string& str);
    void replace_all(string& str, const string& theme);
    string get_noun();
    string get_verb();
    string get_adverb(int type);
    string get_phrase();
    string get_sentence();
    string get_parallel_sentence(const string& theme);
public:
    EssayGenerator() = default; // 显式保留默认构造函数
    EssayGenerator(string json_path)
    {
        ifstream istr(json_path);
        istr >> data;
    }
    string get_title(const string & theme);
    string get_beginning(const string & theme);
    string get_body(const string & theme);
    string get_ending(const string & theme);
    string error(int n);
};

#endif // !GENER
