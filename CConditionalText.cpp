#include "stdafx.h"

#include "TNCondition.hpp"
#include "CConditionalText.hpp"

// ============================================================================
// ======= PUBLIC SECTION =====================================================
// ============================================================================


bool CConditionalText::setVariable(const std::string & name, const std::string & value, bool replace)
{
	if ( mVars.find(name) != mVars.end() )
	{
		if ( replace )
			mVars.erase(mVars.find(name));
		else
			return false;
	}

	mVars.insert( std::pair<const std::string, const std::string>(name, value) );
	return true;
}


bool CConditionalText::setVariable(const std::string & name, float value, bool replace)
{
	std::ostringstream oss;
	oss << value;
	return setVariable(name, oss.str(), replace);
}


bool CConditionalText::setVariable(const std::string & name, double value, bool replace)
{
	std::ostringstream oss;
	oss << value;
	return setVariable(name, oss.str(), replace);
}


bool CConditionalText::setVariable(const std::string & name, int value, bool replace)
{
	std::ostringstream oss;
	oss << value;
	return setVariable(name, oss.str(), replace);
}


bool CConditionalText::setVariable(const std::string & name, long value, bool replace)
{
	std::ostringstream oss;
	oss << value;
	return setVariable(name, oss.str(), replace);
}


void CConditionalText::compile()
{
	mResolved = "";
	mCompiled = mText;

	for (std::map<const std::string, const std::string>::iterator iterator = mVars.begin(); iterator != mVars.end(); ++iterator)
	{
		while (replace(mCompiled, "{$ " + (iterator->first) + " $}" , iterator->second) );
		while (replace(mCompiled, "{$"  + (iterator->first) + " $}" , iterator->second) );
		while (replace(mCompiled, "{ $" + (iterator->first) + "$}"  , iterator->second) );
		while (replace(mCompiled, "{$"  + (iterator->first) + "$}"  , iterator->second) );
	}
}


const std::string & CConditionalText::resolve()
{
	parseTokens();
	mResolved = "";

	std::ostringstream oss;
	oss.clear();

	int m = 0;
	bool print = true;

	std::vector<bool> level;
	level.push_back(true);

	for (unsigned i = 0; i < mTokens.size(); i++)
	{
		if ( mTokens[i] == "{% end %}" )
		{
			level.pop_back();
			continue;
		}

		else if ( mTokens[i].find("{%") == 0 && mTokens[i].find("%}") == mTokens[i].size()-2 )
		{
			std::string cond = mTokens[i].substr(2, mTokens[i].size()-4);
			print = CConditionalText::resolveCondition(cond);
			level.push_back(print);
		}

		else if (level.back())
			oss << mTokens[i];
	}

	mResolved = oss.str();
	return mResolved;
}


#ifdef DEBUG
void CConditionalText::printTokens(std::ostream & ostrm) const
{
	int m = 0;
	for (unsigned i = 0; i < mTokens.size(); i++)
	{
		bool flag = true;
		if ( mTokens[i] == "{% end %}" )
		{
			m -= 1;
			flag = false;
		}

		ostrm << margin(m) << mTokens[i];

		if (flag && mTokens[i].find("{%") == 0 && mTokens[i].find("%}") == mTokens[i].size()-2 )
		{
			m += 1;
			std::string cond = mTokens[i].substr(2, mTokens[i].size()-4);
			ostrm << " // " << CConditionalText::resolveCondition(cond);
		}

		ostrm << std::endl;
	}
}
#endif


// ============================================================================
// ======= PRIVATE SECTION ====================================================
// ============================================================================


void CConditionalText::parseTokens()
{
	mTokens.clear();

	const char * s = mCompiled.c_str();
	unsigned offset = 0;

	while ( offset < mCompiled.size() )
	{
		std::string token = CConditionalText::getToken(s);
		s = s + token.size();
		offset += token.size();
		mTokens.push_back(token);
	}
}


bool CConditionalText::resolveCondition(const std::string & cond)
{
	std::string type;
	std::string raw_left;
	std::string raw_op;
	std::string raw_right;

	std::istringstream iss(cond);

	// zahodime prazdne znaky
	iss >> std::ws;

	if ( iss.peek() == '(' )
		iss >> type;
	else
		type = "(str)";

	char c = iss.peek();
	if ( c == '\'' || c == '"' )
	{
		iss.get();
		getline(iss, raw_left, c);
	}
	else
		iss >> raw_left;

	iss >> raw_op;

	c = iss.peek();
	if ( c == '\'' || c == '"' )
	{
		iss.get();
		getline(iss, raw_left, c);
	}
	else
		iss >> raw_right;

	std::string left = raw_left;
	std::string right = raw_right;

	if ( type == "(str)" )    return TNCondition<std::string> (left, right, raw_op) . resolve();
	if ( type == "(int)" )    return TNCondition<int>         (left, right, raw_op) . resolve();
	if ( type == "(float)" )  return TNCondition<float>       (left, right, raw_op) . resolve();
	if ( type == "(double)" ) return TNCondition<double>      (left, right, raw_op) . resolve();
	if ( type == "(long)" )   return TNCondition<long>        (left, right, raw_op) . resolve();

	return false;
}


std::string CConditionalText::getToken(const std::string & str)
{
	int cmd_start = str.find("{% ");
	int cmd_end = str.find(" %}") + 3;

	if ( cmd_start != 0 )
		return str.substr(0, cmd_start);

	else
		return str.substr(cmd_start, cmd_end);
}
