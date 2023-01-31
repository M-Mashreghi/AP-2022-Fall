
#include "Read_input.hpp"

using namespace std;


line read_command() {
	string data_line;
	getline(cin, data_line);
	line info = split_string(data_line, "command");
	return info;
}

line split_string(string str, string format) {
	char delimiter;
	delimiter = COMMAND_DELIMITER;
	line data_line;
	string data;
	while (str.size() > 0) {
		data = str.substr(0, str.find(delimiter));
		str.erase(0, data.length() + 1);
		data_line.push_back(data);
	}
	return data_line;
}

string IsInteger(string input)
{
	if (input.size() == 0)
		throw BAD_REQUEST;
	for (int i = 0; i < input.size(); i++)
	{
		if (!isdigit(input[i]))
			throw BAD_REQUEST;
	}
	return input;
}