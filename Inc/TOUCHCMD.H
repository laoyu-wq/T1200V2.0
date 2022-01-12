#ifndef __TOUCHCMD_H__
#define __TOUCHCMD_H__

int touch(void);
unsigned char ascii(int valuebuf);
int datasame(int kk,unsigned char *str);
void receive_chartfill(void);
void test(void);
#endif
