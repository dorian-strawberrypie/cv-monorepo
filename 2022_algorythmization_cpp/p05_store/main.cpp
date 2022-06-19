#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <stack>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

class CDate {
public:
    CDate ( int y, int m, int d ) {
        _y = y; _m = m; _d = d;
    }
    bool operator < (const CDate& second) const {
        if (_y < second._y) return true;
        if (_y == second._y && _m < second._m) return true;
        if (_y == second._y && _m == second._m && _d < second._d) return true;
        return false;
    }
private:
    int _y, _m, _d;
};
class CSupermarket
{
public:
    struct item {
        int count;
        CDate exp;
    };
    typedef vector<item> batches_t;

    CSupermarket() = default;

    CSupermarket & store (const string& name, const CDate& expiryDate, int count ) {
        item newItem = {count, expiryDate};

        // create key "name" if not exists,
        // push newItem into value (priority_queue)
        storage[name].push_back(newItem);
        return *this;
    }

    void sell (list<pair<string,int>> & shoppingList ) {

        // if item exits, put into list for later removal
        list<FoundShoppingItem> found_items;
        decideItemsExist(shoppingList, found_items);

        // subtract items in storage and sh.list & remove item if shopping list blank
        releaseItems(found_items);

        // remove elements with count == 0
        cleanStorage();
        cleanList(shoppingList);
    }


    list<pair<string,int>> expired (const CDate & date ) const {
        vector<pair<string,int>> expiredItems;
        findExpiredItems(date, expiredItems);

        // sort by count descending
        sort(expiredItems.begin(), expiredItems.end(), [](const pair<string,int>& a, const pair<string,int>& b)->bool{return a.second > b.second;});

        list<pair<string,int>> result(expiredItems.begin(), expiredItems.end()); // convert vector to list
        return result;
    }
private:
    // map of key and batches - vector of item(count, expiration)
    map<string, batches_t> storage;

    struct FoundShoppingItem {
        string name; int countRequired; pair<string,int>& placeInList;
    };

    // returns iterator to found item, or .end() if not found or ambiguous
    map<string, batches_t>::iterator findAlike(const string & searched) {
        bool found = false;
        auto it = storage.end();

        // iterating through storage MAP
        for (auto& mp : storage) {
            string key = mp.first;
            int mismatches = 0;
            if (key.length() != searched.length()) continue;

            // iterating through key STRING
            // count different string chars
            for (size_t i = 0; i < searched.length(); i++){
                if (searched[i] != key[i]) mismatches++;
                if (mismatches > 1) continue;
            }
            // if mismatch in one char => equal
            if (mismatches == 1) {
                if (found) return storage.end(); // if more equal found => ambiguous
                found = true;
                it = storage.find(key);
            }
        }
        return it;
    }

    // output parameter - vector of expired items
    void findExpiredItems(const CDate& queriedDate, vector<pair<std::string, int>> & expired) const {
        for (const auto& storageItem : storage) {
            int count = 0;
            // each storageItem made of batches
            for (const auto& itemBatch : storageItem.second) {
                if (itemBatch.exp < queriedDate)
                    count += itemBatch.count;
            }
            if (count > 0)
                expired.emplace_back(pair<string,int>(storageItem.first, count));
        }
    }

    // iterate through shopping list to remove fulfilled request
    void cleanList(list<pair<string, int>> &shoppingList) const {
        auto iter = shoppingList.begin();
        while (iter != shoppingList.end()) {
            if (iter->second == 0)
                iter = shoppingList.erase(iter);
            else iter++;
        }
    }

    // iterate through storage to remove empty items
    void cleanStorage() {
        auto iter = storage.begin();
        while (iter != storage.end()) {
            if (iter->second.empty())
                iter = storage.erase(iter);
            else iter++;
        }
    }

    // output parameters shoppingList, foundItems (storage U shoppingList)
    void decideItemsExist(list<pair<string, int>> &shoppingList, list<FoundShoppingItem> &foundItems) {
        for (auto& shoppingListItem : shoppingList) {
            string searched = shoppingListItem.first;

            // try finding with key
            auto it = storage.find(searched);

            // if not found, try finding similar item
            if (it == storage.end())
                it = findAlike(searched);

            // reserve found items for each sh.list item in storage
            if (it != storage.end()) {
                FoundShoppingItem foundItem = {it->first, shoppingListItem.second, shoppingListItem };
                foundItems.push_back(foundItem);
            }
        }
    }

    // returns count of unfulfilled request
    int subtractFromStorage(int demand, vector<item>& place) {
        // put earliest expiration to place.back()
        sort(place.begin(), place.end(), [](const item& a, const item& b) -> bool {
            return (b.exp < a.exp);
        });

        // subtract storage batches (items in vector) until demand is 0
        while (demand > 0 && !place.empty()) {
            int availableInBatch = place.back().count;
            place.back().count -= demand;
            demand -= availableInBatch;
            // if batch empty, remove batch
            if (place.back().count <= 0)
                place.pop_back();
        }

        return demand < 0 ? 0 : demand;
    }

