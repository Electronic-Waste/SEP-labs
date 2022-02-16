#include "Class.h"
#include <string>
#include "Student.h"
#include <cstring>

void Class::addStudent(const Student &st)
{
    StudentWrapper sw(st.id, st);
    students.push_back(sw);
}

StudentWrapper &Class::getStudentWrapper(const std::string &studentId)
{
    for (std::vector<StudentWrapper>::iterator it = students.begin();
         it != students.end();
         ++it) {
        if (it->id == studentId) {
            return *it;
            }
    }
    throw "No matching student!";
}

double Class::getAvgScore()
{
    // TODO: implement getAvgScore.
   double total_Score=0.0;
   int cnt = 0;
    for (vector<StudentWrapper>::iterator it = students.begin();
        it != students.end();
        ++it)   {
        ++cnt;
        total_Score += it->getScore();
    }

    if (!cnt) return 0;
    return total_Score/cnt;
}

double Class::outputScore(string id)
{
    for(vector<StudentWrapper>::iterator it = students.begin();
        it != students.end();
        ++it)
        if (id == it->id) return it->getScore();

}
