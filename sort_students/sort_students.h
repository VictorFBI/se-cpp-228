#pragma once

#include <algorithm>
#include <string>
#include <vector>

struct Date {
    int day = 0;
    int month = 0;
    int year = 0;
};

struct Student {
    std::string name;
    std::string last_name;
    Date birth_date;
};

enum class SortKind { Name, Date };

void SortStudents(std::vector<Student>& students, SortKind sort_kind);
int CompareDates(Date date_1, Date date_2);
int CompareNames(Student student_1, Student student_2);
bool CompareStudentsByNames(Student student_1, Student student_2);
bool CompareStudentsByDates(Student student_1, Student student_2);
