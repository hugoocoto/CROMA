#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Get rid of unused x warning. Max 6 arguments in the same call */
#define UNUSED(what, ...) __VA_OPT__(UNUSED1(__VA_ARGS__);)(void) what
#define UNUSED1(what, ...) __VA_OPT__(UNUSED2(__VA_ARGS__);)(void) what
#define UNUSED2(what, ...) __VA_OPT__(UNUSED3(__VA_ARGS__);)(void) what
#define UNUSED3(what, ...) __VA_OPT__(UNUSED4(__VA_ARGS__);)(void) what
#define UNUSED4(what, ...) __VA_OPT__(UNUSED5(__VA_ARGS__);)(void) what
#define UNUSED5(what, ...) (void) what

/* == OPTIONS == */

#define TRIMPREFIX /* trim the CROMA prefix */
#define LOWERCASE  /* Create a lowecase alias */

#define CROMA_OUTFILE stderr /* file to print */

/* panic, todo, unreachable macros: print and die */

#define PANIC_MSG "PANIC "
#define CROMA_PANIC(fmt, ...)                                                        \
        do {                                                                         \
                fprintf(CROMA_OUTFILE, PANIC_MSG " at %s:%d: ", __FILE__, __LINE__); \
                fprintf(CROMA_OUTFILE, fmt, ##__VA_ARGS__);                          \
                abort();                                                             \
        } while (0)

#define TODO_MSG "TODO "
#define CROMA_TODO(fmt, ...)                                                        \
        do {                                                                        \
                fprintf(CROMA_OUTFILE, TODO_MSG " at %s:%d: ", __FILE__, __LINE__); \
                fprintf(CROMA_OUTFILE, fmt, ##__VA_ARGS__);                         \
                abort();                                                            \
        } while (0)

#define UNREACHABLE_MSG "UNREACHABLE "
#define CROMA_UNREACHABLE(fmt, ...)                                                       \
        do {                                                                              \
                fprintf(CROMA_OUTFILE, UNREACHABLE_MSG "at %s:%d: ", __FILE__, __LINE__); \
                fprintf(CROMA_OUTFILE, fmt, ##__VA_ARGS__);                               \
                abort();                                                                  \
        } while (0)

#ifdef LOWERCASE
#ifdef TRIMPREFIX
#define panic CROMA_PANIC
#define todo CROMA_TODO
#define unreachable CROMA_UNREACHABLE
#else
#define croma_panic CROMA_PANIC
#define croma_todo CROMA_TODO
#define croma_unreachable CROMA_UNREACHABLE
#endif
#endif


/* Type-agnostic Dynamic array */

#define DA_REALLOC(dest, size) realloc((dest), (size));
#define DA_MALLOC(size) malloc((size));
#define AUTO_TYPE __auto_type

#define DA(type)              \
        struct {              \
                int capacity; \
                int count;    \
                type *items;  \
        }

// add E to DA_PTR that is a pointer to a DA of the same type as E
#define da_append(da_ptr, ...)                                                                \
        do {                                                                                  \
                if ((da_ptr)->count >= (da_ptr)->capacity) {                                  \
                        (da_ptr)->capacity = (da_ptr)->capacity ? (da_ptr)->capacity * 2 : 4; \
                        (da_ptr)->items = DA_REALLOC(                                         \
                        (da_ptr)->items,                                                      \
                        sizeof(*((da_ptr)->items)) * (da_ptr)->capacity);                     \
                }                                                                             \
                (da_ptr)->items[(da_ptr)->count++] = (__VA_ARGS__);                           \
        } while (0)

/* Destroy DA pointed by DA_PTR. DA can be initialized again but previous
 * values are not accessible anymore. */
#define da_destroy(da_ptr)                                       \
        do {                                                     \
                if ((da_ptr) == 0) break;                        \
                if ((da_ptr)->items && (da_ptr)->capacity > 0) { \
                        free((da_ptr)->items);                   \
                }                                                \
                (da_ptr)->capacity = 0;                          \
                (da_ptr)->count = 0;                             \
                (da_ptr)->items = NULL;                          \
        } while (0)

/* Insert element E into DA pointed by DA_PTR at index I. */
#define da_insert(da_ptr, e, i)                                                   \
        do {                                                                      \
                da_append((da_ptr), (__typeof__((e))) { 0 });                     \
                memmove((da_ptr)->items + (i) + 1, (da_ptr)->items + (i),         \
                        ((da_ptr)->count - (i) - 1) * sizeof *((da_ptr)->items)); \
                (da_ptr)->items[(i)] = (e);                                       \
        } while (0)

/* Get size */
#define da_count(da_ptr) ((da_ptr)->count)

/* Get the index of an element given a pointer to this element */
#define da_index(da_elem_ptr, da_ptr) ((int) ((da_elem_ptr) - ((da_ptr)->items)))

/* Remove element al index I */
#define da_remove(da_ptr, i)                                                \
        do {                                                                \
                if ((i) >= 0 && (i) < (da_ptr)->count) {                    \
                        --(da_ptr)->count;                                  \
                        memmove(                                            \
                        (da_ptr)->items + (i), (da_ptr)->items + (i) + 1,   \
                        ((da_ptr)->count - (i)) * sizeof *(da_ptr)->items); \
                }                                                           \
        } while (0)

/* can be used as:
 * for_da_each(i, DA), where
 * - i: variable where a pointer to an element from DA is going to be stored
 * - DA: is a valid DA */
#define for_da_each(_i_, da_ptr)                                \
        for (AUTO_TYPE(_i_) = (da_ptr)->items;                  \
             (int) ((_i_) - (da_ptr)->items) < (da_ptr)->count; \
             ++(_i_))

#define da_dup(da_ptr)                                                                             \
        ({                                                                                         \
                __auto_type cpy = *(da_ptr);                                                       \
                cpy.items = malloc((da_ptr)->capacity * sizeof(da_ptr)->items[0]);                 \
                memcpy(cpy.items, (da_ptr)->items, (da_ptr)->capacity * sizeof(da_ptr)->items[0]); \
                cpy;                                                                               \
        })


// Type-agnostic Queue wrapper over DA

#define QQ DA
#define for_qq_each for_da_each

#define qq_top(q_ptr) ((q_ptr)->items[(q_ptr)->count - 1])

#define qq_count(q_ptr) da_count(q_ptr)

#define qq_push(q_ptr, ...)                      \
        do {                                     \
                da_append((q_ptr), __VA_ARGS__); \
        } while (0)

#define qq_pop(q_ptr)                        \
        do {                                 \
                if ((q_ptr)->count > 0) {    \
                        (q_ptr)->count -= 1; \
                }                            \
        } while (0)


#define MIN(a, b) ({              \
        __auto_type _a = (a);     \
        __auto_type _b = (b);     \
        (_a) < (_b) ? (_a) : (_b);\
})

#define MAX(a, b) ({              \
        __auto_type _a = (a);     \
        __auto_type _b = (b);     \
        (_a) > (_b) ? (_a) : (_b);\
})

/* Zero-initialize an object/struct by bytes. */
#define ZERO(x) memset(&(x), 0, sizeof((x)))

/* Binary size helpers (KiB/MiB/GiB/TiB). */
#define KB(x) ((size_t) (x) << 10)
#define MB(x) ((size_t) (x) << 20)
#define GB(x) ((size_t) (x) << 30)
#define TB(x) ((size_t) (x) << 40)

/* Bitflags helpers: N is the flag-set value, F is the mask. */
#define BF(n) ((n) = 0u)
#define BF_SET(n, f) ((n) |= (f))
#define BF_CLR(n, f) ((n) &= ~(f))
#define BF_HAS(n, f) (((n) & (f)) == (f))

#define TOSTRING(x) #x
