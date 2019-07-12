
#ifndef __TYPE_H__
#define __TYPE_H__

#ifndef NULL
#define NULL    ((void *)0)
#endif

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef unsigned int   BOOL;

typedef __packed struct keyboard_report_t
{
    BYTE modifier;
    BYTE reserved;
    BYTE keycode[6];
} keyboard_st;

#endif  /* __TYPE_H__ */
