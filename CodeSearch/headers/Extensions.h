#pragma once


enum Extensions
{
	notsupported = 0,
	c,
	cpp,
	h,
	cs,
	java,
	py,
	js,
	rb,
	swift,
	go,
	rs,
	ts,
};

enum TokenType 
{
	unknown = 0,
	CLASS,
	STRUCT,
	ENUM,
	FUNCTION
};