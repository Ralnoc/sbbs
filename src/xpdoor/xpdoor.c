#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "xpdoor.h"
#include <ansi_cio.h>
#include <comio.h>
#include <genwrap.h>
#include <cterm.h>
#include <dirwrap.h>

struct xpd_info		xpd_info;
static BOOL raw_write=FALSE;

static int xpd_ansi_readbyte_cb(void)
{
	unsigned char	ch;

	switch(xpd_info.io_type) {
		case XPD_IO_STDIO:
			return(ansi_readbyte_cb());
		case XPD_IO_COM:
			if(!comReadByte(xpd_info.io.com, &ch)) {
				if(comGetModemStatus(xpd_info.io.com)&COM_DCD==0)
					return(-2);
				return(-1);
			}
			return(ch);
		case XPD_IO_SOCKET:
			{
				BOOL	can_read;

				if(!socket_check(xpd_info.io.sock, &can_read, NULL, 1000))
					return(-2);
				if(can_read) {
					if(recv(xpd_info.io.sock, &ch, 1, 0)==1)
						return(ch);
					return(-2);
				}
				return(-1);
			}
		case XPD_IO_TELNET:
			{
				BOOL	can_read;

				// TODO: Proper telnet stuff...
				if(!socket_check(xpd_info.io.telnet.sock, &can_read, NULL, 1000))
					return(-2);
				if(can_read) {
					if(recv(xpd_info.io.telnet.sock, &ch, 1, 0)==1)
						return(ch);
					return(-2);
				}
				return(-1);
			}
	}
	return(-2);
}

static int dummy_writebyte_cb(unsigned char ch)
{
	return(ch);
}

static int xpd_ansi_writebyte_cb(unsigned char ch)
{
	switch(xpd_info.io_type) {
		case XPD_IO_STDIO:
			return(ansi_writebyte_cb(ch));
		case XPD_IO_COM:
			if(comWriteByte(xpd_info.io.com, ch))
				return(1);
			return(-1);
		case XPD_IO_SOCKET:
			{
				BOOL	can_write;

				if(!socket_check(xpd_info.io.sock, NULL, &can_write, 580000))
					return(-2);
				if(can_write) {
					if(send(xpd_info.io.sock, &ch, 1, 0)==1)
						return(ch);
					return(-2);
				}
				return(-1);
			}
		case XPD_IO_TELNET:
			{
				BOOL	can_write;

				// TODO: Proper telnet stuff...
				if(!socket_check(xpd_info.io.sock, NULL, &can_write, 580000))
					return(-2);
				if(can_write) {
					if(send(xpd_info.io.sock, &ch, 1, 0)==1)
						return(ch);
					return(-2);
				}
				return(-1);
			}
	}
	return(-2);
}

static int xpd_ansi_initio_cb(void)
{
	switch(xpd_info.io_type) {
		case XPD_IO_STDIO:
			return(ansi_initio_cb());
		case XPD_IO_COM:
		case XPD_IO_SOCKET:
		case XPD_IO_TELNET:
			// TODO: Init stuff... (enable Nagle, Disable non-blocking, etc)
			break;
	}
	return(0);
}

static int xpd_ansi_writestr_cb(unsigned char *str, size_t len)
{
	int i;

	// TODO: Quit being silly.
	switch(xpd_info.io_type) {
		case XPD_IO_STDIO:
			return(ansi_writestr_cb(str,len));
		case XPD_IO_COM:
		case XPD_IO_SOCKET:
		case XPD_IO_TELNET:
			for(i=0; i<len; i++) {
				if(xpd_ansi_writebyte_cb((unsigned char)str[i])<0)
					return(-2);
			}
	}
	return(-2);
}

