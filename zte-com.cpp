#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;
//this is a test line
//add a another line.
//原始数据的data类型
class dataOriginal
{
public:
    int id1;
    int id2;
    int id3;

    dataOriginal(int m1, int m2, int m3):id1(m1),id2(m2),id3(m3){}
    friend ostream & operator << (ostream & os, const dataOriginal& temp)
    {
        os << temp.id1 << "\t" << temp.id2 << "\t" << temp.id3 << "\t";
        return os;
    }

};

class joinData
{
public:
    int t1Id1;
    int t1Id2;
    int t2Id1;
    int t2Id2;

    joinData(int m1, int m2, int m3, int m4):t1Id1(m1), t1Id2(m2), t2Id1(m3), t2Id2(m4){}

    bool operator<(const joinData& para1)
    {
        if(t2Id2 < para1.t2Id2)
            return true;
        if(t2Id2 == para1.t2Id2 && t1Id2 < para1.t1Id2)
            return true;
        return false;
    }
    
    bool operator>(const joinData& para1)
    {
        if(t2Id2 > para1.t2Id2)
            return true;
        if(t2Id2 == para1.t2Id2 && t1Id2 > para1.t1Id2)
            return true;
        return false;
    }
    
    friend ostream &operator <<(ostream & os, joinData & temp)
    {
        os << temp.t1Id1 << "\t" << temp.t1Id2 << "\t" << temp.t2Id1 << "\t" << temp.t2Id2 << endl;
        return os;
    }
};

class groupData
{
public:
    int maxT1D1;
    int t1D2;
    int minT2D1;
    int t2D2;

    groupData(int m1, int m2, int m3, int m4):maxT1D1(m1), t1D2(m2), minT2D1(m3), t2D2(m4){}

    bool operator<(const groupData & para)
    {
        if(maxT1D1 < para.maxT1D1)
            return true;
        else if(maxT1D1 == para.maxT1D1)
            if(t2D2 < para.t2D2)
                return true;
            else if(t2D2 == para.t2D2)
                if(t1D2 < para.t1D2)
                    return true;
        return false;
    }

    friend ostream &operator << (ostream & os, groupData & temp)
    {
        os << temp.maxT1D1 << "\t"<< temp.t1D2 << "\t"<< temp.minT2D1 << "\t"<< temp.t2D2 << "\t";
        return os;
    }
};

//mergesort
void __merger(vector<groupData*> &arr, int l, int mid, int r)
{
    vector<groupData*> arrCopy;
    for (int m = 0; m < r - l + 1; ++m)
    {
        arrCopy.push_back(nullptr);
    }
    //需要根据辅助的空间元素调整参数arr的内容
    for (int i = l; i <=r ; i++)
    {
        arrCopy[i - l] = arr[i];
    }

    int i = l;
    int j = mid + 1;
    for(int k = l;k <= r; k++)
    {
        if(i > mid)
        {
            arr[k] = arrCopy[j - l];
            j ++;
        }
        else if(j > r)
        {
            arr[k] = arrCopy[i - l];
            i++;
        }//以上是判断索引是否合法
        else if((*arrCopy[i - l]) < (*arrCopy[j - l]))
        {
            arr[k] =  arrCopy[i - l];
            i++;
        }
        else
        {
            arr[k] = arrCopy[j - l];
            j++;
        }
    }
}

void mergerSortBU(vector<groupData*> &arr, int n)
{
    for (int sz = 1; sz <= n  ; sz += sz)
    {
        for (int i = 0; i + sz < n; i += sz + sz) {
            __merger(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1));
        }
    }
}


void __mergeSort(vector<groupData*> &arr, int l, int r)
{
    if(l >= r)
        return;
    int mid = (l + r)  / 2;  //可能溢出
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    __merger(arr, l, mid, r);
}


void mergerSortGroupData(vector<groupData*> &arr, int n)
{
    __mergeSort(arr, 0, n-1);
}

template <typename Key, typename Value>
class BSTRepeat {
public:
    struct Node {
        Key key;
        Value value;
        Node *left;
        Node *right;
        Node *next;

