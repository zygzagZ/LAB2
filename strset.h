#ifndef __STRSET_H__
#define __STRSET_H__
#ifdef __cplusplus
#include <cstring>
#include <set>
#include <unordered_map>
struct set_comp {
    bool operator() (const char *a, const char *b) const {
        return strcmp(a, b) < 0;
    }
};
using strset_set = std::set<const char*, set_comp>;
using strset_map = std::unordered_map<unsigned long, strset_set>;
#include <cstddef>
#include <iostream>
namespace jnp1 {
extern "C" {
#else
#include <stddef.h>
#endif
    unsigned long strset_new();

          /*Tworzy nowy zbiór i zwraca jego identyfikator.*/

    void strset_delete(unsigned long id);

          /*Jeżeli istnieje zbiór o identyfikatorze id, usuwa go, a w przeciwnym
          przypadku nie robi nic.*/

    size_t strset_size(unsigned long id);

          /*Jeżeli istnieje zbiór o identyfikatorze id, zwraca liczbę jego elementów,
          a w przeciwnym przypadku zwraca 0.*/

    void strset_insert(unsigned long id, const char* value);

          /*Jeżeli istnieje zbiór o identyfikatorze id i element value nie należy do
          tego zbioru, to dodaje element do zbioru, a w przeciwnym przypadku nie
          robi nic.*/

    void strset_remove(unsigned long id, const char* value);

          /*Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
          zbioru, to usuwa element ze zbioru, a w przeciwnym przypadku nie robi nic.*/

    int strset_test(unsigned long id, const char* value);

          /*Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
          zbioru, to zwraca 1, a w przeciwnym przypadku 0.*/

    void strset_clear(unsigned long id);

          /*Jeżeli istnieje zbiór o identyfikatorze id, usuwa wszystkie jego elementy,
          a w przeciwnym przypadku nie robi nic.*/

    int strset_comp(unsigned long id1, unsigned long id2);

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
#ifdef __cplusplus
}
}
#endif
#endif /*__STRSET_H__*/