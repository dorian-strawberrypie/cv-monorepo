#ifndef __PROGTEST__
#include <cstring>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stdexcept>
#include <algorithm>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

class CDataType {
public:
    bool operator == (const CDataType & other) const {
        return isTypeEqual(other);
    }
    bool operator != (const CDataType & other) const {
        return ! (*this == other);
    }
    virtual size_t getSize() const {
        return size;
    }
    friend ostream& operator << (ostream & out, const CDataType & type) {
        type.print(out);
        return out;
    }
    virtual shared_ptr<CDataType> clone() const {
        return nullptr;
    }
protected:
    CDataType(size_t size, string typeName) : size(size), typeName(std::move(typeName)) {}
    size_t size;
    string typeName;
    virtual void print(ostream& os) const {
        os << typeName;
    }
    virtual bool isTypeEqual(const CDataType & other) const {
        return this->typeName == other.typeName;
    }

};

class CDataTypeInt : public CDataType
{
public:
    CDataTypeInt() : CDataType(4, "int") {}

    shared_ptr<CDataType> clone() const override {
        auto res = make_shared<CDataTypeInt>();
        *res = *this;
        return res;
    }
};

class CDataTypeDouble : public CDataType
{
public:
    CDataTypeDouble() : CDataType(8, "double") {}
    shared_ptr<CDataType> clone() const override {
        auto res = make_shared<CDataTypeDouble>();
        *res = *this;
        return res;
    }
};
class CDataTypeEnum : public CDataType
{
public:
    CDataTypeEnum() : CDataType(4, "enum") {}

    CDataTypeEnum add(const string & val) {
        if (find(values.begin(), values.end(), val) != values.end()) {
            throw invalid_argument("Duplicate enum value: " + val);
        }
        values.push_back(val);
        return *this;
    }
    shared_ptr<CDataType> clone() const override {
        auto res = make_shared<CDataTypeEnum>();
        *res = *this;
        return res;
    }

private:
    vector<string> values;
    bool isTypeEqual(const CDataType & other_raw) const override {
        if (typeid(*this) == typeid(other_raw)) {
            const CDataTypeEnum& other = static_cast<const CDataTypeEnum&>(other_raw);
            size_t sz = values.size();
            if (sz != other.values.size()) return false;
            for (size_t t = 0; t < sz; t++) {
                if (values[t] != other.values[t])
                    return false;
            }
            return true;
        }
        return false;
    }
    void print(ostream & os) const override {
        os << typeName << " { ";
        auto it = values.begin();
        while (it != values.end()) {
            os << *it;
            it++;
            if (it != values.end()) os << ", ";
        }
        os << "\n} ";
    }

};
class CDataTypeStruct : public CDataType
{
public:
    typedef pair<string, shared_ptr<CDataType>> variable;
    CDataTypeStruct() : CDataType(0, "struct") {}

    CDataTypeStruct addField(const string & name, const CDataType & t) {
        for (const auto& m : members) {
            if (m.first == name)
                throw invalid_argument("Duplicate field: " + name);
        }
//        CDataType * t_ptr = t.clone();
        variable v = {name, t.clone()};
        members.push_back(v);
        size += v.second->getSize();
        return *this;
    }

    const CDataType& field(const string & name) const {
        for (const auto& m : members) {
            if (m.first == name) {
                return *m.second;
            }
        }
        throw invalid_argument("Unknown field: " + name);
    }

