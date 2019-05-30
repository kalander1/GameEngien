#include "stdafx.h"
#include "JsonParser.h"



JsonParser::JsonParser()
{
	json j;

	j["object"] = { {"currency", "USD"}, {"value", 42.99} };
	j["object2"] = { {"currency", "EURO"}, {"value", 2.99} };

	ofstream o("pretty.json");
	o << j << std::endl;

	std::ifstream i("pretty.json");
	json z;
	i >> z;

	cout << z << endl;
}


JsonParser::~JsonParser()
{
}
