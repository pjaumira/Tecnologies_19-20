//includes generics
#include "iostream"

//includes xml
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

int main() {

	//Codi doc practica

	rapidxml::xml_document<> doc;
	std::ifstream file(".. / .. /res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);

	std::cout << "Nombre de la raiz" << doc.first_node()->name() << "\n";
	std::cout << "Value" << doc.first_node()->value() << "\n";
}
