package kijko.dsa;

import java.util.LinkedList;
import java.util.Objects;
import java.util.Optional;

class SimpleHashTable<K, V> implements HashTable<K, V> {
    private final int bucketCount = 4; // >= 2
    private final LinkedList<Bucket<K, V>> buckets;

    public SimpleHashTable() {
        this.buckets = new LinkedList<>();

        long fullRangeLength = Integer.MAX_VALUE * 2L;
        long bucketRangeLength = fullRangeLength / bucketCount;

        long bucketRangeStart = Integer.MIN_VALUE;
        for (int i = 0; i < bucketCount; i++) {
            long bucketRangeEnd = bucketRangeStart + bucketRangeLength;
            this.buckets.add(new Bucket<>(new BucketRange(bucketRangeStart, bucketRangeEnd), new LinkedList<>()));

            bucketRangeStart = bucketRangeEnd;
        }
    }

    @Override
    public void insert(K key, V value) {
        Bucket<K, V> b = getBucket(key.hashCode());

        b.put(key, value);
    }

    private Bucket<K, V> getBucket(int hashCode) {
        for (Bucket<K, V> bucket : this.buckets) {
            if (bucket.inRange(hashCode)) {
                return bucket;
            }
        }

        throw new RuntimeException("bucket not found - check bucket init logic");
    }

    @Override
    public void delete(K key) {
        getBucket(key.hashCode()).remove(key);
    }

    @Override
    public Optional<V> search(K key) {
        Bucket<K, V> bucket = getBucket(key.hashCode());

        return bucket.get(key).map(BucketEntry::value);
    }

    private record Bucket<K, V>(BucketRange range, LinkedList<BucketEntry<K, V>> elems) { // todo create no duplicates linked list
        private boolean inRange(int num) {
            return num < range.to && num >= range.from;
        }

        private void put(K key, V value) {
            var entry = new BucketEntry<>(key, value);
            int index = elems.indexOf(entry);
            if (index == -1) {
                elems.add(entry);
            } else {
                elems.remove(index);
                elems.add(entry);
            }
        }

        private Optional<BucketEntry<K, V>> get(K key) {
            int index = elems.indexOf(new BucketEntry<K, V>(key, null));

            return index == -1 ? Optional.empty() : Optional.of(elems.get(index));
        }

        private void remove(K key) {
            elems.remove(new BucketEntry<K, V>(key, null));
        }
    }
    private record BucketRange(long from, long to) {} //from - inclusive, to -exclusive
    private record BucketEntry<K, V>(K key, V value) {
        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            BucketEntry<?, ?> that = (BucketEntry<?, ?>) o;
            return key.equals(that.key);
        }

        @Override
        public int hashCode() {
            return Objects.hash(key);
        }
    }
}
