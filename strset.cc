#include "strsetconst.h"
#include "strset.h"
#include <cassert>
#include <string>
#include <set>
#include <unordered_map>

namespace {
    #ifndef NDEBUG
        const bool debug = true;
    #else
        const bool debug = false;
    #endif
    
    using strset_map = std::unordered_map<unsigned long, std::set<std::string>>;
    
    strset_map& zbior() {
        static strset_map* zbior = new strset_map();
        return *zbior;
    }
    
    unsigned long lastId = 0;
}

namespace jnp1 {
    /*Tworzy nowy zbiór i zwraca jego identyfikator.*/
    unsigned long strset_new() {
        if(debug) {
            std::cerr << "strset_new -> " << lastId << std::endl;
        }
        zbior().emplace(lastId, strset_set());
        return lastId++;
    }

    /*Jeżeli istnieje zbiór o identyfikatorze id, usuwa go, a w przeciwnym
    przypadku nie robi nic.*/
    void strset_delete(unsigned long id) {
        if (id == strset42()) {
            if(debug) {
                std::cerr << "strset_delete " << id << " is const" << std::endl;
            }
            return;
        }

        auto it = zbior().find(id);
        if (it == zbior().end()) {
            if(debug) {
                std::cerr << "strset_delete " << id << " doesn't exist" << std::endl;
            }
            return;
        }

        if(debug) {
            std::cerr << "strset_delete " << id << std::endl;
        }

        zbior().erase(it);

        if(debug) {
            std::cerr << "strset_delete " << id << " success" << std::endl;
        }
    }


    /*Jeżeli istnieje zbiór o identyfikatorze id, zwraca liczbę jego elementów,
    a w przeciwnym przypadku zwraca 0.*/
    size_t strset_size(unsigned long id) {
        auto it = zbior().find(id);
        auto ret = it != zbior().end() ? it->second.size() : 0;

        if(debug) {
            std::cerr << "strset_size " << id << " -> " << ret << std::endl;
        }

        return ret;
    }



    /*Jeżeli istnieje zbiór o identyfikatorze id i element value nie należy do
    tego zbioru, to dodaje element do zbioru, a w przeciwnym przypadku nie
    robi nic.*/
    void strset_insert(unsigned long id, const char* value) {
        if(value == nullptr) {
            if(debug) {
                std::cerr << "strset_insert " << id 
                << " invalid value (NULL)" << std::endl;
            }
            return;
        }

        std::string strvalue = std::string(value);

        if ((strset_size(id) || (strvalue != "42")) && id == strset42()) {
            if(debug) {
                std::cerr << "strset_insert " << id << " is const" << std::endl;
            }
            return;
        }

        auto it = zbior().find(id);
        if (it == zbior().end()) {
            if(debug) {
                std::cerr << "strset_insert " << id << " doesn't exist" << std::endl;
            }
            return;
        }

        auto sit = it->second.find(strvalue);
        if (sit != it->second.end()) {
            if(debug) {
                std::cerr << "strset_insert " << id 
                << " has value " << value << std::endl;
            }
            return;
        }

        if(debug) {
            std::cerr << "strset_insert " << id 
            << " inserted " << value << std::endl;
        }

        it->second.insert(strvalue);
    }


    /*Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
    zbioru, to usuwa element ze zbioru, a w przeciwnym przypadku nie robi nic.*/
    void strset_remove(unsigned long id, const char* value) {
        if(value == nullptr) {
            if(debug) {
                std::cerr << "strset_remove " << id 
                << " invalid value (NULL)" << std::endl;
            }
            return;
        }

        std::string strvalue = std::string(value);

        if (id == strset42()) {
            if(debug) {
                std::cerr << "strset_remove " << id << " is const" << std::endl;
            }

            return;
        }

        auto it = zbior().find(id);
        if (it == zbior().end()) {
            if(debug) {
                std::cerr << "strset_remove " << id << " doesn't exist" << std::endl;
            }
            return;
        }

        auto sit = it->second.find(strvalue);
        if (sit == it->second.end()) {
            if(debug) {
                std::cerr << "strset_remove " << id 
                << " doesn't have value " << value << std::endl;
            }
            return;
        }

        if(debug) {
            std::cerr << "strset_remove " << id 
            << " removed " << value << std::endl;
        }

        it->second.erase(sit);
    }


