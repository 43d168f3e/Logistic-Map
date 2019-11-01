#include "generateTemplate.h"

///////////////////////////////////////////////////////////////////////////////
QString generateTemplateQ()
{
//    std::fstream myfile;
//    myfile.open(name.c_str(), std::ios::in | std::ios::out | std::ios::app);
//m_tmpFile.setFileTemplate("/mnt/ramdisk/XXXXXX.png");
    QTemporaryFile file;
    file.setFileTemplate("/tmp/XXXXXX.wav");
    file.open();// QTemporaryFile creates the file. QFile::copy will not be able to overwrite it,
                // so you will need to delete it first.
    file.close();
    return file.fileName();
}//QTemporaryFile gets destroyed, and deletes the file. Now QFile::copy will work fine.


///////////////////////////////////////////////////////////////////////////////
namespace fs = std::filesystem;
std::string generateTemplate() {
    std::string getcwdPOSIX = fs::current_path();
    getcwdPOSIX += "/";
//    QDir dir;
//    QString curr = dir.currentPath();
//    //QString Curr = dir.toNativeSeparators(const QString &pathName);
//    QString tmpPTH = dir.tempPath();

    //std::locale::global(std::locale("ja_JP.utf8"));
    std::time_t t = std::time(nullptr);
//    char mbstr[100];
//    if (std::strftime(mbstr, sizeof(mbstr), "%A %c", std::localtime(&t))) {
//        std::cout << mbstr << '\n';
//    }

    //time_t t = time(nullptr);   // get time now
    struct tm * now = localtime( & t );

    char buffer [96];
    memset( buffer , 0,  sizeof (buffer));
    std::strftime (buffer, sizeof (buffer) ,"%Y-%m-%d-%H-%M-%S-",now);
    std::string name{buffer};
    getcwdPOSIX += name;
//    getcwdPOSIX += "___";
//    getcwdPOSIX += mbstr;
    getcwdPOSIX += "XXXXXX.json";
    return getcwdPOSIX;
}
///////////////////////////////////////////////////////////////////////////////

generate_Template::generate_Template()
{

}
