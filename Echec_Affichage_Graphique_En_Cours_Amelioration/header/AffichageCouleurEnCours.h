//
// Created by pierre-louis on 20/05/2020.
//

#ifndef ECHEC_AFFICHAGE_AFFICHAGECOULEURENCOURS_H
#define ECHEC_AFFICHAGE_AFFICHAGECOULEURENCOURS_H

#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>

class AffichageCouleurEnCours : public QGroupBox{
private:
    QHBoxLayout *orga;
    QLabel *couleur;
    QLabel *descCoul;
public:
    AffichageCouleurEnCours(QWidget *parent = Q_NULLPTR);
    ~AffichageCouleurEnCours();
    void setTextCouleur(QString s);
};


#endif //ECHEC_AFFICHAGE_AFFICHAGECOULEURENCOURS_H
