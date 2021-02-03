#include <PlateauE.h>

/********************************************************/
/**              Piece                                 **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

Piece::Piece() : QImage(){}

Piece::Piece(QString filename) : QImage(filename){
    this->cheminImage = filename;
}

Piece::Piece(char t, char c, bool d, QString filename) : QImage(filename){
    this->cheminImage = filename;
    this->type = t;
    this->couleur = c;
    this->deplacement = d;
}

/*********** DESTRUCTEUR ***************/

Piece::~Piece() noexcept {}

/*********** GETTEUR ***************/

char Piece::getCouleur() {return this->couleur;}

char Piece::getType() {return this->type;}

bool Piece::getDeplacement() {return this->deplacement;}

QString Piece::getCheminImage() {return this->cheminImage;}

/*********** SETTEUR ***************/

void Piece::setDeplacement(bool rep) {this->deplacement = rep;}

/*********** METHODE A OVERRIDE ***************/

string Piece::typeC() {return "vide";}

short Piece::deplacementV(PlateauE *p, CoupE c) { return 0;}

void Piece::marqueCaseDeplacable(PlateauAffichage *p, short i, short j) {}

void Piece::marqueCaseEchec(PlateauE *p, short i, short j) {}

/********************************************************/
/**              Pion                                  **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

Pion::Pion(char t, char c, bool d, QString filename) : Piece(t,c,d,filename){}

/*********** DESTRUCTEUR ***************/

Pion::~Pion() noexcept {}

/*********** METHODE OVERRIDE ***************/

string Pion::typeC() {return "pion";}

short Pion::deplacementV(PlateauE *p, CoupE c) {
    short derCase = 1;
    switch (this->couleur){
        case 'n' :
            // Promotion
            if(c.getYDest() == 7)
                derCase = 7;
            // Prise en passant
            if(  ((c.getXDest()-1 == c.getXDep()) || (c.getXDest()+1 == c.getXDep())) && ((c.getYDest()-c.getYDep()) == 1) &&
                 (fabs(p->getDerCoup().getYDep()-p->getDerCoup().getYDest()) == 2) &&
                 (p->getEchiquier()[p->getDerCoup().getYDest()][p->getDerCoup().getXDest()]->getPiece()->getType() == 'p') &&
                 ((p->getDerCoup().getXDest()-1 == c.getXDep()) || (p->getDerCoup().getXDest()+1 == c.getXDep())) )
                return 4;
            // Deplacement double
            if( !this->getDeplacement() && (c.getXDest() == c.getXDep()) && ((c.getYDest() - c.getYDep()) == 2)
                && (p->getEchiquier()[c.getYDest()-1][c.getXDest()]->getPiece()->getType() == 'v')
                && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getType() == 'v') )
                return 1;
                // Deplacement simple
            else if( (c.getXDest() == c.getXDep()) && ((c.getYDest()-c.getYDep()) == 1)
                     && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getType() == 'v'))
                return derCase;
                // Prise
            else if( ( (c.getXDest()-1 == c.getXDep()) || (c.getXDest()+1 == c.getXDep()) )
                     && ((c.getYDest()-c.getYDep()) == 1)
                     && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getCouleur() == 'b'))
                return derCase+1;
            return 0;
        case 'b' :
            // Promotion
            if(c.getYDest() == 0)
                derCase = 7;
            // Prise en passant
            if(  ((c.getXDest()-1 == c.getXDep()) || (c.getXDest()+1 == c.getXDep())) && ((c.getYDest()-c.getYDep()) == -1) &&
                 (fabs(p->getDerCoup().getYDep()-p->getDerCoup().getYDest()) == 2) &&
                 (p->getEchiquier()[p->getDerCoup().getYDest()][p->getDerCoup().getXDest()]->getPiece()->getType() == 'p') &&
                 ((p->getDerCoup().getXDest()-1 == c.getXDep()) || (p->getDerCoup().getXDest()+1 == c.getXDep())))
                return 3;
            // Deplacement double
            if( !this->getDeplacement() && (c.getXDep() == c.getXDest()) && ((c.getYDest()-c.getYDep()) == -2)
                && (p->getEchiquier()[c.getYDep()-1][c.getXDep()]->getPiece()->getType() == 'v')
                && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getType() == 'v') )
                return 1;
                // Deplacement simple
            else if( (c.getXDest() == c.getXDep()) && ((c.getYDest()-c.getYDep()) == -1)
                     && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getType() == 'v'))
                return derCase;
                // Prise
            else if( ( (c.getXDest()-1 == c.getXDep()) || (c.getXDest()+1 == c.getXDep()) )
                     && ((c.getYDest()-c.getYDep()) == -1)
                     && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getCouleur() == 'n'))
                return derCase+1;
            return 0;
        case 'v' :
            return 0;
    }
    return true;
}

