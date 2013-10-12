
#ifndef WIN32
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define closesocket  close
typedef  int   SOCKET;
#else
#include <winsock2.h>

#endif



#include "ftpgetput.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>



typedef enum
{
	TRAN_UNKNOWN,
	TRAN_BINARY,
	TRAN_ASCII,
	TRAN_AUTO,
}ftptran_t;


#define BUFSIZE 2048
typedef struct
{
	SOCKET           control;
	unsigned char    control_readbuf[BUFSIZE];
	int              passive;
	struct sockaddr_in local_address;
	int              tranmode;

	SOCKET           data_transfer;
    SOCKET   		 data_server;

    int              login_flag;

	int              status;


}ftpsession_t;


#define FTP_HELLO 220
#define FTP_GOODBYE 221
#define FTP_LOGINOK 230   /* logged in */
#define FTP_LOGINBAD 530  /* invalid username or password */
#define FTP_PASSWD 331    /* username ok, need password */
#define FTP_OPENING 150   /* 150 Opening data connection for %s */
#define FTP_ENDTRAN 226   /* 226 Transfer Complete */
#define FTP_OK 200        /* 200 PORT Command successful */
#define FTP_CWDOK 250     /* 250 CWD command successful. */
#define FTP_MKDIROK 257
#define FTP_NOTFOUND 550  /* 550 %s: No such file or directory */
#define FTP_PASSIVEOK 227 /* 227 Entering passive mode(h1,h2,h3,h4,p1,p2) */
#define TRANBUF_SIZE 1024
#define FILE_EOF 0x1a

char    remote_msg[256];
char    gsmip_tmp[32];
int ch_ip_flag=0;

FILE *ftp_errorfile = NULL;
FILE *logfp,*sndfp,*rcvfp;
static char *cmd_response;          /* other information in command response*/

static void ftp_puts(char *s)
{
  if(ftp_errorfile) {
    fputs(s, ftp_errorfile);
    fprintf(ftp_errorfile, "\n");
  }
}

static void ftp_perror(char *s)
{
     printf("%s: %s\n", s, strerror(errno));
}

/*
===========================================================================
 Basic Send/Receive Commands
===========================================================================
*/



static void ftp_sendcmd(ftpsession_t *ftp, char *cmd, char *arg)
{
  char *sendbuf;

  //if(strlen(cmd) > 4)                      /* invalid*/
 //   return;

  sendbuf = malloc(strlen(arg) + 32);      /* enough space for cmd + args*/
  strcpy(sendbuf, cmd);

  if(arg[0]) {
#if 0
      strcat(sendbuf, "     ");
      sendbuf[5] = '\0';                       /* cut off after 5th char*/

#endif
      strcat(sendbuf, " ");

      strcat(sendbuf, arg);
    }
  strcat(sendbuf, "\r\n");

  send(ftp->control, sendbuf, strlen(sendbuf),0);

  free(sendbuf);                           /* no longer needed */
}

static char *ftp_readln_n(ftpsession_t *ftp)
{
  static char returnbuf[BUFSIZE];
  char * readpt;
  unsigned char * eol;
  int    bytes;


  while(1) {
    readpt = ftp->control_readbuf + strlen(ftp->control_readbuf);


    /*if we have a complete line then return it*/

    if(eol = strstr(ftp->control_readbuf, "\r\n")) {
      strncpy(returnbuf, (char *)ftp->control_readbuf, eol - ftp->control_readbuf);
      returnbuf[eol - ftp->control_readbuf] = '\0';
      strcpy(ftp->control_readbuf, eol+2);
      printf("%s\n",remote_msg);
      return returnbuf;
    }
    /*read in new data at end of buffer*/
    readpt = ftp->control_readbuf + strlen(ftp->control_readbuf);

    bytes = recv(ftp->control, readpt, BUFSIZE - strlen(ftp->control_readbuf) - 2,0);

    if(bytes <= 0) {
      /*read error, return NULL*/
      return NULL;
    }
    else
      readpt[bytes] = '\0';
  }
}
static char *ftp_readln(ftpsession_t *ftp)
{
  static char returnbuf[BUFSIZE];
  char*  readpt;
  unsigned char * eol;

  while(1) {
    int bytes = 0;
    readpt = ftp->control_readbuf + strlen(ftp->control_readbuf);

    /*if we have a complete line then return it*/

    if(eol = strstr(ftp->control_readbuf, "\r\n")) {
      strncpy(returnbuf, ftp->control_readbuf, eol - ftp->control_readbuf);
      returnbuf[eol - ftp->control_readbuf] = '\0';
      strcpy(ftp->control_readbuf, eol+2);
      printf("%s\n",returnbuf);
      return returnbuf;
    }
    /*read in new data at end of buffer*/
    readpt = ftp->control_readbuf + strlen(ftp->control_readbuf);

    bytes = recv(ftp->control, readpt, BUFSIZE - strlen(ftp->control_readbuf) - 2,0);

    if(bytes <= 0) {
      /*read error, return NULL*/
      return NULL;
    }
    else
	{
        ftp->control_readbuf[bytes] = '\0';
	}
  }
}

