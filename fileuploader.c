#include<windows.h>
#include<stdio.h>
#include<wininet.h>

int main(int argc,char *argv[])
{
    if(argc!=4)
    {
        printf("USAGE:fileuploader.exe hostname scriptname filename");
        exit(1);
    }
    HANDLE hfile=CreateFile(argv[3],GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL);
    if(hfile==INVALID_HANDLE_VALUE)
    {
        printf("creatfile error %lu",GetLastError());
        exit(1);
    }
    DWORD filesize=GetFileSize(hfile,NULL);
    //STARTING PREPARING THE WININET CODE.
    PCHAR szstart = "Content-Type: multipart/form-data; boundary=----qwerty";
    PCHAR szData    = "------qwerty\r\n"
                      "Content-Disposition: form-data; name=\"%s\"; filename=\"%s\"\r\n"
                      "Content-Type: application/octet-stream\r\n"
                      "Content-Transfer-Encoding: binary\r\n\r\n";
    PCHAR szDataEnd = "\r\n------qwerty--\r\n";
    char szheaders[1024];
    wsprintf(szheaders,szData,"filetoupload",argv[3]);
    HINTERNET hsession,hconnect,hrequest;
    DWORD bytesread,byteswritten,contentlen;
    hsession=InternetOpen("fileuploader",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
    if(!hsession)
    {
        printf("internet open error %lu",GetLastError());
        exit(1);
    }
    hconnect=InternetConnect(hsession,argv[1],INTERNET_DEFAULT_HTTP_PORT,NULL,NULL,INTERNET_SERVICE_HTTP,0,0);
    hrequest=HttpOpenRequest(hconnect,"POST",argv[2],NULL,NULL,0,0,0);
    contentlen=lstrlen(szheaders)+filesize+lstrlen(szDataEnd);
    LPBYTE pbuf=(LPBYTE)malloc(contentlen);
    CopyMemory(&pbuf[0],szheaders,lstrlen(szheaders));
    ReadFile(hfile,&pbuf[lstrlen(szheaders)],filesize,&bytesread,NULL);
    CopyMemory(&pbuf[lstrlen(szheaders)+filesize],szDataEnd,lstrlen(szDataEnd));
    HttpSendRequest(hrequest,szstart,lstrlen(szstart),pbuf,contentlen);
    char testbuf[1024];
    InternetReadFile(hrequest,testbuf,(DWORD)sizeof(testbuf),&byteswritten);
    printf("%s",testbuf);


}
