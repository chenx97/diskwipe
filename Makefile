BIN = diskwipe
OFILES = $(patsubst src/%.c,src/%.o,$(wildcard src/*.c))
CFLAGS += -O3 -flto
LDFLAGS += $(CFLAGS)
LDLIBS = -lm -lpthread
CLEAN = $(wildcard src/*.o dump* $(BIN))

all: $(BIN)

$(BIN): $(OFILES)
	$(info linking: $(OFILES))
	$(CC) -o $@ $(OFILES) $(LDFLAGS) $(LDLIBS)

src/%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS) -Iinclude

clean:
ifneq ($(CLEAN),)
	$(RM) $(CLEAN)
endif