void Pion::marqueCaseDeplacable(PlateauAffichage *p, short i, short j) {
    switch (this->getCouleur()) {
        case 'b':
            if(i!=0){
                if(!this->getDeplacement() && p->getCaseA(i-1,j)->getPiece()->getType() == 'v')
                    if(p->getCaseA(i-2,j)->getPiece()->getType() == 'v')
                        p->getCaseA(i-2,j)->majCaseDeplacement();
                if(p->getCaseA(i-1,j)->getPiece()->getType() == 'v')
                    p->getCaseA(i-1,j)->majCaseDeplacement();
                if(j!=0){
                    if(p->getCaseA(i-1,j-1)->getPiece()->getCouleur() == 'n')
                        p->getCaseA(i-1,j-1)->majCaseDeplacement();
                }
                if(j!=7){
                    if(p->getCaseA(i-1,j+1)->getPiece()->getCouleur() == 'n')
                        p->getCaseA(i-1,j+1)->majCaseDeplacement();
                }
            }
            if(i==3 && ((p->getDerCoup().getXDep()-1 == j) || (p->getDerCoup().getXDep()+1 == j))
                && (fabs(p->getDerCoup().getYDep()-p->getDerCoup().getYDest()) == 2) )
                p->getCaseA(p->getDerCoup().getYDep()+1,p->getDerCoup().getXDep())->majCaseDeplacement();
            break;
        case 'n':
            if(i!=7){
                if(!this->getDeplacement() && p->getCaseA(i+1,j)->getPiece()->getType() == 'v')
                    if(p->getCaseA(i+2,j)->getPiece()->getType() == 'v')
                        p->getCaseA(i+2,j)->majCaseDeplacement();
                if(p->getCaseA(i+1,j)->getPiece()->getType() == 'v')
                    p->getCaseA(i+1,j)->majCaseDeplacement();
                if(j!=0){
                    if(p->getCaseA(i+1,j-1)->getPiece()->getCouleur() == 'b')
                        p->getCaseA(i+1,j-1)->majCaseDeplacement();
                }
                if(j!=7){
                    if(p->getCaseA(i+1,j+1)->getPiece()->getCouleur() == 'b')
                        p->getCaseA(i+1,j+1)->majCaseDeplacement();
                }
            }
            if(i==4 && ((p->getDerCoup().getXDep()-1 == j) || (p->getDerCoup().getXDep()+1 == j)) && (fabs(p->getDerCoup().getYDep()-p->getDerCoup().getYDest()) == 2) )
                p->getCaseA(p->getDerCoup().getYDep()-1,p->getDerCoup().getXDep())->majCaseDeplacement();
            break;
        default:
            break;
    }
}

void Pion::marqueCaseEchec(PlateauE *p, short i, short j) {
    switch (this->getCouleur()) {
        case 'b':
            if(i!=0){
                if(j == 0)
                    p->getCaseE(i-1,j+1)->setEchecN(true);
                else if(j == 7)
                    p->getCaseE(i-1,j-1)->setEchecN(true);
                else{
                    p->getCaseE(i-1,j+1)->setEchecN(true);
                    p->getCaseE(i-1,j-1)->setEchecN(true);
                }
            }
            break;
        case 'n':
            if(i!=0){
                if(j == 0)
                    p->getCaseE(i+1,j+1)->setEchecB(true);
                else if(j == 7)
                    p->getCaseE(i+1,j-1)->setEchecB(true);
                else{
                    p->getCaseE(i+1,j+1)->setEchecB(true);
                    p->getCaseE(i+1,j-1)->setEchecB(true);
                }
            }
            break;
        default:
            break;
    }
}

/********************************************************/
/**              Tour                                  **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

Tour::Tour(char t, char c, bool d, QString filename) : Piece(t,c,d,filename) {}

/*********** DESTRUCTEUR ***************/

