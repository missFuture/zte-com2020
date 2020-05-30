# zte-com2020
这个repo是关于中兴2020年算法竞赛，题目是关于数据库优化，埃德加考特派别
## 题目要求 数据库连接、分组、排序算法
### 赛题方向 
基于C/C++语言运用合理的算法和数据结构知识设计并实现关系型数据库的连接、分组、排序功能

### 赛题简介
  关系型数据库常见的操作有排序、分组、连接等，例如“SELECT * FROM t1 JOIN t2 group by t1.id1 order by t2.id1”这样的语句。
  现有两张数据表t1(id1 int primary key,id2 int,id3 int)、t2(id1 int primary key,id2 int,id3 int)，其中表t1的数据存储在文件input1.csv中，表t2的数据存储在文件input2.csv中。每个文件中有三个整形字段，字段之间用逗号分开，记录条目之间换行。要求针对以上给出的t1、t2两个表数据，采用C/C++开发能模拟数据库连接(JOIN)、分组(GROUP BY)、排序(ORDER BY)功能的算法程序，正确计算出下面语句的结果。
```sql
select max(t1.id1),min(t2.id1) from t1 join t2 on t1.id3 = t2.id3
group by t1.id2,t2.id2 order by max(t1.id1),t2.id2,t1.id2;
```