# zte-com2020
这个repo是关于中兴2020年算法竞赛，题目是关于数据库优化，埃德加考特派别
## 题目要求 
数据库连接、分组、排序算法
### 赛题方向 
基于C/C++语言运用合理的算法和数据结构知识设计并实现关系型数据库的连接、分组、排序功能

### 赛题简介
  关系型数据库常见的操作有排序、分组、连接等，例如“SELECT * FROM t1 JOIN t2 group by t1.id1 order by t2.id1”这样的语句。
  现有两张数据表t1(id1 int primary key,id2 int,id3 int)、t2(id1 int primary key,id2 int,id3 int)，其中表t1的数据存储在文件input1.csv中，表t2的数据存储在文件input2.csv中。每个文件中有三个整形字段，字段之间用逗号分开，记录条目之间换行。要求针对以上给出的t1、t2两个表数据，采用C/C++开发能模拟数据库连接(JOIN)、分组(GROUP BY)、排序(ORDER BY)功能的算法程序，正确计算出下面语句的结果。
```sql
select max(t1.id1),min(t2.id1) from t1 join t2 on t1.id3 = t2.id3
group by t1.id2,t2.id2 order by max(t1.id1),t2.id2,t1.id2;
```
### 赛题说明
1.输入文件路径为：/home/web/ztedatabase/input1.csv和/home/web/ztedatabase/input2.csv
2.输出请输出到"标准系统输出"中，程序不要输出结果集以外的任何内容,输出结果形式同输入一致；

### 验收准则
（1）输出结果正确
（2）时间越快越优
（3）内存控制合理


## 解题思路
### 算法流程
<div align=center>
<img width = '600' height = '600' src = "https://github.com/missFuture/zte-com2020/blob/master/images/软件框架.png"/>
</div>

### 数据类型
<div align=center>
<img width = '600' height = '600' src = "https://github.com/missFuture/zte-com2020/blob/master/images/数据类型图.png"/>
</div>


### 实验数据
[table1.csv](https://github.com/missFuture/zte-com2020/blob/master/table1.csv)和[table2.csv](https://github.com/missFuture/zte-com2020/blob/master/table2.csv)是采用excel生成的10000组测试数据，id1顺序打乱，id2,id3均在[0，100]范围内,然后采用SQLyog生成正确的实验结果。结果保存在[result.csv](https://www.jianshu.com/p/ea6ec80ad5f2)中。最后和程序运行的结果进行对比，验证其是否正确。

### 实验结果
|阶段|初始化|联结|分组|排序|总计|得分|排名|
|--|--|--|--|--|--|--|--|
|本地测试结果(ms)|6.46|203|865|14|1088|10|98/100|
|--|--|--|--|--|--|--|--|
|本地测试结果(ms)|65|102|23|8|198|.|.|

## 改进方向
对于t2表格，采用带重复键值的二叉树搜索树完成，查询速度不一定是o(logn)，由于前期采用基于红黑树的map完成，提交结果提示超过限制内存，改用二叉搜索树存储t2表数据，键值是id3，这样t2表就按id3有序，理想查找时间是O(logn)，循环嵌套匹配t1表格，实现join。官方对题目讲解中，Join包括三种方法，嵌套循环连接，归并连接，散列连接。所以可以采用unordered_map完成join过程（[参考链接](https://github.com/jueserencai/sql-query-implementation)）。优化后的版本见[optimized_version](https://github.com/missFuture/zte-com2020/blob/master/optimized_version.cpp).