        Node(Key m_key, Value m_value) : key(m_key), value(m_value), left(NULL), right(NULL), next(NULL) {}

        Node(Node *node)
        {
            this->key = node->key;
            this->value = node->value;
            this->left = node->left;
            this->right = node->right;
            this->next = NULL;
        }

    };

    typedef struct Node Node;
    Node *root;
    int count;

public:
    BSTRepeat() {
        root = nullptr;
        count = 0;
    }

    ~BSTRepeat() {
        //..
        destory(root);
        //cout << "t2 has been freed.\n";
    }

    int size() {
        return count;
    }

    bool isEmpty() {
        return count == 0;
    }

    void insert(Key m_key, Value m_value)
    {
        //如果已经包含了这个节点
        if(contain(root, m_key))
        {
            Node *insertNode = new Node(m_key, m_value);
            insertRepeatNode(root, insertNode);
        }
            //反之，BST中不包含这个节点
        else
        {
            root = insertSingleNode(root, m_key, m_value);
        }
    }


    bool contain(Key m_key) {
        return contain(root, m_key);
    }

    vector<Value*> search(Key m_key)
    {
//        assert(contain(m_key));
        vector<Value*> resSearch;
        search(root, m_key, resSearch);
        return resSearch;
    }

    void preOrder() {
        preOrder(root);
    }