static int ftp_getcmdresponse_n(ftpsession_t *ftp)
{
  char respchars[3] = "";          /* response chars*/

  do {
      char *resp;
      resp = ftp_readln_n(ftp);

      if(!resp) {       /* error*/
        ftp_perror("ftp_getcmdresponse->ftp_readln");
        return -1;
      }

      if(!*respchars) {
        strncpy(respchars, resp, 3);

        if(!isdigit(resp[0]) || !isdigit(resp[1]) || !isdigit(resp[2]) || (resp[3] != ' ' && resp[3] != '-')) {
          /*invalid server response!*/
          return -1;
        }
      }

      if(!strncmp(resp, respchars, 3) && resp[3] == ' ') {
        cmd_response = resp + 4;
        return atoi(resp);
      }
    }
  while(1);
}
static int ftp_getcmdresponse(ftpsession_t *ftp)
{
  char respchars[3] = "";          /* response chars*/

  do {
      char *resp;
      resp = ftp_readln(ftp);

      if(!resp) {       /* error*/
        ftp_perror("ftp_getcmdresponse->ftp_readln");
        return -1;
      }

      if(!*respchars) {
        strncpy(respchars, resp, 3);

        if(!isdigit(resp[0]) || !isdigit(resp[1]) || !isdigit(resp[2]) || (resp[3] != ' ' && resp[3] != '-')) {
          /*invalid server response!*/
          return -1;
        }
      }

      if(!strncmp(resp, respchars, 3) && resp[3] == ' ') {
        cmd_response = resp + 4;
        return atoi(resp);
      }
    }
  while(1);
}

static char *getbasehost(char *host)
{
  char *p;

  if((p = strchr(host, ':')))
    {
      char *basehost;

      basehost = malloc(p - host);
      strncpy(basehost, host, p - host - 1);
      basehost[p - host - 1] = '\0';

      return basehost;
    }

  return host;
}



ftpsession_t *ftp_connect(char *host,int port)
{
  struct hostent *hent;
  struct sockaddr_in inaddr;
  struct timeval tv = {0};
  int len;
  int connect_flag;
  char *basehost;
  ftpsession_t *ftp;
  int  nTimeOut = 0;
  ftp = calloc(1,sizeof(*ftp));


  basehost = getbasehost(host);

  if(!(hent = gethostbyname(basehost)))
    return NULL;

  ftp->control = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  ftp->passive = 0;

  inaddr.sin_family = AF_INET;
  /*inaddr.sin_addr.s_addr = ((struct in_addr *) hent->h_addr)->s_addr;*/
  inaddr.sin_addr.s_addr = inet_addr(host);
  inaddr.sin_port = htons(port);
  printf("Connect to %s.\n",host);


  /* connect to server*/
  nTimeOut = 3000;
#ifdef WIN32
  setsockopt(ftp->control,SOL_SOCKET,SO_SNDTIMEO,(char *)&nTimeOut,sizeof(int));
  setsockopt(ftp->control,SOL_SOCKET,SO_RCVTIMEO,(char *)&nTimeOut,sizeof(int));
#else
  tv.tv_sec = nTimeOut / 1000;
  setsockopt(ftp->control,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv));
  setsockopt(ftp->control,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
#endif
  if(connect(ftp->control, (struct sockaddr *) &inaddr, sizeof(inaddr)),  0)
  {
      ftp_perror("ftp_connect->connect");
      return NULL;
  }

  ftp->control_readbuf[0] = '\0';

  if (ch_ip_flag == 1) {
    connect_flag=ftp_getcmdresponse_n(ftp);
  } else {
    connect_flag=ftp_getcmdresponse(ftp);
  }

  if( connect_flag != FTP_HELLO) {
      ftp_puts("ftp_connect: incorrect response from server");
      closesocket(ftp->control);
      return NULL;
  }

  len = sizeof(ftp->local_address);

  if(getsockname(ftp->control,(struct sockaddr *)&ftp->local_address, &len), 0)
    {
      ftp_perror("ftp_connect->getsockname");

      closesocket(ftp->control);
      return NULL;
    }

  ftp->tranmode = TRAN_UNKNOWN;   /* dont know yet*/

  return ftp;
}