Tour::~Tour() noexcept {}

/*********** METHODE OVERRIDE ***************/

string Tour::typeC() {return "tour";}

short Tour::deplacementV(PlateauE *p, CoupE c) {
    bool pion =false; // voir si il y a un pion dans la zone de déplacement, 1 -> il n'y a pas de pion, 0 -> il y a un pion
    if( (c.getXDest() == c.getXDep()) && (c.getYDep() != c.getYDest()) ){
        // Verification que le chemin soit clair
        if( (c.getYDest()-c.getYDep()) > 0 ){
            for (short i=1; i <= (fabs(c.getYDest()-c.getYDep())-1); i++){
                if(p->getEchiquier()[c.getYDep()+i][c.getXDep()]->getPiece()->getType() != 'v')
                    pion = true;
            }
        } else{
            for (short i=1; i <= (fabs(c.getYDest()-c.getYDep())-1); i++){
                if(p->getEchiquier()[c.getYDep()-i][c.getXDep()]->getPiece()->getType() != 'v')
                    pion = true;
            }
        }
        // La tour avance sans manger de piece
        if(!pion && ( p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getType() ==  'v') )
            return 1;
            // La tour avance en mangeant une piece
        else if(!pion && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getCouleur() !=  this->getCouleur()))
            return 2;
    }
    else if ( (c.getYDep() == c.getYDest()) && (c.getXDep() != c.getXDest()) ){
        // Verification que le chemin soit clair
        if( (c.getXDest()-c.getXDep()) > 0 ){
            for (short i=1; i <= (fabs(c.getXDest()-c.getXDep())-1); i++){
                if(p->getEchiquier()[c.getYDep()][c.getXDep()+i]->getPiece()->getType() != 'v')
                    pion = true;
            }
        } else{
            for (short i=1; i <= (fabs(c.getXDest()-c.getXDep())-1); i++){
                if(p->getEchiquier()[c.getYDep()][c.getXDep()-i]->getPiece()->getType() != 'v')
                    pion = true;
            }
        }
        // La tour avance sans manger de piece
        if(!pion && ( p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getType() ==  'v') )
            return 1;
            // La tour avance en mangeant une piece
        else if(!pion && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getCouleur() !=  this->getCouleur()))
            return 2;
    }
    return 0;
}

