#ifndef STUDENT_H_
#define STUDENT_H_

#include <string>
#include <vector>
#include <iostream>
using namespace std;

class Class;

enum Degree {
    undergraduate,
    graduate
};

class Student {
    // TODO: implement class Student.
private:

protected:
    vector <Class*> classes;
    string name;
    string year;
    Degree degree;

public:
    Student (string i,string n,string y,Degree d):name(n),year(y),degree(d),id(i){}
    //Student(){}
    virtual ~Student(){};
    const std::string id;
    std::string toString() const;
    virtual double getGrade() = 0;
    void addclass(Class* c);
};


// TODO: implement class Graduate.
class Graduate:public Student{

public:
    Graduate(string i,string n,string y):Student(i,n,y,graduate){}
    //Graduate(){}
    ~Graduate(){}

    double getGrade();
} ;


// TODO: implement class Undergraduate.
class Undergraduate:public Student{

public:
    Undergraduate(string i,string n,string y):Student(i,n,y,undergraduate){}
    //Undergraduate(){}
    ~Undergraduate(){}
    double getGrade();
};

class StudentWrapper {
private:
    const Student &student;
    double score = 0.0;
public:
    const std::string id;
    // TODO: fix error
    StudentWrapper(const std::string &ID, const Student &STUDENT): id(ID),student(STUDENT) {}
    ~StudentWrapper(){}
    void setScore(double score)
    {
        if (score < 0 || score > 100)
            throw "Invalid Score!";
        this->score = score;
    }

    double getScore() const
    {
        return this->score;
    }

    std::string toString() const
    {
        return student.toString();
    }
};

#endif // STUDENT_H_