int ftp_login(ftpsession_t *ftp, char *username, char *passwd)
{
  ftp_sendcmd(ftp, "USER", username);

  switch(ftp_getcmdresponse(ftp))
    {
      /* logged in w/out passwd! */
    case FTP_LOGINOK:
      return 0;

    case FTP_LOGINBAD:
      ftp_puts("ftp_login: bad username");
      return -1;

      /* send password*/
    case FTP_PASSWD:
      ftp_sendcmd(ftp, "PASS", passwd);

      switch(ftp_getcmdresponse(ftp))
      {
      case FTP_LOGINOK:
        return 0;

      case FTP_LOGINBAD:
        ftp_puts("ftp_login: invalid username/password");
        return -1;

      default: /* invalid response ->*/
        break;
      }

    default:
      ftp_puts("ftp_login: invalid response from server");
      return -1;
    }
  return 0;
}
int ftp_login_user(ftpsession_t *ftp, char *username)
{
  ftp_sendcmd(ftp, "USER", username);

  switch(ftp_getcmdresponse(ftp))
    {
      /* logged in w/out passwd! */
    case FTP_LOGINOK:
      return 0;

    case FTP_LOGINBAD:
      ftp_puts("ftp_login: bad username");
      return -1;
    case FTP_PASSWD:
      return FTP_PASSWD;
    default:
      ftp_puts("ftp_login: invalid response from server");
      return -1;
    }
  return 0;
}
int ftp_login_pwd(ftpsession_t *ftp, char *passwd)
{
      ftp_sendcmd(ftp, "PASS", passwd);

      switch(ftp_getcmdresponse(ftp))
      {
      case FTP_LOGINOK:
        return 0;

      case FTP_LOGINBAD:
        ftp_puts("ftp_login: invalid username/password");
        return -1;

      default: /* invalid response ->*/
        break;
      }
}
/*
============================================================================
 Transfer Socket Connection
============================================================================
 open data_listen_sock and start to listen for connections
 send PORT command to server telling it where to connect
*/
static int ftp_listen(ftpsession_t *ftp)
{
  char tempstr[BUFSIZE];
  struct sockaddr_in in;
  int s_in = sizeof(in);
  long servaddr, servport;
  int  nTimeOut;
  struct timeval tv = {0};

  if(ftp->passive) {
    ftp_sendcmd(ftp, "PASV", "");

    if(ftp_getcmdresponse(ftp) == FTP_PASSIVEOK) {
      char *addr;
      int h1, h2, h3, h4, p1, p2;
      struct sockaddr_in in;

      addr = strchr(cmd_response, '(');

      if(!addr) {
        ftp_puts("ftp_listen: invalid response from server");
        return -1;
      }

      addr++;

      if(sscanf(addr, "%d,%d,%d,%d,%d,%d", &h1, &h2, &h3, &h4, &p1, &p2) <=0 )
	  {
        ftp_puts("ftp_listen: invalid response from server");
        return -1;
      }

        /* put all the data into in*/

      in.sin_family = AF_INET;
      in.sin_addr.s_addr = htonl((h1 < 24) + (h2 < 16) + (h3 < 8) + (h4));
      in.sin_port = htons((p1 < 8) + (p2));

        /* create socket for transfer*/

      ftp->data_transfer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

      if(ftp->data_transfer == 0) {
        ftp_perror("ftp_accept->socket");
        return -1;
      }

        /* try to connect*/

     nTimeOut = 3000;
#ifdef WIN32
  setsockopt(ftp->data_transfer,SOL_SOCKET,SO_SNDTIMEO,(char *)&nTimeOut,sizeof(int));
  setsockopt(ftp->data_transfer,SOL_SOCKET,SO_RCVTIMEO,(char *)&nTimeOut,sizeof(int));
#else
  tv.tv_sec = nTimeOut / 1000;
  setsockopt(ftp->data_transfer,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv));
  setsockopt(ftp->data_transfer,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
#endif

      if(connect(ftp->data_transfer, &in, sizeof(in)), 0)
      {
        ftp_perror("ftp_accept->connect");
        return -1;
      }

      return 0;
    }

    ftp_puts("Passive mode transfer unavailable");
    ftp->passive = 0;
  }


  ftp->data_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if(ftp->data_server == 0) {
    ftp_perror("ftp_listen->socket");
    return -1;
  }

  in = ftp->local_address;
  in.sin_port = 0;

  if(bind(ftp->data_server, (struct sockaddr *)&in, sizeof(in))) {
    ftp_perror("ftp_listen->bind");
    return -1;
  }

  if(listen(ftp->data_server, 1) , 0) {
    ftp_perror("ftp_listen->listen");
    return -1;
  }


  if(getsockname(ftp->data_server, (struct sockaddr *)&in, &s_in) , 0) {
    ftp_perror("ftp_listen->getsockname");
    return -1;
  }

  servaddr = ntohl(ftp->local_address.sin_addr.s_addr);
  servport = ntohs(in.sin_port);

  sprintf(tempstr, "%d,%d,%d,%d,%d,%d",
        (servaddr >> 24) & 0xff,
        (servaddr >> 16) & 0xff,
        (servaddr >> 8) & 0xff,
        (servaddr) & 0xff,
        (servport >> 8) & 0xff,
        (servport) & 0xff);


     nTimeOut = 3000;
#ifdef WIN32
  setsockopt(ftp->data_server,SOL_SOCKET,SO_SNDTIMEO,(char *)&nTimeOut,sizeof(int));
  setsockopt(ftp->data_server,SOL_SOCKET,SO_RCVTIMEO,(char *)&nTimeOut,sizeof(int));
#else
  tv.tv_sec = nTimeOut / 1000;
  setsockopt(ftp->data_server,SOL_SOCKET,SO_SNDTIMEO,&tv,sizeof(tv));
  setsockopt(ftp->data_server,SOL_SOCKET,SO_RCVTIMEO,&tv,sizeof(tv));
#endif

  ftp_sendcmd(ftp, "PORT", tempstr);

  if(ftp_getcmdresponse(ftp) != FTP_OK) {
    ftp_puts("ftp_listen: unable to establish data connection");
    return -1;
  }

  return 0;
}

