CC=g++
EXT=cpp

EXEC=Appli

CFLAGS=-std=c++11 -O2 -lsphero -L.. -DBLUEZ
LDFLAGS=-lsphero -L.. -Wl,-rpath=.. -g
INC=-I../API-src

OBJDIR = obj
SRC= $(wildcard *.$(EXT))
HEAD= $(SRC:.$(EXT)=.h)
OBJ= $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))


.PHONY: all clean clean-all depend

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.$(EXT)
	@mkdir -p $(OBJDIR)
	$(CC) -o $@ -c $< $(LDFLAGS) $(CFLAGS) $(INC)

clean:
	@echo "Suppression des fichiers objet..."
	@rm -rf $(OBJDIR)
	@echo "Suppression de l'exécutable..."
	@rm -f $(EXEC) core$

depend:
	@makedepend $(SRC) -p$(OBJDIR)/
# DO NOT DELETE

obj/appli.o: CommandHandler.h
obj/CommandHandler.o: CommandHandler.h
obj/CommandHandler.o: ../libsphero.so