    //时间复杂度O(n)
    void levelOrder()
    {
        queue<Node *> q;
        q.push(root);
        while (!q.empty())
        {
            Node *node = q.front();
            q.pop();
            cout << node->key << endl;
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }
//    friend ostream &operator <<(ostream & os, Node* node)
//    {
//        os << "key: " << node->key << "value: " << node->value << endl;
//    }

private:

    bool contain(Node* root, Key m_key)
    {
        if(root == NULL)
            return false;
        if(m_key == root->key)
            return true;
        else if(m_key < root->key)
            return contain(root->left, m_key);
        else
            return contain(root->right, m_key);
    }

    Node* insertSingleNode(Node* node, Key m_key, Value m_value)
    {
        if(node == NULL)
        {
            count++;
            return new Node(m_key, m_value);
        }
        if(m_key < node->key)
            node->left = insertSingleNode(node->left, m_key, m_value);
        else if(m_key > node->key)
            node->right = insertSingleNode(node->right, m_key, m_value);
        return node;
    }

    void insertRepeatNode(Node* &node, Node* insertNode)
    {
        Node *curView = node;
        while(curView)
        {
            //待插入的节点key与当前的节点key相同
            if(insertNode->key == curView->key)
            {
                insertNode->next = curView->next;
                curView->next = insertNode;
                return;
            }
            else if(insertNode->key < curView->key)
                curView = curView->left;
            else
                curView = curView->right;
        }
    }

    void destory(Node* node)
    {
        if(node)
        {
            destory(node->left);
            destory(node->right);
            while(node)
            {
                Node* deleteNode = node->next;
                delete node;
                node = deleteNode;
            }
            count--;
        }
    }

    void search(Node* node, Key m_key, vector<Value*> &searchRes)
    {
        //前提是该BST存在这个key
        if(node == NULL)
            return;
        if(node->key == m_key)
        {
            //只有一个key相同的元素
            if(node->next == NULL)
            {
                searchRes.push_back(&(node->value));
                return;
            }
            else//存在相同的元素
            {
                searchRes.push_back(&(node->value));
                while(node->next)
                {
                    searchRes.push_back(&(node->next->value));
                    node = node->next;
                }
                return;
            }
        }
        else if(m_key < node->key)
            return search(node->left, m_key, searchRes);
        else
            return search(node->right, m_key, searchRes);
    }

    void preOrder(Node* node)
    {
        if(node)
        {
            if(node->next)
            {
                Node* nodeTemp = node;
                while(nodeTemp)
                {
                    cout << "key: " << nodeTemp->key << " " << "value: " << *nodeTemp->value;
                    nodeTemp = nodeTemp->next;
                }
                cout << endl;
            }
            else
                cout << "key: " << node->key << " " << "value: " << *node->value << endl;
            preOrder(node->left);
            preOrder(node->right);
        }
    }
};

//mergesort
void __merger(vector<joinData*> &arr, int l, int mid, int r)
{
    vector<joinData*> arrCopy;
    for (int m = 0; m < r - l + 1; ++m)
    {
        arrCopy.push_back(nullptr);
    }
    //需要根据辅助的空间元素调整参数arr的内容
    for (int i = l; i <=r ; i++)
    {
        arrCopy[i - l] = arr[i];
    }

    int i = l;
    int j = mid + 1;
    for(int k = l;k <= r; k++)
    {
        if(i > mid)
        {
            arr[k] = arrCopy[j - l];
            j ++;
        }
        else if(j > r)
        {
            arr[k] = arrCopy[i - l];
            i++;
        }//以上是判断索引是否合法
        else if((*arrCopy[i - l]) < (*arrCopy[j - l]))
        {
            arr[k] =  arrCopy[i - l];
            i++;
        }
        else
        {
            arr[k] = arrCopy[j - l];
            j++;
        }
    }
}

void mergerSortBU(vector<joinData*> &arr, int n)
{
    for (int sz = 1; sz <= n  ; sz += sz)
    {
        for (int i = 0; i + sz < n; i += sz + sz) {
            __merger(arr, i, i + sz - 1, min(i + sz + sz - 1, n - 1));
        }
    }
}


void __mergeSort(vector<joinData*> &arr, int l, int r)
{
    if(l >= r)
        return;
    int mid = (l + r)  / 2;  //可能溢出
    __mergeSort(arr, l, mid);
    __mergeSort(arr, mid+1, r);
    __merger(arr, l, mid, r);
}


void mergerSort(vector<joinData*> &arr, int n)
{
    __mergeSort(arr, 0, n-1);
}

//quickSort3Ways
//quickSort3Ways
//插入排序重载版,前闭后闭[l, r]

void InsertSortV2(vector<joinData*> &arr, int l, int r)
{
    for (int i = l+1; i <= r; ++i)
    {
        joinData* curCopy = arr[i];  //复制当前的值
        int j = 0;  //保存e应该插入的位置
        for (j = i; j > 0 && ((*arr[j-1]) > (*curCopy)); --j)
        {
            arr[j] = arr[j - 1];
        }
        arr[j] = curCopy;
    }
}

void __quickSort3Ways(vector<joinData*> &arr, int l, int r)
{
    if((r - l) <= 15)
    {
        InsertSortV2(arr, l, r);
        return;
    }
    //partition
    swap(arr[l], arr[rand() % (r - l + 1) + l]);//随机选择一个元素作为标定点
    joinData* v = arr[l];//标定点
    int lt = l;//arr[l+1, lt] < v
    int gt = r + 1;//arr[gt, r] > v
    int i = l + 1;//arr[lt + 1, i) = v
    while (i < gt)
    {
        if((*arr[i]) < (*v))
        {
            swap(arr[i], arr[lt + 1]);
            i++;
            lt++;
        }
        else if((*arr[i]) > (*v))
        {
            swap(arr[i], arr[gt - 1]);
            gt--;
        }
        else{//arr[i] > v
            i++;
        }
    }
    swap( arr[l], arr[lt] );
    __quickSort3Ways(arr, l, lt - 1);
    __quickSort3Ways(arr, gt, r);

}

void quickSort3ways(vector<joinData*> &arr, int n)
{
    srand(time(NULL));
    __quickSort3Ways(arr, 0, n - 1);
}


//以上是头文件包含
vector<dataOriginal*> t1;
BSTRepeat<int, dataOriginal*> t2;

//删除字符串中空格，制表符tab等无效字符
string Trim(string& str)
{
    //str.find_first_not_of(" \t\r\n"),在字符串str中从索引0开始，返回首次不匹配"\t\r\n"的位置
    str.erase(0,str.find_first_not_of(" \t\r\n"));
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    return str;
}

vector<vector<int> > readFiles(char directory[])
{
    ifstream fin(directory);
    string line;
    vector<vector<int> > res;
    vector<int> resEach;
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
        string field;
        vector<string> fields; //声明一个字符串向量
        while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
        {
            fields.push_back(field); //将刚刚读取的字符串添加到向量fields中
        }
        int id1 = std::atoi (fields[0].c_str()); //清除掉向量fields中第一个元素的无效字符，并赋值给变量name
        int id2 = std::atoi (fields[1].c_str()); //清除掉向量fields中第二个元素的无效字符，并赋值给变量age
        int id3 = std::atoi (fields[2].c_str()); //清除掉向量fields中第三个元素的无效字符，并赋值给变量birthday
        resEach.push_back(id1);
        resEach.push_back(id2);
        resEach.push_back(id3);
        res.push_back(resEach);
        resEach.clear();
    }
    return res;
}

