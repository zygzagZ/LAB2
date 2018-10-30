#include "strset.h"
#include "strsetconst.h"

namespace {
    #ifndef NDEBUG
        const bool debug = true;
    #else
        const bool debug = false;
    #endif
    
    unsigned long init_strset42() {
        if(debug) {
            std::cerr << "strsetconst init invoked" << std::endl;
        }
        
        auto id = jnp1::strset_new();
        strset_insert(id, "42");
        return id;
    }
}

namespace jnp1 {
    unsigned long strset42() {
        static unsigned long constId = init_strset42();
        return constId;
    }
}