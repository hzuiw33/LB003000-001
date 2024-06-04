// test.c

#include <stdio.h>
#include <stdbool.h>
#include "code.h"

int main() {
    // 일반 사용자 생성
    int user_id = create_user_account(false, "pwned");
    if (user_id == INVALID_USER_ID) {
        fprintf(stderr, "사용자 계정 생성 실패\n");
        return 1;
    }

    printf("Before:\n");
    printf("[*] username : %s\n", username(user_id));
    printf("[*] isAdmin : %d\n", is_admin(user_id));

    // 권한 상승 시도
    update_username(user_id, "A"); // 버퍼 오버플로우 시도

    printf("After:\n");
    printf("[*] username : %s\n", username(user_id));
    printf("[*] isAdmin : %d\n", is_admin(user_id));

    return 0;
}