vector<vector<int> > readFilesRes(char directory[])
{
    ifstream fin(directory);
    string line;
    vector<vector<int> > res;
    vector<int> resEach;
    while (getline(fin, line))   //整行读取，换行符“\n”区分，遇到文件尾标志eof终止读取
    {
        istringstream sin(line); //将整行字符串line读入到字符串流istringstream中
        string field;
        vector<string> fields; //声明一个字符串向量
        while (getline(sin, field, ',')) //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
        {
            fields.push_back(field); //将刚刚读取的字符串添加到向量fields中
        }
        int id1 = std::atoi (fields[0].c_str()); //清除掉向量fields中第一个元素的无效字符，并赋值给变量name
        int id2 = std::atoi (fields[1].c_str()); //清除掉向量fields中第二个元素的无效字符，并赋值给变量age
        resEach.push_back(id1);
        resEach.push_back(id2);
        res.push_back(resEach);
        resEach.clear();
    }
    return res;
}
/*
 * 初始化处理数据
 * 对t1表数据进行处理，对t2表数据进行处理
 */
void initializeData(vector<vector<int> > &vec1, vector<vector<int> > &vec2)
{
    //初始化t1表格
    //vector<dataOriginal*> t1;
    //t1需要手动释放空间
    for(vector<vector<int> >::iterator iter1 = vec1.begin(); iter1 != vec1.end(); iter1++)
    {
        dataOriginal* temp1 = new dataOriginal((*iter1)[0], (*iter1)[1],(*iter1)[2]);
        t1.push_back(temp1);
    }

    //cout << " table1: " << endl;

    /*
    for(auto iter = t1.begin(); iter != t1.end(); iter++)
    {
        cout << **iter << endl;
    }*/
    //初始化t2表格
    //BSTRepeat<int, dataOriginal*> t2;
    random_shuffle(vec2.begin(), vec2.end());
    for(vector<vector<int> >::iterator iter1 = vec2.begin(); iter1 != vec2.end(); iter1++)
    {
        dataOriginal* temp2 = new dataOriginal((*iter1)[0], (*iter1)[1],(*iter1)[2]);
        t2.insert((*iter1)[2], temp2);  //key:t2.id3, value t2.id3对应的行
    }
    //t2.preOrder();

}

/*
 * d对t1表格的空间进行进行释放
 * vector<dataOriginal*> t1;
 */
void freeT1()
{
    for(auto iter = t1.begin(); iter != t1.end(); iter++)
        delete (*iter);
    //cout << "t1 has been freed.\n";
}

void freeJoinData(vector<joinData*> & JoinResult)
{
    for(vector<joinData*>::iterator iter = JoinResult.begin(); iter != JoinResult.end(); iter++)
    {
        if(*iter)
            delete (*iter);
    }
    //cout << "Join result has been freed.\n";
}

