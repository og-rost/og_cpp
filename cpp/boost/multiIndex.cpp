/*

STL containers are designed around the concept that each container controls its own collection of elements,
giving access to them in a manner specified by the container's type: so, an std::set maintains the elements ordered by a specified sorting criterion,
std::list allows for free positioning of elements along a linear sequence, and so on.

Sometimes, the necessity arises of having different access interfaces to the same underlying collection:
for instance, some data might need to be sorted according to more than one comparison predicate,
or a bidirectional list might benefit from a supplemental logarithmic lookup interface.

In these situations, programmers typically resort to manual compositions of different containers, a solution that generally involves a fair amount
of code devoted to preserve the synchronization of the different parts of the composition.

Boost.MultiIndex allows for the specification of multi_index_containers comprised of one or more indices with
different interfaces to the same collection of elements.
The resulting constructs are conceptually cleaner than manual compositions, and often perform much better.

An important design decision has been taken that the indices of a given multi_index_container instantiation be specified at compile time:
this gives ample room for static type checking and code optimization.

Boost.MultiIndex takes inspiration from basic concepts of indexing arising in the theory of relational databases,
though it is not intended to provide a full-fledged relational database framework.

multi_index_container integrates seamlessly into the STL container/algorithm design, and features some extra capabilities regarding
lookup operations and element updating which are useful extensions even for single-indexed containers.

Boost.MultiIndex allows you to create containers with multiple indices, enabling efficient and flexible access to the data stored within them.
In simple terms, it provides a convenient way to organize and access data in different ways within a single container.

Example. Suppose you have a collection of books, and you want to store and retrieve them based on different criteria, such as their titles, authors,
and publication years. With Boost.MultiIndex, you can create a container that allows you to access the books using any of these criteria.

*/

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

#include <iostream>

struct Book {
    std::string title;
    std::string author;
    int publicationYear;
};

using namespace boost::multi_index;

typedef multi_index_container<
    Book,
    indexed_by<
        ordered_unique<member<Book, std::string, &Book::title>>,
        ordered_non_unique<member<Book, std::string, &Book::author>>,
        ordered_non_unique<member<Book, int, &Book::publicationYear>>
    >
> BookContainer;

/*

The multi_index_container template class is used to define the container.
It takes two template parameters: the type of the objects to store (in this case, Book),
and the indexed_by class, which specifies the indices we want to create for the container.

Inside the indexed_by class, we define the indices using the ordered_unique and ordered_non_unique classes.
Each index requires a tag type and a member type. The tag type is used to differentiate between different indices,
and the member type specifies the member variable of the Book structure to index on.

In our example, we define three indices: ordered_unique on the title member, and ordered_non_unique on the author and publicationYear members.
The ordered_unique index ensures that no two books can have the same title, while the ordered_non_unique indices allow duplicate values.

*/

int main() {

    BookContainer books;

    books.insert({"The Great Gatsby", "F. Scott Fitzgerald", 1925});
    books.insert({"To Kill a Mockingbird", "Harper Lee", 1960});
    books.insert({"1984", "George Orwell", 1949});

    // Accessing books by title
    auto& titleIndex = books.get<0>();  // Index 0 corresponds to the title index

    auto it = titleIndex.find("1984");
    if (it != titleIndex.end()) {
        const Book& book = *it;
        std::cout << book.title << std::endl;
    }

    // Accessing books by author
    auto& authorIndex = books.get<1>();  // Index 1 corresponds to the author index

    auto range = authorIndex.equal_range("Harper Lee");
    for (auto it = range.first; it != range.second; ++it) {
        const Book& book = *it;
        std::cout << book.title << std::endl;
    }

    // Accessing books by publication year
    auto& yearIndex = books.get<2>();  // Index 2 corresponds to the publication year index

    auto lower = yearIndex.lower_bound(1930);
    auto upper = yearIndex.upper_bound(1960);
    for (auto it = lower; it != upper; ++it) {
        const Book& book = *it;
        std::cout << book.title << std::endl;
    }

    yearIndex = books.get<2>();  // Index 2 corresponds to the publication year index

    auto year = yearIndex.equal_range(1925);
    for (auto it = year.first; it != year.second; ++it) {
        const Book& book = *it;
        std::cout << book.title << std::endl;
    }

    return 0;
}

/*

In the above code, we use the get function to obtain a reference to a specific index.
We can then use various functions like find, equal_range, lower_bound, and upper_bound
to search or iterate over the books based on the selected index.

The key advantage of Boost.MultiIndex is that it provides efficient access to the data without the need for duplicating or restructuring the container.
It allows you to have different views of the same data, making it easier to implement complex data structures and perform efficient queries.

*/


/*

ordered_unique: This index type creates a unique, sorted index based on the specified key.
                It ensures that no two elements in the container have the same key value.
                The elements are stored in a sorted order, allowing efficient search operations using binary search algorithms.

ordered_non_unique: Similar to the ordered_unique index, this index type also creates a sorted index based on the specified key.
                    However, it allows duplicate key values in the container. The elements are still stored in a sorted order,
                    enabling efficient range-based searches and ordered iteration.

hashed_unique: This index type creates a unique index based on the specified key using a hash function.
               It provides fast access to elements by hashing the key values, resulting in constant-time complexity for insertions, deletions, and searches.
               However, it does not maintain any specific order of elements.

hashed_non_unique: Like the hashed_unique index, this index type uses a hash function to create an index based on the specified key.
                   It allows duplicate key values in the container and provides constant-time complexity for insertions, deletions, and searches.
                   Again, no specific order of elements is maintained.

random_access: This index type provides random access to elements using zero-based indices.
               It allows efficient element retrieval by index, making it useful for scenarios where the position of an element matters,
               such as maintaining a specific order or implementing stack-like behavior.

sequenced: The sequenced index type maintains the order in which elements are inserted into the container.
           It allows efficient insertion at the end and beginning, as well as bidirectional iteration.
           It is suitable for scenarios where maintaining the insertion order is crucial.

*/