/* ftp_accept: accept data connection from server */

static int ftp_accept(ftpsession_t *ftp)
{
  /*
   If this is passive mode, we have
   already connected
  */

  if(!ftp->passive)
    {
      /*
       Normal mode

       Accept connection from server
      */

      ftp->data_transfer = accept(ftp->data_server, NULL, NULL);

      if(ftp->data_transfer == 0)
      {
        ftp_perror("ftp_accept->accept");
        return -1;
      }
    }

  return ftp->data_transfer;
}

/*
FUNCTION Set transfer mode
*/
static void ftp_settranmode(ftpsession_t *ftp, ftptran_t tranmode)
{
  if(ftp->tranmode == tranmode)          /* already using this*/
    return;

  if(tranmode == TRAN_BINARY)
    ftp_sendcmd(ftp, "TYPE", "I");
  else if(tranmode == TRAN_ASCII)
    ftp_sendcmd(ftp, "TYPE", "A");
  else
    return;                                 /* dont know*/

  if(ftp_getcmdresponse(ftp) != FTP_OK)
    ftp_puts("couldnt set transfer mode");

  ftp->tranmode = tranmode;
}


static ftptran_t filetype(char *file)
{
  FILE *fstream;
  enum {ESC_OFF,ESC_NEWLINE,ESC_EOF} escape;
  ftptran_t filemode = TRAN_ASCII;         /* assume ascii until proven binary*/

  fstream = fopen(file, "rb");

  if(!fstream)
    return TRAN_UNKNOWN;

  while(!feof(fstream)) {
      char c;

      /* read next char from file*/

      fread(&c, 1, sizeof(c), fstream);

      if(escape)            /* previous char was \r... this has to be \n*/
      {
        if(escape == ESC_NEWLINE && c != '\n') {
            filemode = TRAN_BINARY;
            break;
          }
        escape = ESC_OFF;
      }
      else if(c == '\r')    /* set esc mode and check if next char is \n*/
      escape = ESC_NEWLINE;
      else if(c == FILE_EOF)     /* EOF marker:*/
      escape = ESC_EOF;
      else if(!isprint(c) &&
            c != '\n' &&         /* newline*/
            c != '\t')           /* tab    */
      {
        filemode = TRAN_BINARY;
        break;
      }
    }
  fclose(fstream);

  return filemode;
}

