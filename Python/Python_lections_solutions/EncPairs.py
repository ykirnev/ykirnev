import sys
word = "Зимбабве"
codes = ["KOI8-R", "CP1251", "MACCYRILLIC", "CP866", "ISO-8859-5", "CP855"]
s = sys.stdin.buffer.read()
for i in codes:
    try:
        dec_t = s.decode(i)
        for e in codes:
            for d in codes:
                try:
                    txt = dec_t.encode(d).decode(e)
                    if word in txt:
                        print(txt)
                        sys.exit(0)
                except (UnicodeDecodeError, UnicodeEncodeError):
                    pass
    except UnicodeDecodeError:
        pass

