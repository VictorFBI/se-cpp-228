#include "sort_students.h"

int CompareDates(Date date_1, Date date_2) {
    if (date_1.year > date_2.year) {
        return 1;
    }
    if (date_1.year < date_2.year) {
        return -1;
    }
    if (date_1.month > date_2.month) {
        return 1;
    }
    if (date_1.month < date_2.month) {
        return -1;
    }
    if (date_1.day > date_2.day) {
        return 1;
    }
    if (date_1.day < date_2.day) {
        return -1;
    }

    return 0;
}

int CompareNames(Student student_1, Student student_2) {
    if (student_1.last_name > student_2.last_name) {
        return 1;
    }
    if (student_1.last_name < student_2.last_name) {
        return -1;
    }
    if (student_1.name > student_2.name) {
        return 1;
    }
    if (student_1.name < student_2.name) {
        return -1;
    }

    return 0;
}

bool CompareStudentsByNames(Student student_1, Student student_2) {
    if (CompareNames(student_1, student_2) == 1) {
        return false;
    }
    if (CompareNames(student_1, student_2) == 0) {
        switch (CompareDates(student_1.birth_date, student_2.birth_date)) {
            case 1:
                return false;
            case -1:
                return true;
        }
    }

    return true;
}
bool CompareStudentsByDates(Student student_1, Student student_2) {
    if (CompareDates(student_1.birth_date, student_2.birth_date) == 1) {
        return false;
    }
    if (CompareDates(student_1.birth_date, student_2.birth_date) == 0) {
        switch (CompareNames(student_1, student_2)) {
            case 1:
                return false;
            case -1:
                return true;
        }
    }

    return true;
}

void SortStudents(std::vector<Student> &students, SortKind sort_kind) {
    if (sort_kind == SortKind::Name) {
        std::sort(students.begin(), students.end(), CompareStudentsByNames);

    } else {
        std::sort(students.begin(), students.end(), CompareStudentsByDates);
    }
}