    // execute handing the items over
    void releaseItems(list<FoundShoppingItem> & list) {
        auto iter = list.begin();
        // go through modified shopping list of found items
        while (iter != list.end()) {
            // release items in STORAGE and erase empty
            auto & placeInStorage = storage[iter->name];
            int unfulfilled = subtractFromStorage(iter->countRequired, placeInStorage);

            // release items in SHOPPING LIST and erase empty
            iter->placeInList.second = unfulfilled;
            iter++;
        }
    }
};

void basic_asserts();

#ifndef __PROGTEST__
int main ( void )
{

    for (int i = 0; i < 10000; i++)
        basic_asserts();

    return EXIT_SUCCESS;
}

void basic_asserts() {
    CSupermarket s;
    s . store ( "bread", CDate ( 2016, 4, 30 ), 100 )
            . store ( "butter", CDate ( 2016, 5, 10 ), 10 )
            . store ( "beer", CDate ( 2016, 8, 10 ), 50 )
            . store ( "bread", CDate ( 2016, 4, 25 ), 100 )
            . store ( "okey", CDate ( 2016, 7, 18 ), 5 );

    list<pair<string,int> > l0 = s . expired ( CDate ( 2018, 4, 30 ) );
    assert (l0.size() == 4);
    assert ((l0 == list<pair<string, int> >{{"bread",  200},
                                            {"beer",   50},
                                            {"butter", 10},
                                            {"okey",   5}}));

    list<pair<string,int> > l1 { { "bread", 2 }, { "Coke", 5 }, { "butter", 20 } };
    s . sell ( l1 );
    assert (l1.size() == 2);
    assert ((l1 == list<pair<string, int> >{{"Coke",   5},
                                            {"butter", 10}}));

    list<pair<string,int> > l2 = s . expired ( CDate ( 2016, 4, 30 ) );
    assert (l2.size() == 1);
    assert ((l2 == list<pair<string, int> >{{"bread", 98}}));

    list<pair<string,int> > l3 = s . expired ( CDate ( 2016, 5, 20 ) );
    assert (l3.size() == 1);
    assert ((l3 == list<pair<string, int> >{{"bread", 198}}));

    list<pair<string,int> > l4 { { "bread", 105 } };
    s . sell ( l4 );
    assert (l4.size() == 0);
    assert ((l4 == list<pair<string, int> >{}));

    list<pair<string,int> > l5 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert (l5.size() == 3);
    assert ((l5 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"okey",  5}}));

    s . store ( "Coke", CDate ( 2016, 12, 31 ), 10 );

    list<pair<string,int> > l6 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 }, { "Cokes", 1 } };
    s . sell ( l6 );
    assert (l6.size() == 3);
    assert ((l6 == list<pair<string, int> >{{"cake",  1},
                                            {"cuke",  1},
                                            {"Cokes", 1}}));

    list<pair<string,int> > l7 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert (l7.size() == 4);
    assert ((l7 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  7},
                                            {"okey",  5}}));

    s . store ( "cake", CDate ( 2016, 11, 1 ), 5 );

    list<pair<string,int> > l8 { { "Cake", 1 }, { "Coke", 1 }, { "cake", 1 }, { "coke", 1 }, { "cuke", 1 } };
    s . sell ( l8 );
    assert (l8.size() == 2);
    assert ((l8 == list<pair<string, int> >{{"Cake", 1},
                                            {"coke", 1}}));

    list<pair<string,int> > l9 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert (l9.size() == 5);
    assert ((l9 == list<pair<string, int> >{{"bread", 93},
                                            {"beer",  50},
                                            {"Coke",  6},
                                            {"okey",  5},
                                            {"cake",  3}}));

    list<pair<string,int> > l10 { { "cake", 15 }, { "Cake", 2 } };
    s . sell ( l10 );
    assert (l10.size() == 2);
    assert ((l10 == list<pair<string, int> >{{"cake", 12},
                                             {"Cake", 2}}));

    list<pair<string,int> > l11 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert (l11.size() == 4);
    assert ((l11 == list<pair<string, int> >{{"bread", 93},
                                             {"beer",  50},
                                             {"Coke",  6},
                                             {"okey",  5}}));

    list<pair<string,int> > l12 { { "Cake", 4 } };
    s . sell ( l12 );
    assert (l12.size() == 0);
    assert ((l12 == list<pair<string, int> >{}));

    list<pair<string,int> > l13 = s . expired ( CDate ( 2017, 1, 1 ) );
    assert (l13.size() == 4);
    assert ((l13 == list<pair<string, int> >{{"bread", 93},
                                             {"beer",  50},
                                             {"okey",  5},
                                             {"Coke",  2}}));

    list<pair<string,int> > l14 { { "Beer", 20 }, { "Coke", 1 }, { "bear", 25 }, { "beer", 10 } };
    s . sell ( l14 );
    assert (l14.size() == 1);
    assert ((l14 == list<pair<string, int> >{{"beer", 5}}));

    s . store ( "ccccb", CDate ( 2019, 3, 11 ), 100 )
            . store ( "ccccd", CDate ( 2019, 6, 9 ), 100 )
            . store ( "dcccc", CDate ( 2019, 2, 14 ), 100 );

    list<pair<string,int> > l15 { { "ccccc", 10 } };
    s . sell ( l15 );
    assert (l15.size() == 1);
    assert ((l15 == list<pair<string, int> >{{"ccccc", 10}}));
}

#endif /* __PROGTEST__ */
