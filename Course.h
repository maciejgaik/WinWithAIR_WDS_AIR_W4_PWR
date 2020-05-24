#ifndef COURSE_H
#define COURSE_H

#include <QString>

class Course{
    QString name;
    int ects;
    bool status;
public:
    Course(QString n, int e, bool s = false){
        name = n;
        ects = e;
        status = s;
    }

    QString getName() const {return name;}
    int getEcts() const {return ects;}
    bool getStatus() const {return status;}
    void changeStatus(bool s){status = s;}
};

#endif // COURSE_H
