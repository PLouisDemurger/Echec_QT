#include <CaseE.h>

/********************************************************/
/**              CaseE                                 **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

CaseE::CaseE() {
    this->echecB = false;
    this->echecN = false;
    this->couleur = 'a';
    this->figurine = new Piece();
}

CaseE::CaseE(bool eN, bool eB, char c, Piece *f) {
    this->echecB = eB;
    this->echecN = eN;
    this->couleur = c;
    this->figurine = f;
}

/*********** DESTRUCTEUR ***************/

CaseE::~CaseE() noexcept {
    delete this->figurine;
}

/*********** GETTEUR ***************/

char CaseE::getCouleur() const{
    return this->couleur;
}

bool CaseE::getEchecB() const{
    return this->echecB;
}

bool CaseE::getEchecN() const{
    return this->echecN;
}

Piece* CaseE::getPiece(){
    return this->figurine;
}

/*********** SETTEUR ***************/

void CaseE::setEchecB(bool s) {
    this->echecB = s;
}

void CaseE::setEchecN(bool s) {
    this->echecN = s;
}

void CaseE::setPiece(Piece *p) {
    this->figurine = p;
}

/*********** METHODE ***************/

void CaseE::copierCase(CaseE *c) {
    if(c != nullptr){
        this->couleur = c->getCouleur();
        //cout << endl << this->figurine->typeC() << endl;
        this->figurine = c->getPiece();
        //cout << endl << this->figurine->typeC() << endl;
        this->echecN = c->getEchecN();
        this->echecB = c->getEchecB();
    }
}

/********************************************************/
/**              CaseAffichage                         **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

CaseAffichage::CaseAffichage(bool eN, bool eB, char c, Piece *f, QWidget *parent) : QLabel(parent), CaseE(eN,eB,c,f) {
    this->selectionnee = false;
    if(c == 'b'){
        this->setStyleSheet("background-color: white; padding: auto; border-style: solid; border-width: 2px;");
    }
    else{
        this->setStyleSheet("background-color: grey; padding: auto; border-style: solid; border-width: 2px;");
    }
    this->setPixmap(QPixmap::fromImage(QImage(this->getPiece()->getCheminImage()).scaled(QSize(25,25),Qt::IgnoreAspectRatio)));
}

CaseAffichage::CaseAffichage(bool eN, bool eB, char c, Piece *f, short x, short y, QWidget *parent) : QLabel(parent), CaseE(eN,eB,c,f) {
    this->selectionnable = true;
    this->selectionnee = false;
    this->cordX = x;
    this->cordY = y;
    if(c == 'b'){
        this->setStyleSheet("background-color: white; padding: auto; border-style: solid; border-width: 2px;");
    }
    else{
        this->setStyleSheet("background-color: grey; padding: auto; border-style: solid; border-width: 2px;");
    }
    this->setPixmap(QPixmap::fromImage(QImage(this->getPiece()->getCheminImage()).scaled(QSize(25,25),Qt::IgnoreAspectRatio)));
}

/*********** DESTRUCTEUR ***************/

CaseAffichage::~CaseAffichage() noexcept {}

/*********** METHODE EVENT ***************/

void CaseAffichage::mousePressEvent(QMouseEvent *event) {
    char c;
    string coor = "";
    c = 'A'+this->cordX;
    coor += c;
    c = 49+this->cordY;
    coor += c;
    if(selectionnee || selectionnable){
        //cout << "Avant envoie: "+coor << endl;
        emit envoieCoordonne(QString(coor.c_str()),this->cordX, this->cordY);
    }
}

/*********** METHODE ***************/

void CaseAffichage::initCase(){
    this->selectionnable = false;
    this->selectionnee = false;
    if(this->couleur == 'b'){
        this->setStyleSheet("background-color: white; padding: auto; border-style: solid; border-width: 2px;");
    }
    else{
        this->setStyleSheet("background-color: grey; padding: auto; border-style: solid; border-width: 2px;");
    }
}

void CaseAffichage::majCase(bool couleur) {
    char c;
    if(couleur)
        c = 'b';
    else
        c = 'n';
    if(this->getPiece()->getCouleur() == c)
        this->selectionnable = true;
    this->selectionnee = false;
    if(this->couleur == 'b'){
        this->setStyleSheet("background-color: white; padding: auto; border-style: solid; border-width: 2px;");
    }
    else{
        this->setStyleSheet("background-color: grey; padding: auto; border-style: solid; border-width: 2px;");
    }
    this->setPixmap(QPixmap::fromImage(this->getPiece()->scaled(QSize(25,25),Qt::IgnoreAspectRatio)));
}

void CaseAffichage::majCaseDeplacement() {
    this->selectionnable = true;
    if(this->couleur == 'b')
        this->setStyleSheet("background-color: white; border-color: #21d50b; padding: auto; border-style: solid; border-width: 2px;");
    else
        this->setStyleSheet("background-color: lightgrey; border-color: #21d50b; padding: auto; border-style: solid; border-width: 2px;");
}

void CaseAffichage::marqueCase(){
    this->selectionnee = true;
    this->selectionnable = false;
    if(this->couleur == 'b')
        this->setStyleSheet("background-color: white; border-color: red; padding: auto; border-style: solid; border-width: 2px;");
    else
        this->setStyleSheet("background-color: grey; border-color: red; padding: auto; border-style: solid; border-width: 2px;");
}

//QImage(this->getPiece()->getCheminImage()).