//
// Created by pierre-louis on 19/05/2020.
//

#ifndef ECHEC_AFFICHAGE_LANCEMENJEU_H
#define ECHEC_AFFICHAGE_LANCEMENJEU_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>

class LancementJeu : public QWidget {
    Q_OBJECT
    public:
        // Constructeur
        LancementJeu(QWidget * parent = Q_NULLPTR);
        // Destructeur
        ~LancementJeu();
    signals:
        void envoiJeu(QString, QString);
    protected slots:
        void lancerJeu();
    private:
        QLineEdit *nom1;
        QLineEdit *nom2;
        QFormLayout *form;
    QVBoxLayout *orga;
        QPushButton *valide;
};


#endif //ECHEC_AFFICHAGE_LANCEMENJEU_H
