#ifndef _MAIN_H
#define _MAIN_H

 
void Menu();
bool Init();
bool InitConfig();
bool InitLog();
bool InitAccount();
int  InitRocksDb();

/*********Check Consistency*********/

bool Check();

#endif
