//
// Created by pierre-louis on 19/05/2020.
//

#include <LancementJeu.h>

/********************************************************/
/**                LANCEMENT JEU                       **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

LancementJeu::LancementJeu(QWidget * parent) : QWidget(parent) {
    this->nom1 = new QLineEdit();
    this->nom2 = new QLineEdit();
    this->form = new QFormLayout();
    this->valide = new QPushButton("VALIDATION", this);
    this->orga = new QVBoxLayout(this);
    this->form->addRow("Nom du joueur 1: ",nom1);
    this->form->addRow("Nom du joueur 2: ",nom2);
    this->orga->addLayout(this->form);
    this->orga->addWidget(this->valide);

    this->show();


    QObject::connect(this->valide,SIGNAL(clicked()),this,SLOT(lancerJeu()));
}

/********** DESTRUCTEUR ***************/

LancementJeu::~LancementJeu() noexcept {}

/*********** METHODE SLOT ***************/

void LancementJeu::lancerJeu() {
    emit envoiJeu(this->nom1->displayText(),this->nom2->displayText());
    this->close();
}