#ifndef GENERATETEMPLATE_H
#define GENERATETEMPLATE_H


#include <filesystem>
#include <ctime>
#include <locale>
#include <tuple>

#include <QDir>
#include <QFile>
#include <QTemporaryFile>

///////////////////////////////////////////////////////////////////////////////
namespace fs = std::filesystem;
std::string generateTemplate();
///////////////////////////////////////////////////////////////////////////////
class generate_Template
{
public:
    generate_Template();
};

#endif // GENERATETEMPLATE_H