    void print(ostream& os) const override {
        os << typeName << " {\n";
        for (const auto& a : members) {
            os << *a.second << " " << a.first << ";\n";
        }
        os << "\n}";
    }
private:
    vector<variable> members;
    bool isTypeEqual(const CDataType & other) const override {
        if (typeid(*this) == typeid(other)) {
            const auto& second = static_cast<const CDataTypeStruct&>(other);
            if (members.size() != second.members.size()) return false;
            for (size_t t = 0; t < members.size(); t++) {
                if (*(members[t].second) != *(second.members[t].second)) return false;
            }
            return true;
        }
        return false;
    }
//    shared_ptr<CDataType> getSharedPtr(const CDataType& t) {
//        if (t.typeName == "int")
//    }
};
#ifndef __PROGTEST__
static inline std::string &stripstr(std::string &s) {
    s.erase(std::remove_if( s.begin(), s.end(),
                            [](char c){ return (c =='\r' || c =='\t' || c == ' ' || c == '\n');}), s.end() );
    return s;
}
static bool        whitespaceMatch                         ( const string    & a,
                                                             const string    & b )
{
    string first = a, second = b;

    stripstr(first);
    stripstr(second);
    return first == second;
}
template <typename T_>
static bool        whitespaceMatch                         ( const T_        & x,
                                                             const string    & ref )
{
    ostringstream oss;
    oss << x;
    return whitespaceMatch ( oss . str (), ref );
}
int main ( void )
{
    const char * dead = "DEAD";
    const char * status = "m_Status";
    CDataTypeInt test = CDataTypeInt();
    CDataTypeStruct  a = CDataTypeStruct () .
            addField ( "m_Length", CDataTypeInt () ) .
            addField ( status, CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( dead ) ).
            addField ( "m_Ratio", CDataTypeDouble () );
    if (a == test);

    CDataTypeStruct b = CDataTypeStruct () .
            addField ( "m_Length", CDataTypeInt () ) .
            addField ( "m_Status", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "READY" ) ).
            addField ( "m_Ratio", CDataTypeDouble () );

    CDataTypeStruct c =  CDataTypeStruct () .
            addField ( "m_First", CDataTypeInt () ) .
            addField ( "m_Second", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "DEAD" ) ).
            addField ( "m_Third", CDataTypeDouble () );

    CDataTypeStruct  d = CDataTypeStruct () .
            addField ( "m_Length", CDataTypeInt () ) .
            addField ( "m_Status", CDataTypeEnum () .
            add ( "NEW" ) .
            add ( "FIXED" ) .
            add ( "BROKEN" ) .
            add ( "DEAD" ) ).
            addField ( "m_Ratio", CDataTypeInt () );
    assert ( whitespaceMatch ( a, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "}") );

    assert ( whitespaceMatch ( b, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    READY\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "}") );

    assert ( whitespaceMatch ( c, "struct\n"
                                  "{\n"
                                  "  int m_First;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Second;\n"
                                  "  double m_Third;\n"
                                  "}") );

    assert ( whitespaceMatch ( d, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  int m_Ratio;\n"
                                  "}") );

    assert ( a != b );
    assert ( a == c );
    assert ( a != d );
    assert ( a . field ( "m_Status" ) == CDataTypeEnum () . add ( "NEW" ) . add ( "FIXED" ) . add ( "BROKEN" ) . add ( "DEAD" ) );
    assert ( a . field ( "m_Status" ) != CDataTypeEnum () . add ( "NEW" ) . add ( "BROKEN" ) . add ( "FIXED" ) . add ( "DEAD" ) );
    assert ( a != CDataTypeInt() );
    assert ( whitespaceMatch ( a . field ( "m_Status" ), "enum\n"
                                                         "{\n"
                                                         "  NEW,\n"
                                                         "  FIXED,\n"
                                                         "  BROKEN,\n"
                                                         "  DEAD\n"
                                                         "}") );

    CDataTypeStruct aOld = a;
    b . addField ( "m_Other", CDataTypeDouble ());

    a . addField ( "m_Sum", CDataTypeInt ());

    assert ( a != aOld );
    assert ( a != c );
    assert ( aOld == c );
    assert ( whitespaceMatch ( a, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "  int m_Sum;\n"
                                  "}") );

    assert ( whitespaceMatch ( b, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    READY\n"
                                  "  } m_Status;\n"
                                  "  double m_Ratio;\n"
                                  "  double m_Other;\n"
                                  "}") );

    c . addField ( "m_Another", a . field ( status ));

    assert ( whitespaceMatch ( c, "struct\n"
                                  "{\n"
                                  "  int m_First;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Second;\n"
                                  "  double m_Third;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Another;\n"
                                  "}") );

    d . addField ( "m_Another", a . field ( "m_Ratio" ));

    assert ( whitespaceMatch ( d, "struct\n"
                                  "{\n"
                                  "  int m_Length;\n"
                                  "  enum\n"
                                  "  {\n"
                                  "    NEW,\n"
                                  "    FIXED,\n"
                                  "    BROKEN,\n"
                                  "    DEAD\n"
                                  "  } m_Status;\n"
                                  "  int m_Ratio;\n"
                                  "  double m_Another;\n"
                                  "}") );

    assert ( a . getSize () == 20 );
    assert ( b . getSize () == 24 );
    try
    {
        a . addField ( "m_Status", CDataTypeInt () );
        assert ( "addField: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        assert ( e . what () == "Duplicate field: m_Status"sv );
    }

    try
    {
        cout << a . field ( "m_Fail" ) << endl;
        assert ( "field: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        assert ( e . what () == "Unknown field: m_Fail"sv );
    }
    const char * first = "FIRST";

    try
    {
        CDataTypeEnum en;
        en . add ( first ) .
                add ( "SECOND" ) .
                add ( "FIRST" );
        assert ( "add: missing exception!" == nullptr );
    }
    catch ( const invalid_argument & e )
    {
        assert ( e . what () == "Duplicate enum value: FIRST"sv );
    }

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
