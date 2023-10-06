#include "scorer.h"
bool Comparison(const Event& event1, const Event& event2) {
    return event1.time < event2.time;
}

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    ScoreTable score_table{};
    std::map<StudentName, std::set<TaskName>> is_opened;
    std::map<StudentName, std::set<TaskName>> is_success;
    auto tmp_events = events;
    std::sort(tmp_events.begin(), tmp_events.end(), Comparison);
    for (auto& el : tmp_events) {
        if (difftime(el.time, score_time) <= 0) {
            if (el.event_type == EventType::MergeRequestOpen) {
                is_opened[el.student_name].insert(el.task_name);
            }
            if (el.event_type == EventType::MergeRequestClosed) {
                is_opened[el.student_name].erase(el.task_name);
            }
            if (el.event_type == EventType::CheckSuccess) {
                is_success[el.student_name].insert(el.task_name);
            }
            if (el.event_type == EventType::CheckFailed) {
                is_success[el.student_name].erase(el.task_name);
            }

            if (is_success[el.student_name].count(el.task_name) && !is_opened[el.student_name].count(el.task_name)) {
                score_table[el.student_name].insert(el.task_name);
            } else {
                score_table[el.student_name].erase(el.task_name);
            }

            if (score_table[el.student_name].empty()) {
                score_table.erase(el.student_name);
            }
        }
    }

    return score_table;
}
