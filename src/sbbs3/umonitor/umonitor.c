/* umonitor.c */

/* Synchronet for *nix node activity monitor */

/* $Id$ */

/****************************************************************************
 * @format.tab-size 4		(Plain Text/Source Code File Header)			*
 * @format.use-tabs true	(see http://www.synchro.net/ptsc_hdr.html)		*
 *																			*
 * Copyright 2003 Rob Swindell - http://www.synchro.net/copyright.html		*
 *																			*
 * This program is free software; you can redistribute it and/or			*
 * modify it under the terms of the GNU General Public License				*
 * as published by the Free Software Foundation; either version 2			*
 * of the License, or (at your option) any later version.					*
 * See the GNU General Public License for more details: gpl.txt or			*
 * http://www.fsf.org/copyleft/gpl.html										*
 *																			*
 * Anonymous FTP access to the most recent released source is available at	*
 * ftp://vert.synchro.net, ftp://cvs.synchro.net and ftp://ftp.synchro.net	*
 *																			*
 * Anonymous CVS access to the development source and modification history	*
 * is available at cvs.synchro.net:/cvsroot/sbbs, example:					*
 * cvs -d :pserver:anonymous@cvs.synchro.net:/cvsroot/sbbs login			*
 *     (just hit return, no password is necessary)							*
 * cvs -d :pserver:anonymous@cvs.synchro.net:/cvsroot/sbbs checkout src		*
 *																			*
 * For Synchronet coding style and modification guidelines, see				*
 * http://www.synchro.net/source.html										*
 *																			*
 * You are encouraged to submit any modifications (preferably in Unix diff	*
 * format) via e-mail to mods@synchro.net									*
 *																			*
 * Note: If this box doesn't appear square, then you need to fix your tabs.	*
 ****************************************************************************/

#include "conwrap.h"	/* this has to go BEFORE curses.h so getkey() can be macroed around */
#include <curses.h>
#include <sys/types.h>
#include <sys/time.h>
#ifdef __QNX__
#include <string.h>
#endif
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "sockwrap.h"	/* Must go before <sys/un.h> */
#include <sys/un.h>
#include "genwrap.h"
#include "uifc.h"
#include "sbbsdefs.h"
#include "genwrap.h"	/* stricmp */
#include "dirwrap.h"	/* lock/unlock/sopen */
#include "filewrap.h"	/* lock/unlock/sopen */
#include "sockwrap.h"

enum {
	 MODE_LIST
	,MODE_ANON
	,MODE_LOCK
	,MODE_INTR
	,MODE_RRUN
	,MODE_DOWN
	,MODE_EVENT
	,MODE_NOPAGE
	,MODE_NOALERTS
	,MODE_STATUS
	,MODE_USERON
	,MODE_ACTION
	,MODE_ERRORS
	,MODE_MISC
	,MODE_CONN
	,MODE_AUX
	,MODE_EXTAUX
	};

enum {
	 SPY_NOSOCKET
	,SPY_NOCONNECT
	,SPY_SELECTFAILED
	,SPY_SOCKETLOST
	,SPY_STDINLOST
	,SPY_CLOSED
	};

/********************/
/* Global Variables */
/********************/
uifcapi_t uifc; /* User Interface (UIFC) Library API */
char tmp[256];
int nodefile;
const char *YesStr="Yes";
const char *NoStr="No";


void bail(int code)
{
    if(code) {
        puts("\nHit a key...");
        getch(); 
	}
    uifc.bail();

    exit(code);
}

void allocfail(uint size)
{
    printf("\7Error allocating %u bytes of memory.\n",size);
    bail(1);
}

