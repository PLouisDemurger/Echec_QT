//
// Created by pierre-louis on 19/05/2020.
//

#include <CoupE.h>

/********************************************************/
/**              CoupE                                 **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

CoupE::CoupE(){
    this->xDep = -1;
    this->yDep = -1;
    this->xDest = -1;
    this->yDest = -1;
}

CoupE::CoupE(short x1, short y1, short x2, short y2) {
    this->xDep = x1;
    this->yDep = y1;
    this->xDest = x2;
    this->yDest = y2;
}

/********** DESTRUCTEUR ***************/

CoupE::~CoupE() {}

/*********** GETTEUR ***************/

short CoupE::getXDep() {
    return this->xDep;
}

short CoupE::getYDep() {
    return this->yDep;
}

short CoupE::getXDest() {
    return this->xDest;
}

short CoupE::getYDest() {
    return this->yDest;
}


/********************************************************/
/**              CoupAffichage                         **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

CoupAffichage::CoupAffichage(short x1, short y1, short x2, short y2, QWidget *parent) : CoupE(x1,y1,x2,y2), QGroupBox(parent){
    this->setTitle("Coup en Cours");
    this->descDep = new QLabel(this);
    this->descDep->setText("Coordonnée début coup: ");
    this->choixDep = new QLabel(this);
    this->descDest = new QLabel(this);
    this->descDest->setText("Coordonnée fin coup: ");
    this->choixDest = new QLabel(this);
    this->orga = new QGridLayout(this);
    this->coup1Saisie = false;
    this->coup2Saisie = false;


    this->descDep->setStyleSheet("color: #2e4daf; font-weight: bold;");
    this->descDest->setStyleSheet("color: #2e4daf; font-weight: bold;");

    this->orga->addWidget(this->descDep,0,0);
    this->orga->addWidget(this->descDest,1,0);
    this->orga->addWidget(this->choixDep,0,1);
    this->orga->addWidget(this->choixDest,1,1);
    this->setStyleSheet("background-color: goldenrod; padding: auto;");
    this->setLayout(this->orga);
    this->setMaximumHeight(300);
}

CoupAffichage::CoupAffichage(QWidget *parent) : CoupE(), QGroupBox(parent){
    this->setTitle("Coup en Cours");
    this->descDep = new QLabel(this);
    this->descDep->setText("Coordonnée début coup: ");
    this->choixDep = new QLabel(this);
    this->descDest = new QLabel(this);
    this->descDest->setText("Coordonnée fin coup: ");
    this->choixDest = new QLabel(this);
    this->orga = new QGridLayout(this);
    this->coup1Saisie = false;
    this->coup2Saisie = false;


    this->descDep->setStyleSheet("color: #2e4daf; font-weight: bold;");
    this->descDest->setStyleSheet("color: #2e4daf; font-weight: bold;");

    this->orga->addWidget(this->descDep,0,0);
    this->orga->addWidget(this->descDest,1,0);
    this->orga->addWidget(this->choixDep,0,1);
    this->orga->addWidget(this->choixDest,1,1);
    this->setStyleSheet("background-color: goldenrod; padding: auto;");
    this->setLayout(this->orga);
    this->setMaximumHeight(300);
}

/********** DESTRUCTEUR ***************/

CoupAffichage::~CoupAffichage() noexcept {}

/*********** METHODE SLOT ***************/

void CoupAffichage::traitementCoup(QString s, short x, short y) {
    bool egal1;
    bool egal2;

    egal1 = (s == this->choixDep->text());
    egal2 = (s == this->choixDest->text()) ;
    if ( (!this->coup1Saisie || egal1)  && (s != this->choixDest->text()) ){
        this->coup1Saisie = !this->coup1Saisie;
        if(!egal1){
            this->choixDep->setText(s);
            this->xDep = x;
            this->yDep = y;
        }
        else{
            this->coup2Saisie = false;
            this->choixDep->setText("");
            this->choixDest->setText("");
            this->xDep = -1;
            this->yDep = -1;
            this->xDest = -1;
            this->yDest = -1;
        }
        emit envoieMajSelection(true,this->xDep,this->yDep);
    }
    else if( (!this->coup2Saisie || egal2) && (s != this->choixDep->text()) ){
        this->coup2Saisie = !this->coup2Saisie;
        if(!egal2){
            this->choixDest->setText(s);
            this->xDest = x;
            this->yDest = y;
        }
        else{
            this->choixDest->setText("");
            this->xDest = -1;
            this->yDest = -1;
        }
        emit envoieMajSelection(false,this->xDest,this->yDest);
    }
    //std::cout << "choixDep: " << this->choixDep->text().toStdString() << std::endl;
    //std::cout << "choixDest: " << this->choixDest->text().toStdString()  << std::endl;
}

/*********** METHODE ***************/

void CoupAffichage::initCoup() {
    this->choixDep->setText("");
    this->choixDest->setText("");
    this->coup2Saisie = this->coup1Saisie = false;
    this->xDest = this->yDest = this->yDep = this->xDep = -1;
}