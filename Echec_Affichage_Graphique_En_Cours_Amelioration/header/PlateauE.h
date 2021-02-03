//
// Created by pierre-louis on 12/05/2020.
//

#ifndef ECHEC_PLATEAUE_H
#define ECHEC_PLATEAUE_H

#include <CaseE.h>
#include <JoueurE.h>
#include <CoupE.h>
#include <vector>
#include <QImage>
#include <QLayout>
#include <QApplication>

#define setTerm2(param)  { printf("%s", param); fflush(stdout); }
#define setBG2(param)  { printf("%s", param); fflush(stdout); }
#define resetTerm2()	{ printf("%s",none_Terminal); fflush(stdout); }

#define    none_Terminal          "\033[0m"
#define    blue_Terminal          "\033[0;34m"
#define    light_red_Terminal     "\033[1;31m"
#define    brown_Terminal         "\033[0;33m"
#define    BG_N_Terminal          "\033[0;40m"
#define    BG_B_Terminal          "\033[0;47m"

class PlateauE{
    protected:
        // Attribut
        CaseE ***echiquier;
        CoupE derCoup;
        vector<Piece> piecePBlanc;
        vector<Piece> piecePNoir;
        // Methode
        short connaitreFront(bool couleur, CoupE c);
        const char* ecrirePieceT(Piece *piece);
        Piece * promotion(char couleur);
        short trouvPieceCEchec(bool couleur, const short X, const short Y);
    public:
        // Methode
        void affichageEchiquier();
        // Methode virtuelle
        virtual void copiePlateau(PlateauE *p);
        virtual bool deplacerPiece(CoupE c);
        virtual bool echecEtMat(bool cJ);
        virtual bool echecRoiJoueurActif(bool c);
        virtual bool jouerCoupVerif(bool cJ, CoupE c);
        virtual bool jouerCoupVerifMat(bool cJ, CoupE c);
        virtual bool jouerCoupVerifSauv(bool cJ, CoupE c);
        virtual void majEchec();
        // Getteur Setteur
        virtual CaseE * getCaseE(short i, short j);
        virtual CaseE *** getEchiquier();
        CoupE getDerCoup();
        void setDerCoup(CoupE e);
        // Constructeur
        PlateauE();
        // Destructeur
        ~PlateauE();
};

class PlateauAffichage : public PlateauE, public QGridLayout{
    private:
        QLabel *lettre[8];
        QLabel *chiffre[8];
        CaseAffichage ***echiquierAff;
    public:
        PlateauAffichage(QWidget* parent);
        ~PlateauAffichage();
        CaseAffichage * getCaseA(short i, short j);
        CaseE *** getEchiquier() override ;
        CaseE * getCaseE(short i, short j) override ;
        void copiePlateau(PlateauE *p) override;
        bool deplacerPiece(CoupE c) override;
        bool echecEtMat(bool cJ) override;
        bool echecRoiJoueurActif(bool c) override;
        void initPlateau();
        bool jouerCoupVerif(bool cJ, CoupE c) override;
        bool jouerCoupVerifMat(bool cJ, CoupE c) override;
        bool jouerCoupVerifSauv(bool cJ, CoupE c) override;
        void majEchec() override;
        void majPlateau(bool cJ);
        void marqueCaseAccessible(short i, short j);
        void tournerPlateauAff(bool couleur);
        Piece * promotionAff(char couleur);
};


#endif //ECHEC_PLATEAUE_H