int spyon(char *sockname)  {
	SOCKET		spy_sock=INVALID_SOCKET;
	struct sockaddr_un spy_name;
	socklen_t	spy_len;
	char		key;
	char		buf[1];
	int		i;
	struct	termios	tio;
	struct	termios	old_tio;
	fd_set	rd;
	BOOL	b;
	int		retval=0;

	/* ToDo Test for it actually being a socket! */
	/* Well, it will fail to connect won't it?   */

	if((spy_sock=socket(PF_LOCAL,SOCK_STREAM,0))==INVALID_SOCKET)  {
		printf("ERROR %d creating local spy socket", errno);
		return(SPY_NOSOCKET);
	}
	
	spy_name.sun_family=AF_LOCAL;
	SAFECOPY(spy_name.sun_path,sockname);
	spy_len=SUN_LEN(&spy_name);
	if(connect(spy_sock,(struct sockaddr *)&spy_name,spy_len))  {
		return(SPY_NOCONNECT);
	}
	i=1;

	tcgetattr(STDIN_FILENO,&old_tio);
	tcgetattr(STDIN_FILENO,&tio);
	cfmakeraw(&tio);
	tcsetattr(STDIN_FILENO,TCSANOW,&tio);
	printf("\r\n\r\nLocal spy mode... press CTRL-C to return to monitor\r\n\r\n");
	while(spy_sock!=INVALID_SOCKET)  {
		FD_ZERO(&rd);
		FD_SET(STDIN_FILENO,&rd);
		FD_SET(spy_sock,&rd);
		if((select(spy_sock > STDIN_FILENO ? spy_sock+1 : STDIN_FILENO+1,&rd,NULL,NULL,NULL))<0)  {
			close(spy_sock);
			spy_sock=INVALID_SOCKET;
			break;
		}
		if(!socket_check(spy_sock,NULL,&b,0)) {
			close(spy_sock);
			spy_sock=INVALID_SOCKET;
			retval=SPY_SOCKETLOST;
			break;
		}
		if(FD_ISSET(STDIN_FILENO,&rd))  {
			if((i=read(STDIN_FILENO,&key,1))==1)  {
				/* Check for control keys */
				switch(key)  {
					case 3:	/* CTRL-C */
						close(spy_sock);
						spy_sock=INVALID_SOCKET;
						retval=SPY_CLOSED;
						break;
					default:
						write(spy_sock,&key,1);
				}
			}
			else if(i<0) {
				close(spy_sock);
				spy_sock=INVALID_SOCKET;
				retval=SPY_STDINLOST;
				break;
			}
		}
		if(spy_sock != INVALID_SOCKET && FD_ISSET(spy_sock,&rd))  {
			if((i=read(spy_sock,&buf,1))==1)  {
				write(STDOUT_FILENO,buf,1);
			}
			else if(i<0) {
				close(spy_sock);
				spy_sock=INVALID_SOCKET;
				retval=SPY_SOCKETLOST;
				break;
			}
		}
	}
	tcsetattr(STDIN_FILENO,TCSANOW,&old_tio);
	return(retval);
}

char* itoa(int val, char* str, int radix)
{
	switch(radix) {
		case 8:
			sprintf(str,"%o",val);
			break;
		case 10:
			sprintf(str,"%u",val);
			break;
		case 16:
			sprintf(str,"%x",val);
			break;
		default:
			sprintf(str,"bad radix: %d",radix);
			break;
	}
	return(str);
}

/****************************************************************************/
/* Unpacks the password 'pass' from the 5bit ASCII inside node_t. 32bits in */
/* node.extaux, and the other 8bits in the upper byte of node.aux			*/
/****************************************************************************/
char *unpackchatpass(char *pass, node_t node)
{
	char 	bits;
	int 	i;

	pass[0]=(node.aux&0x1f00)>>8;
	pass[1]=(char)(((node.aux&0xe000)>>13)|((node.extaux&0x3)<<3));
	bits=2;
	for(i=2;i<8;i++) {
		pass[i]=(char)((node.extaux>>bits)&0x1f);
		bits+=5; }
	pass[8]=0;
	for(i=0;i<8;i++)
		if(pass[i])
			pass[i]+=64;
	return(pass);
}

