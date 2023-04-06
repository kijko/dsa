package kijko.dsa

import spock.lang.Specification

class BinaryTreeTest extends Specification {

    Tree<Integer> tree = new BinaryTree<>()

    def "insert one element to binary tree"() {
        when:
        tree.insert(5)

        then:
        tree.search(5)
        !tree.search(6)

        and:
        tree.toString() == "[0] (5)"
    }

    def "insert more than one element to binary tree"() {
        when:
        tree.insert(5)
        tree.insert(1)
        tree.insert(4)
        tree.insert(3)

        then:
        tree.search(5)
        tree.search(1)
        tree.search(4)
        tree.search(3)

        and:
        !tree.search(-1)

        and:
        tree.toString() == "[0] (5)\n[1] (5-1) (5-4)\n[2] (1-3)"
    }

    def "delete element from binary tree"() {
        when:
        tree.insert(5)
        tree.insert(1)
        tree.insert(4)
        tree.insert(3)

        and:
        tree.delete(1)

        then:
        tree.search(5)
        !tree.search(1)
        tree.search(4)
        tree.search(3)

        and:
        tree.toString() == "[0] (5)\n[1] (5-3) (5-4)"
    }

    def "binary tree allows duplicates"() {
        when:
        tree.insert(5)
        tree.insert(1)
        tree.insert(1)
        tree.insert(4)
        tree.insert(3)

        and:
        tree.delete(1)

        then:
        tree.search(5)
        tree.search(1)
        tree.search(4)
        tree.search(3)

        and:
        tree.toString() == "[0] (5)\n[1] (5-4) (5-1)\n[2] (4-3)"
    }
}
