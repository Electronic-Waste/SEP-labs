#include "Student.h"
#include <string>
#include <sstream>
#include "Class.h"

std::string Student::toString() const
{
    // TODO: uncomment the following code after implementing class Student.

    std::ostringstream oss;
    oss << "Student Information:"
        << "\n\tid: " << id
        << "\n\tname: " << name
        << "\n\tenrollment year: " << year
        << "\n\tdegree: " << (degree == graduate ? "graduate" : "undergraduate")
        << std::endl;
    return oss.str();
}

// TODO: implement functions which are declared in Student.h.
void Student::addclass(Class *c)
{
    classes.push_back(c);
}

double Undergraduate::getGrade()
{
    //cout <<'U'<<endl;
    double grade = 0.0;
    int total_point = 0;

    for (vector<Class*>::iterator it = classes.begin();
         it != classes.end();
         ++it)
    {
        grade += (*it)->outputScore(id)/20 * (*it)->point;
        total_point += (*it)->point;
        //cout <<grade<<endl;
        //cout <<total_point<<endl;
    }

    if (!total_point) return 0;
    else return grade/total_point;
}

double Graduate::getGrade()
{
    double grade = 0.0;
    int total_point = 0;

    for (vector<Class*>::iterator it = classes.begin();
         it != classes.end();
         ++it)
    {
        double score = (*it)->outputScore(id);
        double newgrade;

        switch ((int)score/10)
        {
        case 10:
        case 9: newgrade =4.0;break;
        case 8: newgrade =3.5;break;
        case 7: newgrade =3.0;break;
        case 6: newgrade =2.5;break;
        default: newgrade =2.0;
        }

        grade += newgrade * (*it)->point;
        total_point += (*it)->point;
    }

    if (!total_point) return 0;
    else return grade/total_point;

}

