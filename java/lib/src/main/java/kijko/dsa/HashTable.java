package kijko.dsa;

import java.util.Optional;

interface HashTable<K, V> {

    void insert(K key, V value);
    void delete(K key);
    Optional<V> search(K key);

}