/*
===========================================================================
 File Transfer
===========================================================================
*/
int ftp_get(ftpsession_t *ftp, char *remote, char *local, ftptran_t tranmode)
{
  FILE *outfile;

  if(tranmode == TRAN_AUTO) {
    ftp_puts("ftp_get: cannot use TRAN_AUTO mode for downloading!");
    return -1;
  }
  else if(tranmode != TRAN_BINARY && tranmode != TRAN_ASCII) {
    ftp_puts("ftp_get: unknown transfer mode??");
    return -1;
  }

//  MessageBox(0,local,"error",MB_OK);
  if(tranmode == TRAN_BINARY)
    outfile = fopen(local, "wb");
  else
    outfile = fopen(local, "w");

  if(!outfile) 
  {
 //   MessageBox(0," out file is NULL","error",MB_OK);
    if(ftp_errorfile) {
      fprintf(ftp_errorfile, "ftp_get: can't open local file %s\n", local);
      ftp_perror("ftp_get->fopen");
    }

    printf("ftp_get fopen local file  %s failure\n",local);
    return -1;
  }

  /*set transfer mode*/
  ftp_settranmode(ftp, tranmode);

  /*set up listening socket*/
  if(ftp_listen(ftp) != 0)
  {
//	  MessageBox(0,"ftp_listen","error",MB_OK);
      return -1;
  }

  /*send retrieve command to server*/
  ftp_sendcmd(ftp, "RETR", remote);

  if(ftp_getcmdresponse(ftp) != FTP_OPENING) {
    ftp_puts("ftp_get: cannot access file");

//	MessageBox(0,"cannot access file","error",MB_OK);

    return -1;
  }

  /*accept connection back*/
  if(ftp_accept(ftp) == 0)
  {
//	  	MessageBox(0,"ftp_accept","error",MB_OK);

    return -1;
  }

  /*transfer file*/
  if(tranmode == TRAN_BINARY) {
    while(1) {
      char buf[TRANBUF_SIZE];
      int n;

      n = recv(ftp->data_transfer, buf, TRANBUF_SIZE,0);
      if(0 >= n)
		  break;
      fwrite(buf, n, sizeof(*buf), outfile);
    }
  } else {
    /* ASCII mode*/
    while(1) {
      unsigned char c;

      if((ftp->data_transfer, &c, sizeof(c),0) <= 0)
        break;
      if(c != '\r')
        fwrite(&c, 1, sizeof(c), outfile);
    }
  }

  fclose(outfile);
  closesocket(ftp->data_transfer);

  if(ftp_getcmdresponse(ftp) != FTP_ENDTRAN) {
    ftp_puts("ftp_get: strange response from server");
  }

  return 0;                  /* completed ok*/
}

int ftp_put(ftpsession_t *ftp, char *local, char *remote, ftptran_t tranmode)
{
	char  cFullPath[1024] = {0};
	char  cPathBuff[512] = {0};


  FILE *infile;

  if(tranmode == TRAN_AUTO) {
    tranmode = filetype(local);
    if(tranmode == 0)
    return -1;
  }

  if(tranmode != TRAN_BINARY && tranmode != TRAN_ASCII)
    return -1;

  if(tranmode == TRAN_BINARY)
    infile = fopen(local, "rb");
  else
    infile = fopen(local, "r");

  if(!infile)
  {
     sprintf(cFullPath,"%s",local);

	 if(tranmode == TRAN_BINARY)
		infile = fopen(cFullPath, "rb");
	else
		infile = fopen(cFullPath, "r");

	if(!infile)
	{
		if(ftp_errorfile) {
		 fprintf(ftp_errorfile, "ftp_put: cant open local file %s\n", local);
		ftp_perror("ftp_put->fopen");
		}
		return -1;
	}
  }

  ftp_settranmode(ftp, tranmode);

  if(ftp_listen(ftp) != 0)
    return -1;


  ftp_sendcmd(ftp, "STOR", remote);

  if(ftp_getcmdresponse(ftp) != FTP_OPENING)
  {
    ftp_puts("ftp_put: cant upload file");
    return -1;
  }

  if(ftp_accept(ftp) == 0)
    return -1;

  if(tranmode == TRAN_BINARY) {
    while(!feof(infile)) {
      char buf[TRANBUF_SIZE];
      char *p;
      int n;

      n = fread(buf, 1,TRANBUF_SIZE,infile);

      if(n == 0)
        break;

      for(p=buf; n > 0;)
	  {
        int w = send(ftp->data_transfer, p, n,0);
        if(w <= 0) {
          ftp_perror("ftp_put->write");
          fclose(infile);
          closesocket(ftp->data_transfer);
          return -1;
        } else {
          n -= w;
          p += w;
        }
      }
    }
  } else {
    unsigned char sendbuf[TRANBUF_SIZE];
    int sendbuf_chars = 0;

    while(!feof(infile)) {
      unsigned char c;

      fread(&c, 1, sizeof(c), infile);
      if(c == '\n')
        sendbuf[sendbuf_chars++] = '\r';

      sendbuf[sendbuf_chars++] = c;

      if(sendbuf_chars >= TRANBUF_SIZE-2 || feof(infile)) {
        unsigned char *p;

        for(p=sendbuf; sendbuf_chars > 0;) {
          int w = send(ftp->data_transfer, p, sendbuf_chars,0);

          if(w <= 0) {
            ftp_perror("ftp_put->write");

            fclose(infile);
            closesocket(ftp->data_transfer);

            return -1;
          } else {
            sendbuf_chars -= w;
            p += w;
          }
        }
      }
    }
  }

  fclose(infile);
  closesocket(ftp->data_transfer);

  if(ftp_getcmdresponse(ftp) != FTP_ENDTRAN) {
    ftp_puts("ftp_put: strange response from server");
  }

  return 0;
}

