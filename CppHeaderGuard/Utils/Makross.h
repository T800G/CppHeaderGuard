//custom macros
#ifndef MAKROSS_5B7E52DE_7ADA_4d88_AFAC_296EFC8DDD43_
#define MAKROSS_5B7E52DE_7ADA_4d88_AFAC_296EFC8DDD43_
#pragma once

//bit checking routines
#define CHECKBIT(x,bit) ((x & bit)==bit)
#define HASBITS(x,bits) ((x & bits)!=0)
 
#ifdef _DEBUG
//short syntax for console messages
#define CONMSG(x) wprintf(_T(x))
#define CONMSGSTR(x) wprintf(x)
#define CONMSGSTRA(x) printf(x)
//short syntax for msgboxes
#define CONMSGVAR(x) {CString tmp800;tmp800.Append(x);wprintf(tmp800);}
#define MSGBOX(x) MessageBox(_T(x),_T("Debug"),MB_OK | MB_TASKMODAL)
#define MSGBOXV(x) MessageBox(x,_T("Debug"),MB_OK | MB_TASKMODAL)
#define MSGBOX0(x) MessageBox(NULL,_T(x),_T("Debug"),MB_OK | MB_TASKMODAL)
#define MSGBOXV0(x) MessageBox(NULL,x,_T("Debug"),MB_OK | MB_TASKMODAL)
#define MSGBOXVAR(x) {CString msgvar;msgvar.Append(x);MessageBox(msgvar,_T("Debug"),MB_OK | MB_TASKMODAL);}
#define MSGBOXVAR0(x) {CString msgvar;msgvar.Append(x);MessageBox(NULL,msgvar,_T("Debug"),MB_OK | MB_TASKMODAL);}
#else
#define CONMSG(x)
#define CONMSGSTR(x)
#define CONMSGSTRA(x)
#define CONMSGVAR(x)
#define MSGBOX(x)
#define MSGBOXV(x)
#define MSGBOX0(x)
#define MSGBOXV0(x)
#define MSGBOXVAR(x)
#define MSGBOXVAR0(x)
#endif


#endif//MAKROSS_5B7E52DE_7ADA_4d88_AFAC_296EFC8DDD43_
