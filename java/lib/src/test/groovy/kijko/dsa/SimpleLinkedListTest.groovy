package kijko.dsa

import spock.lang.Specification

class SimpleLinkedListTest extends Specification {
    List<Person> list = new SimpleLinkedList<>()

    def "insert element"() {
        given:
        def p1 = new Person("John Snow")
        def p2 = new Person("Jaroslaw Kaczynski")

        when:
        list.add(p1)
        list.add(p2)

        then:
        list.indexOf(p1) == 0
        list.indexOf(p2) == 1
        list.get(0).get() == p1
        list.get(1).get() == p2
    }

    def "get index of element"() {
        given:
        def p1 = new Person("John Snow")
        def p2 = new Person("Jaroslaw Kaczynski")

        and:
        list.add(p1)
        list.add(p2)

        when:
        def index = list.indexOf(p2)

        then:
        index == 1
    }

    def "remove element by index - first element"() {
        given:
        def p1 = new Person("John Snow")
        def p2 = new Person("Jaroslaw Kaczynski")

        and:
        list.add(p1)
        list.add(p2)

        when:
        list.remove(0)

        then:
        list.indexOf(p1) == -1
        list.get(0).get() == p2
        list.size() == 1
    }

}