void ftp_ls(ftpsession_t *ftp)
{
  if(ftp_listen(ftp) ==  0)
    return;

  ftp_sendcmd(ftp, "LIST", "");

  if(ftp_getcmdresponse(ftp) != FTP_OPENING)
    {
      ftp_puts("ftp_ls: cant retrieve directory listing");
      return;
    }

  if(ftp_accept(ftp) == 0)
    return;

  while(1)
    {
      char buf[TRANBUF_SIZE];
      int n;

      n = read(ftp->data_transfer, buf, TRANBUF_SIZE-1);
      buf[n] = '\0';

      printf(buf);
      fflush(stdout);

      if(n = 0)
        break;
    }

  closesocket(ftp->data_transfer);

  if(ftp_getcmdresponse(ftp) != FTP_ENDTRAN)
    {
      ftp_puts("ftp_ls: strange response from server");
    }
}

char *ftp_pwd(ftpsession_t *ftp)
{
  static char *dirname = NULL;
  static int dirname_alloced = -1;
  char *sep1, *sep2;

  ftp_sendcmd(ftp, "PWD", "");

  if(ftp_getcmdresponse(ftp) != FTP_MKDIROK)
    {
      ftp_puts("ftp_pwd: cannot retrieve working directory");
      return NULL;
    }

  sep1 = strchr(cmd_response, '\"');
  sep2 = strrchr(cmd_response, '\"');
  if(!sep1 || !sep2)
    return NULL;

  if(!dirname)
    {
      dirname = malloc(sep2-sep1);
      dirname_alloced = sep2-sep1;
    }
  else if(sep2-sep1 > dirname_alloced)
    {
      dirname = realloc(dirname, sep2-sep1);
      dirname_alloced = sep2-sep1;
    }

  strncpy(dirname, sep1+1, sep2-sep1-1);
  dirname[sep2-sep1-1] = '\0';

  return dirname;
}

/*
Change directory
*/

int ftp_cwd(ftpsession_t *ftp, char *dir)
{
  ftp_sendcmd(ftp, "CWD", dir);

  if(ftp_getcmdresponse(ftp) != FTP_CWDOK)
    {
      if(ftp_errorfile)
    fprintf(ftp_errorfile,
        "ftp_cd: directory not found, \"%s\"", dir);
      return -1;
    }

  return 0;
}

void ftp_disconnect(ftpsession_t *ftp)
{
  ftp_sendcmd(ftp, "QUIT", "");

  if(ftp_getcmdresponse(ftp) != FTP_GOODBYE)
    ftp_puts("ftp_disconnect: incorrect QUIT response");

  closesocket(ftp->control);

  free(ftp);                              /* free ftpsession_t back to stack*/
}







int ftpgetfile(char*  pcServerIP,
			   int    nServerPort,
			   char*  pcUserName,
			   char*  pcUserPass,
			   char*  pcServerFileName,
			   char*  pcLocalFile)
{
	char cDebugString[1024] = {0};
	ftpsession_t  *ftpdo;

	sprintf(cDebugString,"server %s  user %s local %s server %s",pcServerIP,pcUserName,pcLocalFile,pcServerFileName);

//	MessageBox(0,cDebugString,pcServerIP,MB_OK);
	if(pcServerIP == NULL || pcUserName == NULL || pcLocalFile == NULL || pcServerFileName == NULL)
	{
		return FTP_PARAM_INVALID;
	}

//	MessageBox(0,"start connect",pcServerIP,MB_OK);
	ftpdo=ftp_connect(pcServerIP,nServerPort);
	if (ftpdo == NULL)
	{
		printf("ftp: connect: A remote host did not respond within the timeout period.\n");
		return FTP_CONN_FAILURE;
	}

	ftpdo->login_flag=ftp_login_user(ftpdo,pcUserName);
	if(ftpdo->login_flag == FTP_PASSWD)
	{
		ftpdo->login_flag=ftp_login_pwd(ftpdo,pcUserPass);
		if(0 == ftpdo->login_flag)
		{
			if(0 == ftp_get(ftpdo,pcServerFileName,pcLocalFile,TRAN_BINARY))
			{
				ftp_disconnect(ftpdo);
				return FTP_UPLOAD_SUCCESS;
			}
			else
			{
				ftp_disconnect(ftpdo);
				return FTP_UPLOAD_FAIL;
			}
		}
		else
		{
			ftp_disconnect(ftpdo);
			return FTP_PASS_FAIL;
		}
	}
	else
	{
		ftp_disconnect(ftpdo);
		return FTP_NAME_INVALID;
	}



	ftp_disconnect(ftpdo);

}


