//
// Created by pierre-louis on 14/05/2020.
//

#ifndef ECHEC_JEU_H
#define ECHEC_JEU_H

#include <PlateauE.h>
#include <LancementJeu.h>
#include <AffichageCouleurEnCours.h>
#include <QtCore>
#include <QApplication>
#include <QPushButton>

typedef void * (*pf_void)(void *);

class Jeu : public QWidget{
    Q_OBJECT
    private:
        JoueurE * tabJ[2];
        std::thread *jeu;
        bool couleurJ; // true si blanc sinon false
        PlateauAffichage *plateau;
        CoupAffichage *coupEnCours;
        QGridLayout *orgaPageJeu;
        QVBoxLayout *coteJoueur;
        QPushButton *valider;
        AffichageCouleurEnCours *affCouleurEC;
    protected slots:
        void jouerCoupVerifSlot();
        void traitementSelection(bool, short, short);
        void recevoirJeu(QString, QString);
    public:
        // Constructeur
        Jeu(QWidget* parent = Q_NULLPTR);
        Jeu(string nom1, string nom2, QWidget* parent = Q_NULLPTR);
        // Destructeur
        ~Jeu();
        // Getteur
        CoupE *getCoupEnCours();
        PlateauE* getPlateau();
        bool getCouleurJ();
        JoueurE** getTabJ();
        // Methode
        void jouerCoup();
        void manuel();
        void saisirCoupPoppup();
        void saisirCoupSelection();
};


#endif //ECHEC_JEU_H
