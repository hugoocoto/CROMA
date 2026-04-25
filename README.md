# CROMA

C **header-only** macros for fatal errors, dynamic arrays, stack/queue wrappers, and utility helpers.

## Requirements

- C compiler with GNU extensions
- Recommended minimum: `-std=gnu99`

## Installation

```c
#include "croma.h"
```

## Testing

```sh
make test
```

## Naming and prefixes

The canonical API is prefixed with `croma_` (for example `croma_da_append`, `croma_ss_push`, `croma_qq_pop`).

If `TRIMPREFIX` is defined (it is enabled by default in `croma.h`), short aliases without the prefix are also available (`da_append`, `ss_push`, `qq_pop`, `MIN`, etc.).

## API reference

### Configuration

| Macro | Description |
| --- | --- |
| `TRIMPREFIX` | Enables non-prefixed aliases for the public API. |
| `CROMA_OUTFILE` | Stream used by fatal macros (`stderr` by default). |
| `croma_DA_REALLOC(dest, size)` | Reallocation hook used by dynamic array growth. |
| `croma_DA_MALLOC(size)` | Allocation hook used by helpers like duplication. |

### Unused-value helper

| Macro | Description |
| --- | --- |
| `croma_unused(...)` | Marks up to 6 values/parameters as intentionally unused. |

### Fatal macros

| Macro | Description |
| --- | --- |
| `CROMA_PANIC(fmt, ...)` | Prints message + file/line and aborts. |
| `CROMA_TODO(fmt, ...)` | Prints message + file/line and aborts. |
| `CROMA_UNREACHABLE(fmt, ...)` | Prints message + file/line and aborts. |
| `croma_panic` | Alias of `CROMA_PANIC`. |
| `croma_todo` | Alias of `CROMA_TODO`. |
| `croma_unreachable` | Alias of `CROMA_UNREACHABLE`. |

### Dynamic array (`DA`)

| Macro | Description |
| --- | --- |
| `croma_DA(type)` | Generic dynamic array struct (`capacity`, `count`, `items`). |
| `croma_AUTO_TYPE` | Alias to `__auto_type`. |
| `croma_da_append(da_ptr, value)` | Appends one value. |
| `croma_da_insert(da_ptr, value, index)` | Inserts value at index. |
| `croma_da_remove(da_ptr, index)` | Removes value at index. |
| `croma_da_count(da_ptr)` | Returns element count. |
| `croma_da_index(elem_ptr, da_ptr)` | Returns index of an element pointer. |
| `croma_da_dup(da_ptr)` | Duplicates array struct and backing storage. |
| `croma_da_destroy(da_ptr)` | Frees storage and resets fields. |
| `croma_for_da_each(it, da_ptr)` | Iterates element pointers. |

### Stack wrapper (`SS`, LIFO)

| Macro | Description |
| --- | --- |
| `croma_SS(type)` | Stack container wrapper over `croma_DA(type)`. |
| `croma_for_ss_each` | Alias of `croma_for_da_each`. |
| `croma_ss_push(s_ptr, value)` | Pushes value at the end. |
| `croma_ss_pop(s_ptr)` | Removes the last value. |
| `croma_ss_top(s_ptr)` | Returns the last value. |
| `croma_ss_count(s_ptr)` | Returns stack size. |

### Queue wrapper (`QQ`, FIFO)

| Macro | Description |
| --- | --- |
| `croma_QQ(type)` | Queue container wrapper over `croma_DA(type)`. |
| `croma_for_qq_each` | Alias of `croma_for_da_each`. |
| `croma_qq_push(q_ptr, value)` | Enqueues value at the end. |
| `croma_qq_pop(q_ptr)` | Dequeues value from the front. |
| `croma_qq_top(q_ptr)` | Returns the front value. |
| `croma_qq_count(q_ptr)` | Returns queue size. |

### Utility macros

| Macro | Description |
| --- | --- |
| `croma_min(a, b)` | Minimum with single evaluation per argument. |
| `croma_max(a, b)` | Maximum with single evaluation per argument. |
| `croma_zero(x)` | Zeroes an object (`memset`). |
| `croma_kb(x)` | `x << 10` as `size_t`. |
| `croma_mb(x)` | `x << 20` as `size_t`. |
| `croma_gb(x)` | `x << 30` as `size_t`. |
| `croma_tb(x)` | `x << 40` as `size_t`. |
| `croma_bf(n)` | Initializes bitflags storage to zero. |
| `croma_bf_set(n, f)` | Sets mask `f` in `n`. |
| `croma_bf_clr(n, f)` | Clears mask `f` in `n`. |
| `croma_bf_has(n, f)` | True if all bits in `f` are present in `n`. |
| `croma_tostring(x)` | Stringifies token `x`. |

### Non-prefixed aliases under `TRIMPREFIX`

When `TRIMPREFIX` is enabled, these aliases are exposed:

- `UNUSED`
- `panic`, `todo`, `unreachable`
- `AUTO_TYPE`, `DA`, `da_append`, `da_destroy`, `da_insert`, `da_count`, `da_index`, `da_remove`, `for_da_each`, `da_dup`
- `SS`, `for_ss_each`, `ss_top`, `ss_count`, `ss_push`, `ss_pop`
- `QQ`, `for_qq_each`, `qq_top`, `qq_count`, `qq_push`, `qq_pop`
- `MIN`, `MAX`, `ZERO`, `KB`, `MB`, `GB`, `TB`, `BF`, `BF_SET`, `BF_CLR`, `BF_HAS`, `TOSTRING`

## Notes

- `CROMA_PANIC`, `CROMA_TODO`, and `CROMA_UNREACHABLE` always terminate with `abort()`.
- `QQ` is FIFO and `SS` is LIFO.