void Tour::marqueCaseDeplacable(PlateauAffichage *p, short i, short j) {
    int depX, depY;

    if(i != 7){
        depX = j;
        depY = i;
        do{
            depY++;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                default:
                    return;
            }
        }while(depY < 7 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(j != 0){
        depX = j;
        depY = i;
        do{
            depX--;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                default:
                    return;
            }
        }while(depX > 0 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(j != 7){
        depX = j;
        depY = i;
        do{
            depX++;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                default:
                    return;
            }
        }while(depX < 7 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i!=0){
        depX = j;
        depY = i;
        do{
            depY--;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                default:
                    return;
            }
        }while(depY > 0 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }
}

void Tour::marqueCaseEchec(PlateauE *p, short i, short j) {
    int depX, depY;

    if(i != 7){
        depX = j;
        depY = i;
        do{
            depY++;
            switch (this->couleur) {
                case 'b':
                    p->getCaseE(depY,depX)->setEchecN(true);
                    break;
                case 'n':
                    p->getCaseE(depY,depX)->setEchecB(true);
                    break;
                default:
                    return;
            }
        }while(depY < 7 && p->getCaseE(depY,depX)->getPiece()->getType() == 'v');
    }

    if(j != 0){
        depX = j;
        depY = i;
        do{
            depX--;
            switch (this->couleur) {
                case 'b':
                    p->getCaseE(depY,depX)->setEchecN(true);
                    break;
                case 'n':
                    p->getCaseE(depY,depX)->setEchecB(true);
                    break;
                default:
                    return;
            }
        }while(depX > 0 && p->getCaseE(depY,depX)->getPiece()->getType() == 'v');
    }

    if(j != 7){
        depX = j;
        depY = i;
        do{
            depX++;
            switch (this->couleur) {
                case 'b':
                    p->getCaseE(depY,depX)->setEchecN(true);
                    break;
                case 'n':
                    p->getCaseE(depY,depX)->setEchecB(true);
                    break;
                default:
                    return;
            }
        }while(depX < 7 && p->getCaseE(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i!=0){
        depX = j;
        depY = i;
        do{
            depY--;
            switch (this->couleur) {
                case 'b':
                    p->getCaseE(depY,depX)->setEchecN(true);
                    break;
                case 'n':
                    p->getCaseE(depY,depX)->setEchecB(true);
                    break;
                default:
                    return;
            }
        }while(depY > 0 && p->getCaseE(depY,depX)->getPiece()->getType() == 'v');
    }
}

/********************************************************/
/**              Cavalier                              **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

Cavalier::Cavalier(char t, char c, bool d, QString filename) : Piece(t,c,d,filename) {}

/*********** DESTRUCTEUR ***************/

Cavalier::~Cavalier() noexcept {}

/*********** METHODE OVERRIDE ***************/

string Cavalier::typeC() {return "cavalier";}

short Cavalier::deplacementV(PlateauE *p, CoupE c) {
    short manger = 2;
    // Le cavalier bouge sur une piece de sa couleur
    if(p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getCouleur() == this->getCouleur())
        manger = 0;
    // Le cavalier bouge sur une case vide
    if(p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getType() == 'v')
        manger = 1;
    // Le cavalier peut bouger
    if( (fabs(c.getYDep()-c.getYDest()) == 2) && (fabs(c.getXDep()-c.getXDest()) == 1) )
        return manger;
        // Le cavalier peut bouger
    else if( (fabs(c.getYDep()-c.getYDest()) == 1) && (fabs(c.getXDep()-c.getXDest()) == 2) )
        return manger;
    return 0;
}

void Cavalier::marqueCaseDeplacable(PlateauAffichage *p, short i, short j) {
    //NORD-OUEST
    if( (i+1 <= 7) && (j-2 >= 0) )
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i+1,j-2)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i+1,j-2)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i+1,j-2)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i+1,j-2)->majCaseDeplacement();
                break;
        }
    //NORD-EST
    if( (i+1 <= 7) && (j+2 <= 7) )
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i+1,j+2)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i+1,j+2)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i+1,j+2)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i+1,j+2)->majCaseDeplacement();
                break;
        }
    //NORD D
    if( (i+2 <= 7) && (j+1 <= 7) )
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i+2,j+1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i+2,j+1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i+2,j+1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i+2,j+1)->majCaseDeplacement();
                break;
        }
    //NORD G
    if( (i+2 <= 7) && (j-1 >= 0) )
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i+2,j-1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i+2,j-1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i+2,j-1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i+2,j-1)->majCaseDeplacement();
                break;
        }
    //SUD G
    if( (i-2 >= 0) && (j-1 >= 0) )
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i-2,j-1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i-2,j-1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i-2,j-1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i-2,j-1)->majCaseDeplacement();
                break;
        }
    //SUD D
    if( (i-2 >= 0) && (j+1 < 8) )
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i-2,j+1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i-2,j+1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i-2,j+1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i-2,j+1)->majCaseDeplacement();
                break;
        }
    //SUD-OUEST
    if( (i-1 >=  0) && (j-2 > 0) )
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i-1,j-2)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i-1,j-2)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i-1,j-2)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i-1,j-2)->majCaseDeplacement();
                break;
        }
    //SUD-EST
    if( (i-1 >=  0) && (j+2 < 8) )
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i-1,j+2)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i-1,j+2)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i-1,j+2)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i-1,j+2)->majCaseDeplacement();
                break;
        }
}

void Cavalier::marqueCaseEchec(PlateauE *p, short i, short j) {
    //NORD-OUEST
    if( (i+1 <= 7) && (j-2 >= 0) )
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i+1,j-2)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i+1,j-2)->setEchecB(true);
                break;
        }
    //NORD-EST
    if( (i+1 <= 7) && (j+2 <= 7) )
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i+1,j+2)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i+1,j+2)->setEchecB(true);
                break;
        }
    //NORD D
    if( (i+2 <= 7) && (j+1 <= 7) )
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i+2,j+1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i+2,j+1)->setEchecB(true);
                break;
        }
    //NORD G
    if( (i+2 <= 7) && (j-1 >= 0) )
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i+2,j-1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i+2,j-1)->setEchecB(true);
                break;
        }
    //SUD G
    if( (i-2 >= 0) && (j-1 >= 0) )
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i-2,j-1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i-2,j-1)->setEchecB(true);
                break;
        }
    //SUD D
    if( (i-2 >= 0) && (j+1 < 8) )
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i-2,j+1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i-2,j+1)->setEchecB(true);
                break;
        }
    //SUD-OUEST
    if( (i-1 >=  0) && (j-2 > 0) )
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i-1,j-2)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i-1,j-2)->setEchecB(true);
                break;
        }
    //SUD-EST
    if( (i-1 >=  0) && (j+2 < 8) )
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i-1,j+2)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i-1,j+2)->setEchecB(true);
                break;
        }
}

