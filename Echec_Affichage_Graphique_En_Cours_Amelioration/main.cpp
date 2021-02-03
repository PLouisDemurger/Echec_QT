#include <Jeu.h>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QFile file(app.applicationDirPath()+"/styleSheet.css");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        app.setStyleSheet(stream.readAll());
        file.close();
    }

    Jeu *t = new Jeu();
    t->move(50,0);

    return app.exec();
}
