#include "croma.h"

int main(void) {
    DA(int) xs = {0};
    da_append(&xs, 1);
    da_append(&xs, 2);
    da_insert(&xs, 3, 1);
    da_remove(&xs, 0);

    QQ(int) q = {0};
    qq_push(&q, 10);
    qq_push(&q, 20);
    qq_pop(&q);

    int lo = MIN(1, 2);
    int hi = MAX(1, 2);
    unsigned flags = 0;
    BF(flags);
    BF_SET(flags, 1u << 1);
    BF_CLR(flags, 1u << 2);

    if (BF_HAS(flags, 1u << 1)) {
        UNUSED(lo, hi);
    }

    size_t s = MB(4);
    UNUSED(s);
    da_destroy(&xs);
    da_destroy(&q);
    return 0;
}
