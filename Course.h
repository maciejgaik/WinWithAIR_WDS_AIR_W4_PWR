#ifndef COURSE_H
#define COURSE_H

/*!
 *\file
 *\brief Definicja klasy Course
 * Plik zawiera definicje klasy Course
 *
 * Klasa modeluje kurs jako nazwa, ilosc punktów oraz status
 * Jej atrybutami są: nazwa kursu, wartość punktowa kursu oraz
 * status czy kurs występuje ponownie
 */

#include <QString>

class Course{
    /*!
     * \brief Nazwa kursu
     */
    QString name;

    /*!
     * \brief Wartość punktowa kursu
     */
    int ects;

    /*!
     * \brief Status czy kurs już wystąpił
     */
    bool status;
public:
    /*!
     * \brief Konstruktor inicjalizujacy atrybuty klasy
     * przekazanymi parametrami
     * \param [in] _name - nazwa kursu
     * \param [in] _ects - wartosc punktowa
     * \param [in] _status - status powtórzenia
     */
    Course(QString _name, int _ects, bool _status = false){
        name = _name;
        ects = _ects;
        status = _status;
    }

    /*!
     * \brief Metoda zwraca nazwę obiektu
     * \return name - nazwa kursu
     */
    inline QString getName() const {return name;}

    /*!
     * \brief Zwraca wartość punktową kursu
     * \return ects - wartość punktowa
     */
    inline int getEcts() const {return ects;}

    /*!
     * \brief Zwraca status czy kurs już wystąpił
     * \return status - status powtórzenia
     */
    inline bool getStatus() const {return status;}

    /*!
     * \brief Metoda zmienia status obiektu
     * \param [in] newStatus - wartosc na jaka ma byc zmieniony atrybut status
     */
    inline void changeStatus(bool newStatus){status = newStatus;}
};

#endif // COURSE_H
