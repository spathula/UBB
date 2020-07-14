#include "Assignment12.h"
#include <QtWidgets/QApplication>
#include <fstream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
    std::ifstream file("config.txt");
    std::string repository_mode;
    std::getline(file, repository_mode);
    if (repository_mode == "file")
    {
        Repository repository{};
        mylist_CSV my_CSV{};
        mylist_HTML my_HTML{};
        Validate validator{};
        Service service{ repository, my_CSV, my_HTML, validator };
        RecordingsGUI gui{ service };
        gui.show();
        return a.exec();
    }
    else if (repository_mode == "memory")
    {
        Repository_InMemory repository{};
        Validate validator{};
        Service_InMemory service{ repository, validator };
        RecordingsGUI_InMemory gui{ service };
        gui.show();
        return a.exec();
    }
}
