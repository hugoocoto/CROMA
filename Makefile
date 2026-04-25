CC ?= cc
CFLAGS ?= -std=gnu99 -Wall -Wextra -Werror -I.

TEST_BIN := croma_test
TEST_SRC := test.c

.PHONY: test clean

test: $(TEST_BIN)
	@echo "[test] running $(TEST_BIN)"
	@./$(TEST_BIN)
	@echo "[test] ok"

$(TEST_BIN): $(TEST_SRC) croma.h
	$(CC) $(CFLAGS) $(TEST_SRC) -o $(TEST_BIN)

clean:
	rm -f $(TEST_BIN)
