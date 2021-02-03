//
// Created by pierre-louis on 12/05/2020.
//

#ifndef ECHEC_JOUEURE_H
#define ECHEC_JOUEURE_H

#include <QApplication>
#include <QGroupBox>
#include <QLabel>
#include <QHBoxLayout>
#include <iostream>
using namespace std;

class JoueurE : public QGroupBox{
private:
    QLabel *descNom;
    QLabel *choixNom;
    QHBoxLayout *orga;
    char couleur;
    string nom;
public:
    JoueurE(QWidget * parent = Q_NULLPTR);
    ~JoueurE();
    JoueurE(char c, string n, QWidget * parent = Q_NULLPTR);
    string getNom();
    char getCouleur();
    bool setCouleur(char c);
    bool setNom(string s);
};

#endif //ECHEC_JOUEURE_H
