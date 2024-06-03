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
# EXECUTABLES = simplification_contours
# EXECUTABLES = test_bezier
# EXECUTABLES = test_contour_bezier2 
EXECUTABLES = test_contour_bezier3

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
image.o : image.c image.h types_macros.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module image"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

contour.o : contour.c contour.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module contour"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

geometrie2D.o : geometrie2D.c geometrie2D.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module geometrie2D"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

bezier.o : bezier.c bezier.h contour.h geometrie2D.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

test_bezier.o : test_bezier.c bezier.h image.h contour.h 
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_bezier"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

simplification_contours_segments.o : simplification_contours_segments.c contour.h geometrie2D.h bezier.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module simplification_contours_segments"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<

# test_simplification_contours_segments.o : test_simplification_contours_segments.c image.h contour.h geometrie2D.h
# 	@echo ""
# 	@echo "---------------------------------------------"
# 	@echo "Compilation du module test_simplification_contours_segments"
# 	@echo "---------------------------------------------"
# 	$(CC) -c $(COMPILOPTS) $<

# test_simplification_contours_Bezier2.o: test_simplification_contours_Bezier2.c simplification_contours_segments.h image.h
# 	@echo ""
# 	@echo "---------------------------------------------"
# 	@echo "Compilation du module test_simplification_contours_Bezier2"
# 	@echo "---------------------------------------------"
# 	$(CC) -c $(COMPILOPTS) $<

test_simplification_contours_Bezier3.o: test_simplification_contours_Bezier3.c simplification_contours_segments.h image.h
	@echo ""
	@echo "---------------------------------------------"
	@echo "Compilation du module test_simplification_contours_Bezier3"
	@echo "---------------------------------------------"
	$(CC) -c $(COMPILOPTS) $<


########################################################
# regles explicites de creation des executables

# simplification_contours : simplification_contours_segments.o test_simplification_contours_segments.o geometrie2D.o contour.o image.o
# 	@echo ""
# 	@echo "---------------------------------------------"
# 	@echo "Creation de l'executable "$@
# 	@echo "---------------------------------------------"
# 	$(CC) $^ $(LDOPTS) -o $@

# test_bezier : bezier.o test_bezier.o contour.o image.o geometrie2D.o
# 	@echo ""
# 	@echo "---------------------------------------------"
# 	@echo "Creation de l'executable "$@
# 	@echo "---------------------------------------------"
# 	$(CC) $^ $(LDOPTS) -o $@

# test_contour_bezier2 : test_simplification_contours_Bezier2.o simplification_contours_segments.o bezier.o contour.o image.o geometrie2D.o
# 	@echo ""
# 	@echo "---------------------------------------------"
# 	@echo "Creation de l'executable "$@
# 	@echo "---------------------------------------------"
# 	$(CC) $^ $(LDOPTS) -o $@

test_contour_bezier3 : test_simplification_contours_Bezier3.o simplification_contours_segments.o bezier.o contour.o image.o geometrie2D.o
	@echo ""
	@echo "---------------------------------------------"
	@echo "Creation de l'executable "$@
	@echo "---------------------------------------------"
	$(CC) $^ $(LDOPTS) -o $@

# regle pour "nettoyer" le répertoire
clean:
	rm -fR $(EXECUTABLES) *.o