package kijko.dsa

import spock.lang.Specification

class SimpleHashTableTest extends Specification {

    HashTable<Person, PersonContactNumber> t = new SimpleHashTable<>()

    def "insert and search"() {
        given:
        def person = new Person("John Snow")
        def contact = new PersonContactNumber("777 i 7")

        when:
        t.insert(person, contact)

        then:
        t.search(person).get() == contact
    }

    def "insert and search - no duplicates"() {
        given:
        def person = new Person("John Snow")
        def contact1 = new PersonContactNumber("777 i 7")
        def contact2 = new PersonContactNumber("777 i 7 i 7")

        when:
        t.insert(person, contact1)
        t.insert(person, contact2)

        then:
        t.search(person).get() == contact2
    }

    def "insert, search and delete"() {
        given:
        def person1 = new Person("John Snow")
        def contact1 = new PersonContactNumber("777 i 7")

        and:
        def person2 = new Person("Sponge Bob")
        def contact2 = new PersonContactNumber("666")

        when:
        t.insert(person1, contact1)
        t.insert(person2, contact2)

        and:
        t.delete(person1)

        then:
        t.search(person1).isEmpty()
        t.search(person2).get() == contact2
    }
}