/********************************************************/
/**              Fou                                   **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

Fou::Fou(char t, char c, bool d, QString filename) : Piece(t,c,d,filename) {}

/*********** DESTRUCTEUR ***************/

Fou::~Fou() noexcept {}

/*********** METHODE OVERRIDE ***************/

string Fou::typeC() {return "fou";}

short Fou::deplacementV(PlateauE *p, CoupE c) {
    bool pion=false; // voir si il y a un pion dans la zone de déplacement, 1 -> il n'y a pas de pion, 0 -> il y a un pion
    if( fabs(c.getYDep()-c.getYDest()) == fabs(c.getXDep()-c.getXDest()) ){
        // Verification que le chemin soit libre
        if( ((c.getYDest()-c.getYDep()) > 0)  && ((c.getXDest()-c.getXDep()) > 0) ){
            for (short i=1; i <= (fabs(c.getYDest()-c.getYDep())-1); i++){
                if(p->getEchiquier()[c.getYDep()+i][c.getXDep()+i]->getPiece()->getType() != 'v')
                    pion = true;
            }
        } else if ( ((c.getYDest()-c.getYDep()) > 0)  && ((c.getXDest()-c.getXDep()) < 0) ){
            for (short i=1; i <= (fabs(c.getYDest()-c.getYDep())-1); i++){
                if(p->getEchiquier()[c.getYDep()+i][c.getXDep()-i]->getPiece()->getType() != 'v')
                    pion = true;
            }
        } else if ( ((c.getYDest()-c.getYDep()) < 0) && ((c.getXDest()-c.getXDep()) > 0)  ){
            for (short i=1; i <= (fabs(c.getYDest()-c.getYDep())-1); i++){
                if(p->getEchiquier()[c.getYDep()-i][c.getXDep()+i]->getPiece()->getType() != 'v')
                    pion = true;
            }
        } else{
            for (short i=1; i <= (fabs(c.getYDest()-c.getYDep())-1); i++){
                if(p->getEchiquier()[c.getYDep()-i][c.getXDep()-i]->getPiece()->getType() != 'v')
                    pion = true;
            }
        }
        // Le fou bouge sur une case vide
        if(!pion && ( p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getType() ==  'v') )
            return 1;
            // Le fou bouge mange une piece
        else if(!pion && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getCouleur() !=  p->getEchiquier()[c.getYDep()][c.getXDep()]->getPiece()->getCouleur()))
            return 2;
    }
    return 0;
}

void Fou::marqueCaseDeplacable(PlateauAffichage *p, short i, short j) {
    int depX, depY;

    if(i != 7 && j != 7){
        depX = j;
        depY = i;
        do{
            depX++;
            depY++;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
            }
        }while(depX < 7 && depY < 7 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 0 && j != 0){
        depX = j;
        depY = i;
        do{
            depX--;
            depY--;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
            }
        }while(depX > 0 && depY > 0 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 7 && j != 0){
        depX = j;
        depY = i;
        do{
            depX--;
            depY++;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
            }
        }while(depX > 0 && depY < 7 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 0 && j != 7){
        depX = j;
        depY = i;
        do{
            depX++;
            depY--;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
            }
        }while(depX < 7 && depY > 0 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }
}

