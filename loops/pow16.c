#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define A_MAX_LEN 32000
#define BASE 10

typedef struct u_arbitrary {
    unsigned int l_significand;
    char* significand;
} u_arbitrary;

void u_arbitrary_print(u_arbitrary n) {
    bool sig_digit = false;
    
    for (unsigned int i = 0; i < n.l_significand; i++) {
        if (sig_digit) {
            putchar(n.significand[i] + '0');
        } else {
            if (n.significand[i]) {
                sig_digit = true;
                putchar(n.significand[i] + '0');
            }
        }
    }
    if (!sig_digit) {
        putchar('0');
    }
    putchar('\n');
}

static void u_arbitrary_mul(u_arbitrary* n, char m) {
    char carry = 0;
    
    for (int i = (int) n->l_significand - 1; i >= 0; i--) {
        int product = n->significand[i] * m + carry;
        n->significand[i] = product % BASE;
        carry = (char)(product / BASE);
    }
}

int main() {
    int n;
    scanf("%d", &n);
    
    if (n == 0) {
        printf("1\n");
        return 0;
    }
    
    char* mantisse = calloc(A_MAX_LEN, sizeof(char));
    u_arbitrary res = {
        .l_significand = A_MAX_LEN,
        .significand = mantisse
    };
    res.significand[res.l_significand-1] = 1;
    
    int c = n / 3;
    int r = n % 3;
    
    for (int i = 0; i < c; i++) {
        u_arbitrary_mul(&res, 8);
    }
    for (int i = 0; i < r; i++) {
        u_arbitrary_mul(&res, 2);
    }
    
    u_arbitrary_print(res);
    free(mantisse);
    return 0;
}