/******************************************************************************************/
/* Returns the information for node number 'number' contained in 'node' into string 'str' */
/******************************************************************************************/
char *nodedat(char *str, int number, node_t node)
{
    char hour,mer[3];
	char buf[1024];

	sprintf(str,"Node %2d: ",number);
	switch(node.status) {
		case NODE_WFC:
			strcat(str,"Waiting for call");
			break;
		case NODE_OFFLINE:
			strcat(str,"Offline");
			break;
		case NODE_NETTING:
			strcat(str,"Networking");
			break;
		case NODE_LOGON:
			strcat(str,"At logon prompt");
			break;
		case NODE_EVENT_WAITING:
			strcat(str,"Waiting for all nodes to become inactive");
			break;
		case NODE_EVENT_LIMBO:
			sprintf(buf,"Waiting for node %d to finish external event",node.aux);
			strcat(str,buf);
			break;
		case NODE_EVENT_RUNNING:
			strcat(str,"Running external event");
			break;
		case NODE_NEWUSER:
			strcat(str,"New user");
			strcat(str," applying for access ");
			if(!node.connection)
				strcat(str,"locally");
			else if(node.connection==0xffff)
				strcat(str,"via telnet");
			else {
				sprintf(buf,"at %ubps",node.connection);
				strcat(str,buf); }
			break;
		case NODE_QUIET:
		case NODE_INUSE:
			sprintf(buf,"User #%d",node.useron);
			strcat(str,buf);
			strcat(str," ");
			switch(node.action) {
				case NODE_MAIN:
					strcat(str,"at main menu");
					break;
				case NODE_RMSG:
					strcat(str,"reading messages");
					break;
				case NODE_RMAL:
					strcat(str,"reading mail");
					break;
				case NODE_RSML:
					strcat(str,"reading sent mail");
					break;
				case NODE_RTXT:
					strcat(str,"reading text files");
					break;
				case NODE_PMSG:
					strcat(str,"posting message");
					break;
				case NODE_SMAL:
					strcat(str,"sending mail");
					break;
				case NODE_AMSG:
					strcat(str,"posting auto-message");
					break;
				case NODE_XTRN:
					if(!node.aux)
						strcat(str,"at external program menu");
					else
						sprintf(buf,"running external program #%d",node.aux);
						strcat(str,buf);
					break;
				case NODE_DFLT:
					strcat(str,"changing defaults");
					break;
				case NODE_XFER:
					strcat(str,"at transfer menu");
					break;
				case NODE_RFSD:
					sprintf(buf,"retrieving from device #%d",node.aux);
					strcat(str,buf);
					break;
				case NODE_DLNG:
					strcat(str,"downloading");
					break;
				case NODE_ULNG:
					strcat(str,"uploading");
					break;
				case NODE_BXFR:
					strcat(str,"transferring bidirectional");
					break;
				case NODE_LFIL:
					strcat(str,"listing files");
					break;
				case NODE_LOGN:
					strcat(str,"logging on");
					break;
				case NODE_LCHT:
					strcat(str,"in local chat with sysop");
					break;
				case NODE_MCHT:
					if(node.aux) {
						sprintf(buf,"in multinode chat channel %d",node.aux&0xff);
						strcat(str,buf);
						if(node.aux&0x1f00) { /* password */
							strcat(str,"*");
							sprintf(buf," %s",unpackchatpass(tmp,node));
							strcat(str,buf); } }
					else
						strcat(str,"in multinode global chat channel");
					break;
				case NODE_PAGE:
					sprintf(buf,"paging node %u for private chat",node.aux);
					strcat(str,buf);
					break;
				case NODE_PCHT:
					sprintf(buf,"in private chat with node %u",node.aux);
					strcat(str,buf);
					break;
				case NODE_GCHT:
					strcat(str,"chatting with The Guru");
					break;
				case NODE_CHAT:
					strcat(str,"in chat section");
					break;
				case NODE_TQWK:
					strcat(str,"transferring QWK packet");
					break;
				case NODE_SYSP:
					strcat(str,"performing sysop activities");
					break;
				default:
					sprintf(buf,itoa(node.action,tmp,10));
					strcat(str,buf);
					break;  }
			if(!node.connection)
				strcat(str," locally");
			else if(node.connection==0xffff)
				strcat(str," via telnet");
			else {
				sprintf(buf," at %ubps",node.connection);
				strcat(str,buf); }
			if(node.action==NODE_DLNG) {
				if((node.aux/60)>=12) {
					if(node.aux/60==12)
						hour=12;
					else
						hour=(node.aux/60)-12;
					strcpy(mer,"pm"); }
				else {
					if((node.aux/60)==0)    /* 12 midnite */
						hour=12;
					else hour=node.aux/60;
					strcpy(mer,"am"); }
				sprintf(buf," ETA %02d:%02d %s"
					,hour,node.aux-((node.aux/60)*60),mer); 
				strcat(str,buf); }
			break; }
	if(node.misc&(NODE_LOCK|NODE_POFF|NODE_AOFF|NODE_MSGW|NODE_NMSG)) {
		strcat(str," (");
		if(node.misc&NODE_AOFF)
			strcat(str,"A");
		if(node.misc&NODE_LOCK)
			strcat(str,"L");
		if(node.misc&(NODE_MSGW|NODE_NMSG))
			strcat(str,"M");
		if(node.misc&NODE_POFF)
			strcat(str,"P");
		strcat(str,")"); }
	if(((node.misc
		&(NODE_ANON|NODE_UDAT|NODE_INTR|NODE_RRUN|NODE_EVENT|NODE_DOWN))
		|| node.status==NODE_QUIET)) {
		strcat(str," [");
		if(node.misc&NODE_ANON)
			strcat(str,"A");
		if(node.misc&NODE_INTR)
			strcat(str,"I");
		if(node.misc&NODE_RRUN)
			strcat(str,"R");
		if(node.misc&NODE_UDAT)
			strcat(str,"U");
		if(node.status==NODE_QUIET)
			strcat(str,"Q");
		if(node.misc&NODE_EVENT)
			strcat(str,"E");
		if(node.misc&NODE_DOWN)
			strcat(str,"D");
		if(node.misc&NODE_LCHAT)
			strcat(str,"C");
		strcat(str,"]"); }
	if(node.errors) {
		sprintf(buf," %d error%c",node.errors, node.errors>1 ? 's' : '\0' );
		strcat(str,buf); }
	return(str);
}

