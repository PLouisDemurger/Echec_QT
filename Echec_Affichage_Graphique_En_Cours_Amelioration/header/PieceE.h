//
// Created by pierre-louis on 12/05/2020.
//

#ifndef ECHEC_PIECEE_H
#define ECHEC_PIECEE_H

#include <string>
#include <math.h>
#include <QImage>
#include <QApplication>
#include <iostream>

#define pionNoir (qApp->applicationDirPath()+"/image/pionNoir.png")
#define pionBlanc (qApp->applicationDirPath()+"/image/pionBlanc.png")
#define tourNoir (qApp->applicationDirPath()+"/image/tourNoire.png")
#define tourBlanc (qApp->applicationDirPath()+"/image/tourBlanche.png")
#define chevalNoir (qApp->applicationDirPath()+"/image/chevalNoir.png")
#define chevalBlanc (qApp->applicationDirPath()+"/image/chevalBlanc.png")
#define fouNoir (qApp->applicationDirPath()+"/image/fouNoir.png")
#define fouBlanc (qApp->applicationDirPath()+"/image/fouBlanc.png")
#define dameNoir (qApp->applicationDirPath()+"/image/dameNoire.png")
#define dameBlanc (qApp->applicationDirPath()+"/image/dameBlanche.png")
#define roiNoir (qApp->applicationDirPath()+"/image/roiNoir.png")
#define roiBlanc (qApp->applicationDirPath()+"/image/roiBlanc.png")
#define vide (qApp->applicationDirPath()+"/image/vide3.png")


using namespace std;

class PlateauE;

class PlateauAffichage;

class CoupE;

class Piece : public QImage{

    protected:
        char couleur = 'a';
        char type = 'v';
        bool deplacement = false;
        QString cheminImage = vide;
    public:
        // CONSTRUCTEUR
        Piece();
        Piece(QString filename);
        Piece(char t, char c, bool d, QString filename = vide);
        // DESTRUCTEUR
        ~Piece();
        // METHODE A OVERRIDE
        virtual short deplacementV(PlateauE *p, CoupE c);
        virtual string typeC();
        virtual void marqueCaseDeplacable(PlateauAffichage *p, short i, short j);
        virtual void marqueCaseEchec(PlateauE *p, short i, short j);
        // GETTEUR
        QString getCheminImage();
        char getCouleur();
        char getType();
        bool getDeplacement();
        // SETTEUR
        void setDeplacement(bool rep);
};

class Pion : public Piece{
    public:
        // CONSTRUCTEUR
        Pion(char t, char c, bool d, QString filename = vide);
        // DESTRUCTEUR
        ~Pion();
        // METHODE OVERRIDE
        short deplacementV(PlateauE *p, CoupE c) override;
        string typeC() override;
        void marqueCaseDeplacable(PlateauAffichage *p, short i, short j) override;
        void marqueCaseEchec(PlateauE *p, short i, short j) override;
};

class Tour : public Piece{
    public:
        // CONSTRUCTEUR
        Tour(char t, char c, bool d, QString filename = vide);
        // DESTRUCTEUR
        ~Tour();
        // METHODE OVERRIDE
        short deplacementV(PlateauE *p, CoupE c) override;
        string typeC() override;
        void marqueCaseDeplacable(PlateauAffichage *p, short i, short j) override;
        void marqueCaseEchec(PlateauE *p, short i, short j) override;
};

class Cavalier : public Piece{
    public:
        // CONSTRUCTEUR
        Cavalier(char t, char c, bool d, QString filename = vide);
        // DESTRUCTEUR
        ~Cavalier();
        // METHODE OVERRIDE
        short deplacementV(PlateauE *p, CoupE c) override;
        string typeC() override;
        void marqueCaseDeplacable(PlateauAffichage *p, short i, short j) override;
        void marqueCaseEchec(PlateauE *p, short i, short j) override;
};

class Fou : public Piece{
    public:
        // CONSTRUCTEUR
        Fou(char t, char c, bool d, QString filename = vide);
        // DESTRUCTEUR
        ~Fou();
        // METHODE OVERRIDE
        short deplacementV (PlateauE *p, CoupE c) override;
        string typeC() override;
        void marqueCaseDeplacable(PlateauAffichage *p, short i, short j) override;
        void marqueCaseEchec(PlateauE *p, short i, short j) override;
};

class Dame : public Piece{
    public:
        // CONSTRUCTEUR
        Dame(char t, char c, bool d, QString filename = vide);
        // DESTRUCTEUR
        ~Dame();
        // METHODE OVERRIDE
        short deplacementV(PlateauE *p, CoupE c) override;
        string typeC() override;
        void marqueCaseDeplacable(PlateauAffichage *p, short i, short j) override;
        void marqueCaseEchec(PlateauE *p, short i, short j) override;
};

class Roi : public Piece{
    public:
        // CONSTRUCTEUR
        Roi(char t, char c, bool d, QString filename = vide);
        // DESTRUCTEUR
        ~Roi();
        // METHODE OVERRIDE
        short deplacementV(PlateauE *p, CoupE c) override;
        string typeC() override;
        void marqueCaseDeplacable(PlateauAffichage *p, short i, short j) override;
        void marqueCaseEchec(PlateauE *p, short i, short j) override;
};

#endif //ECHEC_PIECEE_H
