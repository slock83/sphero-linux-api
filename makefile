# Commande de délétion
RM=rm
# Flags de délétion
RMFLAGS=-rf

# Commande de copie
CP=cp

# Bibliothèques supplémentaires
LIB=bluetooth pthread rt

# Répertoires de bibliothèques
LIBDIR?=

# Destination prefix for install
DESTDIR?=/usr/

# System libraries folder
SYSLIB?=$(DESTDIR)/lib/

# System include folder
SYSINC?=$(DESTDIR)/include/

# Commande écho
ECHO=@echo

# Nom de la bibliothèque
LIBNAME=libsphero.so

# Dossiers d'include pero
INCDIR=src

# Dossier d'include externes
EXTINCDIR?=

# Dossier sources
SRCDIR=src

# Dossier objets
OBJDIR=obj

# Dossier où sont mises les dépendances
DEPDIR=dep
df=$(DEPDIR)/$(*F)

SRC=$(shell find $(SRCDIR) -type f -name *.cpp | sed -e "s/$(SRCDIR)\///")
INC=$(shell find $(INCDIR) -type f \( -name *.hpp -o -name *.h -o -name *.tpp \) | sed -e "s/$(INCDIR)\///")

OBJ=$(SRC:.cpp=.o)

CLEAR=clean
INSTALL=install
UNINSTALL=uninstall
REINSTALL=reinstall

MAKEDEPEND = g++ $(addprefix -I, $(EXTINCDIR)) -I$(INCDIR) -o $(df).d -std=c++11 -MM $< #Pour calculer les dépendances

#Compilateur
CC=gcc 
#Options du compilateur
CCFLAGS+=-Wall -fPIC -fpermissive -Wextra -Woverloaded-virtual -std=c++11 -I$(INCDIR) $(addprefix -I, $(EXTINCDIR)) $(addprefix -l, $(LIB)) -c -pthread 

EL=g++ #Éditeur de liens
ELFLAGS= -shared

DEBUG?=FALSE

DSHARP?=FALSE

MAP?=FALSE

PROF?=FALSE

ifneq ($(DEBUG),FALSE)
    CCFLAGS+= -g
    ELFLAGS+= -g
endif

ifneq ($(MAP),FALSE)
    CCFLAGS+= -DMAP
endif

ifneq ($(PROF),FALSE)
    CCFLAGS+= -pg
    ELFLAGS+= -pg
endif


.PHONY: $(CLEAR)
.PHONY: $(INSTALL)
.PHONY: ALL
.PHONY: $(UNINSTALL)
.PHONY: $(REINSTALL)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	@mkdir -p $(DEPDIR);
	@mkdir -p $(OBJDIR);
	@$(MAKEDEPEND); \
		cp $(df).d $(df).P;\
		sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	            -e '/^$$/ d' -e 's/$$/ :/' < $(df).d >> $(df).P;\
        	sed -i '1s/^/$(OBJDIR)\//' $(df).P;
		@rm -f $(df).d
	@$(ECHO) "Compilation de $<"
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -o $@ $<


ALL: $(LIBNAME)
	
$(LIBNAME): $(addprefix $(OBJDIR)/, $(OBJ)) 
	$(ECHO) "Fabrication de la bibliothèque"
	$(EL) -o $(LIBNAME) $(addprefix $(OBJDIR)/, $(OBJ)) $(ELFLAGS) $(addprefix -l, $(LIB)) 

#Fichiers de dépendance
-include $(SRC:%.cpp=$(DEPDIR)/%.P)

$(UNINSTALL):
	@rm $(addprefix $(SYSLIB), $(LIBNAME))
	@rm -rvf $(SYSINC)sphero
	$(ECHO) Désinstallation effectuée

$(INSTALL): $(LIBNAME) 
	@mkdir -p $(SYSLIB)
	$(CP) $(LIBNAME) $(addprefix $(SYSLIB), $(LIBNAME))
	@mkdir -p $(SYSINC)sphero
	cd $(INCDIR) ; $(CP) --parent $(INC) $(SYSINC)sphero

$(REINSTALL): $(UNINSTALL) $(INSTALL)

$(CLEAR):
	$(RM) $(RMFLAGS) $(OBJDIR)/* $(DEPDIR)/*.P $(LIBNAME) 
