#include "admission.h"

bool operator<(Date date_1, Date date_2) {
    if (date_1.year < date_2.year) {
        return true;
    }
    if (date_1.year > date_2.year) {
        return false;
    }
    if (date_1.month < date_2.month) {
        return true;
    }
    if (date_1.month > date_2.month) {
        return false;
    }
    if (date_1.day < date_2.day) {
        return true;
    }
    if (date_1.day > date_2.day) {
        return false;
    }

    return false;
}
bool operator>(Date date_1, Date date_2) {
    if (date_1.year < date_2.year) {
        return false;
    }
    if (date_1.year > date_2.year) {
        return true;
    }
    if (date_1.month < date_2.month) {
        return false;
    }
    if (date_1.month > date_2.month) {
        return true;
    }
    if (date_1.day < date_2.day) {
        return false;
    }
    if (date_1.day > date_2.day) {
        return true;
    }

    return false;
}

bool ComparisonApplicants(const Applicant& applicant_1, const Applicant& applicant_2) {
    if ((applicant_1).points > (applicant_2).points) {
        return true;
    }
    if ((applicant_1).points < (applicant_2).points) {
        return false;
    }
    if ((applicant_1).student.birth_date < (applicant_2).student.birth_date) {
        return true;
    }
    if ((applicant_1).student.birth_date > (applicant_2).student.birth_date) {
        return false;
    }
    if ((applicant_1).student.name < (applicant_2).student.name) {
        return true;
    }
    if ((applicant_1).student.name > (applicant_2).student.name) {
        return false;
    }

    return false;
}
bool ComparisonByNameAndBirth(const Student* student_1, const Student* student_2) {
    if ((*student_1).name < (*student_2).name) {
        return true;
    }
    if ((*student_1).name > (*student_2).name) {
        return false;
    }
    if ((*student_1).birth_date < (*student_2).birth_date) {
        return true;
    }
    if ((*student_1).birth_date > (*student_2).birth_date) {
        return false;
    }

    return false;
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    auto tmp_applicants = applicants;
    std::vector<size_t> indexes;
    for (size_t i = 0; i < tmp_applicants.size(); ++i) {
        indexes.push_back(i);
    }
    for (size_t i = 0; i < tmp_applicants.size() - 1; ++i) {
        for (size_t j = i + 1; j < tmp_applicants.size(); ++j) {
            if (!ComparisonApplicants(tmp_applicants[i], tmp_applicants[j])) {
                std::swap(tmp_applicants[i], tmp_applicants[j]);
                std::swap(indexes[i], indexes[j]);
            }
        }
    }
    AdmissionTable admission_table;
    UniversityTable university_table;
    for (auto& el : universities) {
        std::vector<const Student*> max_students;
        max_students.reserve(el.max_students);
        admission_table.emplace(el.name, max_students);
        university_table.emplace(el.name, el);
    }
    int i = 0;
    for (auto& el : tmp_applicants) {
        for (auto& wish : el.wish_list) {
            if (admission_table[wish].size() < university_table[wish].max_students) {
                admission_table[wish].push_back(&applicants[indexes[i]].student);
                ++i;
                break;
            }
        }
    }

    for (auto& el : admission_table) {
        std::sort(el.second.begin(), el.second.end(), ComparisonByNameAndBirth);
    }

    return admission_table;
}