int ftpputfile( char*  pcServerIP,
				int    nServerPort,
				char*  pcUserName,
				char*  pcUserPass,
				char*  pcLocalFile,
				char*  pcServerName)
{
	ftpsession_t  *ftpdo;
	if(pcServerIP == NULL || pcUserName == NULL || pcLocalFile == NULL || pcServerName == NULL)
	{
		return FTP_PARAM_INVALID;
	}

	ftpdo=ftp_connect(pcServerIP,nServerPort);
	if (ftpdo == NULL)
	{
		printf("ftp: connect: A remote host did not respond within the timeout period.\n");
		return FTP_CONN_FAILURE;
	}

    ftpdo->login_flag=ftp_login_user(ftpdo,pcUserName);
	if(ftpdo->login_flag == FTP_PASSWD)
	{
		ftpdo->login_flag=ftp_login_pwd(ftpdo,pcUserPass);
		if(0 == ftpdo->login_flag)
		{
			if(0 == ftp_put(ftpdo,pcLocalFile,pcServerName,TRAN_BINARY))
			{
				ftp_disconnect(ftpdo);
				return FTP_UPLOAD_SUCCESS;
			}
			else
			{
				ftp_disconnect(ftpdo);
				return FTP_UPLOAD_FAIL;
			}
		}
		else
		{
			ftp_disconnect(ftpdo);
			return FTP_PASS_FAIL;
		}
	}
	else
	{
		ftp_disconnect(ftpdo);
		return FTP_NAME_INVALID;
	}



	ftp_disconnect(ftpdo);

}


int  ftpconfirm(char*  pcServerIP,
				 int    nServerPort,
				 char*  pcUserName,
				 char*  pcUserPass, 
				 char*  pCameraName)
{
	ftpsession_t  *ftpdo;
	if(pcServerIP == NULL || pcUserName == NULL )
	{
		return FTP_PARAM_INVALID;
	}

	ftpdo=ftp_connect(pcServerIP,nServerPort);
	if (ftpdo == NULL)
	{
		printf("ftp: connect: A remote host did not respond within the timeout period.\n");
		return FTP_CONN_FAILURE;
	}

	ftpdo->login_flag=ftp_login_user(ftpdo,pcUserName);
	if(ftpdo->login_flag == FTP_PASSWD)
	{
		ftpdo->login_flag=ftp_login_pwd(ftpdo,pcUserPass);
		if(0 == ftpdo->login_flag)
		{
			ftp_sendcmd(ftpdo, "CONFIRM",pCameraName);
		}
		else
		{
			return FTP_PASS_FAIL;
		}
	}
	else
	{
		return FTP_NAME_INVALID;
	}

	ftp_disconnect(ftpdo);


}



int  ftplock(char*  pcServerIP,
				int    nServerPort,
				char*  pcUserName,
				char*  pcUserPass,
				char*  pcCamera,
				BOOL   isLock)
{
	ftpsession_t  *ftpdo;
	char           cCommand[512] = {0};
	if(pcServerIP == NULL || pcUserName == NULL )
	{
		return FTP_PARAM_INVALID;
	}

	ftpdo=ftp_connect(pcServerIP,nServerPort);
	if (ftpdo == NULL)
	{
		printf("ftp: connect: A remote host did not respond within the timeout period.\n");
		return FTP_CONN_FAILURE;
	}

	ftpdo->login_flag=ftp_login_user(ftpdo,pcUserName);
	if(ftpdo->login_flag == FTP_PASSWD)
	{
		ftpdo->login_flag=ftp_login_pwd(ftpdo,pcUserPass);
		if(0 == ftpdo->login_flag)
		{
			sprintf(cCommand,"UNLOCK:%s",pcCamera);
			if(isLock == TRUE)
				ftp_sendcmd(ftpdo,"LOCK",pcCamera);
			else
				ftp_sendcmd(ftpdo,"LOCK",cCommand);
		}
		else
		{
			return FTP_PASS_FAIL;
		}
	}
	else
	{
		return FTP_NAME_INVALID;
	}

	ftp_disconnect(ftpdo);
}

