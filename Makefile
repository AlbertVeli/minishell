CC = gcc

CFLAGS = -W -Wall -Wextra -Os
LDFLAGS = -lreadline

OBJS = minishell.o
EXE = $(OBJS:.o=)

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)
	strip $@

suid: $(EXE)
	@echo "Changing owner to root and setting suid bit (run with sudo)"
	chown root:root $<
	chmod 4755 $<

unsuid: $(EXE)
	@echo "Removing suid bit (run with sudo)"
	chown $(SUDO_UID):$(SUDO_GID) $<
	chmod 755 $<

clean:
	rm -f $(OBJS) $(EXE)
