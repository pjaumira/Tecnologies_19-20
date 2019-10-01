//includes generics
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <istream>
#include <sstream>

//Includes Docs
#include "Enemies.cpp"

//includes xml
#include "../../dep/inc/XML/rapidxml.hpp"
#include "../../dep/inc/XML/rapidxml_utils.hpp"
#include "../../dep/inc/XML/rapidxml_iterators.hpp"
#include "../../dep/inc/XML/rapidxml_print.hpp"

int main() {

	//Creacion Doc xml
	rapidxml::xml_document<> doc;
	std::ifstream file;
	file.open("../../res/files/config.xml");
	std::stringstream buffer;
	buffer << file.rdbuf();
	file.close();
	std::string content(buffer.str());
	doc.parse<0>(&content[0]);
	//Puntero a la raiz
	rapidxml::xml_node<> *pRoot = doc.first_node();

	for (rapidxml::xml_node<> *pNode = pRoot->first_node("skeleton"); pNode; pNode->next_sibling()) {
		std::cout << pNode->name() << ':' << '\n';
		//imprimir els atributs del enemic
		for (rapidxml::xml_node<> *pNode2 = pNode->first_node(); pNode2; pNode2 = pNode2->next_sibling()) {
			std::cout << pNode2->name() << ':' << pNode2->value() << '\n';
		};
		std::cout << '\n';
	}
};
