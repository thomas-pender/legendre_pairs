include $(top_srcdir)/aminclude.am
ACLOCAL_AMFLAGS = -I m4

noinst_PROGRAMS = src/A src/B src/whiteman src/amicable

src_A_SOURCES = $(top_srcdir)/src/A.c++ $(top_srcdir)/src/args.c++ \
$(top_srcdir)/src/args.h++
src_A_CPPFLAGS = -I$(top_srcdir)/src -I./src
src_A_CFLAGS = -Wall -Wextra -Wpedantic -Wno-unused-function \
-Wno-stringop-overflow
src_A_LDADD = @LIBS@

src_B_SOURCES = $(top_srcdir)/src/B.c++ $(top_srcdir)/src/args.c++ \
$(top_srcdir)/src/args.h++
src_B_CPPFLAGS = -I$(top_srcdir)/src -I./src
src_B_CFLAGS = -Wall -Wextra -Wpedantic -Wno-unused-function \
-Wno-stringop-overflow
src_B_LDADD = @LIBS@

src_whiteman_SOURCES = $(top_srcdir)/src/whiteman.c++ \
$(top_srcdir)/src/sequences.h++
src_whiteman_CPPFLAGS = -I$(top_srcdir)/src -I./src
src_whiteman_CFLAGS = -Wall -Wextra -Wpedantic -Wno-unused-function \
-Wno-stringop-overflow

src_amicable_SOURCES = $(top_srcdir)/src/amicable.c++ \
$(top_srcdir)/src/set.c++ $(top_srcdir)/src/set.h++
src_amicable_CPPFLAGS = -I$(top_srcdir)/src -I./src
src_amicable_CFLAGS = -Wall -Wextra -Wpedantic -Wno-unused-function \
-Wno-stringop-overflow

if DOXY
all-local:
	$(MAKE) doxygen-doc
endif

EXTRA_DIST = $(top_srcdir)/docs_pages
