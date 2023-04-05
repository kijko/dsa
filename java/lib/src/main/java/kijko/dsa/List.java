package kijko.dsa;

import java.util.Optional;

interface List<T> extends Iterable<T> {
    void add(T obj);

    int indexOf(T obj);

    void remove(int index);

    Optional<T> get(int index);

    void remove(T obj);

    boolean isEmpty();
}
