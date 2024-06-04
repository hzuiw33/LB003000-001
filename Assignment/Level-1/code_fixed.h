// code_fixed.h

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_USERNAME_LEN 39
#define SETTINGS_COUNT 10
#define MAX_USERS 100
#define INVALID_USER_ID -1

int userid_next = 0;

typedef struct {
    char username[MAX_USERNAME_LEN + 1];
    bool isAdmin;
    long userid;
    long setting[SETTINGS_COUNT];
} user_account;

user_account *accounts[MAX_USERS];

int create_user_account(bool isAdmin, const char *username) {
    if (userid_next >= MAX_USERS) {
        fprintf(stderr, "사용자 수가 최대치를 초과했습니다.");
        return INVALID_USER_ID;
    }

    if (strlen(username) > MAX_USERNAME_LEN) {
        fprintf(stderr, "사용자 이름이 너무 깁니다.");
        return INVALID_USER_ID;
    }

    user_account *ua = malloc(sizeof(user_account));
    if (ua == NULL) {
        fprintf(stderr, "메모리 할당에 실패했습니다.");
        return INVALID_USER_ID;
    }

    ua->isAdmin = isAdmin;
    ua->userid = userid_next;
    strcpy(ua->username, username);
    memset(&ua->setting, 0, sizeof ua->setting);
    accounts[userid_next] = ua;
    return userid_next++;
}

bool update_username(int user_id, const char *new_name) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL) {
        return false;
    }

    if (strlen(new_name) > MAX_USERNAME_LEN) {
        fprintf(stderr, "새 사용자 이름이 너무 깁니다.");
        return false;
    }

    strncpy(accounts[user_id]->username, new_name, MAX_USERNAME_LEN);
    accounts[user_id]->username[MAX_USERNAME_LEN] = '\0';
    return true;
}

bool update_setting(int user_id, const char *index, const char *value) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL) {
        return false;
    }

    char *endptr;
    long i = strtol(index, &endptr, 10);
    if (*endptr != '\0' || i < 0 || i >= SETTINGS_COUNT) {
        return false;
    }

    long v = strtol(value, &endptr, 10);
    if (*endptr != '\0') {
        return false;
    }

    accounts[user_id]->setting[i] = v;
    return true;
}

bool is_admin(int user_id) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL) {
        fprintf(stderr, "잘못된 사용자 ID입니다.");
        return false;
    }
    return accounts[user_id]->isAdmin;
}

const char* username(int user_id) {
    if (user_id < 0 || user_id >= MAX_USERS || accounts[user_id] == NULL) {
        fprintf(stderr, "잘못된 사용자 ID입니다.");
        return NULL;
    }
    return accounts[user_id]->username;
}
