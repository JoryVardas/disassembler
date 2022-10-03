#ifndef TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_CARTESIAN_PRODUCT_VIEW_HPP
#define TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_CARTESIAN_PRODUCT_VIEW_HPP

#include <iterator>
#include <stdexcept>
#include <string>
#include <tuple>

namespace Testing::Helpers {

namespace Detail {
template <typename Container> class CartesianProductView_Detail_Cursor {
    using ContainerIterator = decltype(std::cbegin(std::declval<Container>()));
    using ContainerDataType = decltype(*std::cbegin(std::declval<Container>()));
    ContainerIterator container_start;
    ContainerIterator container_end;
    ContainerIterator container_cursor;

  public:
    CartesianProductView_Detail_Cursor(Container& container)
        : container_start(std::begin(container)),
          container_end(std::end(container)),
          container_cursor(std::begin(container)) {}

    bool atEnd() const { return container_cursor == container_end; }
    void next() {
        using namespace std::string_literals;
        if (atEnd())
            throw std::logic_error(
                "Attempt to increment view when the cursor is at the end of the container."s);
        ++container_cursor;
    }
    ContainerDataType get() const {
        using namespace std::string_literals;
        if (atEnd()) {
            throw std::out_of_range(
                "Attempt to get the value of container being viewed "
                "but cursor is at the end of the container."s);
        }
        return *container_cursor;
    }
    void reset() { container_cursor = container_start; }
    void makeEnd() { container_cursor = container_end; }

    bool operator==(const CartesianProductView_Detail_Cursor& cursor) const {
        using namespace std::string_literals;
        if (container_start != cursor.container_start ||
            container_end != cursor.container_end)
            throw std::logic_error(
                "Attempt to compare iterators which don't view the same container."s);
        return container_cursor == cursor.container_cursor;
    }

    CartesianProductView_Detail_Cursor() = delete;
    virtual ~CartesianProductView_Detail_Cursor() = default;
    CartesianProductView_Detail_Cursor(
        const CartesianProductView_Detail_Cursor&) = default;
    CartesianProductView_Detail_Cursor(CartesianProductView_Detail_Cursor&&) =
        default;
    CartesianProductView_Detail_Cursor&
    operator=(const CartesianProductView_Detail_Cursor&) = default;
    CartesianProductView_Detail_Cursor&
    operator=(CartesianProductView_Detail_Cursor&&) = default;
};

template <typename... Containers> class CartesianProductView_Detail {};
template <typename Container> class CartesianProductView_Detail<Container> {
    using Cursor = CartesianProductView_Detail_Cursor<Container>;
    Cursor cursor;

  public:
    CartesianProductView_Detail(Container& container) : cursor(container) {}

    bool atEnd() const { return cursor.atEnd(); }
    auto get() const { return std::make_tuple(cursor.get()); }
    void next() { cursor.next(); }
    void reset() { cursor.reset(); }
    void makeEnd() { cursor.makeEnd(); }
    const Cursor& viewCursor() const { return cursor; }

    CartesianProductView_Detail() = delete;
    virtual ~CartesianProductView_Detail() = default;
    CartesianProductView_Detail(const CartesianProductView_Detail&) = default;
    CartesianProductView_Detail(CartesianProductView_Detail&&) = default;
    CartesianProductView_Detail&
    operator=(const CartesianProductView_Detail&) = default;
    CartesianProductView_Detail&
    operator=(CartesianProductView_Detail&&) = default;
};
template <typename Container, typename... Containers>
class CartesianProductView_Detail<Container, Containers...>
    : private CartesianProductView_Detail<Containers...> {
    using Cursor = CartesianProductView_Detail_Cursor<Container>;
    using Base = CartesianProductView_Detail<Containers...>;
    Cursor cursor;

  public:
    CartesianProductView_Detail(Container& container, Containers&... containers)
        : cursor(container), Base(containers...) {}

    bool atEnd() const {
        // If our cursor is at its end then we have gone through every
        // combination included us.
        return cursor.atEnd();
    }
    auto get() const {
        return std::tuple_cat(std::make_tuple(cursor.get()), Base::get());
    }
    void next() {
        Base::next();
        if (Base::atEnd()) {
            Base::reset();
            cursor.next();
        }
    }
    void reset() {
        cursor.reset();
        Base::reset();
    }
    void makeEnd() { cursor.makeEnd(); }
    const Cursor& viewCursor() const { return cursor; }

    CartesianProductView_Detail() = delete;
    virtual ~CartesianProductView_Detail() = default;
    CartesianProductView_Detail(const CartesianProductView_Detail&) = default;
    CartesianProductView_Detail(CartesianProductView_Detail&&) = default;
    CartesianProductView_Detail&
    operator=(const CartesianProductView_Detail&) = default;
    CartesianProductView_Detail&
    operator=(CartesianProductView_Detail&&) = default;
};

} // namespace Detail

// CartesianProductView is conceptually a view but does not meet the
// requirements for the ranges::view api and should not be confused as such.
template <typename... Containers> class CartesianProductView {
    using Cursor = Detail::CartesianProductView_Detail<Containers...>;
    Cursor cursorStart;
    Cursor cursorEnd;

  private:
    // Iterator can not be considered a input_iterator since we do not have a
    // difference type. It would be possible to define a difference type but
    // would add complexity for a feature which isn't needed at this time.
    class Iterator : private Cursor {
      public:
        Iterator() = delete;
        Iterator(Cursor& cursor) : Cursor(cursor) {}
        Iterator(const Iterator&) = default;
        Iterator(Iterator&&) = default;
        Iterator& operator=(const Iterator&) = default;
        Iterator& operator=(Iterator&&) = default;

        bool operator==(const Iterator& iter) const {
            return this->viewCursor() == iter.viewCursor();
        }
        Iterator& operator++() {
            Cursor::next();
            return *this;
        }
        Iterator operator++(int) {
            Iterator ret = *this;
            Cursor::next();
            return ret;
        }
        auto operator*() { return Cursor::get(); };
    };

  public:
    CartesianProductView(Containers&... containers)
        : cursorStart(containers...), cursorEnd(containers...) {
        cursorEnd.makeEnd();
    }

    CartesianProductView() = delete;
    ~CartesianProductView() = default;
    explicit CartesianProductView(const CartesianProductView&) = default;
    CartesianProductView(CartesianProductView&&) = default;
    CartesianProductView& operator=(const CartesianProductView&) = default;
    CartesianProductView& operator=(CartesianProductView&&) = default;

    Iterator begin() { return Iterator(cursorStart); }
    Iterator end() { return Iterator(cursorEnd); }
};

} // namespace Testing::Helpers

#endif // TEST_SINGLE_INSTRUCTION_TESTS_HELPERS_CARTESIAN_PRODUCT_VIEW_HPP
