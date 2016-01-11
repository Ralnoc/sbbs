/*
 * Pass a directory code and get back an array of objects for the files
 * in the specified directory.
 * 
 * Similar to filedir.js.
 */

function FileBase(dir) {
	var f = new File(format("%s%s.ixb", file_area.dir[dir].data_dir, dir));
	var dat = new File(format("%s%s.dat", file_area.dir[dir].data_dir, dir));
	var exb = new File(format("%s%s.exb", file_area.dir[dir].data_dir, dir));
	var record = null;
	var ret = [];

	function FileEntry(idx) {
		var byte;

		function getrec(file, len) {
			var ret=file.read(len);
			ret = ret.replace(/[\x03\r\n].*$/,'');
			return ret;
		}

		// Read from the IXB file
		this.base = f.read(8).replace(/ +$/,'');
		this.ext = f.read(3);
		this.datoffset = f.readBin(2);
		byte = f.readBin(1);
		this.datoffset |= (byte<<16);
		this.uldate = f.readBin(4);
		this.dldate = f.readBin(4);

		// Read from the DAT file
		dat.position = this.datoffset;
		this.credits = parseInt(getrec(dat, 9), 10);
		this.desc = getrec(dat, 58);
		dat.readBin(2);	// Should be \r\n
		this.uploader = getrec(dat, LEN_ALIAS);
		dat.read(5);	// Padding?
		dat.readBin(2);	// Should be \r\n
		this.downloaded = parseInt(getrec(dat, 5), 10);
		dat.readBin(2);	// Should be \r\n
		this.opencount = parseInt(getrec(dat, 3), 10);
		dat.readBin(2);	// Should be \r\n
		this.misc = getrec(dat, 1);
		if (this.misc.length > 0)
			this.misc = ascii(this.misc)-32;
		else
			this.misc = 0;
		this.altpath = parseInt(getrec(dat, 2), 16);

		// Read from the EXB file
		this.extdesc = '';
		if (exb.is_open) {
			if (exb.length > idx*512) {
				exb.position = idx * 512;
				this.extdesc = exb.read(512).replace(/\x00.*$/, '');
			}
		}
	};
	FileEntry.prototype = {
		get name() {
			return this.base+'.'+this.ext;
		}
	};

	if(!f.exists)
		return ret;
	if (!f.open("rb"))
		return ret;

	if(!dat.exists) {
		f.close();
		log(LOG_DEBUG, "readIxb: Invalid code or "+dat.name+" does not exist.");
		return ret;
	}
	if (!dat.open("rb")) {
		log(LOG_DEBUG, "readIxb: Unable to open "+dat.name+".");
		return ret;
	}

	exb.open("rb");

	for(var i = 0; f.position+1<f.length ; i++)
		ret.push(new FileEntry(i));

	f.close();
	dat.close();
	if (exb.is_open)
		exb.close();

	return ret;
}
