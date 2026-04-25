# CROMA

C **header-only** library with utility macros for:

- fatal error handling (`CROMA_PANIC`, `CROMA_TODO`, `CROMA_UNREACHABLE`)
- generic dynamic arrays (`DA(type)`)
- simple queue/stack built on `DA` (`QQ(type)`)
- silencing unused-variable warnings (`UNUSED(...)`)
- small utility helpers (`MIN`, `MAX`, `ZERO`, `KB/MB/GB/TB`, `BF_*`, `TOSTRING`)

## Requirements

- C compiler with GNU extensions 

## Installation

Just include the header in your project:

```c
#include "croma.h"
```

## Testing

Run the smoke test with:

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

## Quick queue/stack (`QQ`)

```c
QQ(int) q = {0};
qq_push(&q, 1);
qq_push(&q, 2);
int top = qq_top(&q); // 2
qq_pop(&q);           // removes the last element
da_destroy(&q);
```

## Configuration options

In `croma.h` you can configure:

- `TRIMPREFIX` and `LOWERCASE` for aliases (`panic`, `todo`, `unreachable`)
- `CROMA_OUTFILE` to change the output stream (default: `stderr`)

## Unused macro (`UNUSED`)

Use `UNUSED(...)` to explicitly mark variables/parameters as intentionally unused and avoid compiler warnings.
It supports up to 6 arguments in a single call.

```c
void handler(int status, void *ctx) {
    UNUSED(status, ctx);
}
```

## Utility macros

- `MIN(a, b)` / `MAX(a, b)`: min/max with single evaluation of each argument.
- `ZERO(x)`: zero-initialize an object/struct by bytes.
- `KB(x)`, `MB(x)`, `GB(x)`, `TB(x)`: binary size helpers based on `size_t`.
- `BF(n)`, `BF_SET(n, f)`, `BF_CLR(n, f)`, `BF_HAS(n, f)`: bitflag helpers.
- `TOSTRING(x)`: stringifies the token `x`.

```c
size_t cap = MB(4);     // 4 * 1024 * 1024
unsigned flags = 0;
BF(flags);
BF_SET(flags, 1u << 2);
if (BF_HAS(flags, 1u << 2)) {
    // ...
}
```

## Note

`CROMA_PANIC`, `CROMA_TODO`, and `CROMA_UNREACHABLE` print a message and terminate the program with `abort()`.
