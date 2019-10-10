# Working with detached state

## The identity of detached state instances

[Check the unit tests covering this topic.]()

```java
// First transaction
tx.begin();
em = JPA.createEntityManager();

Item a = em.find(Item.class, ITEM_ID);
Item b = em.find(Item.class, ITEM_ID);

assertTrue(a == b);
assertTrue(a.equals(b));
assertEquals(a.getId(), b.getId());

tx.commit();
em.close();

// Second transaction
tx.begin();
em = JPA.createEntityManager();

Item c = em.find(Item.class, ITEM_ID);

assertTrue(a != c);
assertFalse(a.equals(c));
assertEquals(a.getId(), c.getId());

tx.commit();
em.close();
```

Problem with identity:
1. Two consecutive loads within one transaction which refer to the same database row will result in one entity instance.
2. Every load in another transaction will result in another entity instance, even if it will be linked to the same database row.
3. By default, Java provides `Object#equals()` method basing on shallow comparison - using `==` operator.
4. If entity class uses the default methods, it may result in extremely hard to find errors, mainly with hash-based collections.
5. [More facts about `Object#equals()` and `Object#hashCode()` methods, check this.](../../java/basics/equals_hashcode.md)

Solution:
* Whenever you work with instances in detached state and you test them for equality (usually in hash-based collections), you need to supply your own implementation of the `equals()` and `hashCode()` methods for your mapped entity class.
* **When you override `equals()`, you always need to also override `hashCode()` so the two methods are consistent.**

## Implementing equality methods 

Problems with creating an `equals()` methods basing on id:
* Identifier values are assigned by Hibernate when instance becomes persistent.
* If the instance is already in `Set`, the hash value change would break the collection.

Introcution of a notion of a **business key** (in contrast with **natural primary key** and **surrogate key**):
* This is a property of a combination of properties that is unique for each instance with the same database identity.
* Unlike **natural primary key**, the business key may change, as long as it changes rarely.
* The **business key** is what the user thinks of as uniquely identifying a particular record.
* The **surrogate key** is what the application and database system rely on.

```java
@Entity
@Table(name = "USERS",
  uniqueConstraints = @UniqueConstraint(columnNames = "USERNAME"))
public class User {

  @Override
  public boolean equals(Object other) {
    if (this == other) return true;
    if (other == null) return false;
    if (!(other instanceof User)) return false; // use instanceof

    User that = (User) other;
    return this.getUsername().equals(that.getUsername()); // use getters
  }

@Override
  public int hashCode() {
    return getUsername().hashCode();
  }

  // ...
}
```

Rules:
* Access the `other` reference via getter methods. This is important because the reference passed as `other` could be a Hibernate proxy. You cannot access the `username` field of a `User` proxy directly.
* Check the type of the `other` reference with `instanceof`, not by comparing values of `getClass()`. The `other` reference may be a proxy.

Overall ideas for the implementation:
* Think of how users tell the difference between one element and another.
* Every immutable is probably a good candidate for the business key. Mutable attributes may be good too, provided they are updated rarely or that you can control the case when they're updated.
* Every attribute that has a `UNIQUE` database constraint is a good candidate for the business key.
* Any date or time-based attributem such as the creation timestamp of the record is usually a good component of a business key. Pay attention to the accuracy of `System.currentTimeMilis()` which is JVM-specific.
* You may use the database identifier of an associated entity instance. This is applicable in cases in which the entity is completely dependent on another and requires an already-persistent object in construction.
