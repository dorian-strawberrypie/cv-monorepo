#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */


class CVATRegister
{
public:

    CVATRegister   (  ) = default;
    ~CVATRegister  (  ) {
        for (auto & i : _data)
            delete i;

        for (auto & i : _invoices)
            delete i;
    };
    bool          newCompany     ( const string    & name,
                                   const string    & addr,
                                   const string    & taxID ) {
        // lower_bound search _data
        // return false if same nameaddr/id
        // insert to lb
        // update indexer
        auto c = new Company(name, addr, taxID);

        if (_hashId.empty()) {
            _hashId.push_back(c);
            _hashNm.push_back(c);
            _data.push_back(c);
            return true;
        }

        auto n_pos = std::lower_bound(_hashNm.begin(), _hashNm.end(), c,
                                      [](Company* left, Company* right){ return left->full_name < right->full_name; });


        auto id_pos = std::lower_bound(_hashId.begin(), _hashId.end(), c,
                                       [](Company* left, Company* right){ return left->id < right->id; });

        if ((n_pos != _hashNm.end() && (*n_pos)->full_name == c->full_name)
                || (id_pos != _hashId.end() && (*id_pos)->id == c->id)) {
            delete c;
            return false;
        }

        _hashNm.insert(n_pos, c);
        _hashId.insert(id_pos, c);
        _data.push_back(c);

        return true;
    }
    bool          cancelCompany  ( const string    & name,
                                   const string    & addr ) {
        Company c(name, addr, "");
        auto iter1 = lower_bound(_hashNm.begin(), _hashNm.end(), &c, [](Company* left, Company* right){ return left->full_name < right->full_name; });
        if (iter1 == _hashNm.end() || (*iter1)->full_name != c.full_name) return false;
        c.id = (*iter1)->id;
        auto iter2 = lower_bound(_hashId.begin(), _hashId.end(), &c, [](Company* left, Company* right){ return left->id < right->id; });
        _hashNm.erase(iter1);
        _hashId.erase(iter2);
        return true;

    }
    bool          cancelCompany  ( const string    & taxID ) {
        Company c("", "", taxID);
        auto iter1 = lower_bound(_hashId.begin(), _hashId.end(), &c, [](Company* left, Company* right){ return left->id < right->id; });
        if (iter1 == _hashId.end() || (*iter1)->id != c.id) return false;
        c.full_name = (*iter1)->full_name;
        auto iter2 = lower_bound(_hashNm.begin(), _hashNm.end(), &c, [](Company* left, Company* right){ return left->full_name < right->full_name; });
        _hashId.erase(iter1);
        _hashNm.erase(iter2);
        return true;
    }
    bool          invoice        ( const string    & taxID,
                                   unsigned int      amount ) {
        Company c("", "", taxID);
        auto iter = lower_bound(_hashId.begin(), _hashId.end(), &c, [](Company* left, Company* right){ return left->id < right->id; });
        if (iter == _hashId.end() || (*iter)->id != taxID) return false;
        addInvoice(amount, iter);
        updateMedian();
        return true;
    }


    bool          invoice        ( const string    & name,
                                   const string    & addr,
                                   unsigned int      amount ) {
        Company c(name, addr, "");
        auto iter = lower_bound(_hashNm.begin(), _hashNm.end(), &c, [](Company* left, Company* right){ return left->full_name < right->full_name; });
        if (iter == _hashNm.end() || (*iter)->full_name != c.full_name) return false;
        addInvoice(amount, iter);
        updateMedian();
        return true;
    }
    bool          audit          ( const string    & name,
                                   const string    & addr,
                                   unsigned int    & sumIncome ) const {
        Company c(name, addr, "");
        sumIncome = 0;
        auto iter = lower_bound(_hashNm.begin(), _hashNm.end(), &c, [](Company* left, Company* right){ return left->full_name < right->full_name; });
        if (iter == _hashNm.end() || (*iter)->full_name != c.full_name) return false;
        for (auto i : (*iter)->invoices)
            sumIncome += *i;
        return true;
    }
    bool          audit          ( const string    & taxID,
                                   unsigned int    & sumIncome ) const {
        Company c("", "", taxID);
        sumIncome = 0;
        auto iter = lower_bound(_hashId.begin(), _hashId.end(), &c, [](Company* left, Company* right){ return left->id < right->id; });
        if (iter == _hashId.end() || (*iter)->id != taxID) return false;
        for (auto i : (*iter)->invoices)
            sumIncome += *i;
        return true;
    }
    bool          firstCompany   ( string          & name,
                                   string          & addr ) const {
        if (_hashNm.empty()) return false;
        name = _hashNm[0]->name;
        addr = _hashNm[0]->addr;
        return true;
    }
    bool          nextCompany    ( string          & name,
                                   string          & addr ) const {
        Company c(name, addr, "");
        auto iter = lower_bound(_hashNm.begin(), _hashNm.end(), &c, [](Company* left, Company* right){ return left->full_name < right->full_name; });
        if (iter == _hashNm.end() || ++iter == _hashNm.end()) return false;
        name = (*iter)->name;
        addr = (*iter)->addr;
        return true;
    }
    unsigned int  medianInvoice  ( void ) const {
        return median;
    }

private:
    class Company {
    public:
        string name;
        string addr;
        string id;

//        string full_name;
        pair<string, string> full_name;

