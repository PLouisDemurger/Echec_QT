//
// Created by pierre-louis on 20/05/2020.
//

#include <AffichageCouleurEnCours.h>

AffichageCouleurEnCours::AffichageCouleurEnCours(QWidget *parent) :  QGroupBox(parent) {
    this->couleur = new QLabel("");
    this->descCoul = new QLabel("La couleur en cours est ");
    this->descCoul->setStyleSheet("color: #2e4daf; font-weight: bold;");
    this->orga = new QHBoxLayout(this);
    this->orga->addWidget(this->descCoul);
    this->orga->addWidget(this->couleur);
    this->setLayout(this->orga);
    this->setTitle("Couleur En Cours");
    this->setMaximumHeight(150);
}

AffichageCouleurEnCours::~AffichageCouleurEnCours() noexcept {}

void AffichageCouleurEnCours::setTextCouleur(QString s) {
    this->couleur->setText(s);
}
