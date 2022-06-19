#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;
#endif /* __PROGTEST__ */

//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument
{
public:
    InvalidDateException ( )
            : invalid_argument ( "invalid date or format" )
    {
    }
};
//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & ( * date_format ( const char * fmt ) ) ( ios_base & x )
{
    return [] ( ios_base & ios ) -> ios_base & { return ios; };
}
//=================================================================================================
class CDate
{
public:

    CDate(const int & y, const int & m, const int & d) {
        _time = {0,0,0,d,m,y};
        if (!_isDateValid()) {
            throw InvalidDateException();
        }
    }
    CDate (const CDate &old_obj) {
        _time = {0,0,0,old_obj._time.tm_mday,old_obj._time.tm_mon,old_obj._time.tm_year};
    }
    ~CDate() = default;
    friend istream & operator >> (istream & is, CDate & date);
    friend ostream & operator << (ostream & os, const CDate & date);

    CDate operator + (const int & add) const {
        return addDays(add);
    }

    CDate operator - (const int & add) const {
        return addDays(-add);
    }

    int operator - (const CDate & other) const {
//        tm a = { 0,0,0, _time.tm_mday, _time.tm_mon - 1, _time.tm_year - 1900};
//        tm b = { 0,0,0, other._time.tm_mday, other._time.tm_mon - 1, other._time.tm_year - 1900};
//        std::time_t x = std::mktime(&a);
//        std::time_t y = std::mktime(&b);
//        double difference = std::difftime(x, y) / (60 * 60 * 24);
//        difference = difference + 0.5 - (difference<0);
//        return (int)difference;
        return rdn(_time.tm_year, _time.tm_mon, _time.tm_mday) - rdn(other._time.tm_year, other._time.tm_mon, other._time.tm_mday);

    }

    bool operator == (const CDate & other) const {
        time_t x, y;
        normalizeTm(other, x, y);
        if (x == y)
            return true;
        return false;
    }
    bool operator > (const CDate & other) const {
        time_t x, y;
        normalizeTm(other, x, y);
        if (x > y)
            return true;
        return false;
    }
    bool operator < (const CDate & other) const {
        time_t x, y;
        normalizeTm(other, x, y);
        if (x < y)
            return true;
        return false;
    }
    bool operator != (const CDate & other) const {
        if (*this == other)
            return false;
        return true;
    }
    bool operator >= (const CDate & other) const {
        if (*this == other || *this > other)
            return true;
        return false;
    }
    bool operator <= (const CDate & other) const {
        if (*this == other || *this < other)
            return true;
        return false;
    }

    CDate operator ++ () {
        *this = *this + 1;
        CDate d = *this;
        return d;
    }
    CDate operator -- () {
        *this = *this - 1;
        CDate d = *this;
        return d;
    }
    CDate operator ++ (int) {
//        ++(*this);
//        return *this;
        CDate d = *this;
        ++(*this);
        return d;
    }
    CDate operator -- (int) {
//        --(*this);
//        return *this;
        CDate d = *this;
        --(*this);
        return d;
    }
private:
    tm _time{};
    int
    static rdn(int y, int m, int d) { /* Rata Die day one is 0001-01-01 */
        if (m < 3)
            y--, m += 12;
        return 365*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306;
    }

