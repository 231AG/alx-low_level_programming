#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct shash_node_s {
    char *key;
    char *value;
    struct shash_node_s *next;
    struct shash_node_s *sprev;
    struct shash_node_s *snext;
};

struct shash_table_s {
    unsigned long int size;
    shash_node_t **array;
    shash_node_t *shead;
    shash_node_t *stail;
};

shash_table_t *shash_table_create(unsigned long int size) {
    shash_table_t *ht = malloc(sizeof(shash_table_t));
    if (ht == NULL) {
        return NULL;
    }
    ht->size = size;
    ht->array = malloc(sizeof(shash_node_t *) * size);
    if (ht->array == NULL) {
        free(ht);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        ht->array[i] = NULL;
    }
    ht->shead = NULL;
    ht->stail = NULL;
    return ht;
}

int shash_table_set(shash_table_t *ht, const char *key, const char *value) {
    unsigned long int hash = 0;
    for (int i = 0; key[i]; i++) {
        hash += key[i];
    }
    hash %= ht->size;

    shash_node_t *node = ht->array[hash];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            // Key already exists, update the value
            node->value = value;
            return 1;
        }
        node = node->next;
    }

    // Key does not exist, create a new node
    node = malloc(sizeof(shash_node_t));
    if (node == NULL) {
        return 0;
    }
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = ht->array[hash];
    ht->array[hash] = node;

    // Insert the new node in the sorted linked list
    if (ht->shead == NULL) {
        ht->shead = node;
        ht->stail = node;
    } else {
        shash_node_t *current = ht->shead;
        while (current->snext != NULL && strcmp(current->snext->key, key) < 0) {
            current = current->snext;
        }
        node->sprev = current;
        node->snext = current->snext;
        if (current->snext != NULL) {
            current->snext->sprev = node;
        }
        current->snext = node;
        if (node->snext == NULL) {
            ht->stail = node;
        }
    }
    return 1;
}

char *shash_table_get(const shash_table_t *ht, const char *key) {
    unsigned long int hash = 0;
    for (int i = 0; key[i]; i++) {
        hash += key[i];
    }
    hash %= ht->size;

    shash_node_t *node = ht->array[hash];
    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return NULL;
}

void shash_table_print(const shash_table_t *ht) {
    shash_node_t *node = ht->shead;
    while (node != NULL) {
        printf("Key: %s, Value: %s\n", node->key, node->value);

