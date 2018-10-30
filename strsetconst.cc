#include "strset.h"
#include "strsetconst.h"

namespace{
  #ifndef DNDEBUG
    const bool debug = true;
  #else
    const bool debug = false;
  #endif
  
  unsigned long init_strset42(){
    if(debug){
      std::cerr << "strsetconst init invoked" << std::endl;
    }
    
    return jnp1::strset_new();
  }
}

namespace jnp1 {
  
  unsigned long strset42() {
    static unsigned long constId = init_strset42();
    static bool inserted = false;
    if (!inserted) {
      inserted = true;
      strset_insert(constId, "42");
    }
    return constId;
  }
  
}