    // from https://www.geeksforgeeks.org/program-check-date-valid-not/
    static bool _isLeap(const int year) {

        return (((year % 4 == 0) &&
                 (year % 100 != 0)) ||
                (year % 400 == 0));
    }
    bool _isDateValid() const {
        int d = _time.tm_mday;
        int m = _time.tm_mon;
        int y = _time.tm_year;
        if (m < 1 || m > 12)
            return false;
        if (d < 1 || d > 31)
            return false;

        if (m == 2)
        {
            if (_isLeap(y))
                return (d <= 29);
            else
                return (d <= 28);
        }

        if (m == 4 || m == 6 ||
            m == 9 || m == 11)
            return (d <= 30);
        return true;
    }
    CDate addDays(const int &add) const {
        tm resTime = {0, 0, 0, _time.tm_mday, _time.tm_mon - 1, _time.tm_year - 1900};
        mktime(&resTime);
        resTime = {0,0,0,resTime.tm_mday + add, resTime.tm_mon, resTime.tm_year};
        mktime(&resTime);
        resTime = {0,0,0,resTime.tm_mday, resTime.tm_mon+1, resTime.tm_year+1900};
//        mktime(&resTime);

        CDate d = CDate(resTime.tm_year, resTime.tm_mon, resTime.tm_mday);
        return d;
    }
    void normalizeTm(const CDate &other, time_t &x, time_t &y) const {
        tm a = {0, 0, 0, _time.tm_mday, _time.tm_mon - 1, _time.tm_year - 1900};
        tm b = { 0,0,0, other._time.tm_mday, other._time.tm_mon - 1, other._time.tm_year - 1900};
        x= mktime(&a);
        y= mktime(&b);
    }
};
ostream & operator << (ostream & os, const CDate & date){
    os << date._time.tm_year << "-" << setw(2) << setfill('0') << date._time.tm_mon << "-" << setw(2) << date._time.tm_mday;
    return os;
}
istream & operator >> (istream & is, CDate & date) {
    int y, m, d; char del1, del2;
    is >> y >> del1 >> m >> del2 >> d;

    CDate temp = date;
    temp._time.tm_mday = d; temp._time.tm_mon = m; temp._time.tm_year = y;
    if (!temp._isDateValid() || del1 != '-' || del2 != '-' || is.fail()) {
        is.setstate(ios::failbit);
        return is;
    }
    date = temp;
    return is;
}

#ifndef __PROGTEST__
int main ( void )
{
    ostringstream oss;
    istringstream iss;

    CDate a ( 2000, 1, 2 );
    CDate b ( 2010, 2, 3 );
    CDate c ( 2004, 2, 10 );
    oss . str ("");
    //b = a + -5;
    oss << a;
    assert ( oss . str () == "2000-01-02" );
    oss . str ("");
    oss << b;
    assert ( oss . str () == "2010-02-03" );
    oss . str ("");
    oss << c;
    assert ( oss . str () == "2004-02-10" );
    a = a + 1500;
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2004-02-10" );
    b = b - 2000;
    oss . str ("");
    oss << b;
    assert ( oss . str () == "2004-08-13" );
    assert ( b - a == 185 );
    assert ( ( b == a ) == false );
    assert ( ( b != a ) == true );
    assert ( ( b <= a ) == false );
    assert ( ( b < a ) == false );
    assert ( ( b >= a ) == true );
    assert ( ( b > a ) == true );
    assert ( ( c == a ) == true );
    assert ( ( c != a ) == false );
    assert ( ( c <= a ) == true );
    assert ( ( c < a ) == false );
    assert ( ( c >= a ) == true );
    assert ( ( c > a ) == false );
    a = ++c;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-11 2004-02-11" );
    a = --c;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-10 2004-02-10" );
    a = c++;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-10 2004-02-11" );
    a = c--;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-11 2004-02-10" );
    iss . clear ();
    iss . str ( "2015-09-03" );
    assert ( ( iss >> a ) );
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2015-09-03" );
    a = a + 70;
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2015-11-12" );

    CDate d ( 2000, 1, 1 );
    try
    {
        CDate e ( 2000, 32, 1 );
        assert ( "No exception thrown!" == nullptr );
    }
    catch ( ... )
    {
    }
    iss . clear ();
    iss . str ( "2000-12-33" );
    assert ( ! ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-01-01" );
    iss . clear ();
    iss . str ( "2000-11-31" );
    assert ( ! ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-01-01" );
    iss . clear ();
    iss . str ( "2000-02-29" );
    assert ( ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-02-29" );
    iss . clear ();
    iss . str ( "2001-02-29" );
    assert ( ! ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-02-29" );


    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