void Fou::marqueCaseEchec(PlateauE *p, short i, short j) {
    int depX, depY;

    if(i != 7 && j != 7){
        depX = j;
        depY = i;
        do{
            depX++;
            depY++;
            switch (this->couleur) {
                case 'b':
                    p->getCaseE(depY,depX)->setEchecN(true);
                    break;
                case 'n':
                    p->getCaseE(depY,depX)->setEchecB(true);
                    break;
            }
        }while(depX < 7 && depY < 7 && p->getCaseE(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 0 && j != 0){
        depX = j;
        depY = i;
        do{
            depX--;
            depY--;
            switch (this->couleur) {
                case 'b':
                    p->getCaseE(depY,depX)->setEchecN(true);
                    break;
                case 'n':
                    p->getCaseE(depY,depX)->setEchecB(true);
                    break;
            }
        }while(depX > 0 && depY > 0 && p->getCaseE(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 7 && j != 0){
        depX = j;
        depY = i;
        do{
            depX--;
            depY++;
            switch (this->couleur) {
                case 'b':
                    p->getCaseE(depY,depX)->setEchecN(true);
                    break;
                case 'n':
                    p->getCaseE(depY,depX)->setEchecB(true);
                    break;
            }
        }while(depX > 0 && depY < 7 && p->getCaseE(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 0 && j != 7){
        depX = j;
        depY = i;
        do{
            depX++;
            depY--;
            switch (this->couleur) {
                case 'b':
                    p->getCaseE(depY,depX)->setEchecN(true);
                    break;
                case 'n':
                    p->getCaseE(depY,depX)->setEchecB(true);
                    break;
            }
        }while(depX < 7 && depY > 0 && p->getCaseE(depY,depX)->getPiece()->getType() == 'v');
    }
}

/********************************************************/
/**              Roi                                   **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

Roi::Roi(char t, char c, bool d, QString filename) : Piece(t,c,d,filename) {}

/*********** DESTRUCTEUR ***************/

Roi::~Roi() noexcept {}

/*********** METHODE OVERRIDE ***************/

string Roi::typeC() {return "roi";}

short Roi::deplacementV(PlateauE *p, CoupE c) {
    short manger = 1;

    if(this->getCouleur() == 'b'){
        if( !(p->getEchiquier()[c.getYDep()][c.getXDep()]->getPiece()->getDeplacement() )
            && (c.getXDest()-c.getXDep() == 2 ) && (c.getYDep() == c.getYDest())
            && !(p->getEchiquier()[7][7]->getPiece()->getDeplacement())
            && (p->getEchiquier()[7][7]->getPiece()->getType()) == 't'){
            for(short i=c.getXDep()+1 ; i<=c.getXDest(); i++){
                if((p->getEchiquier()[c.getYDep()][i]->getEchecB()) || (p->getEchiquier()[c.getYDep()][i]->getPiece()->getType() != 'v') )
                    return 0;
            }
            return 5;
        }
        else if( !(p->getEchiquier()[c.getYDep()][c.getXDep()]->getPiece()->getDeplacement())
                 && (c.getXDest()-c.getXDep() == -2 ) && (c.getYDep() == c.getYDest())
                 && !(p->getEchiquier()[7][0]->getPiece()->getDeplacement())
                 && (p->getEchiquier()[7][0]->getPiece()->getType() == 't')){
            for(short i=c.getXDep()-1 ; i>=c.getXDest(); i--){
                if((p->getEchiquier()[c.getYDep()][i]->getEchecB()) || (p->getEchiquier()[c.getYDep()][i]->getPiece()->getType() != 'v') )
                    return 0;
            }
            return 6;
        }
    }
    else{
        if( !(p->getEchiquier()[c.getYDep()][c.getXDep()]->getPiece()->getDeplacement())
            && (c.getXDest()-c.getXDep() == 2 ) && (c.getYDep() == c.getYDest())
            && !(p->getEchiquier()[0][7]->getPiece()->getDeplacement())
            && (p->getEchiquier()[0][7]->getPiece()->getType() == 't') ){
            for(short i=c.getXDep()+1 ; i<=c.getXDest(); i++){
                if((p->getEchiquier()[c.getYDep()][i]->getEchecN()) || (p->getEchiquier()[c.getYDep()][i]->getPiece()->getType() != 'v') )
                    return 0;
            }
            return 5;
        }
        else if( !(p->getEchiquier()[c.getYDep()][c.getXDep()]->getPiece()->getDeplacement()) && (c.getXDest()-c.getXDep() == -2 ) && (c.getYDep() == c.getYDest())
                 && !(p->getEchiquier()[0][0]->getPiece()->getDeplacement())
                 && (p->getEchiquier()[0][0]->getPiece()->getType() == 't')){
            for(short i=c.getXDep()-1 ; i>=c.getXDest(); i--){
                if((p->getEchiquier()[c.getYDep()][i]->getEchecN()) || (p->getEchiquier()[c.getYDep()][i]->getPiece()->getType() != 'v') )
                    return 0;
            }
            return 6;
        }
    }

    if(p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getCouleur() == this->getCouleur())
        manger = 0;
    if((p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getType() != 'v') && (p->getEchiquier()[c.getYDest()][c.getXDest()]->getPiece()->getCouleur() != this->getCouleur()))
        manger = 2;
    if((fabs(c.getYDep()-c.getYDest()) == 1) && (fabs(c.getXDep()-c.getXDest()) == 1))
        return manger;
    else if((fabs(c.getYDep()-c.getYDest()) == 1) && (c.getXDep() == c.getXDest()))
        return manger;
    else if( (c.getYDep() == c.getYDest()) && (fabs(c.getXDep()-c.getXDest()) == 1))
        return manger;
    return 0;
}

void Roi::marqueCaseDeplacable(PlateauAffichage *p, short i, short j) {
    if(this->couleur == 'b'){
        if(!this->getDeplacement() && (p->getCaseA(7,7)->getPiece()->getType() == 't') && (p->getCaseA(7,7)->getPiece()->getCouleur() == 'b')
            && !p->getCaseA(7,7)->getPiece()->getDeplacement() && (p->getCaseA(7,6)->getPiece()->getType() == 'v')
            && (p->getCaseA(7,5)->getPiece()->getType() == 'v'))
            p->getCaseA(i,j+2)->majCaseDeplacement();
        else if(!this->getDeplacement() && (p->getCaseA(7,0)->getPiece()->getType() == 't') && (p->getCaseA(7,0)->getPiece()->getCouleur() == 'b')
                  && !p->getCaseA(7,0)->getPiece()->getDeplacement() && (p->getCaseA(7,1)->getPiece()->getType() == 'v')
                  && (p->getCaseA(7,2)->getPiece()->getType() == 'v') && (p->getCaseA(7,3)->getPiece()->getType() == 'v'))
            p->getCaseA(i,j-2)->majCaseDeplacement();
    }
    else{
        if(!this->getDeplacement() && (p->getCaseA(0,7)->getPiece()->getType() == 't') && (p->getCaseA(0,7)->getPiece()->getCouleur() == 'n')
           && !p->getCaseA(0,7)->getPiece()->getDeplacement() && (p->getCaseA(0,6)->getPiece()->getType() == 'v') && (p->getCaseA(0,5)->getPiece()->getType() == 'v'))
            p->getCaseA(i,j+2)->majCaseDeplacement();
        else if(!this->getDeplacement() && (p->getCaseA(0,0)->getPiece()->getType() == 't') && (p->getCaseA(0,0)->getPiece()->getCouleur() == 'n')
                && !p->getCaseA(0,0)->getPiece()->getDeplacement() && (p->getCaseA(0,1)->getPiece()->getType() == 'v')
                && (p->getCaseA(0,2)->getPiece()->getType() == 'v') && (p->getCaseA(0,3)->getPiece()->getType() == 'v'))
            p->getCaseA(i,j-2)->majCaseDeplacement();
    }
    if(i+1 <= 7)
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i+1,j)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i+1,j)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i+1,j)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i+1,j)->majCaseDeplacement();
                break;
        }
    if(i-1 >= 0)
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i-1,j)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i-1,j)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i-1,j)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i-1,j)->majCaseDeplacement();
                break;
        }
    if(j-1 >= 0)
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i,j-1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i,j-1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i,j-1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i,j-1)->majCaseDeplacement();
                break;
        }
    if(j+1 <= 7)
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i,j+1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i,j+1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i,j+1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i,j+1)->majCaseDeplacement();
                break;
        }
    if(i+1 <= 7 && j+1 <= 7)
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i+1,j+1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i+1,j+1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i+1,j+1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i+1,j+1)->majCaseDeplacement();
                break;
        }
    if(i+1 <= 7 && j-1 >= 0)
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i+1,j-1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i+1,j-1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i+1,j-1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i+1,j-1)->majCaseDeplacement();
                break;
        }
    if(i-1 >= 0 && j+1 <= 7)
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i-1,j+1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i-1,j+1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i-1,j+1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i-1,j+1)->majCaseDeplacement();
                break;
        }
    if(i-1 >= 0 && j-1 >= 0)
        switch (this->couleur) {
            case 'b':
                if(p->getCaseA(i-1,j-1)->getPiece()->getCouleur() != 'b')
                    p->getCaseA(i-1,j-1)->majCaseDeplacement();
                break;
            case 'n':
                if(p->getCaseA(i-1,j-1)->getPiece()->getCouleur() != 'n')
                    p->getCaseA(i-1,j-1)->majCaseDeplacement();
                break;
        }
}