/****************************************************************************/
/* Reads the data for node number 'number' into the structure 'node'        */
/* from NODE.DAB															*/
/* if lockit is non-zero, locks this node's record. putnodedat() unlocks it */
/****************************************************************************/
void getnodedat(int number, node_t *node, int lockit)
{
	int count;
	char	msg[80];

	number--;	/* make zero based */
	for(count=0;count<LOOP_NODEDAB;count++) {
		if(count)
			SLEEP(100);
		lseek(nodefile,(long)number*sizeof(node_t),SEEK_SET);
		if(lockit
			&& lock(nodefile,(long)number*sizeof(node_t),sizeof(node_t))==-1) 
			continue; 
		if(read(nodefile,node,sizeof(node_t))==sizeof(node_t))
			break;
	}
	if(count>=(LOOP_NODEDAB/2)) {
		sprintf(msg,"NODE.DAB (node %d) COLLISION (READ) - Count: %d\n"
			,number+1, count); 
		uifc.msg(msg); }
	else if(count==LOOP_NODEDAB) {
		sprintf(msg,"!Error reading nodefile for node %d\n",number+1);
		uifc.msg(msg); }
}

/****************************************************************************/
/* Write the data from the structure 'node' into NODE.DAB  					*/
/* getnodedat(num,&node,1); must have been called before calling this func  */
/*          NOTE: ------^   the indicates the node record has been locked   */
/****************************************************************************/
void putnodedat(int number, node_t node)
{
	number--;	/* make zero based */
	lseek(nodefile,(long)number*sizeof(node_t),SEEK_SET);
	if(write(nodefile,&node,sizeof(node_t))!=sizeof(node_t)) {
		unlock(nodefile,(long)number*sizeof(node_t),sizeof(node_t));
		printf("Error writing to nodefile for node %d\n",number+1);
		return; }
	unlock(nodefile,(long)number*sizeof(node_t),sizeof(node_t));
}

void node_toggles(int nodenum)  {
	char**	opt;
	int		i,j;
	node_t	node;
	int		save=0;

	if((opt=(char **)MALLOC(sizeof(char *)*(MAX_OPTS+1)))==NULL)
		allocfail(sizeof(char *)*(MAX_OPTS+1));
	for(i=0;i<(MAX_OPTS+1);i++)
		if((opt[i]=(char *)MALLOC(MAX_OPLN))==NULL)
			allocfail(MAX_OPLN);

	getnodedat(nodenum,&node,0);
	i=0;
	uifc.helpbuf=	"`Node Toggles:`\n"
					"\nToDo: Add help (Mention that changes take effect immediately)";
	while(save==0) {
		j=0;
		sprintf(opt[j++],"%-30s%3s","Locked for SysOps only",node.misc&NODE_LOCK ? YesStr : NoStr);
		sprintf(opt[j++],"%-30s%3s","Interrupt (Hangup)",node.misc&NODE_INTR ? YesStr : NoStr);
		sprintf(opt[j++],"%-30s%3s","Page disabled",node.misc&NODE_POFF ? YesStr : NoStr);
		sprintf(opt[j++],"%-30s%3s","Activity alert disabled",node.misc&NODE_AOFF ? YesStr : NoStr);
		sprintf(opt[j++],"%-30s%3s","Re-run on logoff",node.misc&NODE_RRUN ? YesStr : NoStr);
		sprintf(opt[j++],"%-30s%3s","Down node after logoff",(node.misc&NODE_DOWN || (node.status==NODE_OFFLINE)) ? YesStr : NoStr);
		sprintf(opt[j++],"%-30s%3s","Reset private chat",node.misc&NODE_RPCHT ? YesStr : NoStr);
		opt[j][0]=0;

		switch(uifc.list(WIN_MID,0,0,0,&i,0,"Node Toggles",opt)) {
			case 0:	/* Locked */
				node.misc ^= NODE_LOCK;
				break;

			case 1:	/* Interrupt */
				node.misc ^= NODE_INTR;
				break;

			case 2:	/* Page disabled */
				node.misc ^= NODE_POFF;
				break;

			case 3:	/* Activity alert */
				node.misc ^= NODE_AOFF;
				break;

			case 4:	/* Re-run */
				node.misc ^= NODE_RRUN;
				break;

			case 5:	/* Down */
				if(node.status == NODE_INUSE || node.status==NODE_LOGON)
					node.misc ^= NODE_DOWN;
				else {
					if(node.status!=NODE_OFFLINE)
						node.status=NODE_OFFLINE;
					else
						node.status=NODE_WFC;
				}
				break;

			case 6:	/* Reset chat */
				node.misc ^= NODE_RPCHT;
				break;
				
			case -1:
				save=1;
				break;
				
			default:
				uifc.msg("Option not implemented");
				continue;
		}
		lock(nodefile,(long)(nodenum-1)*sizeof(node_t),sizeof(node_t));
		putnodedat(nodenum,node);
	}
}

