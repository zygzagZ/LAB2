#include <set>
#include <unordered_map>
#include <cstring>
#include "strsetconst.h"
#include "strset.h"
#include <cassert>

#ifdef __cplusplus
namespace jnp1 {
#endif

struct set_comp {
    bool operator() (const char *a, const char *b) const {
        return strcmp(a, b) < 0;
    }
};
using strset_set = std::set<const char*, set_comp>;
using strset_map = std::unordered_map<unsigned long, strset_set>;
unsigned long lastId = 0;
/*Tworzy nowy zbiór i zwraca jego identyfikator.*/
unsigned long strset_new() {
	std::cerr << "strset_new -> " << lastId << std::endl;
	zbior.emplace(lastId, strset_set());
	return lastId++;
}

/*Jeżeli istnieje zbiór o identyfikatorze id, usuwa go, a w przeciwnym
przypadku nie robi nic.*/
void strset_delete(unsigned long id) {
	if (id == strset42()) {
		std::cerr << "strset_delete " << id << " is const" << std::endl;
		return;
	}

	auto it = zbior.find(id);
	if (it == zbior.end()) {
		std::cerr << "strset_delete " << id << " doesn't exist" << std::endl;
		return;
	}
	std::cerr << "strset_delete " << id << std::endl;

	for (auto el : it->second)
		free((void*)el);

	zbior.erase(it);
	std::cerr << "strset_delete " << id << " success" << std::endl;
}


/*Jeżeli istnieje zbiór o identyfikatorze id, zwraca liczbę jego elementów,
a w przeciwnym przypadku zwraca 0.*/
size_t strset_size(unsigned long id) {
	auto it = zbior.find(id);
	auto ret = it != zbior.end() ? it->second.size() : 0;
	std::cerr << "strset_size " << id << " -> " << ret << std::endl;
	return ret;
}



/*Jeżeli istnieje zbiór o identyfikatorze id i element value nie należy do
tego zbioru, to dodaje element do zbioru, a w przeciwnym przypadku nie
robi nic.*/
void strset_insert(unsigned long id, const char* value) {
	assert(value != NULL);
	if ((strset_size(id) || strcmp(value, "42")) && id == strset42()) {
		std::cerr << "strset_insert " << id << " is const" << std::endl;
		return;
	}

	auto it = zbior.find(id);
	if (it == zbior.end()) {
		std::cerr << "strset_insert " << id << " doesn't exist" << std::endl;
		return;
	}

	auto sit = it->second.find(value);
	if (sit != it->second.end()) {
		std::cerr << "strset_insert " << id << " has value " << value << std::endl;
		return;
	}

	std::cerr << "strset_insert " << id << " inserted " << value << std::endl;
	it->second.insert(strdup(value));
}


/*Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
zbioru, to usuwa element ze zbioru, a w przeciwnym przypadku nie robi nic.*/
void strset_remove(unsigned long id, const char* value) {
	assert(value != NULL);
	if (id == strset42()) {
		std::cerr << "strset_remove " << id << " is const" << std::endl;
		return;
	}

	auto it = zbior.find(id);
	if (it == zbior.end()) {
		std::cerr << "strset_remove " << id << " doesn't exist" << std::endl;
		return;
	}

	auto sit = it->second.find(value);
	if (sit == it->second.end()) {
		std::cerr << "strset_remove " << id << " doesn't have value " << value << std::endl;
		return;
	}
	
	std::cerr << "strset_remove " << id << " removed " << value << std::endl;
	free((void*)*sit);
	it->second.erase(sit);
}


/*Jeżeli istnieje zbiór o identyfikatorze id i element value należy do tego
zbioru, to zwraca 1, a w przeciwnym przypadku 0.*/
int strset_test(unsigned long id, const char* value) {
	assert(value != NULL);
	auto it = zbior.find(id);
	if (it == zbior.end()) {
		std::cerr << "strset_test " << id << " doesn't exist" << std::endl;
		return 0;
	}

	auto sit = it->second.find(value);
	auto ret = sit != it->second.end();
	std::cerr << "strset_test " << id << " -> " << ret << std::endl;
	return ret;
}


/*Jeżeli istnieje zbiór o identyfikatorze id, usuwa wszystkie jego elementy,
a w przeciwnym przypadku nie robi nic.*/
void strset_clear(unsigned long id) {
	if (id == strset42()) {
		std::cerr << "strset_clear " << id << " is const" << std::endl;
		return;
	}

	auto it = zbior.find(id);
	if (it == zbior.end()) {
		std::cerr << "strset_clear " << id << " doesn't exist" << std::endl;
		return;
	}
	std::cerr << "strset_clear " << id << std::endl;

	for (auto el : it->second)
		free((void*)el);

	it->second.clear();
	std::cerr << "strset_clear " << id << " success" << std::endl;
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
	size_t size1 = strset_size(id1), size2 = strset_size(id2);
	if (!size1 || !size2) {
		auto ret = size1 ? 1 : size2 ? -1 : 0;
		std::cerr << "strset_comp " << id1 << " " << id2 << " at least one set is empty -> " << ret << std::endl;
		return ret;
	}

	auto it1 = zbior.find(id1), it2 = zbior.find(id2);
	auto el1 = it1->second.begin(), el2 = it2->second.begin();


	std::cerr << "strset_comp " << id1 << " " << id2 << std::endl << "set1: ";
	for (auto i : it1->second)
		std::cerr << i << ", ";
	 std::cerr << std::endl << "set2: ";
	 for (auto i : it2->second)
		std::cerr << i << ", ";
	 std::cerr << std::endl;

	while (el1 != it1->second.end() && el2 != it2->second.end()) {
		int cmp = strcmp(*el1, *el2);
		if (cmp) {
			std::cerr << "strset_comp " << id1 << " " << id2 << " completed on " << *el1 << " / " << *el2 << " -> " << cmp << std::endl;
			return cmp < 0 ? -1 : cmp ? 1 : 0;
		}
		
		el1++;
		el2++;
	}
	auto ret = el1 != it1->second.end() ? 1 : el2 != it2->second.end() ? -1 : 0;
	std::cerr << "strset_comp " << id1 << " " << id2 << " -> " << ret << std::endl;
	return ret;
}

      
#ifdef __cplusplus
}
#endif