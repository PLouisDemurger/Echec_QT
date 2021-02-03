#include <PlateauE.h>
#include <QtWidgets/QMessageBox>

/********************************************************/
/**              PlateauE                              **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

PlateauE::PlateauE() {
    this->derCoup = CoupE(-1,-1,-1,-1);
    this->echiquier = new CaseE**[8];
    this->piecePNoir = vector<Piece>();
    this->piecePBlanc = vector<Piece>();
    this->echiquier = new CaseE**[8];
    for(short i=0 ; i<8 ; i++)
        this->echiquier[i] = new CaseE*[8];
    this->echiquier[0][0] = new CaseE(false,false,'b', new Tour('t','n',false));
    this->echiquier[0][1] = new CaseE(false,false,'n', new Cavalier('c','n',false));
    this->echiquier[0][2] = new CaseE(false,false,'b', new Fou('f','n',false));
    this->echiquier[0][3] = new CaseE(false,false,'n', new Dame('d','n',false));
    this->echiquier[0][4] = new CaseE(false,false,'b', new Roi('r','n',false));
    this->echiquier[0][5] = new CaseE(false,false,'n', new Fou('f','n',false));
    this->echiquier[0][6] = new CaseE(false,false,'b', new Cavalier('c','n',false));
    this->echiquier[0][7] = new CaseE(false,false,'n', new Tour('t','n',false));
    for(short i=0 ; i < 8 ; i++){
        if(i%2==1)
            this->echiquier[1][i] = new CaseE(false,false,'b', new Pion('p','n',false));
        else
            this->echiquier[1][i] = new CaseE(false,false,'n', new Pion('p','n',false));
    }
    for(short i=2 ; i < 6 ; i++){
        for(short j=0 ; j < 8 ; j++){
            if(i%2==1){
                if(j%2==1)
                    this->echiquier[i][j] = new CaseE(false,false,'b', new Piece());
                else
                    this->echiquier[i][j] = new CaseE(false,false,'n', new Piece());
            }
            else {
                if (j%2==1)
                    this->echiquier[i][j] = new CaseE(false, false, 'n', new Piece());
                else
                    this->echiquier[i][j] = new CaseE(false, false, 'b', new Piece());
            }
        }
    }
    for(short i= 0; i < 8 ; i++){
        if(i%2==1)
            this->echiquier[6][i] = new CaseE(false,false,'n',new Pion('p','b',false));
        else
            this->echiquier[6][i] = new CaseE(false,false,'b', new Pion('p','b',false));
    }
    this->echiquier[7][0] = new CaseE(false,false,'n', new Tour('t','b',false));
    this->echiquier[7][1] = new CaseE(false,false,'b', new Cavalier('c','b',false));
    this->echiquier[7][2] = new CaseE(false,false,'n', new Fou('f','b',false));
    this->echiquier[7][3] = new CaseE(false,false,'b', new Dame('d','b',false));
    this->echiquier[7][4] = new CaseE(false,false,'n', new Roi('r','b',false));
    this->echiquier[7][5] = new CaseE(false,false,'b', new Fou('f','b',false));
    this->echiquier[7][6] = new CaseE(false,false,'n', new Cavalier('c','b',false));
    this->echiquier[7][7] = new CaseE(false,false,'b', new Tour('t','b',false));
}

/********** DESTRUCTEUR ***************/

PlateauE::~PlateauE() noexcept {
    for(short i = 0 ; i < 8 ; i++){
        for(short j = 0 ; i < 8 ; i++){
            delete this->echiquier[i][j];
        }
    }
    for(short i=0 ; i<8 ; i++)
        delete this->echiquier[i];
    delete this->echiquier;
}

/*********** GETTEUR ***************/

CoupE PlateauE::getDerCoup() {
    return this->derCoup;
}

CaseE *** PlateauE::getEchiquier() {
    return this->echiquier;
}

CaseE * PlateauE::getCaseE(short i, short j) {
    return this->echiquier[i][j];
}

/*********** SETTEUR ***************/

void PlateauE::setDerCoup(CoupE e) {
    this->derCoup = e;
}

/*********** METHODE PUBLIQUE ***************/

void PlateauE::affichageEchiquier() {
    char lettre;

    setTerm2(blue_Terminal)
    cout << "\n     ";
    for(int i=0 ; i < 8; i++){
        lettre = 65 + i;
        cout << "  " << (lettre) << "   ";
    }
    cout << "\n\n";
    for(int i=0 ; i < 8; i++){
        resetTerm2()
        cout << "     ";
        for(int j=0 ; j < 8 ; j++){
            setTerm2(brown_Terminal)
            switch (this->echiquier[i][j]->getCouleur()){
                case 'b':
                setBG2(BG_B_Terminal)
                    break;
                case 'n':
                setBG2(BG_N_Terminal)
                    break;
                case 'a':
                    break;
            }
            setTerm2(light_red_Terminal)
            cout << "      ";
        }
        resetTerm2()
        cout << "\n";
        setTerm2(blue_Terminal)
        cout << "  " << (8-i) << "  ";
        for(int j=0 ; j < 8 ; j++){
            setTerm2(brown_Terminal)
            switch (this->echiquier[i][j]->getCouleur()){
                case 'b':
                setBG2(BG_B_Terminal)
                    break;
                case 'n':
                setBG2(BG_N_Terminal)
                    break;
                case 'a':
                    break;
            }
            setTerm2(light_red_Terminal)
            cout << "  " << this->ecrirePieceT(this->echiquier[i][j]->getPiece()) << "   ";
        }
        setTerm2(brown_Terminal)
        cout << "\n";
        resetTerm2()
        cout << "     ";
        for(int j=0 ; j < 8 ; j++){
            setTerm2(brown_Terminal)
            switch (this->echiquier[i][j]->getCouleur()){
                case 'b':
                setBG2(BG_B_Terminal)
                    break;
                case 'n':
                setBG2(BG_N_Terminal)
                    break;
                case 'a':
                    break;
            }
            setTerm2(light_red_Terminal)
            cout << "      ";
        }
        resetTerm2()
        cout << "\n";
    }
}

