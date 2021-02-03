//
// Created by pierre-louis on 19/05/2020.
//

#ifndef ECHEC_COUPE_H
#define ECHEC_COUPE_H

#include <QGroupBox>
#include <QLabel>
#include <QGridLayout>
#include <iostream>


class CoupE{
protected:
    short xDest = -1;
    short yDest = -1;
    short xDep = -1;
    short yDep = -1;
public:
    CoupE();
    ~CoupE();
    CoupE(short x1, short y1, short x2, short y2);
    void afficherCoup();
    short getXDest();
    short getYDest();
    short getXDep();
    short getYDep();
};

class CoupAffichage : public QGroupBox, public CoupE{
Q_OBJECT
signals:
    void envoieMajSelection(bool, short, short);
private:
    QGridLayout *orga;
    QLabel *descDep;
    QLabel *descDest;
    QLabel *choixDep;
    QLabel *choixDest;
    bool coup1Saisie;
    bool coup2Saisie;
protected slots:
    void traitementCoup(QString, short, short);
public:
    ~CoupAffichage();
    CoupAffichage(QWidget *parent = Q_NULLPTR);
    CoupAffichage(short x1, short y1, short x2, short y2, QWidget *parent = Q_NULLPTR);
    void initCoup();
};



#endif //ECHEC_COUPE_H
