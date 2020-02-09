#include "stdafx.h"
#include "filterstring.h"

CFilterString::CFilterString(void)
{
}

CFilterString::~CFilterString(void)
{
}
int CFilterString::ConvertCase( int c, BOOL bCaseSensitive )
{
	return bCaseSensitive ? c : toupper(c);
}

//*************************************************************************          
// return TRUE if String Matches Pattern -- 
// -- uses Visual Basic LIKE operator syntax
// CAUTION: Function is recursive
//*************************************************************************          
BOOL CFilterString::MatchPattern( LPCTSTR String, LPCTSTR Pattern, BOOL bCaseSensitive )
{ 
    TCHAR   c, p, l;
	if ((*Pattern==' ')||(*Pattern==0))
		return TRUE;
    for (; ;)
    {
        switch (p = ConvertCase( *Pattern++, bCaseSensitive ) )
        {
        case 0:                             // end of pattern
            return *String ? FALSE : TRUE;  // if end of string TRUE

        case _T('*'):
            while (*String) 
            {               // match zero or more char
                if (MatchPattern (String++, Pattern, bCaseSensitive))
                    return TRUE; 
            }
            return MatchPattern (String, Pattern, bCaseSensitive );

        case _T('?'):
            if (*String++ == 0)             // match any one char 
                return FALSE;               // not end of string 
            break; 

        case _T('['): 
            // match char set 
            if ( (c = ConvertCase( *String++, bCaseSensitive) ) == 0)
                return FALSE;                // syntax 
            l = 0; 
            if( *Pattern == _T('!') )  // match a char if NOT in set []
            {
                ++Pattern;

                while( (p = ConvertCase( *Pattern++, bCaseSensitive) )
                         != _T('\0') ) 
                {
                    if (p == _T(']'))     // if end of char set, then 
                        break;            // no match found 

                    if (p == _T('-')) 
                    {   // check a range of chars? 
                        p = ConvertCase( *Pattern, bCaseSensitive );
                        // get high limit of range 
                        if (p == 0  ||  p == _T(']')) 
                            return FALSE;     // syntax 

                        if (c >= l  &&  c <= p) 
                            return FALSE;     // if in range, return FALSE 
                    } 
                    l = p;
                    if (c == p)               // if char matches this element 
                        return FALSE;         // return false 
                } 
            }
            else    // match if char is in set []
            {
                while( (p = ConvertCase( *Pattern++, bCaseSensitive) ) 
                         != _T('\0') ) 
                {
                    if (p == _T(']'))         // if end of char set, then 
                        return FALSE;         // no match found 

                    if (p == _T('-')) 
                    {   // check a range of chars? 
                        p = ConvertCase( *Pattern, bCaseSensitive );
                        // get high limit of range 
                        if (p == 0  ||  p == _T(']')) 
                            return FALSE;       // syntax 

                        if (c >= l  &&  c <= p) 
                            break;              // if in range, move on 
                    } 
                    l = p;
                    if (c == p)                 // if char matches this element 
                        break;                  // move on 
                } 

                while (p  &&  p != _T(']'))     // got a match in char set 
                    p = *Pattern++;             // skip to end of set 
            }

            break; 

        case _T('#'):
            c = *String++; 
            if( !_istdigit( c ) )
                return FALSE;        // not a digit

            break;

        default: 
            c = ConvertCase( *String++, bCaseSensitive ); 
            if( c != p )            // check for exact char 
                return FALSE;                   // not a match 

            break; 
        } 
    } 
} 



// // Фильтрация по типу данных. если возвращено TRUE - соответствует заданному типу, иначе - нет
BOOL CFilterString::MatchType(VARTYPE vtFilterType, VARTYPE TagType)
{
	if (vtFilterType==VT_EMPTY)
		return TRUE;//игнорируем
	else
		return (vtFilterType==TagType);
}

// Фильтр по правам доступа. Если возвращено TRUE - соответствует, иначе - НЕТ
BOOL CFilterString::MatchAccessRights(DWORD dwAccessRightsFilter, DWORD dwTagAccessRights)
{
	if (dwAccessRightsFilter==0)
		return TRUE;//игнорируем
	else
		return ((dwAccessRightsFilter&dwTagAccessRights)>0);
}
