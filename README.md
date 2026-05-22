# CSV 学生成绩统计

这是一个 C++17 控制台程序示例，用于读取 `data.csv` 并输出学生成绩单。

## 文件说明

- `main.cpp`：程序源代码。
- `data.csv`：示例输入文件，第一列为姓名，第二列为数学成绩，第三列为英语成绩。

## 示例 `data.csv`

```
张三,85,92
李四,78,88
王五,90,79
赵六,72,95
钱七,88,84
```

## 编译与运行

在 Windows 上使用 MinGW 或 GCC：

```powershell
cd g:\C++\grad\csv-grader
G:\C++\mingw64\bin\g++.exe -std=c++17 main.cpp -o csv-grader.exe
./csv-grader.exe
```

## 功能

- 读取 `data.csv`
- 计算每个学生的总分和平均分
- 按总分降序排序
- 在控制台打印带表头的成绩单
- 处理文件打开失败和 CSV 格式错误，并输出清晰错误提示
