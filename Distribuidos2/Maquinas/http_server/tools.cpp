#include "tools.h"
#include <memory>

using namespace std;

Tools::Tools()
{

}
std::string Tools::execute(string cmd) const
{
	#ifdef _WIN32
	return std::string();
	#elif __unix__
	array<char, 128> buffer;
	string result;
	unique_ptr<FILE, decltype(&pclose)> pipe(popen(&cmd[0], "r"), pclose);
	if (!pipe) {
		throw runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
	#endif // _WIN32
}
std::string Tools::generarHash(string pass) const
{
    string str = "echo -n '" + pass + "' | openssl md5";
    str = Tools::execute(str);
    str = str.substr(9, str.size() - 1);
    return Tools::deleteSobrante(str);
}
string Tools::deleteSobrante(string str) const
{
    string resultado;
    for (size_t i = 0; i < str.size() - 1; i++) {
        resultado += str[i];
    }
    return resultado;
}
