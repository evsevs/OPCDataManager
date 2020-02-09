#pragma once
class CFilterString
{
public:
	CFilterString(void);
	virtual ~CFilterString(void);

	//*************************************************************************          
	//Фукнции взяты AS IS из документации по ОРС, зачем голову себе морочить?
	// return TRUE if String Matches Pattern -- 
	// -- uses Visual Basic LIKE operator syntax
	// CAUTION: Function is recursive
	//*************************************************************************          
	BOOL MatchPattern( LPCTSTR String, LPCTSTR Pattern, BOOL bCaseSensitive );
	private:
	inline int ConvertCase( int c, BOOL bCaseSensitive );
public:
	// // Фильтрация по типу данных. если возвращено TRUE - соответствует заданному типу, иначе - нет
	BOOL MatchType(VARTYPE vtFilterType, VARTYPE TagType);
	// Фильтр по правам доступа. Если возвращено TRUE - соответствует, иначе - НЕТ
	BOOL MatchAccessRights(DWORD dwAccessRightsFilter, DWORD dwTagAccessRights);
};
