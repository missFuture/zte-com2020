#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <ostream>


#define DEBUG
//#define OUTPUT
//#define READ
//#define JOIN
//#define GROUP
using std::string ;
using std::vector ;
using std::chrono::high_resolution_clock ;
using std::cout;
using std::cin;
using std::endl;
const string FILE1 = R"(F:\document\clionPro\ZTE-com\version1\data10000row\table1.csv)";
const string FILE2 = R"(F:\document\clionPro\ZTE-com\version1\data10000row\table2.csv)";


class dataOriginal
{
public:
    int id1;
    int id2;
    int id3;

    friend std::ostream & operator << (std::ostream & os , const dataOriginal& tmp)
    {
        os << tmp.id1 << " " << tmp.id2 << " " << tmp.id3 << " ";
        return os;
    }
};

class groupData
{
public:
    int t1Id1;
    int t1Id2;
    int t2Id1;
    int t2Id2;

    groupData():t1Id1(0), t1Id2(0), t2Id1(0), t2Id2(0){}
    friend std::ostream & operator << (std::ostream & os , const groupData& tmp)
    {
        os << tmp.t1Id1 << " " << tmp.t1Id2 << " " << tmp.t2Id1 << " " << tmp.t2Id2 << " " << endl;
        return os;
    }

};


class compareGroupResult
{
public:
    bool operator()(const groupData* group1, const groupData* group2) const
    {
        return group1->t1Id1 < group2->t1Id1 || (group1->t1Id1 == group2->t1Id1 && group1->t2Id2 < group2->t2Id2) ||
        (group1->t1Id1 == group2->t1Id1 && group1->t2Id2 == group2->t2Id2 && group1->t1Id2 < group2->t1Id2);
    }
};

std::vector<dataOriginal*> read_file(const string dir1)
{
    std::vector<dataOriginal*> res;
    std::ifstream fin(dir1);
    char c;
    while (!fin.eof())
    {
        dataOriginal* cur_data = new dataOriginal();
        if(fin >> cur_data->id1 >> c >> cur_data->id2 >> c >> cur_data->id3)
            res.push_back(cur_data);
        else
            break;
    }
    return res;
}

std::vector<std::pair<dataOriginal*, dataOriginal*>> join(const vector<dataOriginal*> table1, const vector<dataOriginal*>table2)
{
#ifdef  DEBUG
    auto timer_start = high_resolution_clock::now();
#endif
    //开始join之前，需要对将table2表格装入到一个unordered_multimap中，key为id3, value为对应的t2数据
    std::unordered_multimap<int, dataOriginal*> table2_map;
    for(auto iter = table2.begin(); iter != table2.end(); iter++)
        table2_map.insert({(*iter)->id3, (*iter)});

    std::vector<std::pair<dataOriginal*, dataOriginal*>> join_result;
    for(auto iter1 = table1.begin(); iter1 != table1.end(); iter1++)
    {
        auto range = table2_map.equal_range((*iter1)->id3);
        for(auto iter2 = range.first; iter2 != range.second; iter2++)
            join_result.push_back({(*iter1), iter2->second});
    }
#ifdef  DEBUG
    auto time_end = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - timer_start);
    cout << "time join dataOriginal " << duration.count() << " milliseconds\n";
#endif
    return join_result;
}


std::vector<groupData*> group(std::vector<std::pair<dataOriginal*, dataOriginal*>> & join_result)
{

    std::unordered_map<int, std::unordered_map<int, groupData*>> group_data;
    for(auto iter = join_result.begin(); iter != join_result.end(); iter++)
    {
        auto t1Id2 = (*iter).first->id2;
        auto t2Id2 = (*iter).second->id2;
        if(group_data.count(t1Id2) == 0)
            group_data[t1Id2] = std::unordered_map<int, groupData *>();//添加一个空的元素
        if(group_data[t1Id2].count(t2Id2) == 0)
        {
            auto group = new groupData();
            group->t1Id1 = (*iter).first->id1;
            group->t1Id2 = (*iter).first->id2;
            group->t2Id1 = (*iter).second->id1;
            group->t2Id2 = (*iter).second->id2;
            group_data[t1Id2][t2Id2] = group;
        }
        else
        {
            auto group = group_data[t1Id2][t2Id2];
            group->t1Id1 = std::max(group->t1Id1, (*iter).first->id1);
            group->t2Id1 = std::min(group->t2Id1, (*iter).second->id1);
        }
    }

    std::vector<groupData*> group_result;
    for(auto iter1 = group_data.begin(); iter1 != group_data.end(); iter1 ++)
    {
        for(auto iter2 = iter1->second.begin(); iter2 != iter1->second.end(); iter2++)
            group_result.push_back(iter2->second);
    }
    return group_result;
}

template <typename type>
void free_table(vector<type*> &table)
{
    if(table.empty())
        return;
    for(auto iter : table)
        delete iter;
}

void free_group()
{

}
int main()
{
#ifdef DEBUG
    string dir1 = FILE1;
    string dir2 = FILE2;
#else
    string file1_name = "/home/web/ztedatabase/input1.csv";
    string file2_name = "/home/web/ztedatabase/input2.csv";
#endif

#ifdef DEBUG
    auto join_begin = high_resolution_clock::now();
#endif

#ifdef DEBUG
    auto read_begin = high_resolution_clock::now();
#endif
    auto table1 = read_file(dir1);
    auto table2 = read_file(dir2);
#ifdef DEBUG
    auto read_end = high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(read_end - read_begin);
    cout << "time read: " << duration.count() << " milliseconds\n";
#endif

    auto join_rows = join(table1, table2);

#ifdef DEBUG
    auto join_end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(join_end - join_begin);
    cout << "Time join: " << duration.count() << " milliseconds\n";
    auto group_begin = high_resolution_clock::now();
#endif

    auto group_result = group(join_rows);
#ifdef DEBUG
    auto group_end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(group_end - group_begin);
    cout << "Time group: " << duration.count() << " milliseconds\n";
    auto sort_begin = high_resolution_clock::now();
#endif
    std::stable_sort(group_result.begin(), group_result.end(), compareGroupResult());//排序

#ifdef DEBUG
    auto sort_end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(sort_end - sort_begin);
    cout << "Time sort: " << duration.count() << " milliseconds\n";
#endif
#ifdef OUTPUT
    for(auto each : group_result)
        cout << each->t1Id1 << " " << each->t2Id1 << "\n";
#endif

#ifdef READ
    cout << "table1: " << endl;
    for(auto each : table1)
        cout << (*each) << endl;
    cout << "table2: " << endl;
    for(auto each : table2)
        cout << (*each) << endl;
#endif

#ifdef JOIN
    cout << "join result: " << endl;
    for(auto each : join_rows)
    {
        cout << (*each.first);
        cout << (*each.second);
        cout << endl;
    }
#endif

#ifdef GROUP
    cout << "group result: " << endl;
    for(auto each : group_result)
    {
        cout << (*each) <<endl;
    }
#endif
    free_table<dataOriginal>(table1);
    free_table<dataOriginal>(table2);
    free_table<groupData>(group_result);
    return 0;
}