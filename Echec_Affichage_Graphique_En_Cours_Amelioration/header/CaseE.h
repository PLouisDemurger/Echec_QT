//
// Created by pierre-louis on 12/05/2020.
//

#ifndef ECHEC_CASEE_H
#define ECHEC_CASEE_H

#include "PieceE.h"
#include <QLabel>
#include <QApplication>
#include <iostream>
using namespace std;

class CaseE{
    protected:
        bool echecN = false;
        bool echecB = false;
        char couleur = 'a';
        Piece *figurine = new Piece();
    public:
        // Constructeur
        CaseE();
        // Destructeur
        ~CaseE();
        CaseE(bool eN, bool eB, char c, Piece *f);
        // Getteur
        char getCouleur() const;
        bool getEchecN() const;
        Piece* getPiece();
        bool getEchecB() const;
        // Setteur
        void setEchecN(bool s);
        void setEchecB(bool s);
        void setPiece(Piece *p);
        // Methode
        void copierCase(CaseE *c);
};

class CaseAffichage : public QLabel, public CaseE{
    Q_OBJECT
    signals:
        void envoieCoordonne(QString, short, short);
    protected:
        void mousePressEvent(QMouseEvent* event);
    private:
        bool selectionnee;
        bool selectionnable;
        short cordX;
        short cordY;
    public:
        // Constructeur
        CaseAffichage(bool eN, bool eB, char c, Piece *f, QWidget *parent = Q_NULLPTR);
        CaseAffichage(bool eN, bool eB, char c, Piece *f, short x, short y, QWidget *parent = Q_NULLPTR);
        // Destructeur
        ~CaseAffichage();
        // Methode
        void initCase();
        void majCase(bool couleur);
        void majCaseDeplacement();
        void marqueCase();
};
#endif //ECHEC_CASEE_H
