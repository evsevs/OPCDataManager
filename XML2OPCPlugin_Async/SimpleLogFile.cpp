
#include "stdafx.h"
#include "SimpleLogFile.h"

bool PhysicalCreatePath(std::string PathToCreate)
{

	std::string::size_type pos,bpos;
	bool bres;	
	int nch=2;
	DWORD er=0;
	bpos=pos=PathToCreate.find("\\");
	nch=1;
	while (pos!=std::string::npos)
	{
		pos=PathToCreate.find("\\",pos+nch);
		printf("Create %s\n",PathToCreate.substr(0,pos).c_str());
		bres=CreateDirectory(PathToCreate.substr(0,pos).c_str(),NULL);
		if (!bres)
			if (GetLastError()!=183)
				break;
	}
		
	return bres;
	
}
std::string CSimpleLogFile::GetPostfix()
{
	return m_LogFilePostfix;
}
//удалить каталог
DWORD PhysicalDeleteDir(std::string DirToDel)
{
	bool bres=0;
	DWORD er=0;
	
	bres=RemoveDirectory(DirToDel.c_str());
	if (!bres)
		er=GetLastError();//145 - not empty
	if (er==145)//not empty
	{
		//ищем и ...удаляем все что движется :-)
		er=0;
		WIN32_FIND_DATA fd;
		HANDLE hFind=FindFirstFile((DirToDel+"\\*").c_str(),&fd);
		
		if (hFind!=INVALID_HANDLE_VALUE) //Можно продолжать поиск
		{
			do
			{   //Вывод структуры
				//printf("find = %s\n",fd.cFileName);
				if ((fd.dwFileAttributes==FILE_ATTRIBUTE_DIRECTORY)&&(strcmp(fd.cFileName,"..")!=0)&&(strcmp(fd.cFileName,".")!=0))
				{
					printf("Dir= %s\n",fd.cFileName);
					er=PhysicalDeleteDir(DirToDel+"\\"+fd.cFileName);
					if (er)
						break;
				}
				else if (fd.dwFileAttributes!=FILE_ATTRIBUTE_DIRECTORY)
				{
					printf("File= %s\n",fd.cFileName);
					if (!DeleteFile((DirToDel+"\\"+fd.cFileName).c_str()))
						er=GetLastError();
					if (er)
						break;
				}
			}while(FindNextFile(hFind,&fd));
			FindClose(hFind);
			
			if (!er)
				if (!RemoveDirectory(DirToDel.c_str()))
					er=GetLastError();
		}
	}
	return er;
}


///////////////////////////////////////////////////////////////////////////////
//						SimpleLogFile [2/20/2002]
///////////////////////////////////////////////////////////////////////////////
void	CSimpleLogFile::SetNewFullLogName(std::string full)
{
	bSetFull=true;
	m_FullLogFileName=full;
}	
void CSimpleLogFile::SetNewLogFile(std::string LogFilePrefix,std::string LogFilePath)
{
	bSetFull=false;
	m_LogFilePrefix=LogFilePrefix;
	m_LogFilePath=LogFilePath;

	m_LogFilePath.empty()?m_FullLogFilePrefix=m_LogFilePrefix:m_FullLogFilePrefix=m_LogFilePath+"\\"+m_LogFilePrefix;
}

void CSimpleLogFile::operator <<(_variant_t Val)
{
	std::string fullog;

	if (bSetFull)
		fullog=m_FullLogFileName;
	else
		fullog=m_FullLogFilePrefix+m_LogFilePostfix+m_LogFileEnd;
	m_file.open(fullog.c_str(),std::ios_base::app);
	if (!m_Mode)
	{
		SYSTEMTIME st;
		GetLocalTime(&st);
		::GetDateFormat( LOCALE_USER_DEFAULT,0,&st,m_strDateFormat,m_FormatTime,sizeof(char)*60 );
		m_file<<m_FormatTime;
		::GetTimeFormat( LOCALE_USER_DEFAULT,0,&st,m_strTimeFormat,m_FormatTime,sizeof(char)*60 );
		m_file<<m_FormatTime;
		char ch[10];
		m_file<<"."<<itoa(st.wMilliseconds,ch,10);
	}

	m_file<<" "<<(_bstr_t)Val<<std::ios_base::end;
	m_file.close();
}

bool CSimpleLogFile::SetTimeFormat(char *Format)
{
	if (Format==NULL) return false;
	if (strlen(Format)>MAX_FORMAT_LEN) return false;
	strcpy(m_strTimeFormat,Format);
	return true;
}


