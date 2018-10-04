

//include Qt
#include <QApplication>

#include <qdebug>
#include "SUi/SUiMainWindow.h"


int main(int argc, char *argv[])
{
	//standard start for Qt applications
	QApplication a(argc, argv);

	// add the path of the library (for the java script)
	QStringList  libraryPaths;
	libraryPaths << QCoreApplication::applicationDirPath () + "/plugins";
	QCoreApplication::setLibraryPaths ( libraryPaths  );


	SUiMainWindow mainWin;
	mainWin.setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
	mainWin.show();



	return a.exec();
		
}

