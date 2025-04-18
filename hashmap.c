#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "hashmap.h"


typedef struct HashMap HashMap;
int enlarge_called=0;

struct HashMap {
    Pair ** buckets;
    long size; //cantidad de datos/pairs en la tabla
    long capacity; //capacidad de la tabla
    long current; //indice del ultimo dato accedido
};

Pair * createPair( char * key,  void * value) {
    Pair * new = (Pair *)malloc(sizeof(Pair));
    new->key = key;
    new->value = value;
    return new;
}

long hash( char * key, long capacity) {
    unsigned long hash = 0;
     char * ptr;
    for (ptr = key; *ptr != '\0'; ptr++) {
        hash += hash*32 + tolower(*ptr);
    }
    return hash%capacity;
}

int is_equal(void* key1, void* key2){
    if(key1==NULL || key2==NULL) return 0;
    if(strcmp((char*)key1,(char*)key2) == 0) return 1;
    return 0;
}


void insertMap(HashMap * map, char * key, void * value) {
    long pos = hash(key, map->capacity);
    if (map->buckets[pos] == NULL || map->buckets[pos]->key == NULL){
        Pair *nuevo = createPair(key, value);
        map->buckets[pos] = nuevo;
        map->size++;
        return;
    }
    else{
        for(long i = (pos + 1); i < map->capacity; i++){
            if (map->buckets[i] == NULL || map->buckets[i]->key == NULL){
                Pair *nuevo = createPair(key, value);
                map->buckets[i] = nuevo;
                map->size++;
                return;
            }
        }
    }
    for(long i = 0; i < pos; i++){
        if (map->buckets[i] == NULL || map->buckets[i]->key == NULL){
            Pair *nuevo = createPair(key, value);
            map->buckets[i] = nuevo;
            map->size++;
            return;
        }
    }
    return NULL;
}

void enlarge(HashMap * map) {
    enlarge_called = 1; //no borrar (testing purposes)


}


HashMap * createMap(long capacity) {
    HashMap *nuevoMapa = (HashMap *)malloc(sizeof(HashMap));
    if(nuevoMapa == NULL) return NULL;

    nuevoMapa->buckets = (Pair **)malloc(capacity * sizeof(Pair *));
    if(nuevoMapa->buckets == NULL){
        free(nuevoMapa);
        return NULL;
    }

    for(long i = 0; i < capacity; i++){
        nuevoMapa->buckets[i] = NULL;
    }
    nuevoMapa->size = 0;
    nuevoMapa->capacity = capacity;
    nuevoMapa->current = -1;

    return nuevoMapa;
}

void eraseMap(HashMap * map,  char * key) {    


}

Pair * searchMap(HashMap * map,  char * key) {   
    long pos = hash(key, map->capacity);
    if(strcmp(map->buckets[pos]->key, key) == 0){
        Pair *nuevo = createPair(key, map->buckets[pos]->value);
        return nuevo;
    }
    else{
        for (long i = pos + 1; i < map->capacity; i++){
            if(strcmp(map->buckets[i]->key, key) == 0){
                Pair *nuevo = createPair(key, map->buckets[i]->value);
                return nuevo;
            }
            if(map->buckets[i] == NULL) return NULL;
    }
    for (long i = 0; i < pos; i++){
        if(strcmp(map->buckets[i]->key, key) == 0){
            Pair *nuevo = createPair(key, map->buckets[i]->value);
            return nuevo;
        }
        if(map->buckets[i] == NULL) return NULL;
    }

    return NULL;
}

Pair * firstMap(HashMap * map) {

    return NULL;
}

Pair * nextMap(HashMap * map) {

    return NULL;
}
