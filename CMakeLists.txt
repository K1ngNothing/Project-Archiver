add_catch(test_archiver
        archive.cpp
        archive.h
        archive_tests.cpp

        dearchive.cpp
        dearchive.h
        dearchive_tests.cpp

        heap.cpp
        heap.h
        heap_tests.cpp

        huffman_algorithm.cpp
        huffman_algorithm.h
        huffman_algorithm_tests.cpp

        istream_wrapper.cpp
        istream_wrapper.h
        istream_wrapper_tests.cpp

        ostream_wrapper.cpp
        ostream_wrapper.h
        ostream_wrapper_tests.cpp

        trie.cpp
        trie.h
        trie_tests.cpp

        vertex.cpp
        vertex.h
        vertex_tests.cpp
        )

add_executable(archiver
        main.cpp

        archive.cpp
        archive.h

        dearchive.cpp
        dearchive.h

        heap.cpp
        heap.h

        huffman_algorithm.cpp
        huffman_algorithm.h

        istream_wrapper.cpp
        istream_wrapper.h

        ostream_wrapper.cpp
        ostream_wrapper.h

        trie.cpp
        trie.h

        vertex.cpp
        vertex.h
        )