void xpd_parse_cmdline(int argc, char **argv)
{
	int	i;

	for(i=0; i<argc; i++) {
		if(strncmp(argv[i],"--io-type=",10)==0) {
			if(stricmp(argv[i]+10, "stdio")==0)
				xpd_info.io_type=XPD_IO_STDIO;
			else if(stricmp(argv[i]+10, "com")==0)
				xpd_info.io_type=XPD_IO_COM;
			else if(stricmp(argv[i]+10, "socket")==0)
				xpd_info.io_type=XPD_IO_SOCKET;
			else if(stricmp(argv[i]+10, "telnet")==0)
				xpd_info.io_type=XPD_IO_TELNET;
			else if(stricmp(argv[i]+10, "local")==0)
				xpd_info.io_type=XPD_IO_LOCAL;
		}
		else if(strncmp(argv[i],"--io-com=",9)==0) {
			xpd_info.io_type=XPD_IO_COM;
			xpd_info.io.com=atoi(argv[i]+9);
		}
		else if(strncmp(argv[i],"--io-socket=",12)==0) {
			xpd_info.io_type=XPD_IO_SOCKET;
			xpd_info.io.sock=atoi(argv[i]+12);
		}
		else if(strncmp(argv[i],"--drop-path=",12)==0) {
			xpd_info.drop.path=strdup(argv[i]+12);
		}
	}
}

int xpd_exit()
{
	ansi_ciolib_setdoorway(0);
}

int xpd_init()
{
	struct text_info	ti;

	if(xpd_info.io_type == XPD_IO_LOCAL) {
		if(initciolib(CIOLIB_MODE_AUTO))
			return(-1);
	}
	else {
		ciolib_ansi_readbyte_cb=xpd_ansi_readbyte_cb;
		ciolib_ansi_writebyte_cb=xpd_ansi_writebyte_cb;
		ciolib_ansi_initio_cb=xpd_ansi_initio_cb;
		ciolib_ansi_writestr_cb=xpd_ansi_writestr_cb;
		if(initciolib(CIOLIB_MODE_ANSI))
			return(-1);
		ansi_ciolib_setdoorway(1);
	}
	gettextinfo(&ti);
	cterm_init(ti.screenheight, ti.screenwidth, 1, 1, 0, NULL, CTERM_EMULATION_ANSI_BBS);
}

#define GETBUF()	if(fgets(buf,sizeof(buf),df)==NULL) goto done_parsing
#define GETIBUF(x)	if(fgets(buf,sizeof(buf),df)==NULL) goto done_parsing; x = atoi(buf)
#define GETSBUF(x)	if(fgets(buf,sizeof(buf),df)==NULL) goto done_parsing; x = strdup(truncnl(buf))
#define GETDBUF(x)	if(fgets(buf,sizeof(buf),df)==NULL) goto done_parsing; { \
						int m,d,y; \
						char *p; \
						p=strtok(buf,"/-"); \
						if(p) { \
							m=strtol(buf,NULL,10); p=strtok(NULL, "/-"); \
							if(p) { \
								d=strtol(buf,NULL,10); p=strtok(NULL, "/-"); \
								if(p) { \
									y=strtol(buf,NULL,10); y+=(y<100?2000:1900); if(y > xpDateTime_now().date.year) y-=100; x = isoDate_create(y,m,d); \
					}}}}
#define GETTBUF(x)	if(fgets(buf,sizeof(buf),df)==NULL) goto done_parsing; { \
						int h,m; \
						char *p; \
						p=strtok(buf,":"); \
						if(p) { \
							h=strtol(buf,NULL,10); p=strtok(NULL, ":"); \
							if(p) { \
								m=strtol(buf,NULL,10); x = isoTime_create(h,m,0); \
					}}}
#define GETBBUF(x)	if(fgets(buf,sizeof(buf),df)==NULL) goto done_parsing; if(buf[0]=='Y' || buf[0]=='y') x=TRUE
#define GETCBUF(x)	if(fgets(buf,sizeof(buf),df)==NULL) goto done_parsing; x=buf[0]

