# CROMA

C **header-only** utility macros for error handling, generic dynamic arrays, queue/stack helpers, and small low-level helpers.

## Requirements

- C compiler with GNU extensions.
- Tested with `-std=gnu99`.

## Installation

```c
#include "croma.h"
```

## Testing

```sh
make test
```

## Quick start

```c
#include "croma.h"

int main(void) {
    DA(int) nums = {0};
    da_append(&nums, 10);
    da_append(&nums, 20);
    da_insert(&nums, 15, 1); // [10, 15, 20]
    da_remove(&nums, 0);     // [15, 20]

    for_da_each(it, &nums) {
        printf("%d\n", *it);
    }

    da_destroy(&nums);
    return 0;
}
```

## API reference

### Unused-value helpers

| Macro | Description |
| --- | --- |
| `UNUSED(...)` | Marks up to 6 values/parameters as intentionally unused. |
| `UNUSED1`..`UNUSED5` | Internal expansion helpers used by `UNUSED`. |

### Configuration macros

| Macro | Description |
| --- | --- |
| `TRIMPREFIX` | Enables short lowercase aliases without `croma_` prefix (`panic`, `todo`, `unreachable`). |
| `LOWERCASE` | Enables lowercase aliases for panic/todo/unreachable macros. |
| `CROMA_OUTFILE` | Output stream used by fatal macros (default: `stderr`). |

### Fatal error macros

| Macro | Description |
| --- | --- |
| `PANIC_MSG` | Prefix string used by `CROMA_PANIC`. |
| `TODO_MSG` | Prefix string used by `CROMA_TODO`. |
| `UNREACHABLE_MSG` | Prefix string used by `CROMA_UNREACHABLE`. |
| `CROMA_PANIC(fmt, ...)` | Prints panic message + file/line and aborts. |
| `CROMA_TODO(fmt, ...)` | Prints todo message + file/line and aborts. |
| `CROMA_UNREACHABLE(fmt, ...)` | Prints unreachable message + file/line and aborts. |

### Conditional aliases for fatal macros

When `LOWERCASE` is enabled:

| Condition | Available aliases |
| --- | --- |
| `TRIMPREFIX` enabled | `panic`, `todo`, `unreachable` |
| `TRIMPREFIX` disabled | `croma_panic`, `croma_todo`, `croma_unreachable` |

### Dynamic array (`DA`) macros

| Macro | Description |
| --- | --- |
| `DA(type)` | Type-agnostic dynamic array struct (`capacity`, `count`, `items`). |
| `DA_REALLOC(dest, size)` | Reallocation backend used by array growth (default: `realloc`). |
| `DA_MALLOC(size)` | Allocation helper macro (default: `malloc`). |
| `AUTO_TYPE` | Alias to `__auto_type`. |
| `da_append(da_ptr, value)` | Appends one item, growing capacity if needed. |
| `da_insert(da_ptr, value, index)` | Inserts at index and shifts following items. |
| `da_remove(da_ptr, index)` | Removes index and shifts remaining items. |
| `da_count(da_ptr)` | Returns item count. |
| `da_index(elem_ptr, da_ptr)` | Returns index for an element pointer. |
| `da_dup(da_ptr)` | Returns a shallow duplicate struct with copied item buffer. |
| `da_destroy(da_ptr)` | Frees item buffer and resets array fields. |
| `for_da_each(it, da_ptr)` | Iterates items as pointers. |

### Queue/stack (`QQ`) macros

| Macro | Description |
| --- | --- |
| `QQ(type)` | Alias over `DA(type)` used as queue/stack container. |
| `for_qq_each` | Alias of `for_da_each`. |
| `qq_push(q_ptr, value)` | Pushes value to the end. |
| `qq_pop(q_ptr)` | Removes the last value if present. |
| `qq_top(q_ptr)` | Returns last value (top). |
| `qq_count(q_ptr)` | Returns element count. |

### Generic utility macros

| Macro | Description |
| --- | --- |
| `MIN(a, b)` | Minimum with single evaluation per argument. |
| `MAX(a, b)` | Maximum with single evaluation per argument. |
| `ZERO(x)` | Byte-zeroes an object (`memset`). |
| `KB(x)` | Returns `x << 10` as `size_t`. |
| `MB(x)` | Returns `x << 20` as `size_t`. |
| `GB(x)` | Returns `x << 30` as `size_t`. |
| `TB(x)` | Returns `x << 40` as `size_t`. |
| `BF(n)` | Initializes bitflag storage to zero. |
| `BF_SET(n, f)` | Sets mask `f` in `n`. |
| `BF_CLR(n, f)` | Clears mask `f` in `n`. |
| `BF_HAS(n, f)` | True when all bits in `f` are present in `n`. |
| `TOSTRING(x)` | Stringifies token `x`. |

## Notes

- `CROMA_PANIC`, `CROMA_TODO`, and `CROMA_UNREACHABLE` always call `abort()`.
- Some macros rely on GNU extensions (`statement expressions`, `__auto_type`, variadic behavior).
