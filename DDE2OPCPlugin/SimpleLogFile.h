#ifndef __SimpleLogFile_H_
#define __SimpleLogFile_H_

#include <fstream>
#include <string>
#include <comdef.h>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_FORMAT_LEN 20


//////////////////////////////////////////////////////////////////////////////////
// Functions [2/20/2002]
//////////////////////////////////////////////////////////////////////////////////
//создает путь на диске
bool PhysicalCreatePath(std::string PathToCreate);
//удалить каталог
DWORD PhysicalDeleteDir(std::string DirToDel);


class CSimpleLogFile  
{
public:
	bool bSetFull;
	float m_LogFileKeepTime;
	bool GenerateLogFile(bool AddDate=true,bool SetAsEnvir=false);

	bool bAddDateToName;
	//получение\установка формата времени
	bool SetTimeFormat(char *Format);
	std::string GetTimeFormat(){	return m_strTimeFormat;}

	//изменяет текущий режим на противоположный
	inline bool ChangeMode(){ return m_Mode=!m_Mode;	}
	//устанавливает режим (0-писать со штампом времени, 1- писать без штампа).
	//по умолчанию - режим 0;
	inline bool SetMode(bool Mode=1){return m_Mode = Mode;}
	//конструктор по умолчанию
	CSimpleLogFile():m_LogFilePrefix("LogFile"),m_LogFilePath(""),m_Mode(false)
	{
		m_LogFilePath.empty()?m_FullLogFilePrefix=m_LogFilePrefix:m_FullLogFilePrefix=m_LogFilePath+"\\"+m_LogFilePrefix;
		strcpy(m_strTimeFormat,"HH:mm:ss");
		strcpy(m_strDateFormat,"yyyy-MM-dd ");
		bAddDateToName=true;
		m_LogFileEnd=".log";
		m_LogFileTime=0;
		m_LogFilePostfix="";
		m_LogFileKeepTime=7;//суток
		m_bIsSetEnvirFlag=FALSE;
		bSetFull=false;
	}
	
	CSimpleLogFile(const std::string FilePrefix,const std::string FilePath="",const bool AddDate=true,const bool Mode=false):
	m_LogFilePrefix(FilePrefix),m_LogFilePath(FilePath),bAddDateToName(AddDate),m_Mode(Mode)
	{
		m_LogFilePath.empty()?m_FullLogFilePrefix=m_LogFilePrefix:m_FullLogFilePrefix=m_LogFilePath+"\\"+m_LogFilePrefix;
		strcpy(m_strTimeFormat,"HH:mm:ss");
		strcpy(m_strDateFormat,"yyyy-MM-dd ");
		m_LogFileEnd=".log";
		m_LogFileTime=0;
		m_LogFilePostfix="";
		m_LogFileKeepTime=7;//суток
		m_bIsSetEnvirFlag=FALSE;
		bSetFull=false;
	}

	virtual	~CSimpleLogFile()
	{
		m_file.close();
	}
	std::string GetPostfix();
	//установка имени файла и пути, где он будет находится. Причем путь должен быть БЕЗ '\' в конце
	virtual void	SetNewLogFile(std::string LogFilePrefix,std::string LogFilePath);
	virtual void	SetNewFullLogName(std::string full);
	//писать в лог-файл
	virtual void	operator<<(_variant_t Val);

	virtual void	operator<<(int ValInt){	operator <<((_variant_t)(long)ValInt);}


private:
	bool SetAsEnviron();

	BOOL m_bIsSetEnvirFlag;
	std::string m_LogFileEnd;
	char m_strTimeFormat[MAX_FORMAT_LEN];
	char m_strDateFormat[MAX_FORMAT_LEN];
	char m_FormatTime[60];			//строка для получения формата времени
//	CEVSTime m_curtime;				//класс для получения\форматирования строки времени 
	std::ofstream m_file;				//файл для вывода (поток)

	std::string m_FullLogFileName;//самое полное!!!
	
	std::string		m_FullLogFilePrefix;		//полное имя файла с путем до него
	std::string		m_LogFilePrefix;		//просто имя файда (без пути)
	std::string		m_LogFilePath;		//просто путь до лог-файла.
	bool m_Mode;//режим записи.(0-писать со штампом времени, 1- писать без штампа)
protected:
	std::string m_LogFilePostfix;
	double m_LogFileTime;
	virtual double GetLastLogCreateTime();//Используется при первом создании лог-файла
};


class CLogFile_CS : public CSimpleLogFile  
{
public:
	bool GenerateLogFile(bool AddDate=true,bool SetAsEnvir=false);
	CLogFile_CS(CRITICAL_SECTION &cs);

	CLogFile_CS();
	virtual ~CLogFile_CS();
	virtual void operator<<(_variant_t Val);

	virtual void operator<<(int ValInt);

	virtual void SetNewLogFile(std::string LogFilePrefix,std::string LogFilePath);
	virtual void SetNewFullLogName(std::string full);
private:
	void UnLock();
	void Lock();
	CRITICAL_SECTION m_cs;
};


/////////////////////////////////////////////////////////////////////////////////
// Functions [2/20/2002]
//////////////////////////////////////////////////////////////////////////////////
/*bool PhysicalCreatePath(std::string PathToCreate)
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
*/
#endif // !defined(_SimpleLogFile_H_)

