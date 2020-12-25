#pragma once

#include "stdafx.h"
#include "stl_helpers.hpp"

/**
 * Genericky (pre viacero typov) reprezentuje podmienku.
 *
 * Usage:
 *  TNCondition<int>("5", "10", "<").resolve() -> true
 *  TNCondition<std::string>("ABC", "ABC", "<=").resolve() -> true
 *
 */
template<typename T>
class TNCondition
{
public:

	class SyntaxError {};


	TNCondition<T>(const std::string & left, const std::string & right, const std::string & op)
	: mOp(op)
	{
		mLeft = parseValue(left);
		mRight = parseValue(right);
		this->_resolve();
	}

//	virtual ~TNCodition<T>(void) {}

	inline bool resolve() const { return mResult; }

	inline T parseValue(const std::string & value)
	{
		std::istringstream iss(value);
		T v = parseValue(iss);
		if ( iss.bad() ) throw SyntaxError();
		return v;
	};

	inline virtual T parseValue(std::istringstream & input)
	{
		T value;
		input >> value;
		return value;
	};


private:

	inline void _resolve()
	{
		if ( mOp == "==" && mLeft == mRight ) mResult = true;
		else if ( mOp == "!=" && mLeft != mRight ) mResult = true;
		else if ( mOp == ">=" && mLeft >= mRight ) mResult = true;
		else if ( mOp == "<=" && mLeft <= mRight ) mResult = true;
		else if ( mOp ==  ">" && mLeft  > mRight ) mResult = true;
		else if ( mOp ==  "<" && mLeft  < mRight ) mResult = true;
		else mResult = false;
	}

	friend std::ostream & operator << (std::ostream & ostrm, const TNCondition & arg)
	{
		return ostrm << arg.mLeft << " " << arg.mOp << " " << arg.mRight << " (" << (arg.mResult ? "true":"false") << ")";
	}

	bool mResult;

	std::string mOp;
	T mLeft;
	T mRight;
};


/**
 * Špecializácia TNCodition<T>::parseValue pre typ string.
 * Dôvod: chceme medzery v stringu - takže ho obalíme do ''.
 * Nepodporuje escapovanie!
 */
template<> std::string TNCondition<std::string>::parseValue(std::istringstream & input)
{
	char c = input.peek();
	std::string value;

	input >> std::ws;

	if ( c == '\'' || c == '"' )
	{
		input.get();
		getline(input, value, c);
	}

	else
	{
		input >> value;
	}

	return value;
}
