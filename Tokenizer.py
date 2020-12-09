#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__
#pragma warning(disable:4786)
#include <string>
#include <vector>
typedef std::vector<std::string> vstring;


class Tokenizer {
public:
	Tokenizer() {};
	~Tokenizer() {};
	void setPosition( int pos );
	void resetPosition(void);
	void setString( std::string str );
	void setDelim( std::string str );
	void cleanString( char *str );
	void cleanString(std::string &str);
	void cleanString(std::string &str, std::string delim);
	void tokenize(std::string str, vstring &v);
	int getTokenNumber( std::string str );
	void tokenize( vstring &v );
	int countTokens();
	std::string currentToken();
	std::string firstToken();
	std::string nextToken();
	std::string lastToken();
private:
	bool isDelim(char c);
	void skipDelim();
private:
	std::string::iterator currentPosition;
	std::string thisToken;
	std::string delim;
	std::string buffer;

};


#endif


