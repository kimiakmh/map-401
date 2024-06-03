#############################################################################
# Fichier Makefile 
# UE MAP401 - DLST - UGA - 2020/2021
#############################################################################
# utilisation des variables internes $@ $< $^ $*
# $@ : correspond au nom de la cible
# $< : correspond au nom de la premiere dependance
# $^ : correspond à toutes les dépendances
# $* : correspond au nom du fichier sans extension 
#       (dans les regles generiques uniquement)
#############################################################################
# information sur la regle executee avec la commande @echo
# (une commande commençant par @ n'est pas affichée à l'écran)
#############################################################################

#############################################################################
# definition des variables locales
#############################################################################

# compilateur C
CC = clang

# chemin d'acces aux librairies (interfaces)
INCDIR = .

# chemin d'acces aux librairies (binaires)
LIBDIR = .

# options pour l'édition des liens
LDOPTS = -L$(LIBDIR) -lm

# options pour la recherche des fichiers .o et .h
INCLUDEOPTS = -I$(INCDIR)

# options de compilation
COMPILOPTS = -g -Wall $(INCLUDEOPTS)

# liste des executables
EXECUTABLES = geometrie2d

#############################################################################
# definition des regles
#############################################################################

########################################################
# la règle par défaut
all : $(EXECUTABLES)

########################################################
# regle generique : 
#  remplace les regles de compilation séparée de la forme
#  module.o : module.c module.h
#      $(CC) -c $(COMPILOPTS) module.c
%.o : %.c %.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module "$*
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de compilation séparée de modules
# n'ayant pas de fichier .h ET/OU dépendant d'autres modules
geometrie2D.o : geometrie2D.c geometrie2D.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geometrie2D"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_geometrie2D.o : test_geometrie2D.c geometrie2D.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_geometrie2D"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

########################################################
# regles explicites de creation des executables

geometrie2d : geometrie2D.o test_geometrie2D.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) *.o
