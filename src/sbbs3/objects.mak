# objects.mak

# Make 'include file' listing object files for SBBS.DLL

# $Id$

# LIBODIR, SLASH, and OFILE must be pre-defined

OBJS	=	$(LIBODIR)$(SLASH)ansiterm.$(OFILE)\
			$(LIBODIR)$(SLASH)answer.$(OFILE)\
			$(LIBODIR)$(SLASH)ars.$(OFILE)\
			$(LIBODIR)$(SLASH)atcodes.$(OFILE)\
			$(LIBODIR)$(SLASH)bat_xfer.$(OFILE)\
			$(LIBODIR)$(SLASH)bulkmail.$(OFILE)\
			$(LIBODIR)$(SLASH)chat.$(OFILE)\
			$(LIBODIR)$(SLASH)chk_ar.$(OFILE)\
			$(LIBODIR)$(SLASH)con_hi.$(OFILE)\
			$(LIBODIR)$(SLASH)con_out.$(OFILE)\
			$(LIBODIR)$(SLASH)crc32.$(OFILE)\
			$(LIBODIR)$(SLASH)data.$(OFILE)\
			$(LIBODIR)$(SLASH)data_ovl.$(OFILE)\
			$(LIBODIR)$(SLASH)date_str.$(OFILE)\
			$(LIBODIR)$(SLASH)download.$(OFILE)\
			$(LIBODIR)$(SLASH)email.$(OFILE)\
			$(LIBODIR)$(SLASH)exec.$(OFILE)\
			$(LIBODIR)$(SLASH)execfile.$(OFILE)\
			$(LIBODIR)$(SLASH)execfunc.$(OFILE)\
			$(LIBODIR)$(SLASH)execmisc.$(OFILE)\
			$(LIBODIR)$(SLASH)execmsg.$(OFILE)\
			$(LIBODIR)$(SLASH)fido.$(OFILE)\
			$(LIBODIR)$(SLASH)file.$(OFILE)\
			$(LIBODIR)$(SLASH)filedat.$(OFILE)\
			$(LIBODIR)$(SLASH)getkey.$(OFILE)\
			$(LIBODIR)$(SLASH)getmsg.$(OFILE)\
			$(LIBODIR)$(SLASH)getnode.$(OFILE)\
			$(LIBODIR)$(SLASH)getstr.$(OFILE)\
			$(LIBODIR)$(SLASH)inkey.$(OFILE)\
			$(LIBODIR)$(SLASH)listfile.$(OFILE)\
			$(LIBODIR)$(SLASH)load_cfg.$(OFILE)\
			$(LIBODIR)$(SLASH)logfile.$(OFILE)\
			$(LIBODIR)$(SLASH)login.$(OFILE)\
			$(LIBODIR)$(SLASH)logon.$(OFILE)\
			$(LIBODIR)$(SLASH)logout.$(OFILE)\
			$(LIBODIR)$(SLASH)lzh.$(OFILE)\
			$(LIBODIR)$(SLASH)mail.$(OFILE)\
			$(LIBODIR)$(SLASH)main.$(OFILE)\
			$(LIBODIR)$(SLASH)misc.$(OFILE)\
			$(LIBODIR)$(SLASH)msgtoqwk.$(OFILE)\
			$(LIBODIR)$(SLASH)netmail.$(OFILE)\
			$(LIBODIR)$(SLASH)newuser.$(OFILE)\
			$(LIBODIR)$(SLASH)pack_qwk.$(OFILE)\
			$(LIBODIR)$(SLASH)pack_rep.$(OFILE)\
			$(LIBODIR)$(SLASH)postmsg.$(OFILE)\
			$(LIBODIR)$(SLASH)prntfile.$(OFILE)\
			$(LIBODIR)$(SLASH)putmsg.$(OFILE)\
			$(LIBODIR)$(SLASH)putnode.$(OFILE)\
			$(LIBODIR)$(SLASH)qwk.$(OFILE)\
			$(LIBODIR)$(SLASH)qwktomsg.$(OFILE)\
			$(LIBODIR)$(SLASH)readmail.$(OFILE)\
			$(LIBODIR)$(SLASH)readmsgs.$(OFILE)\
			$(LIBODIR)$(SLASH)ringbuf.$(OFILE)\
			$(LIBODIR)$(SLASH)scandirs.$(OFILE)\
			$(LIBODIR)$(SLASH)scansubs.$(OFILE)\
			$(LIBODIR)$(SLASH)scfglib1.$(OFILE)\
			$(LIBODIR)$(SLASH)scfglib2.$(OFILE)\
			$(LIBODIR)$(SLASH)smblib.$(OFILE)\
			$(LIBODIR)$(SLASH)smbtxt.$(OFILE)\
			$(LIBODIR)$(SLASH)smbwrap.$(OFILE)\
			$(LIBODIR)$(SLASH)sortdir.$(OFILE)\
			$(LIBODIR)$(SLASH)str.$(OFILE)\
			$(LIBODIR)$(SLASH)telgate.$(OFILE)\
			$(LIBODIR)$(SLASH)telnet.$(OFILE)\
			$(LIBODIR)$(SLASH)text_sec.$(OFILE)\
			$(LIBODIR)$(SLASH)tmp_xfer.$(OFILE)\
			$(LIBODIR)$(SLASH)un_qwk.$(OFILE)\
			$(LIBODIR)$(SLASH)un_rep.$(OFILE)\
			$(LIBODIR)$(SLASH)upload.$(OFILE)\
			$(LIBODIR)$(SLASH)userdat.$(OFILE)\
			$(LIBODIR)$(SLASH)useredit.$(OFILE)\
			$(LIBODIR)$(SLASH)viewfile.$(OFILE)\
			$(LIBODIR)$(SLASH)wrappers.$(OFILE)\
			$(LIBODIR)$(SLASH)writemsg.$(OFILE)\
			$(LIBODIR)$(SLASH)xtrn.$(OFILE)\
			$(LIBODIR)$(SLASH)xtrn_sec.$(OFILE) 
