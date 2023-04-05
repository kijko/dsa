package kijko.dsa;

import java.util.Objects;

class Person {
    final String name;

    Person(String name) {
        this.name = name;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person1 = (Person) o;
        return name.equals(person1.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name);
    }
}

class PersonContactNumber {
    final String contactNumber;

    public PersonContactNumber(String contactNumber) {
        this.contactNumber = contactNumber;
    }
}
