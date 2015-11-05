function Attribute(value) {
	this.value = value;
}

Attribute.prototype = {
	// TODO: High intensity background, not blink
	get blink() {
		return (this.value & 0x80) ? true : false;
	},
	set blink(val) {
		if (val)
			this.value |= 0x80;
		else
			this.value &= ~0x80;
	},

	get bg() {
		return (this.value >> 4) & 0x07;
	},
	set bg(val) {
		this.value &= 0x8f;
		this.value |= ((val << 4) & 0x70);
	},

	get fg() {
		return this.value & 0x0f;
	},
	set fg(val) {
		this.value &= 0xf0;
		this.value |= val & 0x0f;
	}
}

var dk = {
	console:{
		x:1,					// Current column (1-based)
		y:1,					// Current row (1-based)
		attr:new Attribute(7),	// Current attribute
		ansi:true,				// ANSI support is enabled
		charset:'cp437',		// Supported character set
		local:true,				// True if writes should go to the local screen
		remote:true,			// True if writes should go to the remote terminal
		rows:24,				// Rows in users terminal
		expert_mode:true,

		/*
		 * Clears the current screen to black and moves to location 1,1
		 * sets the current attribute to 7
		 */
		clear:function() {
		},

		/*
		 * Clears to end of line.
		 * Not available witout ANSI (???)
		 */
		cleareol:function() {
		},

		/*
		 * Moves the cursor to the specified position.
		 * returns false on error.
		 * Not available without ANSI
		 */
		gotoxy:function(x,y) {
		},

		/*
		 * Returns a Graphic object representing the specified block
		 * or undefined on error (ie: invalid block specified).
		 */
		getblock:function(sx,sy,ex,ey) {
		},

		/*
		 * Writes a string with a "\r\n" appended.
		 */
		println:function(line) {
		},

		/*
		 * Writes a string unmodified.
		 */
		print:function(string) {
		},

		/*
		 * Writes a string after parsing ^A codes and appends a "\r\n".
		 */
		aprintln:function(line) {
		},

		/*
		 * Writes a string after parsing ^A codes.
		 */
		aprint:function(string) {
		},

		/*
		 * Waits up to timeout millisections and returns true if a key
		 * is pressed before the timeout.  For ANSI sequences, returns
		 * true when the entire ANSI sequence is available.
		 */
		waitkey:function(timeout) {
		},

		/*
		 * Returns a single *KEY*, ANSI is parsed to a single key.
		 * Returns undefined if there is no key pressed.
		 */
		getkey:function() {
		},

		/*
		 * Returns a single byte... ANSI is not parsed.
		 */
		getbyte:function() {
		},
	},
	connection:{
		type:undefined,
		baud:undefined,
		parity:undefined,
		node:undefined,
		dte:undefined,
		error_correcting:true,
		time:undefined
	},
	user:{
		full_name:undefined,
		location:undefined,
		home_phone:undefined,
		work_phone:undefined,
		// Just a copy of work_phone when using door.sys
		data_phone:undefined,
		pass:undefined,
		level:undefined,
		times_on:undefined,
		last_called:undefined,
		// These need getter/setters
		seconds_remaining:undefined,
		minutes_remaining:undefined,
		conference:[],
		curr_conference:undefined,
		expires:undefined,
		number:undefined,
		default_protocol:undefined,	// Default transfer protocol... X, Y, Z, etc.
		uploads:undefined,
		upload_kb:undefined,
		downloads:undefined,
		download_kb:undefined,
		kb_downloaded_today:undefined,
		max_download_bytes_per_day:undefined,
		birthdate:undefined,
		alias:undefined,
		ansi_supported:undefined,
		time_credits:undefined,
		last_new_file_scan_date:undefined,
		last_call_time:undefined,
		max_daily_files:undefined,
		downloaded_today:undefined,
		comment:undefined,
		doors_opened:undefined,
		messages_left:undefined
	},
	system:{
		main_dir:undefined,
		gen_dir:undefined,
		sysop_name:undefined,
		default_attr:undefined
	},
	misc:{
		event_time:undefined,
		record_locking:undefined
	},

	parse_dropfile:function(path) {
		var f = new File(path);

		if (f.open("r")) {
		
		}
	}
};