void Roi::marqueCaseEchec(PlateauE *p, short i, short j) {
    if(i+1 <= 7)
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i+1,j)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i+1,j)->setEchecB(true);
                break;
        }
    if(i-1 >= 0)
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i-1,j)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i-1,j)->setEchecB(true);
                break;
        }
    if(j-1 >= 0)
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i,j-1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i,j-1)->setEchecB(true);
                break;
        }
    if(j+1 <= 7)
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i,j+1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i,j+1)->setEchecB(true);
                break;
        }
    if(i+1 <= 7 && j+1 <= 7)
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i+1,j+1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i+1,j+1)->setEchecB(true);
                break;
        }
    if(i+1 <= 7 && j-1 >= 0)
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i+1,j-1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i+1,j-1)->setEchecB(true);
                break;
        }
    if(i-1 >= 0 && j+1 <= 7)
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i-1,j+1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i-1,j+1)->setEchecB(true);
                break;
        }
    if(i-1 >= 0 && j-1 >= 0)
        switch (this->couleur) {
            case 'b':
                p->getCaseE(i-1,j-1)->setEchecN(true);
                break;
            case 'n':
                p->getCaseE(i-1,j-1)->setEchecB(true);
                break;
        }
}


/********************************************************/
/**              Dame                                  **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

Dame::Dame(char t, char c, bool d, QString filename) : Piece(t,c,d,filename) {}

/*********** DESTRUCTEUR ***************/

