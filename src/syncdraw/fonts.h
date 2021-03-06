#ifndef _FONTS_H_
#define _FONTS_H_

#define HeaderSize         12
#define FontRecordSize     25
typedef struct {
	char            FontName[17];
	unsigned long   FilePos;
	unsigned long   Length;
}               FontRecord;

typedef struct {
	char            sign[10];
	unsigned short  NumberofFonts;
}               MysticDrawFontHeader;

typedef struct {
	char            Sign[20];
	char            a[3];
	char            Name[16];
	unsigned char   FontType;
	unsigned char   Spaces;
	short           Nul;
	unsigned short  Chartable[95];
	char            b[20];
}               TheDrawFont;

extern MysticDrawFontHeader Header;
extern FontRecord      FontRec;
extern TheDrawFont     TDFont;
extern unsigned short  SFont;
extern unsigned char   Outline, MaxX, MaxY;
extern unsigned char   Chars[61][25];

void CreateFontFile(void);
void Openfont(int num);
void ReadFonts(unsigned char ch);

#endif
