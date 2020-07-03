#pragma once

#include "../pch/stdafx.h"

/*
	Custom Exceptions class for ZSK to try and catch
	noteworthy exceptions and errors in the code

*/



class file_open_error : public std::invalid_argument
{
public:
	file_open_error(std::string);
};
// END file_open_error



class bad_date_component : public std::invalid_argument
{
public:
	bad_date_component(std::string);
};
// END bad_date_component



class missing_arguments : public std::logic_error
{
	//function ending exception if  not enough argument in comand line
public:
	missing_arguments(std::string);
};
//END missing_Arguments



class bad_mine_ID : public std::invalid_argument
{
	//function ending exception, this mine will not be appended to vector
public:
	bad_mine_ID(std::string);
};
//END bad_mine_ID



class bad_mine_status : public std::invalid_argument
{
	//function ending exception, this mine will not be appended to vector
public:
	bad_mine_status(std::string);
};
//END bad_mine_status



class bad_mine_flagMC : public std::invalid_argument
{
	//function ending exception, this mine will not be appended to vector
public:
	bad_mine_flagMC(std::string);
};

class no_such_object : public std::logic_error
{
	//function ending exception, this mine will not be appended to vector
public:
	no_such_object(std::string);
};