    /*Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
    zbioru, to zwraca 1, a w przeciwnym przypadku 0.*/
    int strset_test(unsigned long id, const char* value) {
        if(value == nullptr) {
            return 0;
        }

        std::string strvalue = std::string(value);

        auto it = zbior().find(id);
        if (it == zbior().end()) {
            if(debug) {
                std::cerr << "strset_test " << id << " doesn't exist" << std::endl;
            }
            return 0;
        }

        auto sit = it->second.find(strvalue);
        auto ret = sit != it->second.end();

        if(debug) {
            std::cerr << "strset_test " << id << " -> " << ret << std::endl;
        }

        return ret;
    }


    /*Jeżeli istnieje zbiór o identyfikatorze id, usuwa wszystkie jego elementy,
    a w przeciwnym przypadku nie robi nic.*/
    void strset_clear(unsigned long id) {
        if (id == strset42()) {
            if(debug) {
                std::cerr << "strset_clear " << id << " is const" << std::endl;
            }
            return;
        }

        auto it = zbior().find(id);
        if (it == zbior().end()) {
            if(debug) {
                std::cerr << "strset_clear " << id << " doesn't exist" << std::endl;
            }
            return;
        }

        if(debug) {
            std::cerr << "strset_clear " << id << std::endl;
        }

        it->second.clear();

        if(debug) {
            std::cerr << "strset_clear " << id << " success" << std::endl;
        }
    }

    /*Porównuje zbiory o identyfikatorach id1 i id2. Niech sorted(id) oznacza
    posortowany leksykograficznie zbiór o identyfikatorze id. Takie ciągi już
    porównujemy naturalnie: pierwsze miejsce, na którym się różnią, decyduje
    o relacji większości. Jeśli jeden ciąg jest prefiksem drugiego, to ten
    będący prefiks jest mniejszy. Funkcja strset_comp(id1, id2) powinna zwrócić
    -1, gdy sorted(id1) < sorted(id2),
    0, gdy sorted(id1) = sorted(id2),
    1, gdy sorted(id1) > sorted(id2).
    Jeżeli zbiór o którymś z identyfikatorów nie istnieje, to jest traktowany
    jako równy zbiorowi pustemu.*/
    int strset_comp(unsigned long id1, unsigned long id2) {
        size_t size1 = strset_size(id1), 
        size2 = strset_size(id2);
        if (!size1 || !size2) {
            auto ret = size1 ? 1 : size2 ? -1 : 0;
            if(debug) {
                std::cerr << "strset_comp " << id1 << " " << id2 
                << " at least one set is empty -> " << ret << std::endl;
            }
            return ret;
        }

        auto it1 = zbior().find(id1), it2 = zbior().find(id2);
        auto el1 = it1->second.begin(), el2 = it2->second.begin();

        if(debug) {
            std::cerr << "strset_comp " << id1 << " " << id2 << std::endl;
            std::cerr  << "set1: ";
            for (auto i : it1->second) {
                std::cerr << i << ", ";
            }
            std::cerr << std::endl << "set2: ";
            for (auto i : it2->second) {
                std::cerr << i << ", ";
            }
            std::cerr << std::endl;
        }

        while (el1 != it1->second.end() && el2 != it2->second.end()) {
            int cmp = (*el1).compare(*el2);
            if (cmp) {
                if(debug) {
                    std::cerr << "strset_comp " << id1 << " " << id2 << " completed on " << *el1 << " / " << *el2 << " -> " << cmp << std::endl;
                }
                return cmp < 0 ? -1 : cmp ? 1 : 0;
            }
            el1++;
            el2++;
        }

        auto ret = el1 != it1->second.end() ? 1 : el2 != it2->second.end() ? -1 : 0;
        if(debug) {
            std::cerr << "strset_comp " << id1 << " " << id2 << " -> " << ret << std::endl;
        }
        return ret;
    }
}
