#pragma once
class CFilterString
{
public:
	CFilterString(void);
	virtual ~CFilterString(void);

	//*************************************************************************          
	//������� ����� AS IS �� ������������ �� ���, ����� ������ ���� ��������?
	// return TRUE if String Matches Pattern -- 
	// -- uses Visual Basic LIKE operator syntax
	// CAUTION: Function is recursive
	//*************************************************************************          
	BOOL MatchPattern( LPCTSTR String, LPCTSTR Pattern, BOOL bCaseSensitive );
	private:
	inline int ConvertCase( int c, BOOL bCaseSensitive );
public:
	// // ���������� �� ���� ������. ���� ���������� TRUE - ������������� ��������� ����, ����� - ���
	BOOL MatchType(VARTYPE vtFilterType, VARTYPE TagType);
	// ������ �� ������ �������. ���� ���������� TRUE - �������������, ����� - ���
	BOOL MatchAccessRights(DWORD dwAccessRightsFilter, DWORD dwTagAccessRights);
};
