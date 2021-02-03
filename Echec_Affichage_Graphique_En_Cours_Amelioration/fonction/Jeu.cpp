#include <Jeu.h>
#include <thread>
#include <QtWidgets/QMessageBox>

/********************************************************/
/**                        Jeu                         **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

Jeu::Jeu(QWidget* parent) : QWidget(parent) {
    LancementJeu *lancerJ = new LancementJeu();

    this->couleurJ = true;
    this->plateau = new PlateauAffichage(this);
    this->orgaPageJeu = new QGridLayout(this);
    this->coteJoueur = new QVBoxLayout();
    this->orgaPageJeu->addLayout(this->plateau,0,0);
    this->coupEnCours = new CoupAffichage(-1,-1,-1,-1,this);
    this->setLayout(this->orgaPageJeu);
    this->hide();

    QObject::connect(lancerJ,SIGNAL(envoiJeu(QString,QString)),this,SLOT(recevoirJeu(QString,QString)));
}

Jeu::Jeu(string nom1, string nom2, QWidget *parent) : QWidget(parent) {
    this->affCouleurEC = new AffichageCouleurEnCours(this);
    this->valider = new QPushButton("Valider Coup");
    this->couleurJ = true;
    this->plateau = new PlateauAffichage(this);
    this->orgaPageJeu = new QGridLayout(this);
    this->coteJoueur = new QVBoxLayout();
    this->orgaPageJeu->addLayout(this->plateau,0,0);
    this->coupEnCours = new CoupAffichage(-1,-1,-1,-1,this);
    this->setLayout(this->orgaPageJeu);
    srand(time(NULL));
    int random = rand();
    cout << "La partie va bientôt commencer" << endl;
    if(random%2==0) {
        this->tabJ[0] = new JoueurE('b', nom1);
        this->tabJ[1] = new JoueurE('n', nom2);
        cout << "----------------------------------------------------" << endl;
        cout << "Le joueur blanc est "+nom1 << endl;
        cout << "Le joueur noir est "+nom2 << endl;
        cout << "----------------------------------------------------" << endl << endl;
    }
    else{
        this->tabJ[1] = new JoueurE('n', nom1);
        this->tabJ[0] = new JoueurE('b', nom2);
        cout << "----------------------------------------------------" << endl;
        cout << "Le joueur blanc est "+nom2 << endl;
        cout << "Le joueur noir est "+nom1 << endl;
        cout << "----------------------------------------------------" << endl << endl;
    }

    this->affCouleurEC->setTextCouleur("Blanc");

    for(short i=0 ; i<8 ; i++){
        for(short j=0 ; j<8 ; j++){
            QObject::connect(this->plateau->getCaseA(i,j),SIGNAL(envoieCoordonne(QString,short,short)),this->coupEnCours,SLOT(traitementCoup(QString,short,short)));
            QObject::connect(this->coupEnCours,SIGNAL(selectionnable(bool)),this->plateau->getCaseA(i,j),SLOT(changerSelection(bool)));
        }
    }
}

/********** DESTRUCTEUR ***************/

Jeu::~Jeu() noexcept {}

/*********** GETTEUR ***************/

PlateauE * Jeu::getPlateau() {return this->plateau;}

JoueurE ** Jeu::getTabJ() {return this->tabJ;}

bool Jeu::getCouleurJ() {return this->couleurJ;}

CoupE* Jeu::getCoupEnCours() {return this->coupEnCours;}

/*********** METHODE SLOT ***************/

void Jeu::jouerCoupVerifSlot() {
    QString message;
    string m;
    CoupE *c = this->coupEnCours;
    bool rep;
    if(this->couleurJ){
        rep = (this->plateau->getCaseA(this->coupEnCours->getYDep(),this->coupEnCours->getXDep())->getPiece()->getCouleur() == 'b');
    }
    else{
        rep = (this->plateau->getCaseA(this->coupEnCours->getYDep(),this->coupEnCours->getXDep())->getPiece()->getCouleur() == 'n');
    }
    if( (this->coupEnCours->getXDest() == -1) || (this->coupEnCours->getYDest() == -1) || (this->coupEnCours->getXDep() == -1) || (this->coupEnCours->getYDep() == -1) ){
        QMessageBox::warning(this, "COUP INVALIDE", "Veuillez saisir un coup !",Q_NULLPTR,Q_NULLPTR);
    }
    else if(!rep){
        QMessageBox::warning(this, "COUP INVALIDE", "Veuillez saisir un pion de votre couleur !",Q_NULLPTR,Q_NULLPTR);
    }
    else{
        rep = this->plateau->jouerCoupVerifSauv(this->couleurJ,*c);

        if(!rep){
            QMessageBox::warning(this, "COUP INVALIDE", "Attention, vous devez saisir un coup valide !",Q_NULLPTR,Q_NULLPTR);
        }
        else{
            this->couleurJ = !this->couleurJ;
            this->plateau->tournerPlateauAff(this->couleurJ);
            if(this->couleurJ)
                this->affCouleurEC->setTextCouleur("Blanc");
            else
                this->affCouleurEC->setTextCouleur("Noir");
        }
    }
    this->plateau->setDerCoup(CoupE(this->coupEnCours->getXDep(),this->coupEnCours->getYDep(),this->coupEnCours->getXDest(),this->coupEnCours->getYDest()));
    this->coupEnCours->initCoup();
    //this->plateau->affichageEchiquier();
    this->plateau->initPlateau();
    this->plateau->majPlateau(this->couleurJ);
    this->plateau->majEchec();
    if(this->plateau->echecEtMat(this->couleurJ)){
        if(!this->couleurJ)
            m = "Le joueur Blanc ("+this->tabJ[0]->getNom()+") a gagné :)\n"+"Le joueur Noir ("+this->tabJ[1]->getNom()+") a perdu :(";
        else
            m = "Le joueur Noir ("+this->tabJ[1]->getNom()+") a gagné :)\n"+"Le joueur Blanc ("+this->tabJ[0]->getNom()+") a perdu :(";
        message = QString(m.c_str());
        QMessageBox::information(this,"FIN DE PARTIE",message,QMessageBox::Ok);
        this->close();
    }

}