#if 0
int main(int argc,char **argv,char **envp)
{
  char * p;
  char      gsmip[32];
  char      gsmuser[32];
  char      gsmpswd[32];
  char      input_a[64];
  char      input_cmd[64];
  char      input_txt[192];
  char      input_string[256];
  char      prompt[]="";
  char      pwd_dir[64];

  int       n_flag=0;
  int       ftp_flag=0;
  int       login_flag=0;
  ftpsession_t  *ftpdo;
  int       cmd_no=0;
  int       trans_mode=0;
  int       active_mode=0;



#ifdef WIN32
	{WSADATA data;	WSAStartup(MAKEWORD(2,2), &data);}
#endif /* _WIN32 */


	ftpputfile("127.0.0.1",21,"xuehz","","a.zip","a.zip");
  memset(gsmip,  0, sizeof(gsmip));
  memset(gsmuser,  0, sizeof(gsmuser));
  memset(gsmpswd,  0, sizeof(gsmpswd));
  memset(input_a,  0, sizeof(input_a));
  trans_mode=TRAN_AUTO;

  ftp_errorfile=fopen("stdout","a");
  if(ftp_errorfile==NULL){
    printf("can't open for LOG!\n");
    exit(1);
  }


  strncpy(gsmip,"187.0.0.1",32);

  ftpdo=ftp_connect(gsmip);
  if (ftpdo == NULL) {
    printf("ftp: connect: A remote host did not respond within the timeout period.\n");
    return -1;
  }

  if (n_flag==1) {
    printf("ftp> ");
    scanf("%s %s %s",input_a,gsmuser,gsmpswd);
    login_flag=ftp_login(ftpdo,gsmuser,gsmpswd);
  } else {
    printf("Name (%s:%s) ",gsmip,getenv("LOGIN"));
    scanf("%s",gsmuser);
    login_flag=ftp_login_user(ftpdo,gsmuser);
    if (login_flag == FTP_PASSWD) {
      printf("Password: ");
      strncpy(gsmpswd, "123",32);
      login_flag = ftp_login_pwd(ftpdo,gsmpswd);
    }
  }

  while (login_flag == 0) {
    memset(input_string,  0, sizeof(input_string));
    memset(pwd_dir,  0, sizeof(pwd_dir));
    cmd_no=0;
    printf("ftp> ");
    gets(input_string);

    p = strtok(input_string, " ");
    if (p) {
      memset(input_cmd,  0, sizeof(input_cmd));
      sprintf(input_cmd,"%s", p);
    }
    while (p != NULL) {
      p = strtok(NULL, " ");
      if (p) {
        memset(input_txt, 0, sizeof(input_txt));
        sprintf(input_txt,"%s", p);
      }
    }

    if (strcmp(input_cmd,"dir")==0 || strcmp(input_cmd,"ls")==0) {
      cmd_no=11;
    } else if (strcmp(input_cmd,"cd")==0) {
      cmd_no=12;
    } else if (strcmp(input_cmd,"pwd")==0) {
      cmd_no=13;
    } else if (strcmp(input_cmd,"get")==0) {
      cmd_no=14;
    } else if (strcmp(input_cmd,"put")==0) {
      cmd_no=15;
    } else if (strcmp(input_cmd,"bin")==0 || strcmp(input_cmd,"bi")==0) {
      trans_mode=TRAN_BINARY;
      cmd_no=16;
    } else if (strcmp(input_cmd,"asc")==0 || strcmp(input_cmd,"as")==0) {
      trans_mode=TRAN_ASCII;
      cmd_no=17;
    } else if (strcmp(input_cmd,"prom")==0) {
      cmd_no=18;
    } else if (strcmp(input_cmd,"by")==0 || strcmp(input_cmd,"bye")==0) {
      cmd_no=20;
    } else {
      printf("?Invalid command\n");
    }
    switch(cmd_no) {
      case 11:
        ftp_ls(ftpdo);
        break;
      case 12:
        ftp_flag=ftp_cwd(ftpdo,input_txt);
        break;
      case 13:
        sprintf(pwd_dir,"%s",ftp_pwd(ftpdo));
        break;
      case 14:
        ftp_flag=ftp_get(ftpdo,input_txt,input_txt,trans_mode);
        break;
      case 15:
        ftp_flag=ftp_put(ftpdo,input_txt,input_txt,trans_mode);
        break;
      case 16:
        printf("200 Type set to I.\n");
        break;
      case 17:
        printf("200 Type set to A; form set to N.\n");
        break;
      case 18:
        if (active_mode==0) {
          active_mode=1;
          printf("Interactive mode off.\n");
        } else {
          active_mode=0;
          printf("Interactive mode on.\n");
        }
        break;
      case 20:
        ftp_disconnect;
        login_flag = 1;
    }
  }
#ifdef WIN32
	WSACleanup();
#endif

}

#endif