int main(int argc, char** argv)  {
	char**	opt;
	char**	mopt;
	int		main_dflt=0;
	int		main_bar=0;
	char revision[16];
	char str[256],str2[256],ctrl_dir[41],*p;
	char title[256];
	int sys_nodes;
	int i,j;
	node_t node;
	char	*buf;
	int		buffile;

	sscanf("$Revision$", "%*s %s", revision);

    printf("\nSynchronet UNIX Monitor %s-%s  Copyright 2003 "
        "Rob Swindell\n",revision,PLATFORM_DESC);

	p=getenv("SBBSCTRL");
	if(p==NULL) {
		printf("\7\nSBBSCTRL environment variable is not set.\n");
		printf("This environment variable must be set to your CTRL directory.");
		printf("\nExample: SET SBBSCTRL=/sbbs/ctrl\n");
		exit(1); }

	sprintf(ctrl_dir,"%.40s",p);
	if(ctrl_dir[strlen(ctrl_dir)-1]!='\\'
		&& ctrl_dir[strlen(ctrl_dir)-1]!='/')
		strcat(ctrl_dir,"/");

	sprintf(str,"%snode.dab",ctrl_dir);
	if((nodefile=sopen(str,O_RDWR|O_BINARY,SH_DENYNO))==-1) {
		printf("\7\nError %d opening %s.\n",errno,str);
		exit(1); }

	sys_nodes=filelength(nodefile)/sizeof(node_t);
	if(!sys_nodes) {
		printf("%s reflects 0 nodes!\n",str);
		exit(1); }

    memset(&uifc,0,sizeof(uifc));

	uifc.esc_delay=500;

	for(i=1;i<argc;i++) {
        if(argv[i][0]=='-'
            )
            switch(toupper(argv[i][1])) {
                case 'C':
        			uifc.mode|=UIFC_COLOR;
                    break;
                case 'L':
                    uifc.scrn_len=atoi(argv[i]+2);
                    break;
                case 'E':
                    uifc.esc_delay=atoi(argv[i]+2);
                    break;
				case 'I':
					uifc.mode|=UIFC_IBM;
					break;
                default:
                    printf("\nusage: %s [ctrl_dir] [options]"
                        "\n\noptions:\n\n"
                        "-c  =  force color mode\n"
                        "-e# =  set escape delay to #msec\n"
						"-i  =  force IBM charset\n"
                        "-l# =  set screen lines to #\n"
						,argv[0]
                        );
        			exit(0);
           }
    }

	uifc.size=sizeof(uifc);
	i=uifcinic(&uifc);  /* curses */
	if(i!=0) {
		printf("uifc library init returned error %d\n",i);
		exit(1);
	}

	if((opt=(char **)MALLOC(sizeof(char *)*(MAX_OPTS+1)))==NULL)
		allocfail(sizeof(char *)*(MAX_OPTS+1));
	for(i=0;i<(MAX_OPTS+1);i++)
		if((opt[i]=(char *)MALLOC(MAX_OPLN))==NULL)
			allocfail(MAX_OPLN);

	if((mopt=(char **)MALLOC(sizeof(char *)*MAX_OPTS))==NULL)
		allocfail(sizeof(char *)*MAX_OPTS);
	for(i=0;i<MAX_OPTS;i++)
		if((mopt[i]=(char *)MALLOC(MAX_OPLN))==NULL)
			allocfail(MAX_OPLN);

	sprintf(title,"Synchronet UNIX Monitor %s-%s",revision,PLATFORM_DESC);
	if(uifc.scrn(title)) {
		printf(" USCRN (len=%d) failed!\n",uifc.scrn_len+1);
		bail(1);
	}

	while(1) {
		for(i=1;i<=sys_nodes;i++) {
			getnodedat(i,&node,0);
			nodedat(mopt[i-1],i,node);
		}
		mopt[i-1][0]=0;

		uifc.helpbuf=	"`Synchronet Monitor:`\n"
						"\nCTRL-E displays the error log"
						"\nToDo: Add more help.";
						
		j=uifc.list(WIN_ORG|WIN_MID|WIN_ESC|WIN_ACT|WIN_DYN,0,0,70,&main_dflt,&main_bar
			,title,mopt);

		if(j==-7) {	/* CTRL-E */
			/* ToDo must get the logs dir from the config */
			sprintf(str,"%s../data/error.log",ctrl_dir);
			if(fexist(str)) {
				if((buffile=sopen(str,O_RDONLY,SH_DENYWR))>=0) {
					j=filelength(buffile);
					if((buf=(char *)MALLOC(j+1))!=NULL) {
						read(buffile,buf,j);
						close(buffile);
						*(buf+j)=0;
						uifc.helpbuf=buf;
						uifc.helptitle="Error Log";
						uifc.showhelp();
						uifc.helptitle=NULL;
						free(buf);
						continue;
					}
					close(buffile);
					uifc.msg("Error allocating memory for the error log");
					continue;
				}
				uifc.msg("Error opening error log");
			}
			else {
				uifc.msg("Error log does not exist");
			}
			continue;
		}

		if(j <= -2)
			continue;

		if(j==-1) {
			i=0;
			strcpy(opt[0],YesStr);
			strcpy(opt[1],NoStr);
			opt[2][0]=0;
			uifc.helpbuf=	"`Exit Synchronet UNIX Monitor:`\n"
							"\n"
							"\nIf you want to exit the Synchronet UNIX monitor utility,"
							"\nselect `Yes`. Otherwise, select `No` or hit ~ ESC ~.";
			i=uifc.list(WIN_MID,0,0,0,&i,0,"Exit Synchronet Monitor",opt);
			if(!i)
				bail(0);
			continue;
		}
		if(j<sys_nodes && j>=0) {
			i=0;
			strcpy(opt[i++],"Spy on node");
			strcpy(opt[i++],"Node toggles");
			strcpy(opt[i++],"Clear Errors");
			opt[i][0]=0;
			i=0;
			uifc.helpbuf=	"`Node Options:`\n"
							"\nToDo: Add help";
			switch(uifc.list(WIN_MID|WIN_SAV,0,0,0,&i,0,"Node Options",opt))  {
				case 0:	/* Spy */
					snprintf(str,sizeof(str),"%slocalspy%d.sock", ctrl_dir, j+1);
					endwin();
					i=spyon(str);
					refresh();
					switch(i) {
						case SPY_NOSOCKET:
							uifc.msg("Could not create socket");
							break;
							
						case SPY_NOCONNECT:
							sprintf(str2,"Failed to connect to %s",str);
							uifc.msg(str2);
							break;

						case SPY_SELECTFAILED:
							uifc.msg("select() failed, connection terminated.");

						case SPY_SOCKETLOST:
							uifc.msg("Spy socket lost");
							break;
							
						case SPY_STDINLOST:
							uifc.msg("STDIN has gone away... you probably can't close this window.  :-)");
							break;
							
						case SPY_CLOSED:
							break;
							
						default:
							sprintf(str,"Unknown return code %d",i);
							uifc.msg(str);
					}
					break;

				case 1: /* Node Toggles */
					node_toggles(j+1);
					break;

				case 2:
					getnodedat(j+1,&node,1);
					node.errors=0;
					putnodedat(j+1,node);
					break;

				case -1:
					break;
					
				default:
					uifc.msg("Option not implemented");
					break;
			}
		}
	}
}
