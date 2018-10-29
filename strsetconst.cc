#include "strset.h"
#include "strsetconst.h"
#ifdef __cplusplus
namespace jnp1 {
#endif
unsigned long strset42() {
	static unsigned long constId = strset_new();
	static bool inserted = false;
	if (!inserted) {
		inserted = true;
		strset_insert(constId, "42");
	}
	return constId;
}
#ifdef __cplusplus
}
#endif