void freeGroupResult(vector<groupData*> groupResult)
{
    for(vector<groupData*>::iterator iter = groupResult.begin(); iter != groupResult.end(); iter++)
    {
        if(*iter)
            delete (*iter);
    }
    //cout << "group result has been freed.\n";
}
//join功能实现
/*
 * 实现Join功能
 * 参数1：原始表1，采用vector<dataOriginal*>类型
 * 参数2：原始表2，BST<int, dataOriginal*>类型，其中key是t2.id3
 * 返回值：满足t1.id3=t2.id3的cases，vector<joinData>类型(t1.id1, t1.id2, t2.id1, t2.id2)
 */
vector<joinData*> joinFun()
{
    vector<joinData*> joinResult;
    for(vector<dataOriginal*>::iterator iter1 = t1.begin(); iter1 != t1.end(); iter1++)
    {
        int t1Id3 = (*iter1)->id3;
        if(t2.contain(t1Id3))//如果表格2中存在t2Id3=t1Id3
        {
            //t2中相同的元素放入t1Id3InT2这个数组中
            vector<dataOriginal **> t1Id3InT2 = t2.search(t1Id3);
            for(vector<dataOriginal **>::iterator iter2 = t1Id3InT2.begin(); iter2 != t1Id3InT2.end(); iter2++)
            {
                joinData* joinResultEach = new joinData((*iter1)->id1, (*iter1)->id2, (**iter2)->id1, (**iter2)->id2);
                joinResult.push_back(joinResultEach);
            }
        }
    }
    /*
    for(vector<joinData*>::iterator iter = joinResult.begin(); iter != joinResult.end(); iter++)
    {
        cout << **iter << endl;
    }*/
    return joinResult;
}

/*
 * group功能实现
 * 参数：join得到的结果
 * 过程：先进行t2.id2和t1.id2字段的排序，然后遍历一遍排序后的结果，相同字段的case进行group，取每一组的maxT1Id1和minT2Id1;
 * 返回：group后的结果，类型是groupData(maxT1D1, t1Id2, minT2D1, t2D2)
 */
vector<groupData*> groupFun(vector<joinData*> &joinResult)
{
    //先排序 后分组
    quickSort3ways(joinResult, joinResult.size());
    //得到的结果按t2Id2, t1Id2有序
    int t2Id2Temp = 0;
    int t1Id2Temp = 0;
    int count = 0;
    vector<joinData*> curGroup;
    vector<groupData*> groupResult;
    for(vector<joinData*>::iterator iter = joinResult.begin(); iter != (joinResult.end()); iter++)
    {
        if(count == 0)
        {
            t1Id2Temp = (*iter)->t1Id2;
            t2Id2Temp = (*iter)->t2Id2;
            curGroup.push_back(*iter);
            count++;
            continue;
        }
        //如果两个字段与上一个case都相同，则属于同一个group
        if((*iter)->t2Id2 == t2Id2Temp && (*iter)->t1Id2 == t1Id2Temp)
        {
            curGroup.push_back(*iter);
            count++;
        }
            //任何一个不同，处理下上一个group，吧new case加入到新的group中去
        else
        {
            //先获得该组的maxT1Id1和minT2Id1;
            int maxT1Id1Temp = curGroup[0]->t1Id1;
            int minT2Id1Temp = curGroup[0]->t2Id1;
            int t1Id2TempHello = curGroup[0]->t1Id2;
            int t2Id2TempHello = curGroup[0]->t2Id2;
            for(vector<joinData*>::iterator iter = curGroup.begin(); iter != curGroup.end(); iter++)
            {
                maxT1Id1Temp = max(maxT1Id1Temp, (*iter)->t1Id1);
                minT2Id1Temp = min(minT2Id1Temp, (*iter)->t2Id1);
            }
            groupData *groupResultEach = new groupData(maxT1Id1Temp, t1Id2TempHello, minT2Id1Temp, t2Id2TempHello);
            groupResult.push_back(groupResultEach);
            curGroup.clear(); //清空当前group，准备装入新的数据
            curGroup.push_back(*iter);//由于当前的数据是一个新的分组，所以最后要加入
            t2Id2Temp = (*iter)->t2Id2;
            t1Id2Temp = (*iter)->t1Id2;
        }
    }
    //处理最后一组数据
    if(curGroup.size())
    {
        //先获得该组的maxT1Id1和minT2Id1;
        int maxT1Id1Temp = curGroup[0]->t1Id1;
        int minT2Id1Temp = curGroup[0]->t2Id1;
        int t1Id2TempHello = curGroup[0]->t1Id2;
        int t2Id2TempHello = curGroup[0]->t2Id2;
        for(vector<joinData*>::iterator iter = curGroup.begin(); iter != curGroup.end(); iter++)
        {
            maxT1Id1Temp = max(maxT1Id1Temp, (*iter)->t1Id1);
            minT2Id1Temp = min(minT2Id1Temp, (*iter)->t2Id1);
        }
        groupData *groupResultEach = new groupData(maxT1Id1Temp, t1Id2TempHello, minT2Id1Temp, t2Id2TempHello);
        groupResult.push_back(groupResultEach);
        curGroup.clear();
    }
    /*
    cout << "group result: " << endl;
    for(vector<groupData*>::iterator iter = groupResult.begin(); iter != groupResult.end(); iter++)
    {
        cout << **iter << endl;
    }
    */
    return groupResult;
}


