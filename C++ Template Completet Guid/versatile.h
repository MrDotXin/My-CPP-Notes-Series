#ifndef VERSATILE_H_
#include <type_traits>
#include <concepts>

namespace TCG {

#if __cplusplus >= 201103L

namespace __helper {

    struct init {
        template<typename T>
        operator T();
    };

};

#if __cplusplus >= 202002L

namespace __detail {

    template<bool is_constructible, typename TS, typename...init_list>
    struct size_s_impl { static constexpr int value = sizeof...(init_list) - 2; };
    template<typename TS, typename...init_list>
    struct size_s_impl<true, TS, init_list...> {
        static constexpr int value = size_s_impl< requires { TS { init_list{}... }; }, TS, init_list..., __helper::init>::value;
    };
}

// Get the number of data in aggregate class TS.
template<typename TS>
    requires std::is_aggregate_v<TS>
struct size_s { static constexpr int value = __detail::size_s_impl< requires { TS{}; }, TS>::value; };

template<typename TS>
inline constexpr int size_s_v = size_s<TS>::value;  

#endif  // c++20 required

// Index sequence from given start index to the end index.
#if __cplusplus >= 201402L

template<std::size_t...N>
struct range_index_sequence 
{ 
    static constexpr std::size_t size() noexcept { return sizeof...(N); }
};

namespace __detail {

    template<std::size_t offset, std::size_t...N>
    constexpr decltype(auto) add_offset_to_index_sequence(std::index_sequence<N...>)
    { return range_index_sequence<(N + offset)...>{}; }

    template<std::size_t start_index, std::size_t end_index>
    struct make_range_index_sequence_helper
    { 
        static_assert((start_index <= end_index), "Error in <versatile.h> line 40 : Invalid index range.");
        using sequence = decltype(add_offset_to_index_sequence<start_index>(std::make_index_sequence<end_index - start_index + 1>{})); 
    };

}

// Generate index sequence from start index to end index.
template<std::size_t start_index, std::size_t end_index>    
using make_range_index_sequence = typename __detail::make_range_index_sequence_helper<start_index, end_index>::sequence; 

#endif  // c++14 required

#endif // c++11 required;
};


#endif