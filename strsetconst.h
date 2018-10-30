#ifndef __STRSETCONST_H__
#define __STRSETCONST_H__

#ifdef __cplusplus
namespace jnp1 {
    extern "C" {
#endif
        /*Zwraca identyfikator zbioru, którego nie można modyfikować i który zawiera
        jeden element: napis "42". Zbiór jest tworzony przy pierwszym wywołaniu tej
        funkcji i wtedy zostaje ustalony jego numer.*/
        unsigned long strset42();

#ifdef __cplusplus
    }
}
#endif

#endif /*__STRSETCONST_H__*/