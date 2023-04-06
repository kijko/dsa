package kijko.dsa;

import java.util.Optional;
import java.util.function.BiConsumer;
import java.util.function.Predicate;

/**
 * Useless binary tree. It's not binary search tree
 */
class BinaryTree<T> implements Tree<T> {
    private Node<T> root;

    @Override
    public boolean search(T elem) {
        if (this.root == null) {
            return false;
        }

        return findFirstNode((Node<T> node) -> node.value.equals(elem)).isPresent();
    }

    @Override
    public void insert(T elem) {
        if (this.root == null) {
            this.root = new Node<>(elem);
            return;
        }

        Optional<Node<T>> parent = findFirstNode(Node::canAdoptChild);

        parent.ifPresent(node -> node.adopt(elem));
    }

    private Optional<Node<T>> findFirstNode(Predicate<Node<T>> predicate) {
        if (this.root == null) {
            return Optional.empty();
        }

        int level = 0;
        List<Node<T>> levelNodes;
        do {
            levelNodes = getNodesAtLevel(level);

            for (Node<T> node : levelNodes) {
                if (predicate.test(node)) {
                    return Optional.of(node);
                }
            }

            level++;
        } while (!levelNodes.isEmpty());

        return Optional.empty();
    }

    private void forEach(BiConsumer<Integer, Node<T>> consumer) {
        if (this.root == null) {
            return;
        }

        int level = 0;
        List<Node<T>> levelNodes;
        do {
            levelNodes = getNodesAtLevel(level);

            for (Node<T> node : levelNodes) {
                consumer.accept(level, node);
            }

            level++;
        } while (!levelNodes.isEmpty());
    }

    private List<Node<T>> getNodesAtLevel(int level) { // >= 0
        int currentLevel = 0;
        List<Node<T>> currentLevelNodes = new SimpleLinkedList<>();
        currentLevelNodes.add(this.root);

        while (currentLevel < level) {
            currentLevelNodes = getNextLevelNodes(currentLevelNodes);
            currentLevel++;
        }

        return currentLevelNodes;
    }

    private List<Node<T>> getNextLevelNodes(List<Node<T>> currentLevelNodes) {
        if (currentLevelNodes.isEmpty()) {
            return new SimpleLinkedList<>();
        } else {
            List<Node<T>> nextLevelNodes = new SimpleLinkedList<>();

            for (Node<T> node : currentLevelNodes) {
                for (Node<T> child : node.children.asList()) {
                    nextLevelNodes.add(child);
                }
            }

            return nextLevelNodes;
        }
    }

    @Override
    public void delete(T elem) {
        findFirstNode(node -> node.value.equals(elem)).ifPresent(node -> {
            node.parent.abort(node);

            List<Node<T>> allDescendants = new SimpleLinkedList<>();
            getAllDescendants(allDescendants, node);

            for (Node<T> descendant : allDescendants) {
                insert(descendant.value);
            }
        });
    }

    private void getAllDescendants(List<Node<T>> current, Node<T> node) {
        if (node.hasAnyChild()) {
            for (Node<T> child : node.children.asList()) {
                current.add(child);
                getAllDescendants(current, child);
            }
        }
    }

    @Override
    public String toString() {
        List<List<Node<T>>> levels = new SimpleLinkedList<>();

        forEach((level, node) -> {
            boolean listExists = levels.get(level).isPresent();

            List<Node<T>> levelList;
            if (listExists) {
                levelList = levels.get(level).get();
            } else {
                levelList = new SimpleLinkedList<>();
                levels.add(levelList);
            }

            levelList.add(node);
        });

        StringBuilder b = new StringBuilder();
        for (int lvl = 0; lvl < levels.size(); lvl++) {
            b.append(String.format("[%d] ", lvl));

            var level = levels.get(lvl).get();
            int levelSize = level.size();
            for (int i = 0; i < levelSize; i++) {
                b.append(level.get(i).get());
                if (i < (levelSize - 1)) {
                    b.append(" ");
                }
            }

            if (lvl < levels.size() - 1) {
                b.append("\n");
            }
        }

        return b.toString();
    }

    private static class Node<T> {
        private T value;
        private Node<T> parent;
        private Children<T> children;

        private Node(T value) {
            this.value = value;
            this.parent = null;
            this.children = new Children<>(null, null);
        }

        private Node(T value, Node<T> parent) {
            this.value = value;
            this.parent = parent;
            this.children = new Children<>(null, null);
        }

        private void adopt(T value) {
            Node<T> child = new Node<>(value, this);

            if (this.children.left == null) {
                this.children.left = child;
            } else if (this.children.right == null) {
                this.children.right = child;
            } else {
                throw new RuntimeException("Node cannot adopt child anymore");
            }
        }

        private boolean hasAnyChild() {
            return this.children.left != null || this.children.right != null;
        }

        private boolean canAdoptChild() {
            return this.children.hasPlace();
        }

        @Override
        public String toString() {
            return parent != null
                    ? String.format("(%s-%s)", parent.value.toString(), this.value.toString())
                    : String.format("(%s)", this.value.toString());
        }

        public void abort(Node<T> child) {
            if (this.children.left == child) {
                this.children.left = null;
            } else if (this.children.right == child) {
                this.children.right = null;
            }

            child.parent = null;
        }

        private static class Children<T> {
            private Node<T> left;
            private Node<T> right;

            public Children(Node<T> left, Node<T> right) {
                this.left = left;
                this.right = right;
            }

            List<Node<T>> asList() {
                List<Node<T>> children = new SimpleLinkedList<>();

                if (left != null) children.add(left);
                if (right != null) children.add(right);

                return children;
            }

            boolean hasPlace() {
                return left == null || right == null;
            }
        }
    }

}