void compareResult(vector<groupData*> &groupRes, vector<vector<int> > &correctRes)
{
    cout << "\ncorrect size: " << correctRes.size() << endl;
    for (int i = 0; i < correctRes.size(); ++i)
    {
        if(correctRes[i][0] != groupRes[i]->maxT1D1 ||
           correctRes[i][1] != groupRes[i]->minT2D1)
        {
            cout << "wrong answer!!\n";
            cout << "correct answer: " << correctRes[i][0] << " " << correctRes[i][1] << endl;
            cout << "your answer: " << groupRes[i]->maxT1D1 << " " << groupRes[i]->minT2D1 << endl;
            return;
        }
    }
    cout << "all correct!\n";
}

/*
 * 进行order
 * 最后采用一次归并排序就可以
 */

void orderFun(vector<groupData*> &data)
{
    //vector<vector<int> > resPredict;
    //vector<int> resPredictEach;
    mergerSortGroupData(data, data.size());
    for(auto iter = data.begin(); iter != data.end(); iter++)
    {
    	/*
        if(iter != (data.end() - 1))
    		cout << (*iter)->maxT1D1 << "," << (*iter)->minT2D1 << endl;
    	else
    		cout << (*iter)->maxT1D1 << "," << (*iter)->minT2D1;
            */
        cout << (*iter)->maxT1D1 << "," << (*iter)->minT2D1 << endl;
    }
    /*
    cout << "final result.\n";
    for(vector<groupData*>::iterator iter = data.begin(); iter != data.end(); iter++)
    {
        resPredictEach.push_back((*iter)->maxT1D1);
        resPredictEach.push_back((*iter)->minT2D1);
        resPredict.push_back(resPredictEach);
    }
    for(auto iter = data.begin(); iter != data.end(); iter++)
    {
        cout << **iter << endl;
    }*/
}

int main()
{
    char dir1[] = "/home/web/ztedatabase/input1.csv";
    char dir2[]= "/home/web/ztedatabase/input2.csv";
    //char dir1[] = "/data/lixulong/ZTE-com/ZTE-com/version1/data1000row/table1.csv";
    //char dir2[]= "/data/lixulong/ZTE-com/ZTE-com/version1/data1000row/table2.csv";
    //char resDir[]= "/data/lixulong/ZTE-com/ZTE-com/version1/data1000row/result.csv";
    vector<vector<int> > table1Vec(readFiles(dir1));
    vector<vector<int> > table2Vec(readFiles(dir2));
    //vector<vector<int> > correctRes(readFilesRes(resDir));
    initializeData(table1Vec, table2Vec);
    vector<joinData*> joinResult = joinFun();
    vector<groupData*> groupResult = groupFun(joinResult);
    orderFun(groupResult);
    //compareResult(groupResult, correctRes);
    freeT1();
    freeJoinData(joinResult);
    freeGroupResult(groupResult);
    return 0;
}