        Company(string n, string a, string i) {
            name = n; addr = a; id = i;
            string tmpN = name, tmpA = addr;
            std::transform(tmpN.begin(), tmpN.end(), tmpN.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            std::transform(tmpA.begin(), tmpA.end(), tmpA.begin(),
                           [](unsigned char c){ return std::tolower(c); });
            full_name.first = tmpN; full_name.second = tmpA;

        }
        vector<unsigned int *> invoices;

    };
    unsigned int median = 0;
    void updateMedian() {
        unsigned int n = _invoices.size() / 2;
        median = *_invoices[n];
    }

    void addInvoice(unsigned int amount, const vector<Company *>::iterator &iter) {
        auto a = new unsigned int(amount);
        auto invoicePos = lower_bound(_invoices.begin(), _invoices.end(), a, [](const unsigned int* left, const unsigned int* right){ return *left < *right; });
        _invoices.insert(invoicePos, a);
        (*iter)->invoices.push_back(a);
    }

    vector<unsigned int *> _invoices;
    vector<Company *> _hashId;
    vector<Company *> _hashNm;
    vector<Company *> _data;

};

#ifndef __PROGTEST__
int               main           ( void )
{
      string name, addr;
  unsigned int sumIncome;

  CVATRegister b1;
  assert ( b1 . newCompany ( "ACME", "Thakurova", "666/666" ) );
  assert ( b1 . newCompany ( "ACME", "Kolejni", "666/666/666" ) );
  assert ( b1 . newCompany ( "Dummy", "Thakurova", "123456" ) );
  assert ( b1 . invoice ( "666/666", 2000 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "666/666/666", 3000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 4000 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "aCmE", "Kolejni", 5000 ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . audit ( "ACME", "Kolejni", sumIncome ) && sumIncome == 8000 );
  assert ( b1 . audit ( "123456", sumIncome ) && sumIncome == 4000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "ACME" && addr == "Kolejni" );
  assert ( b1 . nextCompany ( name, addr ) && name == "ACME" && addr == "Thakurova" );
  assert ( b1 . nextCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "ACME", "KoLeJnI" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . cancelCompany ( "666/666" ) );
  assert ( b1 . medianInvoice () == 4000 );
  assert ( b1 . invoice ( "123456", 100 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 300 ) );
  assert ( b1 . medianInvoice () == 3000 );
  assert ( b1 . invoice ( "123456", 200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 230 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 830 ) );
  assert ( b1 . medianInvoice () == 830 );
  assert ( b1 . invoice ( "123456", 1830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 1830 );
  assert ( b1 . invoice ( "123456", 2830 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . invoice ( "123456", 3200 ) );
  assert ( b1 . medianInvoice () == 2000 );
  assert ( b1 . firstCompany ( name, addr ) && name == "Dummy" && addr == "Thakurova" );
  assert ( ! b1 . nextCompany ( name, addr ) );
  assert ( b1 . cancelCompany ( "123456" ) );
  assert ( ! b1 . firstCompany ( name, addr ) );

  CVATRegister b2;
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . newCompany ( "Dummy", "Kolejni", "123456" ) );
  assert ( ! b2 . newCompany ( "AcMe", "kOlEjNi", "1234" ) );
  assert ( b2 . newCompany ( "Dummy", "Thakurova", "ABCDEF" ) );
  assert ( b2 . medianInvoice () == 0 );
  assert ( b2 . invoice ( "ABCDEF", 1000 ) );
  assert ( b2 . medianInvoice () == 1000 );
  assert ( b2 . invoice ( "abcdef", 2000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( b2 . invoice ( "aCMe", "kOlEjNi", 3000 ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . invoice ( "1234567", 100 ) );
  assert ( ! b2 . invoice ( "ACE", "Kolejni", 100 ) );
  assert ( ! b2 . invoice ( "ACME", "Thakurova", 100 ) );
  assert ( ! b2 . audit ( "1234567", sumIncome ) );
  assert ( ! b2 . audit ( "ACE", "Kolejni", sumIncome ) );
  assert ( ! b2 . audit ( "ACME", "Thakurova", sumIncome ) );
  assert ( ! b2 . cancelCompany ( "1234567" ) );
  assert ( ! b2 . cancelCompany ( "ACE", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Thakurova" ) );
  assert ( b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . medianInvoice () == 2000 );
  assert ( ! b2 . cancelCompany ( "abcdef" ) );
  assert ( b2 . newCompany ( "ACME", "Kolejni", "abcdef" ) );
  assert ( b2 . cancelCompany ( "ACME", "Kolejni" ) );
  assert ( ! b2 . cancelCompany ( "ACME", "Kolejni" ) );

    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
