#include "croma.h"

int main(void) {
    croma_DA(int) xs = {0};
    croma_da_append(&xs, 1);
    croma_da_append(&xs, 2);
    croma_da_insert(&xs, 3, 1);
    croma_da_remove(&xs, 0);

    croma_SS(int) s = {0};
    croma_ss_push(&s, 10);
    croma_ss_push(&s, 20);
    if (croma_ss_top(&s) != 20) return 1;
    croma_ss_pop(&s);
    if (croma_ss_top(&s) != 10) return 1;

    croma_QQ(int) q = {0};
    croma_qq_push(&q, 10);
    croma_qq_push(&q, 20);
    if (croma_qq_top(&q) != 10) return 1;
    croma_qq_pop(&q);
    if (croma_qq_top(&q) != 20) return 1;

    int lo = croma_min(1, 2);
    int hi = croma_max(1, 2);
    unsigned flags = 0;
    croma_bf(flags);
    croma_bf_set(flags, 1u << 1);
    croma_bf_clr(flags, 1u << 2);

    if (croma_bf_has(flags, 1u << 1)) {
        croma_unused(lo, hi);
    }

    size_t bytes = croma_mb(4);
    croma_unused(bytes);
    croma_da_destroy(&xs);
    croma_da_destroy(&s);
    croma_da_destroy(&q);
    return 0;
}
