#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/header.h"

typedef struct {
    char name[50];
    int age;
    char city[50];
} Person;

char *read_file(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Can't open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char *)malloc(length + 1);
    if (!data) {
        perror("Can't allocate memory");
        fclose(file);
        return NULL;
    }

    fread(data, 1, length, file);
    data[length] = '\0';
    fclose(file);
    return data;
}

void write_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "wb");
    if (!file) {
        perror("Can't open file");
        return;
    }

    fwrite(data, sizeof(char), strlen(data), file);
    fclose(file);
}

Person read_json_to_struct(const char *filename) {
    Person person;
    char *file_content = read_file(filename);
    if (!file_content) {
        perror("Error reading file");
        exit(1);
    }

    cJSON *json = cJSON_Parse(file_content);
    if (!json) {
        printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        free(file_content);
        exit(1);
    }

    cJSON *name = cJSON_GetObjectItemCaseSensitive(json, "name");
    cJSON *age = cJSON_GetObjectItemCaseSensitive(json, "age");
    cJSON *city = cJSON_GetObjectItemCaseSensitive(json, "city");

    if (cJSON_IsString(name) && (name->valuestring != NULL)) {
        strcpy(person.name, name->valuestring);
    }
    if (cJSON_IsNumber(age)) {
        person.age = age->valueint;
    }
    if (cJSON_IsString(city) && (city->valuestring != NULL)) {
        strcpy(person.city, city->valuestring);
    }

    cJSON_Delete(json);
    free(file_content);
    return person;
}

void write_struct_to_json(const char *filename, Person person) {
    cJSON *json = cJSON_CreateObject();

    cJSON_AddStringToObject(json, "name", person.name);
    cJSON_AddNumberToObject(json, "age", person.age);
    cJSON_AddStringToObject(json, "city", person.city);

    char *json_string = cJSON_Print(json);
    write_file(filename, json_string);

    cJSON_Delete(json);
    free(json_string);
}

int main() {
    const char *filename = "./data/data.json";
    Person person;

    strcpy(person.name, "Alice");
    person.age = 25;
    strcpy(person.city, "Los Angeles");

    write_struct_to_json(filename, person);

     person = read_json_to_struct(filename);

    printf("Name: %s\n", person.name);
    printf("Age: %d\n", person.age);
    printf("City: %s\n", person.city);

   
    return 0;
}
