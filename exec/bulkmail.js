// bulkmail.js

// Bulk email all users that match AR String input

// written by the hanged man, Solace BBS, solace.synchro.net

load("sbbsdefs.js");

const REVISION = "$Revision$".split(' ')[1];

print("Synchronet BulkMailer " + REVISION);

print("Enter ARS matches to send mail to or [ENTER] for everyone");

printf("ARS to match: "); 
if((ars=console.getstr(40,K_UPPER))==undefined)
	exit();

printf("\r\n\1y\1hSubject: ");

if((subj=console.getstr(70,K_LINE))=="")
	exit();

fname = system.temp_dir + "bulkmsg.txt";

file_remove(fname)

console.editfile(fname);

if(!file_exists(fname))	// Edit aborted
	exit();

file = new File(fname);
if(!file.open("rt")) {
    log("!ERROR " + errno_str + " opening " + fname);
    exit();
}
msgtxt = lfexpand(file.read(file_size(fname)));
file.close();
delete file;

if(msgtxt == "")
    exit();

msgbase = new MsgBase("mail");
if(msgbase.open()==false) {
	log("!ERROR " + msgbase.last_error);
	exit();
}

var u;	// user object

if(system.lastuser!=undefined)
	lastuser=system.lastuser;				// v3.11
else
    lastuser=system.stats.total_users;		// v3.10

var sent=0;

for(i=1; i<=lastuser; i++)
{
    u = new User(i);

    if(!u.compare_ars(ars))
		continue;

	/*checking for netmail forward */
	if(u.settings&USER_NETMAIL && u.netmail.length)
		hdr = { to_net_addr: u.netmail, to_net_type: NET_INTERNET };
	else
		hdr = { to_ext: String(u.number) };
	
	hdr.to = u.alias;
	hdr.from = system.operator;
	hdr.from_ext = "1";
	hdr.subject = subj;  

	printf("Sending mail to %s #%u\r\n", hdr.to, i);

	if(!msgbase.save_msg(hdr, msgtxt))
		log("!ERROR " + msgbase.last_error + "saving bulkmail message");
	else {
		log(format("Sent bulk mail message to: %s #%u", u.alias, i));
		sent++;
	}
}

msgbase.close();

if(sent>1) {
	print("Sent bulk mail to " + sent + " users");
	log("Sent bulk mail message to " + sent + " users");
}