int xpd_parse_dropfile()
{
	FILE	*df=NULL;
	char	*p;
	char	buf[1024];
	int		tmp;

	if(xpd_info.drop.path==NULL)
		goto error_return;
	df=fopen(xpd_info.drop.path,"r");
	if(df==NULL)
		goto error_return;
	p=getfname(xpd_info.drop.path);
	if(p==NULL)
		goto error_return;
	if(stricmp(p,"door.sys")==0) {
		/* COM0:, COM1:, COM0:STDIO, COM0:SOCKET123 */
		GETBUF();
		if(strcmp(buf,"COM0:STDIO")==0) {
			xpd_info.io_type=XPD_IO_STDIO;
		}
		else if(strncmp(buf,"COM0:SOCKET",11)==0) {
			xpd_info.io_type=XPD_IO_SOCKET;
			xpd_info.io.sock=atoi(buf+11);
		}
		GETIBUF(xpd_info.drop.baud);
		GETIBUF(xpd_info.drop.parity);
		GETIBUF(xpd_info.drop.node);
		GETBUF();
		GETBUF();
		GETBUF();
		GETBUF();
		GETBUF();
		GETSBUF(xpd_info.drop.user.full_name);
		GETSBUF(xpd_info.drop.user.location);
		GETSBUF(xpd_info.drop.user.home_phone);
		GETSBUF(xpd_info.drop.user.work_phone);
		GETSBUF(xpd_info.drop.user.password);
		GETIBUF(xpd_info.drop.user.level);
		GETIBUF(xpd_info.drop.user.times_on);
		GETDBUF(xpd_info.drop.user.last_call_date);
		GETIBUF(xpd_info.drop.user.seconds_remaining);
		GETIBUF(tmp);
		if(tmp*60 > xpd_info.drop.user.seconds_remaining)
			xpd_info.drop.user.seconds_remaining = tmp*60;
		xpd_info.end_time=time(NULL)+xpd_info.drop.user.seconds_remaining;
		GETBUF();
		if(strcmp(buf,"GR"))
			xpd_info.drop.user.dflags |= XPD_ANSI_SUPPORTED|XPD_CP437_SUPPORTED;
		else if(strcmp(buf,"NG"))
			xpd_info.drop.user.dflags |= XPD_CP437_SUPPORTED;
		GETIBUF(xpd_info.drop.user.rows);
		GETBBUF(xpd_info.drop.user.expert);
		GETDBUF(xpd_info.drop.user.expiration);
		GETIBUF(xpd_info.drop.user.number);
		GETCBUF(xpd_info.drop.user.protocol);
		GETIBUF(xpd_info.drop.user.uploads);
		GETIBUF(xpd_info.drop.user.downloads);
		GETIBUF(xpd_info.drop.user.download_k_today);
		GETIBUF(xpd_info.drop.user.max_download_k_today);
		GETDBUF(xpd_info.drop.user.birthday);
		GETSBUF(xpd_info.drop.sys.main_dir);
		GETSBUF(xpd_info.drop.sys.gen_dir);
		GETSBUF(xpd_info.drop.sys.sysop_name);
		GETSBUF(xpd_info.drop.user.alias);
		GETBUF();
		GETBUF();
		GETBUF();
		GETBUF();
		GETIBUF(xpd_info.drop.sys.default_attr);
		GETBUF();
		GETBUF();
		GETTBUF(xpd_info.drop.user.call_time);
		GETTBUF(xpd_info.drop.user.last_call_time);
		GETIBUF(xpd_info.drop.user.max_files_per_day);
		GETIBUF(xpd_info.drop.user.downloads_today);
		GETIBUF(xpd_info.drop.user.total_upload_k);
		GETIBUF(xpd_info.drop.user.total_download_k);
		GETSBUF(xpd_info.drop.user.comment);
		GETIBUF(xpd_info.drop.user.total_doors);
		GETIBUF(xpd_info.drop.user.total_messages);
	}

error_return:
	if(df)
		fclose(df);
	return(-1);

done_parsing:
	if(ferror(df)) {
		fclose(df);
		return(-1);
	}
	if(feof(df)) {
		fclose(df);
		return(0);
	}
}

int xpd_rwrite(const char *data, int data_len)
{
	struct text_info	ti;

	if(data_len == -1)
		data_len=strlen(data);

	/* Set up cterm to match conio */
	gettextinfo(&ti);
	cterm.xpos=ti.winleft+ti.curx-1;
	cterm.ypos=ti.wintop+ti.cury-1;
	cterm.attr=ti.attribute;
	cterm.quiet=TRUE;
	cterm.doorway_mode=TRUE;

	/* Disable ciolib output for ANSI */
	ciolib_ansi_writebyte_cb=dummy_writebyte_cb;

	/* Send data to cterm */
	cterm_write((char *)data, data_len, NULL, 0, NULL);

	/* Send data to remote */
	xpd_ansi_writestr_cb((char *)data,data_len);

	/* Set conio to match cterm */
	gotoxy(cterm.xpos-ti.winleft+1, cterm.ypos-ti.winright+1);
	textattr(cterm.attr);

	/* Re-enable ciolib output */
	ciolib_ansi_writebyte_cb=xpd_ansi_writebyte_cb;
}