void Jeu::traitementSelection(bool selectOrdre, short x, short y) {
    if(selectOrdre){
        if(x!=-1 || y!=-1){
            this->plateau->initPlateau();
            this->plateau->getCaseA(y,x)->marqueCase();
            this->plateau->marqueCaseAccessible(y,x);
        }else{
            this->plateau->initPlateau();
            this->plateau->majPlateau(this->couleurJ);
        }
    }
    else{
        if(x!=-1 || y!=-1){
            this->plateau->initPlateau();
            this->plateau->getCaseA(y,x)->marqueCase();
            this->plateau->getCaseA(this->getCoupEnCours()->getYDep(),this->getCoupEnCours()->getXDep())->marqueCase();
        }else{
            this->plateau->initPlateau();
            this->plateau->getCaseA(this->getCoupEnCours()->getYDep(),this->getCoupEnCours()->getXDep())->marqueCase();
            this->plateau->marqueCaseAccessible(this->getCoupEnCours()->getYDep(),this->getCoupEnCours()->getXDep());
        }
    }
}

void Jeu::recevoirJeu(QString nom1, QString nom2) {
    srand(time(NULL));
    int random = rand();
    cout << "La partie va bientôt commencer" << endl;
    if(random%2==0) {
        this->tabJ[0] = new JoueurE('b', nom1.toStdString(),this);
        this->tabJ[1] = new JoueurE('n', nom2.toStdString(),this);
        cout << "----------------------------------------------------" << endl;
        cout << "Le joueur blanc est "+nom1.toStdString() << endl;
        cout << "Le joueur noir est "+nom2.toStdString() << endl;
        cout << "----------------------------------------------------" << endl << endl;
    }
    else{
        this->tabJ[1] = new JoueurE('n', nom1.toStdString(),this);
        this->tabJ[0] = new JoueurE('b', nom2.toStdString(),this);
        cout << "----------------------------------------------------" << endl;
        cout << "Le joueur blanc est "+nom2.toStdString() << endl;
        cout << "Le joueur noir est "+nom1.toStdString() << endl;
        cout << "----------------------------------------------------" << endl << endl;
    }
    this->valider = new QPushButton("Valider Coup");
    this->affCouleurEC = new AffichageCouleurEnCours(this);
    this->coteJoueur->addWidget(this->tabJ[0]);
    this->coteJoueur->addWidget(this->tabJ[1]);
    this->coteJoueur->addWidget(this->coupEnCours);
    this->coteJoueur->addWidget(this->affCouleurEC);
    this->coteJoueur->addWidget(this->valider);
    this->orgaPageJeu->addLayout(this->coteJoueur,0,15);

    this->affCouleurEC->setTextCouleur("Blanc");

    this->plateau->initPlateau();
    this->plateau->majPlateau(this->couleurJ);
    
    for(short i=0 ; i<8 ; i++){
        for(short j=0 ; j<8 ; j++){
            QObject::connect(this->plateau->getCaseA(i,j),SIGNAL(envoieCoordonne(QString,short,short)),this->coupEnCours,SLOT(traitementCoup(QString,short,short)));
            QObject::connect(this->coupEnCours,SIGNAL(envoieMajSelection(bool,short,short)),this,SLOT(traitementSelection(bool,short,short)));
        }
    }

    QObject::connect(this->valider,SIGNAL(clicked()),this,SLOT(jouerCoupVerifSlot()));
    this->show();
}

/*********** METHODE ***************/

void Jeu::manuel() {
    setTerm2(light_red_Terminal)
    cout << endl << "\tMANUEL D'UTILISATION" << endl << endl << endl;

    cout << "-> SAISIR UN COUP: " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "Exemple de saisie pour un coup:" << endl;
    cout << "Coordonnée début: b8" << endl;
    cout << "Coordonnée fin: c6" << endl;
    cout << "ATENTION LES LETTRES DOIVENT ÊTRE EN MINUSCULE" << endl;
    cout << "----------------------------------------------------" << endl << endl;

    cout << "-> FONCTIONNEMENT DU JEU: " << endl;
    cout << "----------------------------------------------------" << endl;
    cout << "La couleur du Joueur est attribué aléatoirement" << endl;
    cout << "Les joueurs doivent saisir leur coup tour par tour" << endl;
    cout << "La partie s'arrête automatiquement dès qu'il y a echec et math" << endl;
    cout << "----------------------------------------------------" << endl << endl;
}