/**********************************/

void PlateauE::copiePlateau(PlateauE *p) {
    for(short i=0 ; i<8 ; i++){
        for(short j=0 ; j<8 ; j++){
            this->echiquier[i][j]->copierCase(p->getCaseE(i,j));
        }
    }
}

/**********************************/

bool PlateauE::deplacerPiece(CoupE c) {
    Piece *sauv = this->echiquier[c.getYDep()][c.getXDep()]->getPiece();
    Piece *perdu;
    switch (this->echiquier[c.getYDep()][c.getXDep()]->getPiece()->deplacementV(this,c)) {
        case 1:
            cout << 1 << endl;
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            this->echiquier[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquier[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            return true;
        case 2:
            cout << 2 << endl;
            perdu = this->echiquier[c.getYDest()][c.getXDest()]->getPiece();
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            if(perdu->getCouleur()=='b')
                this->piecePBlanc.push_back(*perdu);
            else
                this->piecePNoir.push_back(*perdu);
            this->echiquier[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquier[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            return true;
        case 3:
            cout << 3 << endl;
            perdu = this->echiquier[c.getYDest()+1][c.getXDest()]->getPiece();
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            if(perdu->getCouleur()=='b')
                this->piecePBlanc.push_back(*perdu);
            else
                this->piecePNoir.push_back(*perdu);
            this->echiquier[c.getYDest()+1][c.getXDest()]->setPiece(new Piece(vide));
            this->echiquier[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquier[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            return true;
        case 4:
            cout << 4 << endl;
            perdu = this->echiquier[c.getYDest()-1][c.getXDest()]->getPiece();
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            if(perdu->getCouleur()=='b')
                this->piecePBlanc.push_back(*perdu);
            else
                this->piecePNoir.push_back(*perdu);
            this->echiquier[c.getYDest()+1][c.getXDest()]->setPiece(new Piece(vide));
            this->echiquier[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquier[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            return true;
        case 5:
            cout << 5 << endl;
            sauv->setDeplacement(true);
            perdu = this->echiquier[c.getYDep()][0]->getPiece();
            this->echiquier[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquier[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            this->echiquier[c.getYDest()][c.getXDest()+1]->setPiece(perdu);
            this->echiquier[c.getYDep()][0]->setPiece(new Piece(vide));
            return true;
        case 6:
            cout << 6 << endl;
            sauv->setDeplacement(true);
            perdu = this->echiquier[c.getYDep()][7]->getPiece();
            this->echiquier[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquier[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            this->echiquier[c.getYDest()][c.getXDest()-1]->setPiece(perdu);
            this->echiquier[c.getYDep()][7]->setPiece(new Piece(vide));
            return true;
        case 7:
            cout << 7 << endl;
            this->echiquier[c.getYDest()][c.getXDest()]->setPiece(this->promotion(sauv->getCouleur()));
            this->echiquier[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            return true;
        case 8:
            cout << 8 << endl;
            perdu = this->echiquier[c.getYDest()][c.getXDest()]->getPiece();
            if(perdu->getCouleur()=='b')
                this->piecePBlanc.push_back(*perdu);
            else
                this->piecePNoir.push_back(*perdu);
            this->echiquier[c.getYDest()][c.getXDest()]->setPiece(this->promotion(sauv->getCouleur()));
            this->echiquier[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            return true;
        default:
            //cout << endl << this->echiquier[c.getYDep()][c.getXDep()]->getPiece()->typeC() << endl;
            //cout << "deplacement invalide" << endl;
            return false;
    }
}

/**********************************/

bool PlateauE::echecEtMat(bool cJ) {
    // NECESSAIRE
    char coul;
    short posX, posY;
    short test, dir = -1;
    short nbFront = 0, nbBloc = 0;
    short X = 0, Y = 0;
    bool trouver = false;
    bool echecR;
    PlateauE sauv;

    // DETECTION DES COORDONNEES DU ROI
    while(!trouver && X < 8){
        Y = 0;
        while(!trouver && Y < 8){
            if(cJ) {
                if ((this->echiquier[Y][X]->getPiece()->getCouleur() == 'b') &&
                    (this->echiquier[Y][X]->getPiece()->getType() == 'r')) {
                    if (!this->echiquier[Y][X]->getEchecB())
                        return false;
                    trouver = true;
                }
            }
            else{
                if( (this->echiquier[Y][X]->getPiece()->getCouleur() == 'n') && (this->echiquier[Y][X]->getPiece()->getType() == 'r') ){
                    if(!this->echiquier[Y][X]->getEchecN())
                        return false;
                    trouver = true;
                }
            }
            if(!trouver)
                Y++;
        }
        if(!trouver)
            X++;
    }

    if(X > 7)
        return true;

    // REGARDE LES CASES AUTOUR DU ROI ET VERIFIE SI IL PEUT BOUGER
    if(X==0 && Y==0){
        nbBloc = 5;
        for(short i=X ; i<=X+1 ; i++){
            for(short j=Y ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==0 && Y==7){
        nbBloc = 5;
        for(short i=X ; i<=X+1 ; i++){
            for(short j=Y-1 ; j<=Y ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==7 && Y==0){
        nbBloc = 5;
        for(short i=X-1 ; i<=X ; i++){
            for(short j=Y ; j<Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==7 && Y==7){
        nbBloc = 5;
        for(short i=X-1 ; i<=X ; i++){
            for(short j=Y-1 ; j<=Y ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==0){
        nbBloc = 3;
        for(short i=X ; i<=X+1 ; i++){
            for(short j=Y-1 ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(Y==0){
        nbBloc = 3;
        for(short i=X-1 ; i<=X+1 ; i++){
            for(short j=Y ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==7){
        nbBloc = 3;
        for(short i=X-1 ; i<=X+1 ; i++){
            for(short j=Y-1 ; j<=Y ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(Y==7){
        nbBloc = 3;
        for(short i=X-1 ; i<=X ; i++){
            for(short j=Y-1 ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else{
        for(short i=X-1 ; i<=X+1 ; i++){
            for(short j=Y-1 ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }

    if(nbFront>1)
        return true;



    // TROUVER UNE FACON DE CONTRER L'ATTAQUE (CHEMIN ET TROUVE LA PIECE QUI ATTAQUE LE ROI)
    posX = X;
    posY = Y;
    switch (dir){
        case 1: // Y+1 et X
            while((this->echiquier[++posY][posX]->getPiece()->getType() == 'v') && (posY < 8)){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 6: // Y-1 et X
            while((this->echiquier[--posY][posX]->getPiece()->getType() == 'v') && (posY > 0)){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 4: // Y et X-1
            while((this->echiquier[posY][--posX]->getPiece()->getType() == 'v') && (posX > 0)){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 3: // Y et X+1
            while((this->echiquier[posY][++posX]->getPiece()->getType() == 'v') && (posX < 8)){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 0: // Y+1 et X+1
            while((this->echiquier[++posY][++posX]->getPiece()->getType() == 'v') && ((posX < 8) || (posY < 8))){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 2: // Y+1 et X-1
            while((this->echiquier[++posY][--posX]->getPiece()->getType() == 'v') && ((posX > 0) || (posY < 8))){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 5: // Y-1 et X+1
            while((this->echiquier[--posY][++posX]->getPiece()->getType() == 'v') && ((posX < 8) || (posY > 0))){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 7: // Y-1 et X-1
            while((this->echiquier[--posY][--posX]->getPiece()->getType() == 'v') && ((posX > 0) || (posY > 0))){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        default:
            posX = -1;
            posY = -1;
            break;
    }

    // TEST POUR MANGER LA PIECE QUI ATTAQUE
    if(cJ)
        coul = 'b';
    else
        coul = 'n';
    if( (posX != -1) && (posY != -1) && (this->echiquier[posY][posX]->getPiece()->getCouleur() != 'v') && (this->echiquier[posY][posX]->getPiece()->getCouleur() != coul) ){
        return !this->trouvPieceCEchec(cJ,posX,posY);
    }

    return true;
}

/**********************************/

bool PlateauE::echecRoiJoueurActif(bool c) {
    this->majEchec();
    if(c){
        for(short i=0 ; i < 8 ; i++){
            for(short j=0 ; j < 8 ; j++){
                if((this->echiquier[i][j]->getPiece()->getType() == 'r') && (this->echiquier[i][j]->getPiece()->getCouleur() == 'b'))
                    return  ( !this->echiquier[i][j]->getEchecB() );
            }
        }
    }
    else{
        for(short i=0 ; i < 8 ; i++){
            for(short j=0 ; j < 8 ; j++){
                if ((this->echiquier[i][j]->getPiece()->getType() == 'r') && (this->echiquier[i][j]->getPiece()->getCouleur() == 'n'))
                    return  ( !this->echiquier[i][j]->getEchecN() );
            }
        }
    }
    return false;
}

/**********************************/

bool PlateauE::jouerCoupVerifMat(bool cJ, CoupE c) {
    PlateauE *sauv;
    bool rep;

    sauv->copiePlateau(this);
    rep = this->jouerCoupVerif(cJ,c);
    if(!rep)
        this->copiePlateau(sauv);

    return rep;

}

/**********************************/

void PlateauE::majEchec() {
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            this->echiquier[i][j]->setEchecN(false);
            this->echiquier[i][j]->setEchecB(false);
        }
    }
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            this->echiquier[i][j]->getPiece()->marqueCaseEchec(this,i,j);
        }
    }
}

/*********** METHODE PRIVEE ***************/

short PlateauE::connaitreFront(bool couleur, CoupE c){
    short differenceX, differenceY;
    short i, j;

    differenceX = c.getXDep() - c.getXDest();
    differenceY = c.getYDep() - c.getYDest();
    if(fabs(differenceX)>1 || fabs(differenceY)>1)
        return -1;
    i = c.getYDest();
    j = c.getXDest();
    if(couleur){
        while( (i < 8) && (j < 8) && (i > 0) && (j > 0) && (this->echiquier[i][j]->getEchecB()) && (this->echiquier[i][j]->getPiece()->getType() == 'v') ){i -= differenceY; j -= differenceX;};
        if(this->echiquier[i][j]->getPiece()->getCouleur() == 'n'){
            switch(differenceY){
                case -1:
                    switch(differenceX){
                        case -1:
                            return 0;
                        case 0:
                            return 1;
                        case 1:
                            return 2;
                        default:
                            return -1;
                    }
                case 0:
                    switch(differenceX){
                        case -1:
                            return 3;
                        case 0:
                            return -1;
                        case 1:
                            return 4;
                        default:
                            return -1;
                    }
                case 1:
                    switch(differenceX){
                        case -1:
                            return 5;
                        case 0:
                            return 6;
                        case 1:
                            return 7;
                        default:
                            return -1;
                    }
                default:
                    return -1;
            }
        }
    }else{
        while( (i < 8) && (j < 8) && (i > 0) && (j > 0) && (this->echiquier[i][j]->getEchecN()) && (this->echiquier[i][j]->getPiece()->getType() == 'v') ){i -= differenceY; j -= differenceX;};
        if(this->echiquier[i][j]->getPiece()->getCouleur() == 'b') {
            switch(differenceY){
                case -1:
                    switch(differenceX){
                        case -1:
                            return 0;
                        case 0:
                            return 1;
                        case 1:
                            return 2;
                        default:
                            return -1;
                    }
                case 0:
                    switch(differenceX){
                        case -1:
                            return 3;
                        case 0:
                            return -1;
                        case 1:
                            return 4;
                        default:
                            return -1;
                    }
                case 1:
                    switch(differenceX){
                        case -1:
                            return 5;
                        case 0:
                            return 6;
                        case 1:
                            return 7;
                        default:
                            return -1;
                    }
                default:
                    return -1;
            }
        }
    }
    return -1;
}

/**********************************/

const char* PlateauE::ecrirePieceT(Piece *piece){
    switch (piece->getCouleur()){
        case 'n':
            switch (piece->getType()){
                case 'p':
                    return "\u265F";
                case 't':
                    return "\u265C";
                case 'c':
                    return "\u265E";
                case 'f':
                    return "\u265D";
                case 'r':
                    return "\u265A";
                case 'd':
                    return "\u265B";
                case 'v':
                    return " ";
            }
            break;
        case 'b':
            switch (piece->getType()){
                case 'p':
                    return "\u2659";
                case 't':
                    return "\u2656";
                case 'c':
                    return "\u2658";
                case 'f':
                    return "\u2657";
                case 'r':
                    return "\u2654";
                case 'd':
                    return "\u2655";
                case 'v':
                    return " ";
            }
            break;
        case 'a':
            return " ";
            break;
    }
    return " ";
}

/**********************************/

bool PlateauE::jouerCoupVerif(bool cJ, CoupE c) {
    return ( this->deplacerPiece(c) && this->echecRoiJoueurActif(cJ) ) ;
}

/**********************************/

bool PlateauE::jouerCoupVerifSauv(bool cJ, CoupE c) {
    PlateauE *sauv = new PlateauE();
    bool rep;

    sauv->copiePlateau(this);
    rep = this->jouerCoupVerif(cJ,c);
    if(!rep)
        this->copiePlateau(sauv);

    return rep;

}

/**********************************/

Piece * PlateauE::promotion(char couleur) {
    short saisie = 0;
    do{
        cout << endl << "++++++++++++++++++++++++++++++++" << endl;
        cout << "+         PROMOTION            +" << endl;
        cout << "++++++++++++++++++++++++++++++++" << endl;
        cout << "+ 1:tour                       +" << endl;
        cout << "+ 2:cavalier                   +" << endl;
        cout << "+ 3:fou                        +" << endl;
        cout << "+ 4:roi                        +" << endl;
        cout << "+ 5:dame                       +" << endl;
        cout << "+ 6:pion                       +" << endl;
        cout << "++++++++++++++++++++++++++++++++" << endl << endl;
        cout << "saisie: ";
        cin >> saisie;
        cin.clear();
        cin.ignore();
    }while(saisie<1 || saisie>6);
    switch(saisie){
        case 1:
            return new Tour('t',couleur,true);
        case 2:
            return new Cavalier('c',couleur,true);
        case 3:
            return new Fou('f',couleur,true);
        case 4:
            return new Roi('r',couleur,true);
        case 5:
            return new Dame('d',couleur,true);
        default:
            return new Pion('p',couleur,true);
    }
}

/**********************************/

short PlateauE::trouvPieceCEchec(bool couleur, const short X, const short Y){
    PlateauE sauv;
    if(couleur){
        for(short i=0; i < 8 ; i++){
            for (short j = 0;  j < 8 ; j++) {
                if( (this->echiquier[i][j]->getPiece()->getCouleur() == 'b') && (this->echiquier[i][j]->getPiece()->getType() != 'r')){
                    if (this->jouerCoupVerifMat(couleur, CoupE(j, i, X, Y)))
                        return true;
                }
            }
        }
    }
    else{
        for(short i=0; i < 8 ; i++){
            for (short j = 0;  j < 8 ; j++) {
                if( (this->echiquier[i][j]->getPiece()->getCouleur() == 'n') && (this->echiquier[i][j]->getPiece()->getType() != 'r')){
                    if (this->jouerCoupVerifMat(couleur, CoupE(j, i, X, Y)))
                        return true;
                }
            }
        }
    }
    return false;
}

/********************************************************/
/**              PlateauAffichage                      **/
/********************************************************/

/********** CONSTRUCTEUR ***************/

PlateauAffichage::PlateauAffichage(QWidget* parent) : QGridLayout(){
    this->derCoup = CoupE(-1,-1,-1,-1);
    this->echiquierAff = new CaseAffichage**[8];
    for(short i=0 ; i<8 ; i++) {
        this->echiquierAff[i] = new CaseAffichage *[8];
        this->lettre[i] = new QLabel(parent);
        this->chiffre[i] = new QLabel(parent);
        this->lettre[i]->setStyleSheet("color: blue; grey; padding: auto;");
        this->chiffre[i]->setStyleSheet("color: blue; grey; padding: auto;");
        this->lettre[i]->setText(QString(i+'A'));
        this->chiffre[i]->setText(QString(i+49));
    }
    this->echiquierAff[0][0] = new CaseAffichage(false,false,'b', new Tour('t','n',false,tourNoir),0,0,parent);
    this->echiquierAff[0][1] = new CaseAffichage(false,false,'n', new Cavalier('c','n',false,chevalNoir),1,0,parent);
    this->echiquierAff[0][2] = new CaseAffichage(false,false,'b', new Fou('f','n',false,fouNoir),2,0,parent);
    this->echiquierAff[0][3] = new CaseAffichage(false,false,'n', new Dame('d','n',false,dameNoir),3,0,parent);
    this->echiquierAff[0][4] = new CaseAffichage(false,false,'b', new Roi('r','n',false,roiNoir),4,0,parent);
    this->echiquierAff[0][5] = new CaseAffichage(false,false,'n', new Fou('f','n',false,fouNoir),5,0,parent);
    this->echiquierAff[0][6] = new CaseAffichage(false,false,'b', new Cavalier('c','n',false,chevalNoir),6,0,parent);
    this->echiquierAff[0][7] = new CaseAffichage(false,false,'n', new Tour('t','n',false,tourNoir),7,0,parent);
    for(short i=0 ; i < 8 ; i++){
        if(i%2==1)
            this->echiquierAff[1][i] = new CaseAffichage(false,false,'b', new Pion('p','n',false,pionNoir),i,1,parent);
        else
            this->echiquierAff[1][i] = new CaseAffichage(false,false,'n', new Pion('p','n',false,pionNoir),i,1,parent);
    }
    for(short i=2 ; i < 6 ; i++){
        for(short j=0 ; j < 8 ; j++){
            if(i%2==1){
                if(j%2==1)
                    this->echiquierAff[i][j] = new CaseAffichage(false,false,'b', new Piece(vide),j,i,parent);
                else
                    this->echiquierAff[i][j] = new CaseAffichage(false,false,'n', new Piece(vide),j,i,parent);
            }
            else {
                if (j%2==1)
                    this->echiquierAff[i][j] = new CaseAffichage(false, false, 'n', new Piece(vide),j,i,parent);
                else
                    this->echiquierAff[i][j] = new CaseAffichage(false, false, 'b', new Piece(vide),j,i,parent);
            }
        }
    }
    for(short i= 0; i < 8 ; i++){
        if(i%2==1)
            this->echiquierAff[6][i] = new CaseAffichage(false,false,'n',new Pion('p','b',false,pionBlanc),i,6,parent);
        else
            this->echiquierAff[6][i] = new CaseAffichage(false,false,'b', new Pion('p','b',false,pionBlanc),i,6,parent);
    }
    this->echiquierAff[7][0] = new CaseAffichage(false,false,'n', new Tour('t','b',false,tourBlanc),0,7,parent);
    this->echiquierAff[7][1] = new CaseAffichage(false,false,'b', new Cavalier('c','b',false,chevalBlanc),1,7,parent);
    this->echiquierAff[7][2] = new CaseAffichage(false,false,'n', new Fou('f','b',false,fouBlanc),2,7,parent);
    this->echiquierAff[7][3] = new CaseAffichage(false,false,'b', new Dame('d','b',false,dameBlanc),3,7,parent);
    this->echiquierAff[7][4] = new CaseAffichage(false,false,'n', new Roi('r','b',false,roiBlanc),4,7,parent);
    this->echiquierAff[7][5] = new CaseAffichage(false,false,'b', new Fou('f','b',false,fouBlanc),5,7,parent);
    this->echiquierAff[7][6] = new CaseAffichage(false,false,'n', new Cavalier('c','b',false,chevalBlanc),6,7,parent);
    this->echiquierAff[7][7] = new CaseAffichage(false,false,'b', new Tour('t','b',false,tourBlanc),7,7,parent);

    for(short i=0 ; i < 8 ; i++) {
        this->addWidget(this->lettre[i],0,i+1);
        for (short j = 0; j < 8; j++) {
            this->addWidget(this->echiquierAff[i][j],i+1,j+1);
        }
        this->addWidget(this->chiffre[i],i+1,0);
    }
}

/********** DESTRUCTEUR ***************/

PlateauAffichage::~PlateauAffichage() noexcept {}

/********** GETTEUR ***************/

CaseAffichage * PlateauAffichage::getCaseA(short i, short j) {
    return this->echiquierAff[i][j];
}

CaseE * PlateauAffichage::getCaseE(short i, short j) {
    return this->echiquierAff[i][j];
}

/**********************************/

CaseE *** PlateauAffichage::getEchiquier() {
    for(short i=0 ; i<8 ; i++){
        for(short j=0 ; j<8 ; j++){
            this->echiquier[i][j]->setPiece(this->echiquierAff[i][j]->getPiece());
            this->echiquier[i][j]->setEchecN(this->echiquierAff[i][j]->getEchecN());
            this->echiquier[i][j]->setEchecB(this->echiquierAff[i][j]->getEchecB());
        }
    }
    return this->echiquier;
}

/*********** METHODE ***************/

void PlateauAffichage::initPlateau(){
    for(short i=0 ; i < 8 ; i++) {
        for (short j = 0; j < 8; j++) {
            this->echiquierAff[i][j]->initCase();
        }
    }
}

void PlateauAffichage::majPlateau(bool cJ) {
    for(short i=0 ; i < 8 ; i++) {
        for (short j = 0; j < 8; j++) {
            this->echiquierAff[i][j]->majCase(cJ);
        }
    }
}

void PlateauAffichage::marqueCaseAccessible(short i, short j) {
    this->echiquierAff[i][j]->getPiece()->marqueCaseDeplacable(this,i,j);
}

/*********** METHODE OVERRIDE ***************/

void PlateauAffichage::copiePlateau(PlateauE *p) {
    for(short i=0 ; i<8 ; i++){
        for(short j=0 ; j<8 ; j++){
            this->echiquierAff[i][j]->copierCase(p->getCaseE(i,j));
        }
    }
}

/**********************************/

bool PlateauAffichage::deplacerPiece(CoupE c) {
    Piece *sauv = this->echiquierAff[c.getYDep()][c.getXDep()]->getPiece();
    Piece *perdu;
    switch (this->echiquierAff[c.getYDep()][c.getXDep()]->getPiece()->deplacementV(this,c)) {
        case 1:
            //cout << 1 << endl;
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            this->echiquierAff[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquierAff[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            return true;
        case 2:
            //cout << 2 << endl;
            perdu = this->echiquierAff[c.getYDest()][c.getXDest()]->getPiece();
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            if(perdu->getCouleur()=='b')
                this->piecePBlanc.push_back(*perdu);
            else
                this->piecePNoir.push_back(*perdu);
            this->echiquierAff[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquierAff[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            return true;
        case 3:
            //cout << 3 << endl;
            perdu = this->echiquierAff[c.getYDest()+1][c.getXDest()]->getPiece();
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            if(perdu->getCouleur()=='b')
                this->piecePBlanc.push_back(*perdu);
            else
                this->piecePNoir.push_back(*perdu);
            this->echiquierAff[c.getYDest()+1][c.getXDest()]->setPiece(new Piece(vide));
            this->echiquierAff[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquierAff[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            return true;
        case 4:
            //cout << 4 << endl;
            perdu = this->echiquierAff[c.getYDest()-1][c.getXDest()]->getPiece();
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            if(perdu->getCouleur()=='b')
                this->piecePBlanc.push_back(*perdu);
            else
                this->piecePNoir.push_back(*perdu);
            this->echiquierAff[c.getYDest()+1][c.getXDest()]->setPiece(new Piece(vide));
            this->echiquierAff[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquierAff[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            if(!sauv->getDeplacement())
                sauv->setDeplacement(true);
            return true;
        case 5:
            //cout << 5 << endl;
            sauv->setDeplacement(true);
            perdu = this->echiquierAff[c.getYDep()][7]->getPiece();
            this->echiquierAff[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquierAff[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            this->echiquierAff[c.getYDest()][c.getXDest()-1]->setPiece(perdu);
            this->echiquierAff[c.getYDep()][7]->setPiece(new Piece(vide));
            return true;
        case 6:
            //cout << 6 << endl;
            sauv->setDeplacement(true);
            perdu = this->echiquierAff[c.getYDep()][0]->getPiece();
            this->echiquierAff[c.getYDest()][c.getXDest()]->setPiece(sauv);
            this->echiquierAff[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            this->echiquierAff[c.getYDest()][c.getXDest()+1]->setPiece(perdu);
            this->echiquierAff[c.getYDep()][0]->setPiece(new Piece(vide));
            return true;
        case 7:
            //cout << 7 << endl;
            this->echiquierAff[c.getYDest()][c.getXDest()]->setPiece(this->promotionAff(sauv->getCouleur()));
            this->echiquierAff[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            return true;
        case 8:
            //cout << 8 << endl;
            perdu = this->echiquierAff[c.getYDest()][c.getXDest()]->getPiece();
            if(perdu->getCouleur()=='b')
                this->piecePBlanc.push_back(*perdu);
            else
                this->piecePNoir.push_back(*perdu);
            this->echiquierAff[c.getYDest()][c.getXDest()]->setPiece(this->promotionAff(sauv->getCouleur()));
            this->echiquierAff[c.getYDep()][c.getXDep()]->setPiece(new Piece(vide));
            return true;
        default:
            //cout << endl << this->echiquierAff[c.getYDep()][c.getXDep()]->getPiece()->typeC() << endl;
            //cout << "deplacement invalide" << endl;
            return false;
    }
}

/**********************************/

bool PlateauAffichage::echecEtMat(bool cJ) {
    // NECESSAIRE
    char coul;
    short posX, posY;
    short test, dir = -1;
    short nbFront = 0, nbBloc = 0;
    short X = 0, Y = 0;
    bool trouver = false;
    PlateauE sauv;

    if(cJ)
        coul = 'b';
    else
        coul = 'n';

    // DETECTION DES COORDONNEES DU ROI
    while(!trouver && X < 8){
        Y = 0;
        while(!trouver && Y < 8){
            if(cJ) {
                if ((this->echiquierAff[Y][X]->getPiece()->getCouleur() == 'b') &&
                    (this->echiquierAff[Y][X]->getPiece()->getType() == 'r')) {
                    if (!this->echiquierAff[Y][X]->getEchecB())
                        return false;
                    trouver = true;
                }
            }
            else{
                if( (this->echiquierAff[Y][X]->getPiece()->getCouleur() == 'n') && (this->echiquierAff[Y][X]->getPiece()->getType() == 'r') ){
                    if(!this->echiquierAff[Y][X]->getEchecN())
                        return false;
                    trouver = true;
                }
            }
            if(!trouver)
                Y++;
        }
        if(!trouver)
            X++;
    }

    if(X > 7)
        return true;

    // REGARDE LES CASES AUTOUR DU ROI ET VERIFIE SI IL PEUT BOUGER
    if(X==0 && Y==0){
        nbBloc = 5;
        for(short i=X ; i<=X+1 ; i++){
            for(short j=Y ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==0 && Y==7){
        nbBloc = 5;
        for(short i=X ; i<=X+1 ; i++){
            for(short j=Y-1 ; j<=Y ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==7 && Y==0){
        nbBloc = 5;
        for(short i=X-1 ; i<=X ; i++){
            for(short j=Y ; j<Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==7 && Y==7){
        nbBloc = 5;
        for(short i=X-1 ; i<=X ; i++){
            for(short j=Y-1 ; j<=Y ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==0){
        nbBloc = 3;
        for(short i=X ; i<=X+1 ; i++){
            for(short j=Y-1 ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(Y==0){
        nbBloc = 3;
        for(short i=X-1 ; i<=X+1 ; i++){
            for(short j=Y ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(X==7){
        nbBloc = 3;
        for(short i=X-1 ; i<=X+1 ; i++){
            for(short j=Y-1 ; j<=Y ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else if(Y==7){
        nbBloc = 3;
        for(short i=X-1 ; i<=X ; i++){
            for(short j=Y-1 ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }
    else{
        for(short i=X-1 ; i<=X+1 ; i++){
            for(short j=Y-1 ; j<=Y+1 ; j++){
                if( (i!=X || j!=Y) && this->jouerCoupVerifMat(cJ, CoupE(X, Y, i, j)) )
                    return false;
                else if( (i!=X || j!=Y) && (test = this->connaitreFront(cJ,CoupE(X,Y,i,j))) != -1 ){
                    dir = test;
                    nbFront++;
                }
                else if (i!=X || j!=Y){
                    nbBloc++;
                }
            }
        }
    }

    if(nbFront>1)
        return true;



    // TROUVER UNE FACON DE CONTRER L'ATTAQUE (CHEMIN ET TROUVE LA PIECE QUI ATTAQUE LE ROI)
    posX = X;
    posY = Y;
    switch (dir){
        case 1: // Y+1 et X
            while((this->echiquierAff[++posY][posX]->getPiece()->getType() == 'v') && (posY < 8)){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 6: // Y-1 et X
            while((this->echiquierAff[--posY][posX]->getPiece()->getType() == 'v') && (posY > 0)){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 4: // Y et X-1
            while((this->echiquierAff[posY][--posX]->getPiece()->getType() == 'v') && (posX > 0)){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 3: // Y et X+1
            while((this->echiquierAff[posY][++posX]->getPiece()->getType() == 'v') && (posX < 8)){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 0: // Y+1 et X+1
            while((this->echiquierAff[++posY][++posX]->getPiece()->getType() == 'v') && ((posX < 8) || (posY < 8))){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 2: // Y+1 et X-1
            while((this->echiquierAff[++posY][--posX]->getPiece()->getType() == 'v') && ((posX > 0) || (posY < 8))){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 5: // Y-1 et X+1
            while((this->echiquierAff[--posY][++posX]->getPiece()->getType() == 'v') && ((posX < 8) || (posY > 0))){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        case 7: // Y-1 et X-1
            while((this->echiquierAff[--posY][--posX]->getPiece()->getType() == 'v') && ((posX > 0) || (posY > 0))){
                if(trouvPieceCEchec(cJ,posX,posY))
                    return false;
            }
            break;
        default:
            posX = -1;
            posY = -1;
            // Attaque cavalier ?
            //Gauche Bas
            if(X-2 >= 0 && Y-1 >= 0){
                if(this->echiquierAff[Y-1][X-2]->getPiece()->getCouleur() != coul && this->echiquierAff[Y-1][X-2]->getPiece()->getType() == 'c') {
                    posX = X - 2;
                    posY = Y - 1;
                }
            }
            //Gauche Haut
            if(X-2 >= 0 && Y+1 < 8){
                if(this->echiquierAff[Y+1][X-2]->getPiece()->getCouleur() != coul && this->echiquierAff[Y+1][X-2]->getPiece()->getType() == 'c') {
                    posX = X - 2;
                    posY = Y + 1;
                }
            }
            //Bas Gauche
            if(X-1 >= 0 && Y+2 < 8){
                if(this->echiquierAff[Y+2][X-1]->getPiece()->getCouleur() != coul && this->echiquierAff[Y+2][X-1]->getPiece()->getType() == 'c') {
                    posX = X - 1;
                    posY = Y + 2;
                }
            }
            //Bas Droite
            if(X+1 < 8 && Y+2 < 8){
                if(this->echiquierAff[Y+2][X+1]->getPiece()->getCouleur() != coul && this->echiquierAff[Y+2][X+1]->getPiece()->getType() == 'c') {
                    posX = X + 1;
                    posY = Y + 2;
                }
            }
            //Droite Bas
            if(X+2 < 8 && Y+1 < 8){
                if(this->echiquierAff[Y+1][X+2]->getPiece()->getCouleur() != coul && this->echiquierAff[Y+1][X+2]->getPiece()->getType() == 'c') {
                    posX = X + 2;
                    posY = Y + 1;
                }
            }
            //Droite Haut
            if(X+2 < 8 && Y-1 >= 0){
                if(this->echiquierAff[Y-1][X+2]->getPiece()->getCouleur() != coul && this->echiquierAff[Y-1][X+2]->getPiece()->getType() == 'c') {
                    posX = X + 2;
                    posY = Y - 1;
                }
            }
            //Haut Droite
            if(X+1 < 8 && Y-2 >= 0){
                if(this->echiquierAff[Y-2][X+1]->getPiece()->getCouleur() != coul && this->echiquierAff[Y-2][X+1]->getPiece()->getType() == 'c') {
                    posX = X + 1;
                    posY = Y - 2;
                }
            }
            //Haut Gauche
            if(X-1 >= 0 && Y-2 >= 0){
                if(this->echiquierAff[Y-2][X-1]->getPiece()->getCouleur() != coul && this->echiquierAff[Y-2][X-1]->getPiece()->getType() == 'c') {
                    posX = X - 1;
                    posY = Y - 2;
                }
            }
            break;
    }

    // TEST POUR MANGER LA PIECE QUI ATTAQUE
    if( (posX != -1) && (posY != -1) && (this->echiquierAff[posY][posX]->getPiece()->getCouleur() != 'v') && (this->echiquierAff[posY][posX]->getPiece()->getCouleur() != coul) ){
        return !this->trouvPieceCEchec(cJ,posX,posY);
    }

    return true;
}

/**********************************/

bool PlateauAffichage::echecRoiJoueurActif(bool c) {
    this->majEchec();
    if(c){
        for(short i=0 ; i < 8 ; i++){
            for(short j=0 ; j < 8 ; j++){
                if((this->echiquierAff[i][j]->getPiece()->getType() == 'r') && (this->echiquierAff[i][j]->getPiece()->getCouleur() == 'b'))
                    return  ( !this->echiquierAff[i][j]->getEchecB() );
            }
        }
    }
    else{
        for(short i=0 ; i < 8 ; i++){
            for(short j=0 ; j < 8 ; j++){
                if ((this->echiquierAff[i][j]->getPiece()->getType() == 'r') && (this->echiquierAff[i][j]->getPiece()->getCouleur() == 'n'))
                    return  ( !this->echiquierAff[i][j]->getEchecN() );
            }
        }
    }
    return false;
}

/**********************************/

bool PlateauAffichage::jouerCoupVerif(bool cJ, CoupE c) {
    return ( this->deplacerPiece(c) && this->echecRoiJoueurActif(cJ) ) ;
}

/**********************************/

bool PlateauAffichage::jouerCoupVerifMat(bool cJ, CoupE c) {
    bool rep;

    for(short i=0 ; i < 8 ; i++){
        for(short j=0 ; j < 8 ; j++){
            this->echiquier[i][j]->copierCase(this->echiquierAff[i][j]);
        }
    }
    rep = this->jouerCoupVerif(cJ,c);
    for(short i=0 ; i < 8 ; i++){
            for(short j=0 ; j < 8 ; j++){
                this->echiquierAff[i][j]->copierCase(this->echiquier[i][j]);
            }
        }

    return rep;

}

/**********************************/

bool PlateauAffichage::jouerCoupVerifSauv(bool cJ, CoupE c) {
    bool rep;

    for(short i=0 ; i < 8 ; i++){
        for(short j=0 ; j < 8 ; j++){
            this->echiquier[i][j]->copierCase(this->echiquierAff[i][j]);
        }
    }
    rep = this->jouerCoupVerif(cJ,c);
    if(!rep)
        for(short i=0 ; i < 8 ; i++){
            for(short j=0 ; j < 8 ; j++){
                this->echiquierAff[i][j]->copierCase(this->echiquier[i][j]);
            }
        }

    return rep;

}

/**********************************/

void PlateauAffichage::majEchec() {
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            this->echiquierAff[i][j]->setEchecN(false);
            this->echiquierAff[i][j]->setEchecB(false);
        }
    }
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            //cout << "Avant -> piece echiquier: " << this->getCaseE(i,j)->getPiece()->getType() << " | piece echiquierAff: " << this->getCaseA(i,j)->getPiece()->getType() << endl;
            this->getCaseE(i,j)->setPiece(this->getCaseA(i,j)->getPiece());
            //cout << "Après -> piece echiquier: " << this->getCaseE(i,j)->getPiece()->getType() << " | piece echiquierAff: " << this->getCaseA(i,j)->getPiece()->getType() << endl;
        }
    }
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            this->echiquierAff[i][j]->getPiece()->marqueCaseEchec(this,i,j);
        }
    }
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            this->getCaseA(i,j)->setEchecB(this->getCaseE(i,j)->getEchecB());
            this->getCaseA(i,j)->setEchecN(this->getCaseE(i,j)->getEchecN());
        }
    }

    /*
    cout << "================AFFICHAGE================" << endl;

    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            cout << this->getCaseA(i,j)->getPiece()->getType() << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Echec case Blanc: " << endl << endl;
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            cout << this->getCaseA(i,j)->getEchecB() << " ";
        }
        cout << endl;
    }
    cout << endl << "Echec case Noir: " << endl << endl;
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            cout << this->getCaseA(i,j)->getEchecN() << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "================NORMAL================" << endl;

    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            cout << this->getCaseE(i,j)->getPiece()->getType() << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "Echec case Blanc: " << endl << endl;
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            cout << this->getCaseE(i,j)->getEchecB() << " ";
        }
        cout << endl;
    }
    cout << endl << "Echec case Noir: " << endl << endl;
    for(short i=0 ; i<8 ; i++ ){
        for(short j=0 ; j < 8 ; j++ ) {
            cout << this->getCaseE(i,j)->getEchecN() << " ";
        }
        cout << endl;
    }
    cout << endl;
    */
}

/**********************************/

void PlateauAffichage::tournerPlateauAff(bool couleur) {
    if(couleur){
        for(short i=0 ; i < 8 ; i++) {
            for (short j = 0; j < 8; j++) {
                this->addWidget(this->echiquierAff[i][j],i+1,j+1);
            }
            this->addWidget(this->chiffre[i],i+1,0);
        }
    }
    else{
        for(short i=7 ; i >= 0 ; i--) {
            for (short j=7 ; j >= 0 ; j--) {
                //cout << (8-i) << endl;
                this->addWidget(this->echiquierAff[i][j],8-i,8-j);
            }
            this->addWidget(this->chiffre[i],8-i,0);
        }
    }
}

/**********************************/

Piece * PlateauAffichage::promotionAff(char couleur) {
    QMessageBox msgBox;
    msgBox.setText("The document has been modified.");
    msgBox.setInformativeText("Do you want to save your changes?");
    QPushButton* pButtonTour = msgBox.addButton("Tour",QMessageBox::YesRole);
    QPushButton* pButtonCavalier = msgBox.addButton("Cavalier",QMessageBox::YesRole);
    QPushButton* pButtonFou = msgBox.addButton("Fou",QMessageBox::YesRole);
    QPushButton* pButtonRoi = msgBox.addButton("Roi",QMessageBox::YesRole);
    QPushButton* pButtonDame = msgBox.addButton("Dame",QMessageBox::YesRole);
    QPushButton* pButtonPion = msgBox.addButton("Pion",QMessageBox::YesRole);
    msgBox.exec();
    if(msgBox.clickedButton() == reinterpret_cast<QAbstractButton *>(pButtonTour)){
        if(couleur=='b'){
            return new Tour('t',couleur,true,tourBlanc);
        }
        else{
            return new Tour('t',couleur,true,tourNoir);
        }
    }
    if(msgBox.clickedButton() == reinterpret_cast<QAbstractButton *>(pButtonCavalier)){
        if(couleur=='b'){
            return new Cavalier('c',couleur,true,chevalBlanc);
        }
        else{
            return new Cavalier('c',couleur,true,chevalNoir);
        }
    }
    if(msgBox.clickedButton() == reinterpret_cast<QAbstractButton *>(pButtonFou)){
        if(couleur=='b'){
            return new Fou('f',couleur,true,fouBlanc);
        }
        else{
            return new Fou('f',couleur,true,fouNoir);
        }
    }
    if(msgBox.clickedButton() == reinterpret_cast<QAbstractButton *>(pButtonRoi)){
        if(couleur=='b'){
            return new Roi('r',couleur,true,roiBlanc);
        }
        else{
            return new Roi('r',couleur,true,roiNoir);
        }
    }
    if(msgBox.clickedButton() == reinterpret_cast<QAbstractButton *>(pButtonDame)){
        if(couleur=='b'){
            return new Dame('d',couleur,true,dameBlanc);
        }
        else{
            return new Dame('d',couleur,true,dameNoir);
        }
    }
    if(couleur=='b'){
        return new Pion('p',couleur,true,pionBlanc);
    }
    else{
        return new Pion('p',couleur,true,pionNoir);
    }

}