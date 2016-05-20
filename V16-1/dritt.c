#include <stdio.h>
#include <sys/ptrace.h>
#include <stdlib.h>
#include <string.h>
static int lol[] = { 4, 2, 3, 1, 0, 5 };
const char a[] = "dCEhffYmV6FR7RFVfZXJU1ZFVQo=\x00\x00\x00\x00";
const unsigned char b[] = { 97, 116, 103, 114, 111, 117, 89, 86,
				 39, 124, 124, 50, 89, 96, 114, 113, 0 };
static inline void c(void) { if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) { fprintf(stderr, "no trace pls!\n"); exit(EXIT_FAILURE); } }
static inline int d(const char *s1, const char *s2) { int c1, c2; const char *s = s1; const char *t = s2; do { c1 = *s++; c2 = *t++; if (c1 == '\0') return c1 - c2; } while (c1 == c2); return c1 - c2; }
static inline void enc_input(char *input) { for (size_t i = 0; i < sizeof(b) - 1; i++) input[i] ^= 6; }
int main(void) { char buf[128] = { 0 }; c(); setvbuf(stdout, NULL, _IONBF, 0); printf("Password please: "); if (!fgets(buf, sizeof(buf), stdin)) { perror("fgets()"); exit(EXIT_FAILURE); } buf[strcspn(buf, "\r\n")] = '\0'; enc_input(buf); if (d(buf, (char *)b)) { fprintf(stderr, "Wrong :(\n"); exit(EXIT_FAILURE); } for (size_t i = 0; i < 6; i++) { int index = lol[i] * 5; printf("%.5s", &a[index]);	} printf("\n"); return 0; }
