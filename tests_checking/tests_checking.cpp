#include "tests_checking.h"

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<StudentAction> deque;
    for (auto& el : student_actions) {
        if (el.side == Side::Top) {
            deque.push_front(el);
        } else {
            deque.push_back(el);
        }
    }

    std::vector<std::string> order_of_checking;
    for (auto el : queries) {
        order_of_checking.push_back(deque[el - 1].name);
    }

    return order_of_checking;
}
