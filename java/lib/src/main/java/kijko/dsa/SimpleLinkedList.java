package kijko.dsa;

import java.util.Iterator;
import java.util.Optional;

class SimpleLinkedList<T> implements List<T> {
    private ListNode<T> last = null;
    private int size = 0;

    @Override
    public void add(T obj) {
        if (this.last == null) {
            this.last = new ListNode<T>(0, null, null, obj);
        } else {
            var node = new ListNode<T>(this.last.index + 1, null, this.last, obj);
            this.last.next = node;
            this.last = node;
        }

        size++;
    }

    private static class ListNode<T> {
        private int index;
        private ListNode<T> next;
        private ListNode<T> prev;
        private T value;

        public ListNode(int index, ListNode<T> next, ListNode<T> prev, T value) {
            this.index = index;
            this.next = next;
            this.prev = prev;
            this.value = value;
        }
    }

    @Override
    public int indexOf(T obj) {
        ListNode<T> currentNode = this.last;

        while (currentNode != null) {
            if (currentNode.value.equals(obj)) {
                return currentNode.index;
            }
            currentNode = currentNode.prev;
        }

        return -1;
    }

    @Override
    public void remove(int index) {
        if (index < 0) throw new RuntimeException("Index cannot be negative");

        ListNode<T> currNode = this.last;

        while (currNode != null) {
            if (currNode.index == index) {
                var prev = currNode.prev;
                var next = currNode.next;

                if (prev == null && next == null) { // only one element
                    this.last = null;
                } else if (prev == null) { // first element
                    currNode.next = null;
                    next.prev = null;
                } else if (next == null) { // last element
                    currNode.prev = null;
                    prev.next = null;
                    this.last = prev;
                } else { // between elements
                    prev.next = next;
                    next.prev = prev;
                    currNode.prev = null;
                    currNode.next = null;
                }

                size--;

                break;
            }
            currNode = currNode.prev;
        }

        currNode = this.last;
        int currIndex = size - 1;
        while (currNode != null) {
            if (currIndex < 0) throw new RuntimeException("failed to reindex the list");
            currNode.index = currIndex;

            currNode = currNode.prev;
            currIndex--;
        }
    }

    @Override
    public Optional<T> get(int index) {
        var currNode = this.last;

        while (currNode != null) {
            if (currNode.index == index) {
                return Optional.of(currNode.value);
            }

            currNode = currNode.prev;
        }

        return Optional.empty();
    }

    @Override
    public void remove(T obj) {
        int index = indexOf(obj);

        if (index > -1) {
            remove(index);
        }
    }

    @Override
    public boolean isEmpty() {
        return this.size == 0;
    }

    @Override
    public Iterator<T> iterator() {
        return new SimpleLinkedListIterator<>(this);
    }

    static class SimpleLinkedListIterator<T> implements Iterator<T> {
        private SimpleLinkedList<T> list;
        private int currentIndex = -1;

        SimpleLinkedListIterator(SimpleLinkedList<T> list) {
            this.list = list;
        }

        @Override
        public boolean hasNext() {
            if (list.isEmpty()) {
                return false;
            }

            int nextIndex = currentIndex + 1;

            return this.list.get(nextIndex).isPresent();
        }

        @Override
        public T next() {
            int nextIndex = currentIndex + 1;
            var elem = this.list.get(nextIndex).orElseThrow(() -> new RuntimeException("iterator is trying to get next element but there is none"));
            currentIndex = nextIndex;

            return elem;
        }
    }
}