Dame::~Dame() noexcept {}

/*********** METHODE OVERRIDE ***************/

string Dame::typeC() {return "dame";}

short Dame::deplacementV(PlateauE *p, CoupE c) {
    Tour t('t',this->getCouleur(),this->getDeplacement());
    Fou f('f',this->getCouleur(),this->getDeplacement());
    short resultF, resultT;

    resultF = t.deplacementV(p,c);
    resultT = f.deplacementV(p,c);

    if ( (resultT == 2) || (resultF == 2))
        return 2;
    return ( resultT || resultF );
}

void Dame::marqueCaseDeplacable(PlateauAffichage *p, short i, short j) {
    int depX, depY;

    if(i != 7 && j != 7){
        depX = j;
        depY = i;
        do{
            depX++;
            depY++;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
            }
        }while(depX < 7 && depY < 7 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 0 && j != 0){
        depX = j;
        depY = i;
        do{
            depX--;
            depY--;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
            }
        }while(depX > 0 && depY > 0 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 7 && j != 0){
        depX = j;
        depY = i;
        do{
            depX--;
            depY++;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
            }
        }while(depX > 0 && depY < 7 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 0 && j != 7){
        depX = j;
        depY = i;
        do{
            depX++;
            depY--;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
            }
        }while(depX < 7 && depY > 0 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i != 7){
        depX = j;
        depY = i;
        do{
            depY++;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                default:
                    return;
            }
        }while(depY < 7 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(j != 0){
        depX = j;
        depY = i;
        do{
            depX--;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                default:
                    return;
            }
        }while(depX > 0 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(j != 7){
        depX = j;
        depY = i;
        do{
            depX++;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                default:
                    return;
            }
        }while(depX < 7 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }

    if(i!=0){
        depX = j;
        depY = i;
        do{
            depY--;
            switch (this->couleur) {
                case 'b':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'b')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                case 'n':
                    if(p->getCaseA(depY,depX)->getPiece()->getCouleur() != 'n')
                        p->getCaseA(depY,depX)->majCaseDeplacement();
                    break;
                default:
                    return;
            }
        }while(depY > 0 && p->getCaseA(depY,depX)->getPiece()->getType() == 'v');
    }
}

void Dame::marqueCaseEchec(PlateauE *p, short i, short j) {
    Tour t('t',this->getCouleur(),this->getDeplacement());
    Fou f('f',this->getCouleur(),this->getDeplacement());
    t.marqueCaseEchec(p,i,j);
    f.marqueCaseEchec(p,i,j);
}
