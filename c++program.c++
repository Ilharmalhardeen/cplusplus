#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    std::string stream;
    std::string className;
    std::vector<int> marks;
    int totalMarks;

    Student(const std::string& n, const std::string& s, const std::string& c, const std::vector<int>& m)
        : name(n), stream(s), className(c), marks(m), totalMarks(0) {}
};

bool compareStudents(const Student& s1, const Student& s2) {
    return s1.totalMarks > s2.totalMarks;
}

void readStudentData(std::vector<Student>& students) {
    std::ifstream inputFile("student_data.txt");
    if (!inputFile) {
        std::cout << "Error opening file. Make sure student_data.txt exists." << std::endl;
        return;
    }

    std::string name, stream, className;
    int marksCount, mark;
    while (inputFile >> name >> stream >> className >> marksCount) {
        std::vector<int> marks;
        for (int i = 0; i < marksCount; ++i) {
            inputFile >> mark;
            marks.push_back(mark);
        }
        students.emplace_back(name, stream, className, marks);
    }

    inputFile.close();
}

void calculateTotalMarks(std::vector<Student>& students) {
    for (auto& student : students) {
        for (int mark : student.marks) {
            student.totalMarks += mark;
        }
    }
}

void rankStudents(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), compareStudents);
}

void printRankings(const std::vector<Student>& students) {
    std::cout << "School Rankings:" << std::endl;
    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << "Rank " << i + 1 << ": " << students[i].name << " (Total Marks: " << students[i].totalMarks << ")" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Class Rankings:" << std::endl;
    std::string currentClass = "";
    int classRank = 0;
    for (const auto& student : students) {
        if (student.className != currentClass) {
            currentClass = student.className;
            classRank = 0;
            std::cout << "Class " << currentClass << ":" << std::endl;
        }
        ++classRank;
        std::cout << "Rank " << classRank << ": " << student.name << " (Total Marks: " << student.totalMarks << ")" << std::endl;
    }
}

void writeRankingsToFile(const std::vector<Student>& students) {
    std::ofstream outputFile("rankings.txt");
    if (!outputFile) {
        std::cout << "Error opening file for writing rankings." << std::endl;
        return;
    }

    outputFile << "School Rankings:" << std::endl;
    for (size_t i = 0; i < students.size(); ++i) {
        outputFile << "Rank " << i + 1 << ": " << students[i].name << " (Total Marks: " << students[i].totalMarks << ")" << std::
