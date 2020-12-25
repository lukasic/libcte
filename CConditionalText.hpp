#pragma once

#include "stdafx.h"


class CConditionalText
{
public:
	
	CConditionalText(const std::string & text)
	: mText(text)
	{}

	virtual ~CConditionalText() {}

	/**
	 * Nastavenie hodnoty premennej, ktora sa vyskytuje v sablone.
	 *
	 */
	bool setVariable(const std::string & name, const std::string & value, bool replace = false);

	/**
	 * Nastavenie hodnoty premennej, ktora sa vyskytuje v sablone.
	 * Pretazena metoda prijimajuca float.
	 */
	bool setVariable(const std::string & name, float value, bool replace = false);

	/**
	 * Nastavenie hodnoty premennej, ktora sa vyskytuje v sablone.
	 * Pretazena metoda prijimajuca double.
	 */
	bool setVariable(const std::string & name, double value, bool replace = false);

	/**
	 * Nastavenie hodnoty premennej, ktora sa vyskytuje v sablone.
	 * Pretazena metoda prijimajuca int.
	 *
	 */
	bool setVariable(const std::string & name, int value, bool replace = false);

	/**
	 * Nastavenie hodnoty premennej, ktora sa vyskytuje v sablone.
	 * Pretazena metoda prijimajuca long.
	 *
	 */
	bool setVariable(const std::string & name, long value, bool replace = false);

	/**
	 * Nahradí v texte všetky známe premenné. Spustiť po nastavení všetkých premenných.
	 * Známa premenná je taká, ktorú sme špecifikovali metódou setVariable.
	 *
	 * TODO: metóda je neefektívna a pomalá pri vyššom počte premenných alebo
	 *   rozsiahlejšom texte. Ak to bude potrebné, zvážiť prepísanie.
	 */
	void compile();

	/**
	 * Vyhodnotí všetky podmienky v texte a vygeneruje výstupný text.
	 *
	 */
	const std::string & resolve();

	/**
	 * Preťažený operátor pre výstup do streamu.
	 */
	friend inline std::ostream & operator << (std::ostream & ostrm, const CConditionalText & arg)
	{
		return ostrm << arg.mResolved;
	}

	#ifdef DEBUG
	/**
	 * Do zadaného streamu vypíše aktuálny stav rozparsovaných tokenov.
	 * Vhodné pri debugovaní.
	 */
	void printTokens(std::ostream & ostrm) const;
	#endif

private:

	/**
	 * Parsuje skompilovaný text do jednotlivých tokenov, ktoré je možné vyhodnotiť
	 * buď ako surový text alebo podmienku.
	 */
	void parseTokens();

	/**
	 * Vyhodnotí rozparsovanú podmienku, ktorá sa nachádza
	 * v tokenu.
	 *
	 * Pre úplnosť syntax:
	 *   (typ) value1 oper value2
	 *   - ak (typ) nie je zadaný, vyhodnotí sa ako (str)
	 */
	static bool resolveCondition(const std::string & cond);

	/**
	 * Vytiahne zo stringu token (text, alebo podmienku).
	 *
	 */
	static std::string getToken(const std::string & str);

	//< Aktuálne rozparsované tokeny (texty a podmienky)
	std::vector<std::string> mTokens;

	//< Pôvodný text, ktorý sme dostali na vstupe.
	const std::string mText;

	//< Text, v ktorom sú nahradené premenné.
	std::string mCompiled;

	//< Vyhodnotený text, výstup celého procesu.
	std::string mResolved;

	//< Interná databáza premenných, ktoré sa nahradia v texte.
	std::map<const std::string, const std::string> mVars;
};