double CSimpleLogFile::GetLastLogCreateTime()
{
	WIN32_FIND_DATA wfd;
	SYSTEMTIME st;
	double LastTime=0;
	HANDLE hFind=FindFirstFile((m_FullLogFilePrefix+"*"+m_LogFileEnd).c_str(),&wfd);

   if (hFind!=INVALID_HANDLE_VALUE) //Можно продолжать поиск
   {
	   do
	   {   //Вывод структуры
	   }while(FindNextFile(hFind,&wfd));
		FindClose(hFind);
		if(FileTimeToSystemTime(&wfd.ftCreationTime,&st))
			SystemTimeToVariantTime(&st,&LastTime);
   }
   return LastTime;
}

bool CSimpleLogFile::GenerateLogFile(bool AddDate,bool SetAsEnvir)
{
	bool bres=false;
	SYSTEMTIME st;
//берем системное
	GetLocalTime(&st);
	double SysTime;
	SystemTimeToVariantTime(&st,&SysTime);	
	//m_FullLogFilePrefix+m_LogFilePostfix+m_LogFileEnd
	if(AddDate)
	{
		bAddDateToName=AddDate;
		if ((m_LogFileTime=GetLastLogCreateTime())==0)
		{
			//Формируем постфикс
			char x[10];
			GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&st,"ddMMyy",x,sizeof(char)*10);
			m_LogFilePostfix=x;
		}
		else
		{
			//может сменить?
			if(((SysTime-m_LogFileTime)>m_LogFileKeepTime)||((m_LogFileTime-SysTime)>1))
			//берем новое
				m_LogFileTime=SysTime;
			
				
			//формируем постфикс
			VariantTimeToSystemTime(m_LogFileTime,&st);
			char x[10];
			GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,&st,"ddMMyy",x,sizeof(char)*10);
			m_LogFilePostfix=x;
		}
	}

	if(SetAsEnvir)
		SetAsEnviron();
	
	return bres;
}

bool	CSimpleLogFile::SetAsEnviron()
{
	if (m_LogFilePath=="") return true;
	char *buf = new char[1500];
	DWORD SBuf = 1500;
	
	if (m_bIsSetEnvirFlag==FALSE) {
		
		if (GetEnvironmentVariable("PATH",buf,SBuf)==0)  
			Beep(200,100);
		else {
			/**/		strcat(buf,";");
			/**/		strcat(buf,m_LogFilePath.c_str());
			/**/		strcat(buf,";");
			if  (SetEnvironmentVariable("PATH",buf)==0) 
				Beep(200,100);		
			else
				m_bIsSetEnvirFlag = TRUE;
		}
	} 

	delete[] buf;

	return (bool)m_bIsSetEnvirFlag;
}

///////////////////////////////////////////////////////////////////////////////
//						LogFile_CS [2/20/2002]
///////////////////////////////////////////////////////////////////////////////


CLogFile_CS::CLogFile_CS()
{	InitializeCriticalSection(&m_cs);}

CLogFile_CS::CLogFile_CS(CRITICAL_SECTION &cs)
{
	m_cs=cs;
	InitializeCriticalSection(&m_cs);
}

CLogFile_CS::~CLogFile_CS()
{	DeleteCriticalSection(&m_cs);}

void CLogFile_CS::Lock()
{EnterCriticalSection(&m_cs);}

void CLogFile_CS::UnLock()
{	LeaveCriticalSection(&m_cs);}

void CLogFile_CS::operator<<(_variant_t Val)
{
	Lock();
	CSimpleLogFile::operator <<(Val);
	UnLock();
}

void CLogFile_CS::operator <<(int ValInt)
{
	Lock();
	CSimpleLogFile::operator <<(ValInt);
	UnLock();
}
void CLogFile_CS::SetNewFullLogName(std::string full)
{
	Lock();
	CSimpleLogFile::SetNewFullLogName(full);
	UnLock();
}
void CLogFile_CS::SetNewLogFile(std::string LogFilePrefix,std::string LogFilePath)
{
	Lock();
	CSimpleLogFile::SetNewLogFile(LogFilePrefix,LogFilePath);
	UnLock();
}


bool CLogFile_CS::GenerateLogFile(bool AddDate,bool SetAsEnvir)
{
	
	Lock();
	BOOL bres=false;
	bres=CSimpleLogFile::GenerateLogFile(AddDate,SetAsEnvir);
	UnLock();
	return bres;
}