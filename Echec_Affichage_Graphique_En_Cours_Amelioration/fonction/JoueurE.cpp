//
// Created by pierre-louis on 12/05/2020.
//

#include "../header/JoueurE.h"

/********************************************************/
/**              JoueurE                               **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

JoueurE::JoueurE(QWidget * parent) : QGroupBox(parent){}

JoueurE::JoueurE(char c, string n,QWidget * parent) : QGroupBox(parent) {
    this->choixNom = new QLabel(this);
    this->descNom = new QLabel(this);
    this->orga = new QHBoxLayout(this);
    if( (c=='n') || (c=='b') )
        this->couleur = c;
    this->nom = n;
    if(c == 'b'){
        this->setTitle("Joueur Blanc");
        this->descNom->setText("NOM: ");
        this->descNom->setStyleSheet("color: #2e4daf; font-weight: bold;");
        this->choixNom->setText(QString(this->nom.c_str()));
        this->setStyleSheet("background-color: white; padding: auto;");
    }
    else {
        this->setTitle("Joueur Noir");
        this->descNom->setText("NOM: ");
        this->descNom->setStyleSheet("color: #2e4daf; font-weight: bold;");
        this->choixNom->setText(QString(this->nom.c_str()));
        this->setStyleSheet("background-color: lightgrey; padding: auto;");
    }
    this->orga->addWidget(this->descNom);
    this->orga->addWidget(this->choixNom);
    this->setMaximumHeight(150);
    this->setLayout(this->orga);
    this->setFont(QFont("times",16,16));
}

/********** DESTRUCTEUR ***************/

JoueurE::~JoueurE() {
    /*
    delete &this->nom;
    delete &this->couleur;
     */
}

/*********** GETTEUR ***************/

char JoueurE::getCouleur() {
    return this->couleur;
}

string JoueurE::getNom() {
    return this->nom;
}

/*********** SETTEUR ***************/

bool JoueurE::setCouleur(char c) {
    if(c=='b' || c=='n'){
        this->couleur = c;
        return true;
    }
    return false;
}

bool JoueurE::setNom(string s) {
    this->nom = s;
    return true;
}