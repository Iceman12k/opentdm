# this nice line comes from the linux kernel makefile
ARCH := $(shell uname -m | sed -e s/i.86/i386/ -e s/sun4u/sparc64/ -e s/arm.*/arm/ -e s/sa110/arm/ -e s/alpha/axp/)


ifndef REV
    REV := $(shell git rev-list HEAD | wc -l)
    #REV := $(shell echo $$((181+$REV1)))
endif

ifndef VER
    VER := r$(REV)-$(shell git rev-parse --short HEAD)-pf
endif

CURL_CFLAGS ?= $(shell pkg-config libcurl --cflags)
CFLAGS=-O -g -fPIC -Wall -DHAVE_CURL $(CURL_CFLAGS)
CFLAGS += -DOPENTDM_VERSION='"$(VER)"' -DOPENTDM_REVISION=$(REV)

#LDFLAGS=-lcurl

game_SRC:=g_chase.c g_cmds.c g_combat.c g_func.c g_items.c g_main.c g_misc.c \
g_phys.c g_save.c g_spawn.c g_svcmds.c g_target.c g_tdm_client.c g_tdm_cmds.c \
g_tdm_core.c g_tdm_curl.c g_tdm_macros.c g_tdm_stats.c g_tdm_vote.c g_trigger.c \
g_utils.c g_weapon.c mt19937.c p_client.c p_hud.c p_menu.c p_view.c p_weapon.c \
g_tdm_votemenu.c q_shared.c sys_linux.c

game_OBJ:=$(game_SRC:.c=.o)

ALLSRC:=$(game_SRC)

.PHONY: default clean

default: game$(ARCH)-opentdm-$(VER).so

TARGETS:=game$(ARCH).so

game$(ARCH)-opentdm-$(VER).so: $(game_OBJ)
	$(CC) -lcurl -shared -o $@ $^ $(LDFLAGS)

clean:
	rm -f *.o game$(ARCH)*.so

