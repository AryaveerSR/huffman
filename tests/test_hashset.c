#include <stdlib.h>
#include <assert.h>

#include "hashset.h"
#include "log.h"

int main(void)
{
    log_init();

    struct Hashset set;
    hashset_init(&set);

    char *hello_1 = hashset_insert(&set, "hello");
    char *hello_2 = hashset_insert(&set, "hello");

    assert(hello_1 == hello_2);

    hashset_insert(&set, "val0");
    hashset_insert(&set, "val1");
    hashset_insert(&set, "val2");
    hashset_insert(&set, "val3");
    hashset_insert(&set, "val4");
    hashset_insert(&set, "val5");
    hashset_insert(&set, "val6");
    hashset_insert(&set, "val7");
    hashset_insert(&set, "val8");
    hashset_insert(&set, "val9");
    hashset_insert(&set, "val10");
    hashset_insert(&set, "val11");
    hashset_insert(&set, "val12");
    hashset_insert(&set, "val13");
    hashset_insert(&set, "val14");
    hashset_insert(&set, "val15");
    hashset_insert(&set, "val16");
    hashset_insert(&set, "val17");
    hashset_insert(&set, "val18");
    hashset_insert(&set, "val19");
    hashset_insert(&set, "val20");
    hashset_insert(&set, "val21");
    hashset_insert(&set, "val22");
    hashset_insert(&set, "val23");
    char *val_24 = hashset_insert(&set, "val24");
    hashset_insert(&set, "val25");
    hashset_insert(&set, "val26");
    hashset_insert(&set, "val27");
    hashset_insert(&set, "val28");
    hashset_insert(&set, "val29");
    hashset_insert(&set, "val30");
    hashset_insert(&set, "val31");
    hashset_insert(&set, "val32");
    hashset_insert(&set, "val33");
    hashset_insert(&set, "val34");
    hashset_insert(&set, "val35");
    hashset_insert(&set, "val36");
    hashset_insert(&set, "val37");
    hashset_insert(&set, "val38");
    hashset_insert(&set, "val39");
    hashset_insert(&set, "val40");
    hashset_insert(&set, "val41");
    hashset_insert(&set, "val42");
    hashset_insert(&set, "val43");
    hashset_insert(&set, "val44");
    hashset_insert(&set, "val45");
    hashset_insert(&set, "val46");
    hashset_insert(&set, "val47");
    hashset_insert(&set, "val48");
    hashset_insert(&set, "val49");
    char *val_50 = hashset_insert(&set, "val50");
    hashset_insert(&set, "val51");
    hashset_insert(&set, "val52");
    hashset_insert(&set, "val53");
    hashset_insert(&set, "val54");
    hashset_insert(&set, "val55");
    hashset_insert(&set, "val56");
    hashset_insert(&set, "val57");
    hashset_insert(&set, "val58");
    hashset_insert(&set, "val59");
    hashset_insert(&set, "val60");
    hashset_insert(&set, "val61");
    hashset_insert(&set, "val62");
    hashset_insert(&set, "val63");
    hashset_insert(&set, "val64");
    hashset_insert(&set, "val65");
    hashset_insert(&set, "val66");
    hashset_insert(&set, "val67");
    hashset_insert(&set, "val68");
    hashset_insert(&set, "val69");
    hashset_insert(&set, "val70");
    hashset_insert(&set, "val71");
    hashset_insert(&set, "val72");
    hashset_insert(&set, "val73");
    hashset_insert(&set, "val74");
    hashset_insert(&set, "val75");
    char *val_76 = hashset_insert(&set, "val76");
    hashset_insert(&set, "val77");
    hashset_insert(&set, "val78");
    hashset_insert(&set, "val79");

    assert(val_24 == hashset_insert(&set, "val24"));
    assert(val_50 == hashset_insert(&set, "val50"));
    assert(val_76 == hashset_insert(&set, "val76"));

    hashset_free(&set);
}
