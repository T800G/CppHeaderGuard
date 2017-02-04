#ifndef _B76EAD06_581D_40DD_AC54_A8C1A75AF5B4_
#define _B76EAD06_581D_40DD_AC54_A8C1A75AF5B4_

class CIncludeGen
{
public:

	CIncludeGen(void);//ctor
	void generate(LPCTSTR headerfile=NULL);
	CString GetIncludeGuardText() const {return m_text;}
	bool copy2clipboard(HWND clipbrdowner);

private:
	CString m_text;
	CString CreateGuid();

	C_SplitPath pathsplitter;

};

#endif//_B76EAD06_581D_40DD_AC54_A8C1A75AF5B4_
