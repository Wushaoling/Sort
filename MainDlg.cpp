#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include "resource.h"
#include "MainDlg.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
TCHAR open[100]={"D:/a.txt"}, save[100]={"D:/b.txt"};
BOOL WINAPI Main_Proc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hWnd, WM_INITDIALOG, Main_OnInitDialog);
        HANDLE_MSG(hWnd, WM_COMMAND, Main_OnCommand);
		HANDLE_MSG(hWnd,WM_CLOSE, Main_OnClose);
    }

    return FALSE;
}

BOOL Main_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
    return TRUE;
}

void Main_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {
        case IDC_OK:
			char s1[100];
			GetDlgItemText(hwnd,IDC_EDIT1,s1,sizeof(s1));
			if(strlen(s1) != 0)
			{
				memset(open,0,sizeof(open));
				strcpy(open,s1);
			}
			memset(s1,0,sizeof(s1));	
			GetDlgItemText(hwnd,IDC_EDIT2,s1,sizeof(s1));
			if(strlen(s1) != 0)
			{
				memset(save,0,sizeof(save));
				strcpy(save,s1);
			}
			FILE *fp0, *fp1, *fp2;
			int i = 0, j, n = 0, flag = 0;  //行数
			char str[10005];
			if((fp0 = fopen(open,"r")) == NULL) //判断文件是否存在及可读
			{
				MessageBox(NULL,TEXT("失败"),NULL,MB_OK|MB_ICONERROR);
				return ;
			}

			while (!feof(fp0))         //求行数
			{
				fgets(str,10005,fp0);
				n ++;
			}

			memset(str, 0, sizeof(str));
			fclose(fp0);
			
			if((fp1 = fopen(open,"r")) == NULL) //判断文件是否存在及可读
			{
				MessageBox(NULL,TEXT("失败"),NULL,MB_OK|MB_ICONERROR);
				return ;
			}

			if((fp2 = fopen(save,"w+")) == NULL) //判断文件是否存在及可写
			{
				MessageBox(NULL,TEXT("失败"),NULL,MB_OK|MB_ICONERROR);
				return ;
			}

			char **s=(char ** )malloc((n+10)*sizeof(char *));
			while (!feof(fp1))
			{
				fgets(str,10005,fp1);  //读取一行
				s[i]=(char * )malloc((strlen(str)+100)*sizeof(char));
				strcpy(s[i], str);
				i ++;
				memset(str, 0, sizeof(str));
			}

			for(i = 1; i <= n-1; i++)
			{
				for(j = 0; j < n - i; j++)
				{
					if((strlen(s[j])) > (strlen(s[j+1])))
					{
						char *temp = s[j];
						s[j] = s[j+1];
						s[j+1] = temp;
					}
				}
			}

			for(i=0;i<n;i++)
			{
				if(strlen(s[i])>44)
					break;
				flag++;
			}
			if(flag%2!=0)
				flag--;

			for(i=0; i<n; i++)
			{
				
				
				if(i==flag/2)
					fputs("=========================================================================================\n",fp2);
				if(i==flag-1)
					fputs("=========================================================================================\n",fp2);
				fputs(s[i],fp2);
				free(s[i]);
			}

			fclose(fp1);                     //关闭文件
			fclose(fp2);                     //关闭文件
			MessageBox(NULL,TEXT("已完成"),TEXT("提示"),MB_OK|MB_ICONWARNING);

        break;
    }
}

void Main_OnClose(HWND hwnd)
{
    EndDialog(hwnd, 0);
}