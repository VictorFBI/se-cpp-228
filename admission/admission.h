#pragma once

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

struct Date {
    int day = 0;
    int month = 0;
    int year = 0;
};

struct Student {
    std::string name;
    Date birth_date;
};

struct University {
    std::string name;
    size_t max_students = 0;
};

struct Applicant {
    Student student;
    int points;
    std::vector<std::string> wish_list;
};

using AdmissionTable = std::unordered_map<std::string, std::vector<const Student*>>;
using UniversityTable = std::unordered_map<std::string, University>;

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants);

bool ComparisonApplicants(const Applicant& applicant_1, const Applicant& applicant_2);
bool ComparisonByNameAndBirth(const Student* student_1, const Student* student_2);

bool operator<(Date date_1, Date date_2);
bool operator>(Date date_1, Date date_2);
