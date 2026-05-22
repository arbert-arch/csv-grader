#include <algorithm>
#include <exception>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Student {
    std::string name;
    int math = 0;
    int english = 0;
    int total = 0;
    double average = 0.0;
};

int main() {
    const std::string filename = "data.csv";
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "错误：无法打开文件 '" << filename << "'。请检查文件是否存在并具有读取权限。" << std::endl;
        return 1;
    }

    std::vector<Student> students;
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;
        if (line.empty()) {
            continue; // 忽略空行
        }

        std::istringstream lineStream(line);
        std::string name;
        std::string mathStr;
        std::string englishStr;

        if (!std::getline(lineStream, name, ',')) {
            std::cerr << "错误：第 " << lineNumber << " 行格式错误。缺少姓名字段。" << std::endl;
            return 1;
        }
        if (!std::getline(lineStream, mathStr, ',')) {
            std::cerr << "错误：第 " << lineNumber << " 行格式错误。缺少数学成绩字段。" << std::endl;
            return 1;
        }
        if (!std::getline(lineStream, englishStr, ',')) {
            std::cerr << "错误：第 " << lineNumber << " 行格式错误。缺少英语成绩字段。" << std::endl;
            return 1;
        }

        // 去掉字段两端的空白
        auto trim = [](std::string &s) {
            auto notSpace = [](unsigned char ch) { return !std::isspace(ch); };
            s.erase(s.begin(), std::find_if(s.begin(), s.end(), notSpace));
            s.erase(std::find_if(s.rbegin(), s.rend(), notSpace).base(), s.end());
        };

        trim(name);
        trim(mathStr);
        trim(englishStr);

        if (name.empty()) {
            std::cerr << "错误：第 " << lineNumber << " 行格式错误。姓名不能为空。" << std::endl;
            return 1;
        }

        try {
            int mathScore = std::stoi(mathStr);
            int englishScore = std::stoi(englishStr);

            Student student;
            student.name = name;
            student.math = mathScore;
            student.english = englishScore;
            student.total = mathScore + englishScore;
            student.average = student.total / 2.0;
            students.push_back(student);
        } catch (const std::invalid_argument &) {
            std::cerr << "错误：第 " << lineNumber << " 行格式错误。数学或英语成绩不是有效整数。" << std::endl;
            return 1;
        } catch (const std::out_of_range &) {
            std::cerr << "错误：第 " << lineNumber << " 行格式错误。成绩整数超出范围。" << std::endl;
            return 1;
        }
    }

    if (students.empty()) {
        std::cerr << "警告：文件中没有有效的学生成绩数据。" << std::endl;
        return 1;
    }

    // 按总分降序排序
    std::sort(students.begin(), students.end(), [](const Student &a, const Student &b) {
        return a.total > b.total;
    });

    // 打印成绩单表头
    std::cout << std::left << std::setw(20) << "姓名"
              << std::right << std::setw(8) << "数学"
              << std::setw(8) << "英语"
              << std::setw(10) << "总分"
              << std::setw(10) << "平均分" << std::endl;
    std::cout << std::string(56, '-') << std::endl;

    // 打印每个学生信息
    for (const auto &student : students) {
        std::cout << std::left << std::setw(20) << student.name
                  << std::right << std::setw(8) << student.math
                  << std::setw(8) << student.english
                  << std::setw(10) << student.total
                  << std::setw(10) << std::fixed << std::setprecision(1) << student.average
                  << std::endl;
    }

    return 0;
}
